#pragma once
//
//
//
//

#include <deque>


#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(base/la32def.hpp)


class PCHistory {
public:
    static constexpr size_t     DEFAULT_DEPTH   = 32;

private:
    size_t                  depth;
    std::deque<Jasse::pc_t> history;

public:
    using iterator          = std::deque<Jasse::pc_t>::iterator;
    using const_iterator    = std::deque<Jasse::pc_t>::const_iterator;

public:
    PCHistory(size_t depth = DEFAULT_DEPTH) noexcept;

    //
    size_t              GetDepth() const noexcept;
    void                SetDepth(size_t depth) noexcept;

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
