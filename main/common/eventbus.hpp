#pragma once
//
// BullsEye EventBus
//
//

#include <string>
#include <vector>
#include <memory>
#include <atomic>
#include <algorithm>
#include <optional>
#include <functional>
#include <type_traits>


#define CERR_EB3001             "EB-3001: The dedicated type _TEvent is not subclass of Event<_TEvent>"


namespace BullsEye {

    // --> essentials

    // Pre-declarations
    template<class _TEvent> class Event;
    template<class _TEvent> class EventListener;
    template<class _TEvent> class EventBus;
    template<class _TEvent> class EventBusGroup;


    typedef unsigned int                EventBusId;


    // Event Instance Interface
    template<class _TEvent>
    class Event {
    public:
        static EventBusGroup<_TEvent>&  GetEventBusGroup() noexcept;
        static std::optional<std::reference_wrapper<EventBus<_TEvent>>>
                                        GetEventBus(EventBusId busId = 0) noexcept;
        static bool                     HasEventBus(EventBusId busId = 0) noexcept;
        static EventBus<_TEvent>&       RequireEventBus(EventBusId busId = 0) noexcept;

        static void                     Register(std::shared_ptr<EventListener<_TEvent>> listener, EventBusId busId = 0) noexcept;

        static int                      Unregister(const std::string& name, EventBusId busId = 0) noexcept;
        static bool                     UnregisterOnce(const std::string& name, EventBusId busId = 0) noexcept;
        static void                     UnregisterAll(EventBusId busId = 0) noexcept;

    public:
        _TEvent&                        Fire(EventBusId busId = 0);
        _TEvent&                        Fire(EventBus<_TEvent>& eventbus);

    private:
        static void                     __STATIC_ASSERT_PLACEHOLDER()
        { static_assert(std::is_base_of_v<Event<_TEvent>, _TEvent>, CERR_EB3001); }
    };

    template<template<typename> typename _TListener, class _TEvent>
    inline void RegisterListener(std::shared_ptr<_TListener<_TEvent>> listener, EventBusId busId = 0) noexcept
    { Event<_TEvent>::Register(listener, busId); }


    // Cancellable Event
    class CancellableEvent {
    private:
        bool    cancelled;

    public:
        CancellableEvent() noexcept;

        void                        SetCancelled(bool cancalled = true) noexcept;
        bool                        IsCancelled() const noexcept;
    };

    // Execptionable Event
    template<class _TException>
    class ExceptionableEvent {
    private:
        bool        exceptioned;
        _TException exception;

    public:
        ExceptionableEvent() noexcept;

        bool                        HasException() const noexcept;
        const _TException&          GetException() const noexcept;

        void                        SetException(_TException exception, bool exceptioned = true) noexcept;
    };


    // Event Handler
    template<class _TEvent>
    class EventListener {
        static_assert(std::is_convertible_v<_TEvent, Event<_TEvent>>, CERR_EB3001);

    private:
        const std::string   name;
        const int           priority;

    public:
        EventListener(const std::string& name, int priority) noexcept;
        virtual ~EventListener() noexcept;

        const std::string&          GetName() const noexcept;
        int                         GetPriority() const noexcept;

        virtual void                OnEvent(_TEvent& event) = 0;
    };


    // Event Bus
    template<class _TEvent>
    class EventBus {
        static_assert(std::is_convertible_v<_TEvent, Event<_TEvent>>, CERR_EB3001);

    private:
        std::vector<std::shared_ptr<EventListener<_TEvent>>> list;

    public:
        using iterator          = std::vector<std::shared_ptr<EventListener<_TEvent>>>::iterator;
        using const_iterator    = std::vector<std::shared_ptr<EventListener<_TEvent>>>::const_iterator;

    private:
        typename std::vector<std::shared_ptr<EventListener<_TEvent>>>::const_iterator _NextPos(int priority) noexcept;

    public:
        EventBus() noexcept;
        ~EventBus() noexcept;

        void                        Register(std::shared_ptr<EventListener<_TEvent>> listener) noexcept;

        int                         Unregister(const std::string& name) noexcept;
        bool                        UnregisterOnce(const std::string& name) noexcept;
        void                        UnregisterAll() noexcept;

        iterator                    begin() noexcept;
        const_iterator              begin() const noexcept;
        iterator                    end() noexcept;
        const_iterator              end() const noexcept;

        _TEvent&                    FireEvent(_TEvent& event);
    };


    // Event Bus Group
    template<class _TEvent>
    class EventBusGroup {
        static_assert(std::is_convertible_v<_TEvent, Event<_TEvent>>, CERR_EB3001);

    private:
        std::vector<EventBus<_TEvent>>  buses;

    public:
        EventBusGroup() noexcept;
        ~EventBusGroup() noexcept;

        EventBusGroup(const EventBusGroup<_TEvent>&) = delete;
        EventBusGroup(EventBusGroup<_TEvent>&&) = delete;

        std::optional<std::reference_wrapper<EventBus<_TEvent>>>
                                    GetEventBus(EventBusId busId = 0) noexcept;

        std::optional<std::reference_wrapper<const EventBus<_TEvent>>>
                                    GetEventBus(EventBusId busId = 0) const noexcept;

        EventBus<_TEvent>&          RequireEventBus(EventBusId busId) noexcept;

        bool                        HasEventBus(EventBusId busId) const noexcept;
        size_t                      GetEventBusCount() const noexcept;
    };


    // Event Bus Dispatchment
    class EventBusDispatchment {
    public:
        static EventBusDispatchment&    Global() noexcept;

    private:
        std::atomic_uint    busIdIncrement;

    public:
        EventBusDispatchment() noexcept;
        ~EventBusDispatchment() noexcept;

        unsigned int                    NextEventBusId() noexcept;
    };



    // --> utilities

    // Event Handler Functional Stub
    template<class _TEvent>
    class EventListenerFunctionalStub : public EventListener<_TEvent> {
    private:
        std::function<void(_TEvent&)>   func;

    public:
        EventListenerFunctionalStub(const std::string& name, int priority, std::function<void(_TEvent&)> func) noexcept;
        virtual ~EventListenerFunctionalStub() noexcept;

        virtual void                OnEvent(_TEvent& event) override;
    };

    template<class _TEvent>
    using FunctionalEventListener   = EventListenerFunctionalStub<_TEvent>;

    template<class _TEvent>
    inline std::shared_ptr<FunctionalEventListener<_TEvent>>
        MakeListener(const std::string& name, int priority, std::function<void(_TEvent&)>&& func) noexcept
    { return std::make_shared<FunctionalEventListener<_TEvent>>(name, priority, func); }

    template<class _TEvent>
    inline std::shared_ptr<FunctionalEventListener<_TEvent>>
        MakeListener(const std::string& name, int priority, void(*func)(_TEvent&)) noexcept
    { return std::make_shared<FunctionalEventListener<_TEvent>>(name, priority, func); }
    
    template<class _TEvent, class _Tx>
    inline std::shared_ptr<FunctionalEventListener<_TEvent>>
        MakeListener(const std::string& name, int priority, void(_Tx::* mfunc)(_TEvent&), _Tx* mthis) noexcept
    { return std::make_shared<FunctionalEventListener<_TEvent>>(name, priority, std::bind(mfunc, mthis, std::placeholders::_1)); }

    template<class _TEvent, class _Tx>
    inline std::shared_ptr<FunctionalEventListener<_TEvent>>
        MakeListener(const std::string& name, int priority, void(_Tx::* mfunc)(_TEvent&) const, const _Tx* mthis) noexcept
    { return std::make_shared<FunctionalEventListener<_TEvent>>(name, priority, std::bind(mfunc, mthis, std::placeholders::_1)); }


    // Event Handler Reference
    template<class _TEvent>
    class EventListenerReference : public EventListener<_TEvent> {
    private:
        EventListener<_TEvent>& ref;

    public:
        EventListenerReference(EventListener<_TEvent>& ref) noexcept;
        virtual ~EventListenerReference() noexcept;

        EventListener<_TEvent>&         GetReference() noexcept;
        const EventListener<_TEvent>&   GetReference() const noexcept;

        virtual void                    OnEvent(_TEvent& event) override;
    };

    template<class _TEvent>
    using RefEventListener          = EventListenerReference<_TEvent>;


    //
    template<class _TEvent>
    inline void UnregisterListener(const std::string& name, EventBusId busId = 0) noexcept
    { Event<_TEvent>::Unregister(name, busId); }

    template<template<typename> typename _TListener, class _TEvent>
    inline void UnregisterListener(const std::string& name, [[maybe_unused]] const _TListener<_TEvent>& listener, EventBusId busId = 0) noexcept
    { Event<_TEvent>::Unregister(name, busId); }

    template<template<typename> typename _TListener, class _TEvent>
    inline void UnregisterListener(const std::string& name, [[maybe_unused]] const std::shared_ptr<_TListener<_TEvent>>& listener, EventBusId busId = 0) noexcept
    { Event<_TEvent>::Unregister(name, busId); }

    template<class _TEvent>
    inline void UnregisterListener(const std::string& name, [[maybe_unused]] std::function<void(_TEvent&)>&& func, EventBusId busId = 0) noexcept
    { Event<_TEvent>::Unregister(name, busId); }

    template<class _TEvent>
    inline void UnregisterListener(const std::string& name, [[maybe_unused]] void(*func)(_TEvent&), EventBusId busId = 0) noexcept
    { Event<_TEvent>::Unregister(name, busId); }

    template<class _TEvent, class _Tx>
    inline void UnregisterListener(const std::string& name, [[maybe_unused]] void(_Tx::* mfunc)(_TEvent&), EventBusId busId = 0) noexcept
    { Event<_TEvent>::Unregister(name, busId); }

    template<class _TEvent, class _Tx>
    inline void UnregisterListener(const std::string& name, [[maybe_unused]] void(_Tx::* mfunc)(_TEvent&) const, EventBusId busId = 0) noexcept
    { Event<_TEvent>::Unregister(name, busId); }
}



// Implementation of: template<class _TEvent> class Event
namespace BullsEye {

    //
    template<class _TEvent>
    inline EventBusGroup<_TEvent>& Event<_TEvent>::GetEventBusGroup() noexcept
    {
        static EventBusGroup<_TEvent> global_eventBusGroup;

        return global_eventBusGroup;
    }

    template<class _TEvent>
    inline std::optional<std::reference_wrapper<EventBus<_TEvent>>> Event<_TEvent>::GetEventBus(EventBusId busId) noexcept
    {
        return GetEventBusGroup().GetEventBus(busId);
    }

    template<class _TEvent>
    inline bool Event<_TEvent>::HasEventBus(EventBusId busId) noexcept
    {
        return GetEventBusGroup().HasEventBus(busId);
    }

    template<class _TEvent>
    inline EventBus<_TEvent>& Event<_TEvent>::RequireEventBus(EventBusId busId) noexcept
    {
        return GetEventBusGroup().RequireEventBus(busId);
    }

    template<class _TEvent>
    inline void Event<_TEvent>::Register(std::shared_ptr<EventListener<_TEvent>> listener, EventBusId busId) noexcept
    {
        RequireEventBus(busId).Register(listener);
    }

    template<class _TEvent>
    inline int Event<_TEvent>::Unregister(const std::string& name, EventBusId busId) noexcept
    {
        if (auto bus_ref = GetEventBus(busId))
            return bus_ref->get().Unregister(name);
        
        return 0;
    }

    template<class _TEvent>
    inline bool Event<_TEvent>::UnregisterOnce(const std::string& name, EventBusId busId) noexcept
    {
        if (auto bus_ref = GetEventBus(busId))
            return bus_ref->get().UnregisterOnce(name);
    }

    template<class _TEvent>
    inline void Event<_TEvent>::UnregisterAll(EventBusId busId) noexcept
    {
        if (auto bus_ref = GetEventBus(busId))
            bus_ref->get().UnregisterAll();
    }

    template<class _TEvent>
    inline _TEvent& Event<_TEvent>::Fire(EventBusId busId)
    {
        if (auto bus_ref = GetEventBus(busId))
            bus_ref->get().FireEvent(static_cast<_TEvent&>(*this));

        return static_cast<_TEvent&>(*this);
    }

    template<class _TEvent>
    inline _TEvent& Event<_TEvent>::Fire(EventBus<_TEvent>& eventbus)
    {
        eventbus.FireEvent(static_cast<_TEvent&>(*this));

        return static_cast<_TEvent&>(*this);
    }
}


// Implementation of: class CancellableEvent
namespace BullsEye {
    //
    // bool    cancelled;
    //

    inline CancellableEvent::CancellableEvent() noexcept
        : cancelled (false)
    { }

    inline void CancellableEvent::SetCancelled(bool cancelled) noexcept
    {
        this->cancelled = cancelled;
    }

    inline bool CancellableEvent::IsCancelled() const noexcept
    {
        return this->cancelled;
    }
}


// Implementation of: template<class _TException> class ExceptionableEvent
namespace BullsEye {
    //
    // bool        exceptioned;
    // _TException exception;
    //

    template<class _TException>
    inline ExceptionableEvent<_TException>::ExceptionableEvent() noexcept
        : exceptioned   (false)
        , exception     ()
    { }

    template<class _TException>
    inline bool ExceptionableEvent<_TException>::HasException() const noexcept
    {
        return this->exceptioned;
    }

    template<class _TException>
    inline void ExceptionableEvent<_TException>::SetException(_TException exception, bool exceptioned) noexcept
    {
        this->exception     = exception;
        this->exceptioned   = exceptioned;
    }

    template<class _TException>
    inline const _TException& ExceptionableEvent<_TException>::GetException() const noexcept
    {
        return this->exception;
    }
}



// Implementation of: template<class _TEvent> class EventListener
namespace BullsEye {
    //
    // const std::string   name;
    // const int           priority;
    //

    template<class _TEvent>
    inline EventListener<_TEvent>::EventListener(const std::string& name, int priority) noexcept
        : name      (name)
        , priority  (priority)
    { }

    template<class _TEvent>
    inline EventListener<_TEvent>::~EventListener() noexcept
    { }

    template<class _TEvent>
    inline const std::string& EventListener<_TEvent>::GetName() const noexcept
    {
        return name;
    }

    template<class _TEvent>
    inline int EventListener<_TEvent>::GetPriority() const noexcept
    {
        return priority;
    }
}


// Implementation of: template<class _TEvent> class EventBus
namespace BullsEye {
    //
    // std::vector<std::shared_ptr<EventListener<_TEvent>>> list;
    //

    template<class _TEvent>
    inline typename std::vector<std::shared_ptr<EventListener<_TEvent>>>::const_iterator EventBus<_TEvent>::_NextPos(int priority) noexcept
    {
        auto iter = list.begin();
        for (; iter != list.end(); iter++)
            if (iter->get()->GetPriority() > priority)
                break;

        return iter;
    }

    template<class _TEvent>
    inline EventBus<_TEvent>::EventBus() noexcept
        : list  ()
    { }

    template<class _TEvent>
    inline EventBus<_TEvent>::~EventBus() noexcept
    { }
    
    template<class _TEvent>
    inline void EventBus<_TEvent>::Register(std::shared_ptr<EventListener<_TEvent>> listener) noexcept
    {
        list.insert(_NextPos(listener->GetPriority()), listener);
    }

    template<class _TEvent>
    inline int EventBus<_TEvent>::Unregister(const std::string& name) noexcept
    {
        auto epos = std::remove_if(list.begin(), list.end(), 
            [name](std::shared_ptr<EventListener<_TEvent>> obj) -> bool {
                return obj->GetName() == name;
            });

        int count = std::distance(epos, list.end());

        list.erase(epos, list.end());

        return count;
    }

    template<class _TEvent>
    inline bool EventBus<_TEvent>::UnregisterOnce(const std::string& name) noexcept
    {
        bool found;

        auto epos = list.begin();
        for (; epos != list.end(); epos++)
            if ((*epos)->GetName() == name)
            {
                found = true;
                break;
            }
        
        if (found)
            list.erase(epos);

        return found;
    }

    template<class _TEvent>
    inline void EventBus<_TEvent>::UnregisterAll() noexcept
    {
        list.clear();
        list.shrink_to_fit();
    }

    template<class _TEvent>
    inline EventBus<_TEvent>::iterator EventBus<_TEvent>::begin() noexcept
    {
        return list.begin();
    }

    template<class _TEvent>
    inline EventBus<_TEvent>::const_iterator EventBus<_TEvent>::begin() const noexcept
    {
        return list.begin();
    }

    template<class _TEvent>
    inline EventBus<_TEvent>::iterator EventBus<_TEvent>::end() noexcept
    {
        return list.end();
    }

    template<class _TEvent>
    inline EventBus<_TEvent>::const_iterator EventBus<_TEvent>::end() const noexcept
    {
        return list.end();
    }
    
    template<class _TEvent>
    inline _TEvent& EventBus<_TEvent>::FireEvent(_TEvent& event)
    {
        for (auto& listener : list)
            listener->OnEvent(event);

        return event;
    }
}


// Implementation of: template<class _TEvent> class EventBusGroup
namespace BullsEye {
    /*
    std::vector<EventBus<_TEvent>>  buses;
    */

    template<class _TEvent>
    inline EventBusGroup<_TEvent>::EventBusGroup() noexcept
        : buses ()
    { 
        buses.emplace_back(); // default eventbus
    }

    template<class _TEvent>
    inline EventBusGroup<_TEvent>::~EventBusGroup() noexcept
    { }

    template<class _TEvent>
    inline std::optional<std::reference_wrapper<EventBus<_TEvent>>> EventBusGroup<_TEvent>::GetEventBus(EventBusId busId) noexcept
    {
        if (HasEventBus(busId))
            return { std::ref(buses[busId]) };
        
        return std::nullopt;
    }

    template<class _TEvent>
    inline std::optional<std::reference_wrapper<const EventBus<_TEvent>>> EventBusGroup<_TEvent>::GetEventBus(EventBusId busId) const noexcept
    {
        if (HasEventBus(busId))
            return { std::cref(buses[busId]) };

        return std::nullopt;
    }

    template<class _TEvent>
    inline EventBus<_TEvent>& EventBusGroup<_TEvent>::RequireEventBus(EventBusId busId) noexcept
    {
        while (!HasEventBus(busId))
            buses.emplace_back();

        return buses[busId];
    }

    template<class _TEvent>
    inline bool EventBusGroup<_TEvent>::HasEventBus(EventBusId busId) const noexcept
    {
        return busId < buses.size();
    }

    template<class _TEvent>
    inline size_t EventBusGroup<_TEvent>::GetEventBusCount() const noexcept
    {
        return buses.size();
    }
}


// Implementation of: class EventBusDispatchment
namespace BullsEye {
    //
    // std::atomic_uint    busIdIncrement;
    //

    inline EventBusDispatchment& EventBusDispatchment::Global() noexcept
    {
        static EventBusDispatchment global_eventBusDispatchment;

        return global_eventBusDispatchment;
    }

    inline EventBusDispatchment::EventBusDispatchment() noexcept
        : busIdIncrement    (0)
    { }

    inline EventBusDispatchment::~EventBusDispatchment() noexcept
    { }

    inline unsigned int EventBusDispatchment::NextEventBusId() noexcept
    {
        return busIdIncrement.fetch_add(1) + 1;
    }
}


// Implementation of: template<class _TEvent> class EventListenerFunctionalStub
namespace BullsEye {
    //
    // std::function<void(_TEvent&)>   func;
    //

    template<class _TEvent>
    inline EventListenerFunctionalStub<_TEvent>::EventListenerFunctionalStub(
            const std::string&              name, 
            int                             priority, 
            std::function<void(_TEvent&)>   func) noexcept
        : EventListener<_TEvent>(name, priority)
        , func                  (func)
    { }

    template<class _TEvent>
    inline EventListenerFunctionalStub<_TEvent>::~EventListenerFunctionalStub() noexcept
    { }

    template<class _TEvent>
    inline void EventListenerFunctionalStub<_TEvent>::OnEvent(_TEvent& event)
    {
        return func(event);
    }
}


// Implementation of: template<class _TEvent> class EventListenerReference
namespace BullsEye {
    //
    // EventListener<_TEvent>& ref;
    //

    template<class _TEvent>
    inline EventListenerReference<_TEvent>::EventListenerReference(EventListener<_TEvent>& ref) noexcept
        : ref   (ref)
    { }

    template<class _TEvent>
    inline EventListenerReference<_TEvent>::~EventListenerReference() noexcept
    { }

    template<class _TEvent>
    inline EventListener<_TEvent>& EventListenerReference<_TEvent>::GetReference() noexcept
    {
        return ref;
    }

    template<class _TEvent>
    inline const EventListener<_TEvent>& EventListenerReference<_TEvent>::GetReference() const noexcept
    {
        return ref;
    }

    template<class _TEvent>
    inline void EventListenerReference<_TEvent>::OnEvent(_TEvent& event)
    {
        ref.OnEvent(event);
    }
}
