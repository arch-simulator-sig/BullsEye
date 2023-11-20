#include "appmain_historypc.hpp"
//
//
//
//


// Implementation of: class PCTrace
/*
size_t                  depth;
std::deque<Jasse::pc_t> history;
*/

PCHistory::PCHistory(size_t depth) noexcept
    : depth(depth)
{ }

size_t PCHistory::GetDepth() const noexcept
{
    return depth;
}

void PCHistory::SetDepth(size_t depth) noexcept
{
    this->depth = depth;

    while (history.size() > depth)
        history.pop_back();
}

void PCHistory::Push(Jasse::pc_t pc) noexcept
{
    history.push_front(pc);

    while (history.size() > depth)
        history.pop_back();
}

size_t PCHistory::GetSize() const noexcept
{
    return history.size();
}

Jasse::pc_t PCHistory::Get(unsigned int index) const noexcept
{
    return history[index];
}

void PCHistory::Clear() noexcept
{
    history.clear();
}

PCHistory::iterator PCHistory::begin() noexcept
{
    return history.begin();
}

PCHistory::const_iterator PCHistory::begin() const noexcept
{
    return history.begin();
}

PCHistory::iterator PCHistory::end() noexcept
{
    return history.end();
}

PCHistory::const_iterator PCHistory::end() const noexcept
{
    return history.end();
}
