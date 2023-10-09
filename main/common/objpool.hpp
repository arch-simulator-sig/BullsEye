#pragma once
//
// BullsEye Memory Managament (Object Pool)
//
//

#include <list>
#include <bitset>
#include <memory>


namespace BullsEye {

    // Default Empty Initializer
    template<class _TObject>
    struct ObjectPoolDefaultInitializer
    {
        void operator()(_TObject& obj) const noexcept {};
    };

    // Default Empty Finalizer
    template<class _TObject>
    struct ObjectPoolDefaultFinalizer
    {
        void operator()(_TObject& obj) const noexcept {};
    };


    // Round-Robin Object Pool
    // 
    // Objects would be allocated by chunks. When the maximum chunk count was reached,
    // allocation of new objects would reuse the oldest object slots.
    // Allocated chunks were visited by round-robin when the pool was full.
    //
    // *NOTICE: The _TObject type must implement the default zero parameter constructor.
    //          _TObject is required to be DefaultConstructible.
    //          _TObject is not required to be CopyConstructible, CopyAssignable.
    //          _TObject is not required to be MoveConstructible, MoveAssignable.
    template<class _TObject,
             class _TInitializer    = ObjectPoolDefaultInitializer<_TObject>,
             class _TFinalizer      = ObjectPoolDefaultFinalizer<_TObject> >
    class RoundRobinObjectPool
    {
    private:
        class Chunk {
        private:
            const size_t    size;
            _TObject*       objs;

        public:
            Chunk(size_t size) noexcept;
            ~Chunk() noexcept;

            Chunk(const Chunk& obj) = delete;

            size_t              GetSize() const noexcept;

            _TObject&           operator[](int index) noexcept;
            const _TObject&     operator[](int index) const noexcept;

            void                operator=(const Chunk& obj) = delete;
        };

        class ChunkMetadata {
        private:
            const size_t                size;

            std::shared_ptr<bool>**     valid_refset;

            size_t                      read_ptr;
            bool                        read_ptrb;

            size_t                      write_ptr;
            bool                        write_ptrb;

            size_t                      lru_counter;

        private:
            void                _IncrReadPtr() noexcept;
            void                _IncrWritePtr() noexcept;
            void                _Activate(size_t index) noexcept;
            void                _Deactivate(size_t index) noexcept;

        public:
            ChunkMetadata(size_t size) noexcept;
            ~ChunkMetadata() noexcept;

            ChunkMetadata(const ChunkMetadata& obj) = delete;

            size_t              GetSize() const noexcept;
            
            bool                IsFull() const noexcept;

            bool                IsActive(size_t index) const noexcept;

            size_t              GetFreeCount() const noexcept;
            size_t              GetActiveCount() const noexcept;

            std::shared_ptr<bool>*  GetValidRef(size_t index) noexcept;

            size_t              Head() const noexcept;
            size_t              Tail() const noexcept;

            size_t              ActivateHead() noexcept;
            size_t              DeactivateTail() noexcept;

            size_t              GetLRUCounter() const noexcept;
            size_t              IncreaseLRUCounter() noexcept;
            
            void                operator=(const Chunk& obj) = delete;
        };

    public:
        class Reference {
            friend class RoundRobinObjectPool;

        private:
            static const std::shared_ptr<bool>  CONSTANT_FALSE;

        private:
            std::shared_ptr<bool>   valid_ref;
            _TObject*               ref;

        private:
            _TObject*           _ObserveRef() noexcept;
            const _TObject*     _ObserveRef() const noexcept;
                
        private:
            Reference(std::shared_ptr<bool>& valid_ref, _TObject* ref) noexcept;

        public:
            Reference() noexcept;
            Reference(const Reference& obj) noexcept;
           
        public:
            bool                IsValid() const noexcept;

            void                Reset() noexcept;

            _TObject&           operator*() noexcept;
            const _TObject&     operator*() const noexcept;

            _TObject*           operator->() noexcept;
            const _TObject*     operator->() const noexcept;

            Reference&          operator=(const Reference& obj) noexcept;

            operator            bool() const noexcept;
        };

    private:
        const size_t                chunk_size;
        const size_t                chunk_max_count;

        std::list<Chunk*>           chunks;
        std::list<ChunkMetadata*>   chunks_info;

    protected:
        static const _TInitializer  INITIALZER;
        static const _TFinalizer    FINALIZER;

    private:
        void                _NewBlock() noexcept;
        void                _NewBlockAndRotate() noexcept;
        void                _Rotate() noexcept;

    public:
        RoundRobinObjectPool(size_t chunk_size, size_t chunk_max_count) noexcept;
        ~RoundRobinObjectPool() noexcept;

        RoundRobinObjectPool(const RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>& obj) = delete;

        size_t              GetChunkSize() const noexcept;
        size_t              GetChunkMaxCount() const noexcept;

        size_t              GetChunkCount() const noexcept;
        size_t              GetActiveCount() const noexcept;

        bool                IsChunkSaturated() const noexcept;
        bool                IsObjectSaturated() const noexcept;

        Reference           Acquire() noexcept;

        void                Clear() noexcept;

        void                operator=(const RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>& obj) = delete;
    };
}


// Implementation of: class ObjectPool::Block
namespace BullsEye {
    //
    // const size_t     size;
    // _TObject*        objs;
    //

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Chunk::Chunk(size_t size) noexcept
        : size  (size)
        , objs  (new _TObject[size])
    { }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Chunk::~Chunk() noexcept
    {
        delete[] objs;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Chunk::GetSize() const noexcept
    {
        return size;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline _TObject& RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Chunk::operator[](int index) noexcept
    {
        return objs[index];
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline const _TObject& RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Chunk::operator[](int index) const noexcept
    {
        return objs[index];
    }
}


// Implementation of: class ObjectPool::BlockMetadata
namespace BullsEye {
    //
    // const size_t                size;
    //
    // std::shared_ptr<bool>**     valid_refset;
    //
    // size_t                      read_ptr;
    // bool                        read_ptrb;
    //
    // size_t                      write_ptr;
    // bool                        write_ptrb;
    //
    // size_t                      lru_counter;
    //

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::ChunkMetadata(size_t size) noexcept
        : size          (size)
        , valid_refset  (new std::shared_ptr<bool>*[size])
        , read_ptr      (0)
        , read_ptrb     (false)
        , write_ptr     (0)
        , write_ptrb    (false)
        , lru_counter   (0)
    { }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::~ChunkMetadata() noexcept
    {
        for (int i = 0; i < size; i++)
            if (valid_refset[i] && **(valid_refset[i]))
                _Deactivate(i);

        delete[] valid_refset;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::GetSize() const noexcept
    {
        return size;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline bool RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::IsFull() const noexcept
    {
        return (write_ptrb != read_ptrb) && (write_ptr == read_ptr);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline bool RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::IsActive(size_t index) const noexcept
    {
        return (write_ptrb == read_ptrb) ? (index < write_ptr && index >= read_ptr)
                                         : (index < write_ptr || index >= read_ptr);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::GetFreeCount() const noexcept
    {
        return (write_ptrb == read_ptrb) ? (size - write_ptr + read_ptr)
                                         : (read_ptr - write_ptr);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::GetActiveCount() const noexcept
    {
        return (write_ptrb == read_ptrb) ? (write_ptr - read_ptr)
                                         : (size - read_ptr + write_ptr);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline std::shared_ptr<bool>* RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::GetValidRef(size_t index) noexcept
    {
        return valid_refset[index];
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::Head() const noexcept
    {
        return write_ptr;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::Tail() const noexcept
    {
        return read_ptr;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::_IncrReadPtr() noexcept
    {
        read_ptr++;

        if (read_ptr == size)
        {
            read_ptr  = 0;
            read_ptrb = !read_ptrb;
        }
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::_IncrWritePtr() noexcept
    {
        write_ptr++;

        if (write_ptr == size)
        {
            write_ptr  = 0;
            write_ptrb = !write_ptrb;
        }
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::_Deactivate(size_t index) noexcept
    {
        **(valid_refset[index]) = false;

        delete valid_refset[index];
        valid_refset[index] = nullptr;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::_Activate(size_t index) noexcept
    {
        valid_refset[index] = new std::shared_ptr<bool>(new bool(true));
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::ActivateHead() noexcept
    {
        size_t index = write_ptr;

        _Activate(index);
        _IncrWritePtr();

        return index;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::DeactivateTail() noexcept
    {
        size_t index = read_ptr;

        _Deactivate(index);
        _IncrReadPtr();

        return index;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::GetLRUCounter() const noexcept
    {
        return lru_counter;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ChunkMetadata::IncreaseLRUCounter() noexcept
    {
        if (++lru_counter == size)
            lru_counter = 0;

        return lru_counter;
    }
}


// Implementation of: class ObjectPool::Reference
namespace BullsEye {
    //
    // std::shared_ptr<bool>   valid_ref;
    // _TObject*               ref;
    //

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline const std::shared_ptr<bool> RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::CONSTANT_FALSE = std::shared_ptr<bool>(new bool(false));

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::Reference() noexcept
        : valid_ref (CONSTANT_FALSE)
        , ref       (ref)
    { }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::Reference(std::shared_ptr<bool>& valid_ref, _TObject* ref) noexcept
        : valid_ref (valid_ref)
        , ref       (ref)
    { }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::Reference(const Reference& obj) noexcept
        : valid_ref (obj.valid_ref)
        , ref       (obj.ref)
    { }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline _TObject* RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::_ObserveRef() noexcept
    {
        return (*valid_ref) ? ref : nullptr;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline const _TObject* RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::_ObserveRef() const noexcept
    {
        return (*valid_ref) ? ref : nullptr;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline bool RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::IsValid() const noexcept
    {
        return *valid_ref;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::Reset() noexcept
    {
        valid_ref = CONSTANT_FALSE;
        ref       = nullptr;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline _TObject& RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::operator*() noexcept
    {
        return *(_ObserveRef());
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline const _TObject& RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::operator*() const noexcept
    {
        return *(_ObserveRef());
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline _TObject* RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::operator->() noexcept
    {
        return _ObserveRef();
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline const _TObject* RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::operator->() const noexcept
    {
        return _ObserveRef();
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>::Reference& RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::operator=(const Reference& obj) noexcept
    {
        valid_ref   = obj.valid_ref;
        ref         = obj.ref;
        return *this;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::operator bool() const noexcept
    {
        return IsValid();
    }
}


// Implementation of: class ObjectPool
namespace BullsEye {
    //
    // const size_t                chunk_size;
    // const size_t                chunk_max_count;
    //
    // std::list<Block*>           chunks;
    // std::list<BlockMetadata*>   chunks_info;
    //

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline const _TInitializer RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::INITIALZER = _TInitializer();

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline const _TFinalizer RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::FINALIZER = _TFinalizer();

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::RoundRobinObjectPool(size_t chunk_size, size_t chunk_max_count) noexcept
        : chunk_size        (chunk_size)
        , chunk_max_count   (chunk_max_count)
        , chunks            ()
        , chunks_info       ()
    { }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::~RoundRobinObjectPool() noexcept
    {
        for (ChunkMetadata* metadata : chunks_info)
            delete metadata;

        for (Chunk* block : chunks)
            delete block;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::GetChunkSize() const noexcept
    {
        return chunk_size;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::GetChunkMaxCount() const noexcept
    {
        return chunk_max_count;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::GetChunkCount() const noexcept
    {
        return chunks.size();
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::GetActiveCount() const noexcept
    {
        int count = 0;

        for (ChunkMetadata* metadata : chunks_info)
            count += metadata->GetActiveCount();

        return count;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline bool RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::IsChunkSaturated() const noexcept
    {
        return GetChunkCount() >= chunk_max_count;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline bool RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::IsObjectSaturated() const noexcept
    {
        return GetActiveCount() >= (chunk_size * chunk_max_count);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::_NewBlock() noexcept
    {
        chunks.push_back(new Chunk(chunk_size));
        chunks_info.push_back(new ChunkMetadata(chunk_size));
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::_NewBlockAndRotate() noexcept
    {
        _Rotate();
        _NewBlock();
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::_Rotate() noexcept
    {
        Chunk*         rotating_block    = chunks.back();
        chunks.pop_back();
        chunks.push_front(rotating_block);
        
        ChunkMetadata* rotating_metadata = chunks_info.back();
        chunks_info.pop_back();
        chunks_info.push_front(rotating_metadata);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline typename RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>::Reference RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Acquire() noexcept
    {
        if (chunks_info.empty())
            _NewBlock();
        
        ChunkMetadata* tail_info  = chunks_info.back();
        Chunk*         tail_block = chunks.back();

        if (tail_info->IsFull())
            FINALIZER((*tail_block)[tail_info->DeactivateTail()]);

        size_t block_offset = tail_info->ActivateHead();

        INITIALZER((*tail_block)[block_offset]);

        if (!tail_info->IncreaseLRUCounter())
        {
            if (IsChunkSaturated())
                _Rotate();
            else
                _NewBlockAndRotate();
        }

        return Reference(
            *(tail_info->GetValidRef(block_offset)), 
            &((*tail_block)[block_offset]));
    }


    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void RoundRobinObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Clear() noexcept
    {
        for (ChunkMetadata* metadata : chunks_info)
            delete metadata;

        for (Chunk* block : chunks)
            delete block;

        chunks.clear();
        chunks_info.clear();
    }
}
