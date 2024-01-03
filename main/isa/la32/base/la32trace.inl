//#include "la32trace.hpp"
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Trace Subsystem Infrastructures
//

#include <cstdint>
#include <limits>
#include <utility>


// Template implementation of: class LA32TraceEntity
namespace Jasse {
    /*
    ContentType<Content>    contentType;
    Content                 content;

    Reference               parent0;
    Reference               parent1;
    Reference               parent2;
    */
    template<class _TContent>
    inline _TContent& LA32TraceEntity::ReinterpretContent() noexcept
    {
        return *reinterpret_cast<_TContent*>(&this->content);
    }

    template<class _TContent>
    inline const _TContent& LA32TraceEntity::ReinterpretContent() const noexcept
    {
        return *reinterpret_cast<const _TContent*>(&this->content);
    }

    template<class _TContent>
    inline std::optional<std::reference_wrapper<_TContent>> LA32TraceEntity::GetContent(ContentType<_TContent> type) noexcept
    {
        if (uintptr_t(this->contentType) == uintptr_t(type))
            return { std::ref(this->ReinterpretContent<_TContent>()) };

        return std::nullopt;
    }

    template<class _TContent>
    inline std::optional<std::reference_wrapper<const _TContent>> LA32TraceEntity::GetContent(ContentType<_TContent> type) const noexcept
    {
        if (uintptr_t(this->contentType) == uintptr_t(type))
            return { std::cref(this->ReinterpretContent<_TContent>()) };

        return std::nullopt;
    }

    template<class _TContent>
    inline void LA32TraceEntity::SetContent(ContentType<_TContent> type, const _TContent& content) noexcept
    {
        this->contentType   = reinterpret_cast<ContentType<Content>>(type);
        this->content       = reinterpret_cast<const LA32TraceEntity::Content&>(content);
    }

    template<class _TContent>
    inline _TContent& LA32TraceEntity::SetContentType(ContentType<_TContent> type) noexcept
    {
        this->contentType   = reinterpret_cast<ContentType<Content>>(type);
        return this->ReinterpretContent<_TContent>();
    }
}


// Template implementation of: class LA32TraceEntity::ContentTypeBase
namespace Jasse {
    /*
    const std::string_view          name;

    */

    template<class _TContent>
    inline LA32TraceEntity::ContentTypeBase<_TContent>::ContentTypeBase(const char* name) noexcept
        : name  (name)
    { }

    template<class _TContent>
    inline const std::string_view& LA32TraceEntity::ContentTypeBase<_TContent>::GetName() const noexcept
    {
        return this->name;
    }

    template<class _TContent>
    inline bool LA32TraceEntity::ContentTypeBase<_TContent>::HasTracedArch32Value() const noexcept
    {
        return false;
    }

    template<class _TContent>
    inline arch32_t LA32TraceEntity::ContentTypeBase<_TContent>::GetTracedArch32Value(const _TContent& content) const noexcept
    {
        return 0;
    }

    template<class _TContent>
    inline void LA32TraceEntity::ContentTypeBase<_TContent>::SetTracedArch32Value(_TContent& content, arch32_t value) const noexcept
    { }

    template<class _TContent>
    inline bool LA32TraceEntity::ContentTypeBase<_TContent>::HasTracedArch32ValueSecond() const noexcept
    {
        return false;
    }

    template<class _TContent>
    inline arch32_t LA32TraceEntity::ContentTypeBase<_TContent>::GetTracedArch32ValueSecond(const _TContent& content) const noexcept
    {
        return 0;
    }

    template<class _TContent>
    inline void LA32TraceEntity::ContentTypeBase<_TContent>::SetTracedArch32ValueSecond(_TContent& content, arch32_t value) const noexcept
    { }

    template<class _TContent>
    inline void LA32TraceEntity::ContentTypeBase<_TContent>::Finalize(LA32TraceEntity& entity) const noexcept
    { }
}



// Template implementation of: class LA32TraceHistoryManagement::CompressedIncremental::Chunk
namespace Jasse::LA32TraceHistoryManagement {
    //
    // LA32TraceHistory*   vector;
    // size_t*             address_table;
    //
    // size_t              capacity_exponent;
    // size_t              count;
    //

    template<unsigned int _CompressRatio>
    inline CompressedIncremental<_CompressRatio>::Chunk::Chunk()
        : vector            (nullptr)
        , address_table     (nullptr)
        , capacity_exponent (0)
        , count             (0)
    { }

    template<unsigned int _CompressRatio>
    inline CompressedIncremental<_CompressRatio>::Chunk::~Chunk()
    {
        if (vector)
            delete[] vector;

        if (address_table)
            delete[] address_table;
    }

    template<unsigned int _CompressRatio>
    inline std::optional<size_t> CompressedIncremental<_CompressRatio>::Chunk::_Find(size_t address, size_t* slot_hint) const noexcept
    {
        if (!address_table)
            return std::nullopt;

        if (!count)
            return std::nullopt;

        // check pivot
        size_t pivot = !capacity_exponent ? 0 
            : (address & (std::numeric_limits<size_t>::max() >> ((sizeof(size_t) << 3) - capacity_exponent)));

        size_t lptr, rptr;

        if (pivot < count)
        {
            if (address_table[pivot] == address)
                return { pivot }; // direct hit

            // select side of pivot
            if (address_table[pivot] < address)
            {
                lptr = pivot + 1;
                rptr = count - 1;
            }
            else if (pivot)
            {
                lptr = 0;
                rptr = pivot - 1;
            }
            else
                return std::nullopt;
        }
        else
        {
            lptr = 0;
            rptr = count - 1;
        }

        // binary search on selected side of pivot
        while (lptr <= rptr)
        {
            pivot = (lptr + rptr) >> 1;

            if (address_table[pivot] == address)
                return { pivot };
            else if (address_table[pivot] < address)
                lptr = pivot + 1;
            else if (pivot)
                rptr = pivot - 1;
            else
                return std::nullopt;
        }

        if (slot_hint)
            *slot_hint = pivot;

        return std::nullopt;
    }

    template<unsigned int _CompressRatio>
    inline size_t CompressedIncremental<_CompressRatio>::Chunk::_FindSlot(size_t address, size_t slot_hint) const noexcept
    {
        if (!address_table)
            return 0;

        if (address_table[slot_hint] < address) // search right
        {
            if (slot_hint == count)
                return slot_hint;

            do { slot_hint++; } while (slot_hint < count && address_table[slot_hint] < address);
        }
        else // search left
        {
            if (slot_hint == 0)
                return slot_hint;

            do { slot_hint--; } while (slot_hint >= 0    && address_table[slot_hint] > address);

            slot_hint++; // compensation for left slot insertion
        }

        return slot_hint;
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Chunk::_Initialize() noexcept
    {
        vector        = new LA32TraceHistory[1];
        address_table = new size_t[1];
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Chunk::_Expand(size_t reserved_slot) noexcept
    {
        size_t capacity = 1 << capacity_exponent;

        // construct & move vector
        LA32TraceHistory* newVector = new LA32TraceHistory[capacity << 1];

        if (reserved_slot == 0)
            std::move(vector, vector + capacity, newVector + 1);
        else if (reserved_slot == capacity)
            std::move(vector, vector + capacity, newVector);
        else
        {
            std::move(vector, vector + reserved_slot, newVector);
            std::move(vector + reserved_slot, vector + capacity, newVector + reserved_slot + 1);
        }

        delete[] vector;
        vector = newVector;

        // construct & move address table
        size_t* newAddressTable = new size_t[capacity << 1];

        if (reserved_slot == 0)
            std::move(address_table, address_table + capacity, newAddressTable + 1);
        else if (reserved_slot == capacity)
            std::move(address_table, address_table + capacity, newAddressTable);
        else
        {
            std::move(address_table, address_table + reserved_slot, newAddressTable);
            std::move(address_table + reserved_slot, address_table + capacity, newAddressTable + reserved_slot + 1);
        }

        delete[] address_table;
        address_table = newAddressTable;

        capacity_exponent++;
    }

    template<unsigned int _CompressRatio>
    inline LA32TraceHistory& CompressedIncremental<_CompressRatio>::Chunk::_NewSlot(size_t address, size_t slot_hint) noexcept
    {
        size_t new_slot_index = _FindSlot(address, slot_hint);

        if (!address_table)
            _Initialize();
        else if (count == (1 << capacity_exponent))
            _Expand(new_slot_index);
        else if (new_slot_index != count)
        {
            std::move_backward(vector + new_slot_index, vector + count, vector + new_slot_index + 1);
            std::move_backward(address_table + new_slot_index, address_table + count, address_table + new_slot_index + 1);
        }

        address_table[new_slot_index] = address;

        return vector[new_slot_index];
    }

    template<unsigned int _CompressRatio>
    inline std::optional<std::reference_wrapper<LA32TraceHistory>> CompressedIncremental<_CompressRatio>::Chunk::Get(size_t address) noexcept
    {
        std::optional<size_t> index = _Find(address);

        if (index)
            return { std::ref(vector[*index]) };
        
        return std::nullopt;
    }

    template<unsigned int _CompressRatio>
    inline std::optional<std::reference_wrapper<const LA32TraceHistory>> CompressedIncremental<_CompressRatio>::Chunk::Get(size_t address) const noexcept
    {
        std::optional<size_t> index = _Find(address);

        if (index)
            return { std::cref(vector[*index]) };

        return std::nullopt;
    }

    template<unsigned int _CompressRatio>
    template<bool _EnableOnExists, bool _EnableOnAbsent, class _T>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::_Set(size_t address, _T&& obj) noexcept
    {
        size_t slot_hint = 0;

        std::optional<size_t> index = _Find(address, &slot_hint);

        if (!index)
        {
            if constexpr (_EnableOnAbsent)
                _NewSlot(address, slot_hint) = std::forward<_T>(obj);
            else
                return false;
        }
        else
        {
            if constexpr (_EnableOnExists)
                vector[*index] = std::forward<_T>(obj);
            else
                return false;
        }

        return true;
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Chunk::Set(size_t address, const LA32TraceHistory& obj) noexcept
    {
        _Set<true, true>(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Chunk::Set(size_t address, LA32TraceHistory&& obj) noexcept
    {
        _Set<true, true>(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept
    {
        return _Set<true, false>(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept
    {
        return _Set<true, false>(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfAbsent(size_t address, const LA32TraceHistory& obj) noexcept
    {
        return _Set<false, true>(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfAbsent(size_t address, LA32TraceHistory&& obj) noexcept
    {
        return _Set<false, true>(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept
    {
        std::optional<size_t> index = _Find(address);

        if (!index)
            return false;

        std::swap(vector[*index], obj);
        return true;
    }

    template<unsigned int _CompressRatio>
    inline LA32TraceHistory& CompressedIncremental<_CompressRatio>::Chunk::Acquire(size_t address, size_t default_depth) noexcept
    {
        size_t slot_hint = 0;

        std::optional<size_t> index = _Find(address, &slot_hint);

        if (index)
            return vector[*index];
        else
        {
            LA32TraceHistory& obj = _NewSlot(address, slot_hint);

            obj.SetDepth(default_depth);
            return obj;
        }
    }
}


// Template implementation of: class LA32TraceHistoryManagement::CompressIncremental
namespace Jasse::LA32TraceHistoryManagement {
    //
    // const size_t    max_size;
    //
    // const size_t    chunk_count;
    // Chunk*          chunks;
    //
    // size_t          default_depth;
    //

    template<unsigned int _CompressRatio>
    inline CompressedIncremental<_CompressRatio>::CompressedIncremental(size_t max_size, size_t default_depth) noexcept
        : max_size      (max_size)
        , chunk_count   ((max_size >> _CompressRatio) + 1)
        , chunks        (new Chunk[chunk_count])
        , default_depth (default_depth)
    { }

    template<unsigned int _CompressRatio>
    inline CompressedIncremental<_CompressRatio>::~CompressedIncremental() noexcept
    {
        delete[] chunks;
    }

    template<unsigned int _CompressRatio>
    inline size_t CompressedIncremental<_CompressRatio>::GetDefaultDepth() const noexcept
    {
        return default_depth;
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::SetDefaultDepth(size_t val) noexcept
    {
        default_depth = val;
    }

    template<unsigned int _CompressRatio>
    inline constexpr size_t CompressedIncremental<_CompressRatio>::_ToChunkAddress(size_t address) noexcept
    {
        return address >> _CompressRatio;
    }

    template<unsigned int _CompressRatio>
    inline constexpr size_t CompressedIncremental<_CompressRatio>::_ToAddressInChunk(size_t address) noexcept
    {
        return address;
        // return (address & (std::numeric_limits<size_t>::max() >> ((sizeof(size_t) << 3) - _CompressRatio)));
    }

    template<unsigned int _CompressRatio>
    inline std::optional<std::reference_wrapper<LA32TraceHistory>> CompressedIncremental<_CompressRatio>::Get(size_t address) noexcept
    {
        return chunks[_ToChunkAddress(address)].Get(_ToAddressInChunk(address));
    }

    template<unsigned int _CompressRatio>
    inline std::optional<std::reference_wrapper<const LA32TraceHistory>> CompressedIncremental<_CompressRatio>::Get(size_t address) const noexcept
    {
        return chunks[_ToChunkAddress(address)].Get(_ToAddressInChunk(address));
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Set(size_t address, const LA32TraceHistory& obj) noexcept
    {
        chunks[_ToChunkAddress(address)].Set(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Set(size_t address, LA32TraceHistory&& obj) noexcept
    {
        chunks[_ToChunkAddress(address)].Set(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfExists(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfExists(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::SetIfAbsent(size_t address, const LA32TraceHistory& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfAbsent(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::SetIfAbsent(size_t address, LA32TraceHistory&& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfAbsent(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SwapIfExists(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline LA32TraceHistory& CompressedIncremental<_CompressRatio>::Acquire(size_t address) noexcept
    {
        return chunks[_ToChunkAddress(address)].Acquire(address, default_depth);
    }
}



// Template implementation of: class LA32GPRTracerSubtrate
namespace Jasse {
    //
    // mutable _HistoryManager  manager;
    //

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32GPRTracerSubtrate<_HistoryManager>::LA32GPRTracerSubtrate(size_t default_depth) noexcept
        : manager   (SIZE, default_depth)
    { }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32GPRTracerSubtrate<_HistoryManager>::~LA32GPRTracerSubtrate() noexcept
    { }

    template<LA32TraceHistoryManager _HistoryManager>
    inline size_t LA32GPRTracerSubtrate<_HistoryManager>::GetDefaultDepth() const noexcept
    {
        return manager.GetDefaultDepth();
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32GPRTracerSubtrate<_HistoryManager>::SetDefaultDepth(size_t depth) noexcept
    {
        manager.SetDefaultDepth(depth);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline constexpr size_t LA32GPRTracerSubtrate<_HistoryManager>::GetSize() const noexcept
    {
        return SIZE;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline constexpr bool LA32GPRTracerSubtrate<_HistoryManager>::CheckBound(size_t index) const noexcept
    {
        return index >= 0 && index < SIZE;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32TraceHistory& LA32GPRTracerSubtrate<_HistoryManager>::Get(size_t index) noexcept
    {
        return manager.Acquire(index);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline const LA32TraceHistory& LA32GPRTracerSubtrate<_HistoryManager>::Get(size_t index) const noexcept
    {
        return manager.Acquire(index);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32GPRTracerSubtrate<_HistoryManager>::Set(size_t index, const LA32TraceHistory& obj) noexcept
    {
        manager.Set(index, obj);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32GPRTracerSubtrate<_HistoryManager>::Set(size_t index, LA32TraceHistory&& obj) noexcept
    {
        manager.Set(index, std::move(obj));
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32GPRTracerSubtrate<_HistoryManager>::Swap(size_t index, LA32TraceHistory& obj) noexcept
    {
        if (!manager.SwapIfExists(index, obj))
            std::swap(manager.Acquire(index), obj);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32TraceHistory& LA32GPRTracerSubtrate<_HistoryManager>::operator[](size_t index) noexcept
    {
        return Get(index);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline const LA32TraceHistory& LA32GPRTracerSubtrate<_HistoryManager>::operator[](size_t index) const noexcept
    {
        return Get(index);
    }
}


// Template implementation of: class LA32MemoryTracerSubtrate
namespace Jasse {
    //
    // const size_t            size;
    //
    // mutable _HistoryManager manager;
    //
    // AddressRangeMapper      address_range_mapper;
    //

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32MemoryTracerSubtrate<_HistoryManager>::LA32MemoryTracerSubtrate(size_t size, size_t default_depth) noexcept
        : size                  (size)
        , manager               (size, default_depth)
        , address_range_mapper  (_DefaultAddressRangeMapper)
    { }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32MemoryTracerSubtrate<_HistoryManager>::~LA32MemoryTracerSubtrate() noexcept
    { }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::_DefaultAddressRangeMapper(
        const LA32MemoryTracerSubtrate<_HistoryManager>& obj, size_t& address) noexcept
    {
        return address >= 0 && address <= obj.GetSize();
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline size_t LA32MemoryTracerSubtrate<_HistoryManager>::GetDefaultDepth() const noexcept
    {
        return manager.GetDefaultDepth();
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32MemoryTracerSubtrate<_HistoryManager>::SetDefaultDepth(size_t depth) noexcept
    {
        manager.SetDefaultDepth(depth);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline size_t LA32MemoryTracerSubtrate<_HistoryManager>::GetSize() const noexcept
    {
        return size;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::CheckBound(size_t address) const noexcept
    {
        return address_range_mapper(*this, address);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline std::optional<std::reference_wrapper<LA32TraceHistory>> LA32MemoryTracerSubtrate<_HistoryManager>::Get(size_t address) noexcept
    {
        if (!address_range_mapper(*this, address))
            return std::nullopt;

        auto __from_get = manager.Get(address);
        return __from_get ? std::optional<std::reference_wrapper<LA32TraceHistory>>(std::ref(*__from_get)) : std::nullopt;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline std::optional<std::reference_wrapper<const LA32TraceHistory>> LA32MemoryTracerSubtrate<_HistoryManager>::Get(size_t address) const noexcept
    {
        if (!address_range_mapper(*this, address))
            return std::nullopt;

        auto __from_const_get = std::as_const(manager).Get(address);
        return __from_const_get ? std::optional<std::reference_wrapper<const LA32TraceHistory>>(std::cref(*__from_const_get)) : std::nullopt;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32TraceHistory& LA32MemoryTracerSubtrate<_HistoryManager>::Acquire(size_t address) noexcept
    {
        address_range_mapper(*this, address);
        return manager.Acquire(address);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline const LA32TraceHistory& LA32MemoryTracerSubtrate<_HistoryManager>::Acquire(size_t address) const noexcept
    {
        address_range_mapper(*this, address);
        return manager.Acquire(address);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline std::optional<std::reference_wrapper<LA32TraceHistory>> LA32MemoryTracerSubtrate<_HistoryManager>::AcquireInBound(size_t address) noexcept
    {
        if (!address_range_mapper(*this, address))
            return std::nullopt;

        return Acquire(address);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline std::optional<std::reference_wrapper<const LA32TraceHistory>> LA32MemoryTracerSubtrate<_HistoryManager>::AcquireInBound(size_t address) const noexcept
    {
        if (!address_range_mapper(*this, address))
            return std::nullopt;

        return Acquire(address);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::Set(size_t address, const LA32TraceHistory& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;

        manager.Set(address, obj);
        return true;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::Set(size_t address, LA32TraceHistory&& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;
        
        manager.Set(address, std::move(obj));
        return true;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;

        return manager.SetIfExists(address, obj);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;

        return manager.SetIfExists(address, std::move(obj));
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::SetIfAbsent(size_t address, const LA32TraceHistory& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;

        return manager.SetIfAbsent(address, obj);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::SetIfAbsent(size_t address, LA32TraceHistory&& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;
        
        return manager.SetIfAbsent(address, std::move(obj));
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;

        return manager.SwapIfExists(address, obj);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32MemoryTracerSubtrate<_HistoryManager>::AddressRangeMapper& LA32MemoryTracerSubtrate<_HistoryManager>::GetAddressRangeMapper() noexcept
    {
        return address_range_mapper;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline const LA32MemoryTracerSubtrate<_HistoryManager>::AddressRangeMapper& LA32MemoryTracerSubtrate<_HistoryManager>::GetAddressRangeMapper() const noexcept
    {
        return address_range_mapper;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32MemoryTracerSubtrate<_HistoryManager>::SetAddressRangeMapper(const AddressRangeMapper& mapper) noexcept
    {
        address_range_mapper = mapper;
    }
}
