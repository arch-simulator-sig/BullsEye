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


    // *NOTICE: The _TObject type must implement the default zero parameter constructor.
    //          _TObject is required to be DefaultConstructible.
    //          _TObject is not required to be CopyConstructible, CopyAssignable.
    //          _TObject is not required to be MoveConstructible, MoveAssignable.
    template<class _TObject,
             class _TInitializer    = ObjectPoolDefaultInitializer<_TObject>,
             class _TFinalizer      = ObjectPoolDefaultFinalizer<_TObject> >
    class ObjectPool
    {
    private:
        class Block {
        private:
            const size_t    size;
            _TObject*       objs;

        public:
            Block(size_t size) noexcept;
            ~Block() noexcept;

            Block(const Block& obj) = delete;

            size_t              GetSize() const noexcept;

            _TObject&           operator[](int index) noexcept;
            const _TObject&     operator[](int index) const noexcept;

            void                operator=(const Block& obj) = delete;
        };

        class BlockMetadata {
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
            BlockMetadata(size_t size) noexcept;
            ~BlockMetadata() noexcept;

            BlockMetadata(const BlockMetadata& obj) = delete;

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
            
            void                operator=(const Block& obj) = delete;
        };

    public:
        class Reference {
        private:
            std::shared_ptr<bool>   valid_ref;
            _TObject*               ref;

        private:
            _TObject*           _ObserveRef() noexcept;
            const _TObject*     _ObserveRef() const noexcept;

        private:
            Reference(std::shared_ptr<bool>& valid_ref, _TObject* ref) noexcept;
           
        public:
            bool                IsValid() const noexcept;

            _TObject&           operator*() noexcept;
            const _TObject&     operator*() const noexcept;

            _TObject*           operator->() noexcept;
            const _TObject*     operator->() const noexcept;
        };

    private:
        const size_t                block_size;
        const size_t                block_max_count;

        std::list<Block*>           blocks;
        std::list<BlockMetadata*>   blocks_info;

    protected:
        static _TInitializer        INITIALZER;
        static _TFinalizer          FINALIZER;

    private:
        void                _NewBlock() noexcept;
        void                _NewBlockAndRotate() noexcept;
        void                _Rotate() noexcept;

    public:
        ObjectPool(size_t block_size, size_t block_max_count) noexcept;
        ~ObjectPool() noexcept;

        ObjectPool(const ObjectPool<_TObject, _TInitializer, _TFinalizer>& obj) = delete;

        size_t              GetBlockSize() const noexcept;
        size_t              GetBlockMaxCount() const noexcept;

        size_t              GetBlockCount() const noexcept;
        size_t              GetActiveCount() const noexcept;

        bool                IsBlockSaturated() const noexcept;
        bool                IsObjectSaturated() const noexcept;

        Reference           Acquire() noexcept;

        void                Clear() noexcept;

        void                operator=(const ObjectPool<_TObject, _TInitializer, _TFinalizer>& obj) = delete;
    };

}


// Implementation of: class ObjectPool::Block
namespace BullsEye {
    //
    // const size_t     size;
    // _TObject*        objs;
    //

    template<class _TObject, class _TInitializer, class _TFinalizer>
    ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Block::Block(size_t size) noexcept
        : size  (size)
        , objs  (new _TObject[size])
    { }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Block::~Block() noexcept
    {
        delete[] objs;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Block::GetSize() const noexcept
    {
        return size;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline _TObject& ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Block::operator[](int index) noexcept
    {
        return objs[index];
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline const _TObject& ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Block::operator[](int index) const noexcept
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
    ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::BlockMetadata(size_t size) noexcept
        : size          (size)
        , valid_refset  (new std::shared_ptr<bool>*[size])
        , read_ptr      (0)
        , read_ptrb     (false)
        , write_ptr     (0)
        , write_ptrb    (false)
        , lru_counter   (0)
    { }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::~BlockMetadata() noexcept
    {
        for (int i = 0; i < _IBlockSize; i++)
            if (valid_refset[i] && **(valid_refset[i]))
                _Deactivate(i);

        delete[] valid_refset;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::GetSize() const noexcept
    {
        return size;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline bool ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::IsFull() const noexcept
    {
        return (write_ptrb != read_ptrb) && (write_ptr == read_ptr);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline bool ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::IsActive(size_t index) const noexcept
    {
        return (write_ptrb == read_ptrb) ? (index < write_ptr && index >= read_ptr)
                                         : (index < write_ptr || index >= read_ptr);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::GetFreeCount() const noexcept
    {
        return (write_ptrb == read_ptrb) ? (size - write_ptr + read_ptr)
                                         : (read_ptr - write_ptr);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::GetActiveCount() const noexcept
    {
        return (write_ptrb == read_ptrb) ? (write_ptr - read_ptr)
                                         : (size - read_ptr + write_ptr);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline std::shared_ptr<bool>* ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::GetValidRef(size_t index) noexcept
    {
        return valid_refset[index];
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::Head() const noexcept
    {
        return write_ptr;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::Tail() const noexcept
    {
        return read_ptr;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::_IncrReadPtr() noexcept
    {
        read_ptr++;

        if (read_ptr == size)
        {
            read_ptr  = 0;
            read_ptrb = !read_ptrb;
        }
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::_IncrWritePtr() noexcept
    {
        write_ptr++;

        if (write_ptr == size)
        {
            write_ptr  = 0;
            write_ptrb = !write_ptrb;
        }
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::_Deactivate(size_t index) noexcept
    {
        **(valid_refset[index]) = false;

        delete valid_refset[index];
        valid_refset[index] = nullptr;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::_Activate(size_t index) noexcept
    {
        valid_refset[index] = new std::shared_ptr<bool>(new bool(true));
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::ActivateHead() noexcept
    {
        _Activate(write_ptr);
        _IncrWritePtr();
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::DeactivateTail() noexcept
    {
        _Deactivate(read_ptr);
        _IncrReadPtr();
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::GetLRUCounter() const noexcept
    {
        return lru_counter;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::BlockMetadata::IncreaseLRUCounter() noexcept
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
    ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::Reference(std::shared_ptr<bool>& valid_ref, _TObject* ref)
        : valid_ref (valid_ref)
        , ref       (ref)
    { }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline _TObject* ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::_ObserveRef() noexcept
    {
        return (*valid_ref) ? ref : nullptr;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline const _TObject* ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::_ObserveRef() const noexcept
    {
        return (*valid_ref) ? ref : nullptr;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline bool ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::IsValid() const noexcept
    {
        return *valid_ref;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline _TObject& ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::operator*() noexcept
    {
        return *(_ObserveRef());
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline const _TObject& ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::operator*() const noexcept
    {
        return *(_ObserveRef());
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline _TObject* ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::operator->() noexcept
    {
        return _ObserveRef();
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline const _TObject* ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Reference::operator->() const noexcept
    {
        return _ObserveRef();
    }
}


// Implementation of: class ObjectPool
namespace BullsEye {
    //
    // const size_t                block_size;
    // const size_t                block_max_count;
    //
    // std::list<Block*>           blocks;
    // std::list<BlockMetadata*>   blocks_info;
    //

    template<class _TObject, class _TInitializer, class _TFinalizer>
    ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::ObjectPool(size_t block_size, size_t block_max_count) noexcept
        : block_size        (block_size)
        , block_max_count   (block_max_count)
        , blocks            ()
        , blocks_info       ()
    { }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::~ObjectPool() noexcept
    {
        for (BlockMetadata* metadata : blocks_info)
            delete metadata;

        for (Block* block : blocks)
            delete block;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::GetBlockSize() const noexcept
    {
        return block_size;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::GetBlockMaxCount() const noexcept
    {
        return block_max_count;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::GetBlockCount() const noexcept
    {
        return blocks.size();
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    size_t ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::GetActiveCount() const noexcept
    {
        int count = 0;

        for (BlockMetadata* metadata : blocks_info)
            count += metadata->GetActiveCount();

        return count;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline bool ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::IsBlockSaturated() const noexcept
    {
        return GetBlockCount() >= block_max_count;
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline bool ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::IsObjectSaturated() const noexcept
    {
        return GetActiveCount() >= (block_size * block_max_count);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::_NewBlock() noexcept
    {
        blocks.push_back(new Block(block_size));
        blocks_info.push_back(new BlockMetadata(block_size));
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::_NewBlockAndRotate() noexcept
    {
        _Rotate();
        _NewBlock();
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    inline void ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::_Rotate() noexcept
    {
        Block*         rotating_block    = blocks.back();
        blocks.pop_back();
        blocks.push_front(rotating_block);
        
        BlockMetadata* rotating_metadata = blocks_info.back();
        blocks_info.pop_back();
        blocks_info.push_front(rotating_metadata);
    }

    template<class _TObject, class _TInitializer, class _TFinalizer>
    ObjectPool<_TObject, _TInitializer, _TFinalizer>::Reference ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Acquire() noexcept
    {
        if (blocks_info.empty())
            _NewBlock();
        
        BlockMetadata* tail_info  = blocks_info.back();
        Block*         tail_block = blocks.back();

        if (tail_info->IsFull())
            tail_info->DeactivateTail();

        size_t block_offset = tail_info->ActivateHead();

        if (!tail_info->IncreaseLRUCounter())
        {
            if (IsBlockSaturated())
                _Rotate();
            else
                _NewBlockAndRotate();
        }

        return Reference(
            *(tail_info->GetValidRef(block_offset)), 
            &((*tail_block)[block_offset]));
    }


    template<class _TObject, class _TInitializer, class _TFinalizer>
    void ObjectPool<_TObject, _TInitializer, _TFinalizer>
        ::Clear() noexcept
    {
        for (BlockMetadata* metadata : blocks_info)
            delete metadata;

        for (Block* block : blocks)
            delete block;

        blocks.clear();
        blocks_info.clear();
    }
}
