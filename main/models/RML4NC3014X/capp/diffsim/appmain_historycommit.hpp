#pragma once
//
//
//
//

#include <deque>
#include <cstddef>


#include "../csrc/core/ds232_event.hpp"
#include "../csrc/core/ds232_uop40.hpp"


#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(base/la32def.hpp)


class CommitHistory {
public:
    static constexpr size_t     DEFAULT_DEPTH   = 32;

public:
    class Builder;

    class Entry {
    private:
        uint64_t                            eval_time;

        BullsEye::Draconids3014::uop40_t    uop40;

        Jasse::pc_t                         pc;
        Jasse::insnraw_t                    insn;

    public:
        Entry() noexcept;
        Entry(uint64_t eval_time, BullsEye::Draconids3014::uop40_t uop40, Jasse::pc_t pc, Jasse::insnraw_t insn) noexcept;

        uint64_t                            GetEvalTime() const noexcept;
        void                                SetEvalTime(uint64_t eval_time) noexcept;

        BullsEye::Draconids3014::uop40_t    GetUOP40() const noexcept;
        void                                SetUOP40(BullsEye::Draconids3014::uop40_t uop40) noexcept;

        Jasse::pc_t                         GetPC() const noexcept;
        void                                SetPC(Jasse::pc_t pc) noexcept;

        Jasse::insnraw_t                    GetInstruction() const noexcept;
        void                                SetInstruction(Jasse::insnraw_t insn) noexcept;
    };

private:
    unsigned int                                eventBusId;
    int                                         eventPriority;

    size_t                                      depth;
    std::deque<Entry>                           history;

    BullsEye::Draconids3014::Thinpad*           dut;

public:
    using iterator          = std::deque<Entry>::iterator;
    using const_iterator    = std::deque<Entry>::const_iterator;

protected:
    std::string     GetListenerName(const char* name) const noexcept;
    void            RegisterListeners() noexcept;
    void            UnregisterListeners() noexcept;

    void            OnROBCommit(BullsEye::Draconids3014::DS232ROBCommitEvent& event) noexcept;

public:
    CommitHistory(BullsEye::Draconids3014::Thinpad* dut, size_t depth, unsigned int eventBusId, int eventPriority) noexcept;
    ~CommitHistory() noexcept;

    //
    unsigned int    GetEventBusId() const noexcept;
    int             GetEventPriority() const noexcept;

    //
    size_t          GetDepth() const noexcept;
    void            SetDepth(size_t depth) noexcept;

    //
    Entry&          Push() noexcept;
    void            Push(const Entry& entry) noexcept;
    void            Push(Entry&& entry) noexcept;

    template<class... Args>
    Entry&          Push(Args&&... args) noexcept;

    size_t          GetSize() const noexcept;
    const Entry&    Get(unsigned int index) const noexcept;

    void            Clear() noexcept;

    //
    void                                            SetDUT(BullsEye::Draconids3014::Thinpad* dut) noexcept;
    BullsEye::Draconids3014::Thinpad*               GetDUT() noexcept;
    const BullsEye::Draconids3014::Thinpad*         GetDUT() const noexcept;

    //
    iterator        begin() noexcept;
    const_iterator  begin() const noexcept;

    iterator        end() noexcept;
    const_iterator  end() const noexcept;
};


class CommitHistory::Builder {
private:
    BullsEye::Draconids3014::Thinpad*           dut;
    size_t                                      depth;
    unsigned int                                eventBusId;
    int                                         eventPriority;

public:
    Builder() noexcept;

    //
    Builder&        DUT(BullsEye::Draconids3014::Thinpad* dut) noexcept;
    Builder&        Depth(size_t depth) noexcept;
    Builder&        EventBusId(unsigned int eventBusId) noexcept;
    Builder&        EventPriority(int eventPriority) noexcept;
    
    //
    BullsEye::Draconids3014::Thinpad*           GetDUT() noexcept;
    void                                        SetDUT(BullsEye::Draconids3014::Thinpad* dut) noexcept;

    size_t                                      GetDepth() const noexcept;
    void                                        SetDepth(size_t depth) noexcept;

    unsigned int                                GetEventBusId() const noexcept;
    void                                        SetEventBusId(unsigned int eventBusId) noexcept;

    int                                         GetEventPriority() const noexcept;
    void                                        SetEventPriority(int eventPriority) noexcept;

    //
    CommitHistory*  Build() noexcept;
};
