#pragma once
//
//
//
//

#include <deque>


#include "autoinclude.h"

#include AUTOINC_BE_N1_SOC_LA32(mmu_event.hpp)


class MMIOHistory {
public:
    class Entry {
    public:
        enum class Type {
            READ = 0,
            WRITE
        };

    private:
        Type                    type;
        Jasse::LA32MOPPath      path;
        Jasse::addr_t           address;
        Jasse::LA32MOPWidth     width;
        Jasse::memdata_t        data;
        Jasse::LA32MOPOutcome   outcome;

    public:
        Entry(Type                  type, 
              Jasse::LA32MOPPath    path,
              Jasse::addr_t         address,
              Jasse::LA32MOPWidth   width,
              Jasse::memdata_t      data,
              Jasse::LA32MOPOutcome outcome) noexcept;

        Type                    GetType() const noexcept;
        Jasse::LA32MOPPath      GetPath() const noexcept;
        Jasse::addr_t           GetAddress() const noexcept;
        Jasse::LA32MOPWidth     GetWidth() const noexcept;
        Jasse::memdata_t        GetData() const noexcept;
        Jasse::LA32MOPOutcome   GetOutcome() const noexcept;
    };

public:
    static constexpr size_t     DEFAULT_DEPTH   = 32;

private:
    size_t              depth;
    std::deque<Entry>   history;

public:
    using iterator          = std::deque<Entry>::iterator;
    using const_iterator    = std::deque<Entry>::const_iterator;

public:
    MMIOHistory(size_t depth = DEFAULT_DEPTH) noexcept;

    //
    size_t              GetDepth() const noexcept;
    void                SetDepth(size_t depth) noexcept;

    //
    void                Push(const Entry& entry) noexcept;

    void                Emplace(Entry::Type           type,
                                Jasse::LA32MOPPath    path,
                                Jasse::addr_t         address,
                                Jasse::LA32MOPWidth   width,
                                Jasse::memdata_t      data,
                                Jasse::LA32MOPOutcome outcome) noexcept;

    size_t              GetCount() const noexcept;
    const Entry&        Get(unsigned int index) const noexcept;

    void                Clear() noexcept;

    //
    iterator            begin() noexcept;
    const_iterator      begin() const noexcept;

    iterator            end() noexcept;
    const_iterator      end() const noexcept;
};



// MMIO Read History
class MMIOReadHistory : public MMIOHistory {
public:
    class Builder;

private:
    unsigned int    eventBusId;
    int             eventPriority;

protected:
    std::string     GetListenerName(const char* name) const noexcept;
    void            RegisterListeners() noexcept;
    void            UnregisterListeners() noexcept;

protected:
    void            OnMMUPostReadPostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostReadPostEvent& event) noexcept;

protected:
    MMIOReadHistory(size_t depth, unsigned int eventBusId, int eventPriority) noexcept;

public:
    ~MMIOReadHistory() noexcept;

    unsigned int    GetEventBusId() const noexcept;
    int             GetEventPriority() const noexcept;

    MMIOReadHistory(const MMIOReadHistory&) = delete;
    MMIOReadHistory& operator=(const MMIOReadHistory&) = delete;

    MMIOReadHistory(MMIOReadHistory&&) = delete;
    MMIOReadHistory& operator=(MMIOReadHistory&&) = delete;
};


class MMIOReadHistory::Builder {
private:
    size_t          depth;
    unsigned int    eventBusId;
    int             eventPriority;

public:
    Builder() noexcept;

    //
    Builder&        Depth(size_t depth) noexcept;
    Builder&        EventBusId(unsigned int eventBusId) noexcept;
    Builder&        EventPriority(int eventPriority) noexcept;

    //
    size_t          GetDepth() const noexcept;
    void            SetDepth(size_t depth) noexcept;

    unsigned int    GetEventBusId() const noexcept;
    void            SetEventBusId(unsigned int eventBusId) noexcept;

    int             GetEventPriority() const noexcept;
    void            SetEventPriority(int eventPriority) noexcept;

    //
    MMIOReadHistory* Build() noexcept;
};



// MMIO Write History
class MMIOWriteHistory : public MMIOHistory {
public:
    class Builder;

private:
    unsigned int    eventBusId;
    int             eventPriority;

protected:
    std::string     GetListenerName(const char* name) const noexcept;
    void            RegisterListeners() noexcept;
    void            UnregisterListeners() noexcept;

protected:
    void            OnMMUPostWritePostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostWritePostEvent& event) noexcept;

protected:
    MMIOWriteHistory(size_t depth, unsigned int eventBusId, int eventPriority) noexcept;

public:
    ~MMIOWriteHistory() noexcept;

    unsigned int    GetEventBusId() const noexcept;
    int             GetEventPriority() const noexcept;

    MMIOWriteHistory(const MMIOWriteHistory&) = delete;
    MMIOWriteHistory& operator=(const MMIOWriteHistory&) = delete;

    MMIOWriteHistory(MMIOWriteHistory&&) = delete;
    MMIOWriteHistory& operator=(MMIOWriteHistory&&) = delete;
};


class MMIOWriteHistory::Builder {
private:
    size_t          depth;
    unsigned int    eventBusId;
    int             eventPriority;

public:
    Builder() noexcept;

    //
    Builder&        Depth(size_t depth) noexcept;
    Builder&        EventBusId(unsigned int eventBusId) noexcept;
    Builder&        EventPriority(int eventPriority) noexcept;

    //
    size_t          GetDepth() const noexcept;
    void            SetDepth(size_t depth) noexcept;

    unsigned int    GetEventBusId() const noexcept;
    void            SetEventBusId(unsigned int eventBusId) noexcept;

    int             GetEventPriority() const noexcept;
    void            SetEventPriority(int eventPriority) noexcept;
    
    //
    MMIOWriteHistory* Build() noexcept;
};



// MMIO Read & Write History
class MMIOReadWriteHistory : public MMIOHistory {
public:
    class Builder;

private:
    unsigned int    eventBusId;
    int             eventPriority;

protected:
    std::string     GetListenerName(const char* name) const noexcept;
    void            RegisterListeners() noexcept;
    void            UnregisterListeners() noexcept;

protected:
    void            OnMMUPostReadPostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostReadPostEvent& event) noexcept;
    void            OnMMUPostWritePostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostWritePostEvent& event) noexcept;

protected:
    MMIOReadWriteHistory(size_t depth, unsigned int eventBusId, int eventPriority) noexcept;

public:
    ~MMIOReadWriteHistory() noexcept;

    unsigned int    GetEventBusId() const noexcept;
    int             GetEventPriority() const noexcept;

    MMIOReadWriteHistory(const MMIOReadWriteHistory&) = delete;
    MMIOReadWriteHistory& operator=(const MMIOReadWriteHistory&) = delete;

    MMIOReadWriteHistory(MMIOReadWriteHistory&&) = delete;
    MMIOReadWriteHistory& operator=(MMIOReadWriteHistory&&) = delete;
};


class MMIOReadWriteHistory::Builder {
private:
    size_t          depth;
    unsigned int    eventBusId;
    int             eventPriority;

public:
    Builder() noexcept;

    //
    Builder&        Depth(size_t depth) noexcept;
    Builder&        EventBusId(unsigned int eventBusId) noexcept;
    Builder&        EventPriority(int eventPriority) noexcept;

    //
    size_t          GetDepth() const noexcept;
    void            SetDepth(size_t depth) noexcept;

    unsigned int    GetEventBusId() const noexcept;
    void            SetEventBusId(unsigned int eventBusId) noexcept;

    int             GetEventPriority() const noexcept;
    void            SetEventPriority(int eventPriority) noexcept;

    //
    MMIOReadWriteHistory* Build() noexcept;
};
