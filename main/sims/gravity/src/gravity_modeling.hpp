#pragma once

#ifndef __BULLSEYE_SIMS_GRAVITY__MODELING
#define __BULLSEYE_SIMS_GRAVITY__MODELING

#include <string>

#include "gravity_configmacros.hpp"
#include "gravity_utility.hpp"
#include "gravity_eventbus.hpp"
#include "gravity_logging.hpp"


#define GRAVITY_WAVEFRONT_OUT(type)         type
#define GRAVITY_WAVEFRONT_IN(type)          void


namespace Gravity {

    /*
    */
    class Phase;

    template<class TWavefront>
    class Wavefront;

    template<class TWavefront,
             class TWavefrontCollector>
    class Dimension;


    /*
    Dimension for different architectural namespaces.
    */
    typedef Gravity::EventBusId     DimensionId;


    /*
    The Architectural Phase.
    */
    class Phase {
    private:
        DimensionId         inDimension;
        DimensionId         outDimension;

        const std::string   name;

    public:
        Phase(DimensionId           inDimension, 
              DimensionId           outDimension, 
              const std::string&    name) noexcept;
        virtual ~Phase() noexcept;
    
    public:
        DimensionId     GetInDimension() const noexcept;
        void            SetInDimension(DimensionId inDimension) noexcept;

        DimensionId     GetOutDimension() const noexcept;
        void            SetOutDimension(DimensionId outDimension) noexcept;
    };


    /*
    Plain event.
    */
    /*
    template<class T>
    class Event : public ::Event<T> {
    };
    */


    /*
    Wavefront collector.
    */
    template<class TWavefront>
    using WavefrontCollector = EventListener<TWavefront>;

    /*
    Dimension bus with checking in replacement of plain EventBus.
    */
    template<class TWavefront,
             class TWavefrontCollector  = WavefrontCollector<TWavefront>>
    class Dimension : public EventBus<TWavefront, TWavefrontCollector, DimensionId> {
    public:
        Dimension(DimensionId id) noexcept;

    public:
        TWavefront&     Fire(TWavefront& event) override;
    }; 

    /*
    Dimension collection.
    */
    template<class TWavefront,
             class TWavefrontCollector  = WavefrontCollector<TWavefront>,
             class TDimension           = Dimension<TWavefront, TWavefrontCollector>>
    using Dimensions = EventBusGroup<TWavefront, TWavefrontCollector, DimensionId, TDimension>;


    /*
    The Wavefront forwarding Architectural Phase progresses.
    */
    template<class TWavefront>
    class Wavefront : public Event<TWavefront, 
                                   WavefrontCollector<TWavefront>, 
                                   DimensionId, 
                                   Dimension<TWavefront>,
                                   Dimensions<TWavefront>> {
    private:
        const std::string       name;
        Phase&                  source;

    public:
        Wavefront(const std::string& name, Phase& source) noexcept;
        ~Wavefront() noexcept;

    public:
        const std::string&      GetName() const noexcept;

        Phase&                  GetSource() noexcept;
        const Phase&            GetSource() const noexcept;
    };


    /*
    Positive-edge Clock Wavefront
    */
    class ClockPosedge : public Wavefront<ClockPosedge> {
    public:
        ClockPosedge(Phase& phase) noexcept;
        ClockPosedge(const std::string& name, Phase& source) noexcept;
        ~ClockPosedge() noexcept;
    };

    /*
    Negative-edge Clock Wavefront
    */
    class ClockNegedge : public Wavefront<ClockNegedge> {
    public:
        ClockNegedge(Phase& phase) noexcept;
        ClockNegedge(const std::string& name, Phase& source) noexcept;
        ~ClockNegedge() noexcept;
    };
}



// Template of: class Dimension
namespace Gravity {

    template<class TWavefront, class TWavefrontCollector>
    Dimension<TWavefront, TWavefrontCollector>::Dimension(DimensionId id) noexcept
        : EventBus<TWavefront, TWavefrontCollector>(id)
    { }

    template<class TWavefront, class TWavefrontCollector>
    inline TWavefront& 
    Dimension<TWavefront, TWavefrontCollector>::Fire(TWavefront& event) 
    {
#       ifdef GRAVITY_SANITY_CHECK_WAVEFRONT_FLOATING
        {
            if (this->begin() == this->end())
            {
                if constexpr (std::derived_from<TWavefront, Wavefront<TWavefront>>) 
                {
                    auto& wavefront = static_cast<Wavefront<TWavefront>&>(event);
                    
                    LogWarn(StringAppender("Dimension(")
                                .Append(this->GetId())
                                .Append(")::Fire(")
                                .Append(wavefront.GetName())
                                .Append(")")
                                .ToString(),
                            GRAVITY_SANITY_CHECK_WAVEFRONT_FLOATING__MESSAGE)
                        .Fire();
                }

                return event;
            }
        }
#       endif

        return EventBus<TWavefront, TWavefrontCollector>::FireEvent(event);
    }
}


// Template of: class Wavefront
namespace Gravity {
    /*
    const std::string       name;
    Phase&                  source;
    */

    template<class T>
    Wavefront<T>::Wavefront(const std::string& name, Phase& source) noexcept
        : name      (name)
        , source    (source)
    { }

    template<class T>
    Wavefront<T>::~Wavefront() noexcept
    { }

    template<class T>
    const std::string& Wavefront<T>::GetName() const noexcept
    {
        return name;
    }

    template<class T>
    Phase& Wavefront<T>::GetSource() noexcept
    {
        return source;
    }

    template<class T>
    const Phase& Wavefront<T>::GetSource() const noexcept
    {
        return source;
    }
}


#endif // __BULLSEYE_SIMS_GRAVITY__MODELING
