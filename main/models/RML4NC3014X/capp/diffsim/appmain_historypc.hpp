#pragma once
//
//
//
//

#include <deque>


#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(base/la32def.hpp)


#define PC_HISTORY_DEPTH      32


class PCHistory {
public:
    static constexpr size_t     MAX_SIZE    = PC_HISTORY_DEPTH;

private:
    std::deque<Jasse::pc_t> history;

public:
    using iterator          = std::deque<Jasse::pc_t>::iterator;
    using const_iterator    = std::deque<Jasse::pc_t>::const_iterator;

public:
    PCHistory() noexcept;

    //
    void                Push(Jasse::pc_t pc) noexcept;

    size_t              GetSize() const noexcept;
    Jasse::pc_t         Get(unsigned int index) const noexcept;

    void                Clear() noexcept;

    //
    iterator            begin() noexcept;
    const_iterator      begin() const noexcept;

    iterator            end() noexcept;
    const_iterator      end() const noexcept;
};
