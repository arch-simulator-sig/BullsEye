#include "appmain_pctrace.hpp"
//
//
//
//


// Implementation of: class PCTrace
/*
std::deque<Jasse::pc_t> traced;
*/

PCTrace::PCTrace() noexcept
{ }

void PCTrace::Push(Jasse::pc_t pc) noexcept
{
    traced.push_front(pc);

    while (traced.size() > MAX_SIZE)
        traced.pop_back();
}

size_t PCTrace::GetSize() const noexcept
{
    return traced.size();
}

Jasse::pc_t PCTrace::Get(unsigned int index) const noexcept
{
    return traced[index];
}

void PCTrace::Clear() noexcept
{
    traced.clear();
}

PCTrace::iterator PCTrace::begin() noexcept
{
    return traced.begin();
}

PCTrace::const_iterator PCTrace::begin() const noexcept
{
    return traced.begin();
}

PCTrace::iterator PCTrace::end() noexcept
{
    return traced.end();
}

PCTrace::const_iterator PCTrace::end() const noexcept
{
    return traced.end();
}
