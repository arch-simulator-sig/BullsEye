#pragma once
//
//
//
//

#include <deque>


#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(base/la32def.hpp)


#define PC_TRACE_DEPTH      32


class PCTrace {
public:
    static constexpr size_t     MAX_SIZE    = PC_TRACE_DEPTH;

private:
    std::deque<Jasse::pc_t> traced;

public:
    using iterator          = std::deque<Jasse::pc_t>::iterator;
    using const_iterator    = std::deque<Jasse::pc_t>::const_iterator;

public:
    PCTrace() noexcept;

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
