#pragma once

#if defined(_DEBUG)
#define DEBUGONLY(x) x
#else
#define DEBUGONLY(x)
#endif

#define ALIGNMENT 16

#pragma pack(ALIGNMENT)
#define class_alignment alignas(ALIGNMENT)


template <class T, class MemInterface>
class Allocator : public MemInterface
{
public:
    //    typedefs
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

public:
    //    convert an allocator<T> to allocator<U>

    template<typename U, class MemInterface>
    struct rebind {
        typedef Allocator<U, MemInterface> other;
    };

public:
    inline Allocator() {}
    inline ~Allocator() {}
    inline Allocator(Allocator const&) {}
    template<typename U>
    inline Allocator(Allocator<U, MemInterface> const&) {}

    inline pointer address(reference r) { return &r; }
    inline const_pointer address(const_reference r) { return &r; }

    inline pointer allocate(size_type cnt, typename allocator<void>::const_pointer = 0)
    {
        cout << "Trying to allocate " << cnt << " objects in memory" << endl;
        pointer new_memory = reinterpret_cast<pointer>(operator new(cnt * sizeof(T)));
        cout << "Allocated " << cnt << " objects in memory at location:" << new_memory << endl;
        return new_memory;
    }

    inline void deallocate(pointer p, size_type n)
    {
        operator delete(p, n * sizeof(T));
        cout << "Deleted " << n << " objects from memory" << endl;
    }

    inline size_type max_size() const
    {
        return numeric_limits<size_type>::max() / sizeof(T);
    }

    inline bool operator==(Allocator const&) const
    {
        return true;
    }

    inline bool operator!=(Allocator const& a)
    {
        return !operator==(a);
    }
};

class DefaultMemInterface
{
    struct Metadata
    {
        size_t space;
    };

public:
    //Use global new/delete
    void* DefaultMemInterface::operator new(size_t size)
    {
        cout << "custom new for size " << size << '\n';
        size_t alignment = ALIGNMENT;
        Metadata metadata = { 0 };
        metadata.space = size + sizeof(Metadata) + alignment;
        void* raw_pointer = malloc(metadata.space);
        assert(raw_pointer);
        void* aligned_pointer = align(alignment, size + sizeof(Metadata), raw_pointer, metadata.space);
        assert(aligned_pointer);
        *(Metadata*)((char*)aligned_pointer + size) = metadata;
        return aligned_pointer;
    }

    void* DefaultMemInterface::operator new[](size_t counter)
    {
        cout << "custom new for size " << counter << '\n';
        return operator new(counter);
    }

    void operator delete(void* ptr, size_t size)
    {
        cout << "custom delete for size " << size << '\n';
        size_t alignment = ALIGNMENT;
        void* aligned_pointer = ptr;
        Metadata* metadata = (Metadata*)((char*)aligned_pointer + size);
        void* raw_pointer = (void*)((char*)aligned_pointer - (size + sizeof(Metadata) + alignment - metadata->space));
        free(raw_pointer);
    }

    void operator delete[](void* ptr, size_t counter)
    {
        cout << "custom delete for size " << counter << '\n';
        operator delete(ptr, counter);
    }
};

static_assert(sizeof(DefaultMemInterface) == 1, "Not an empty base class");

namespace Atomic
{
    inline int64_t increment(volatile int64_t& data)
    {
        return _InterlockedIncrement64(&data);
    }

    inline int64_t decrement(volatile int64_t& data)
    {
        return _InterlockedDecrement64(&data);
    }

    inline int32_t increment(volatile int32_t& data)
    {
        return _InterlockedIncrement((volatile long*)&data);
    }

    inline int32_t decrement(volatile int32_t& data)
    {
        return _InterlockedDecrement((volatile long*)&data);
    }

    inline int32_t compare_exchange_weak(volatile int32_t& data, int32_t comperand, int32_t value)
    {
        return _InterlockedCompareExchange((volatile long*)&data, (long)value, (long)comperand);
    }

    inline int64_t compare_exchange_weak(volatile int64_t& data, int64_t comperand, int64_t value)
    {
        return _InterlockedCompareExchange64(&data, value, comperand);
    }

    template <class T>
    inline T* compare_exchange_weak(T* volatile& data, T* comperand, T* value)
    {
        return reinterpret_cast<T*>(_InterlockedCompareExchangePointer((void * volatile *)&data, (void *)value, (void *)comperand));
    }

    inline bool compare_exchange_weak_128(volatile int64_t data[], int64_t comperand[], int64_t valueHi, int64_t valueLo)
    {
        return _InterlockedCompareExchange128(data, valueHi, valueLo, comperand) == 1;
    }

    typedef int64_t Type;
};

union Address
{
    volatile void* pointer;
    Atomic::Type as_atomic;
};

template<typename T, class MemInterface>
struct LockFreeNode;

template<typename T, class MemInterface>
struct AtomicLockFreeNode : public MemInterface
{
    typedef LockFreeNode<T, MemInterface> Node;
    union {
        Node* volatile node;
        Atomic::Type as_atomic;
    };
};
static_assert(sizeof(AtomicLockFreeNode<void*, DefaultMemInterface>) == sizeof(Address), "Size of AtomicLockFreeNode is incorrect.");

template<typename T, class MemInterface>
struct class_alignment LockFreeNode : public MemInterface
{
    typedef AtomicLockFreeNode<T, MemInterface> AtomicNode;

    explicit operator void*() const { return reinterpret_cast<void*>(this); }

    inline LockFreeNode() { next.node = nullptr; }
    inline const T& load() const { return value; }
    inline void store(const T& _value) { value = _value; }

    AtomicNode next;
    T value;

    static_assert(sizeof(T) <= sizeof(Address), "The size is not really important, but T should be a POD.");
};
static_assert(sizeof(LockFreeNode<void*, DefaultMemInterface>) == sizeof(Address) * 2, "Size of AtomicLockFreeNode is incorrect.");

template<typename T, class MemInterface>
struct class_alignment AtomicLockFreeNodePointer : public MemInterface
{
    typedef AtomicLockFreeNode<T, MemInterface> AtomicNode;

    union Data
    {
        struct
        {
            AtomicNode points_to;
            Address access;
        };
        Atomic::Type as_atomic[2];
    };

    inline void clear()
    {
        data.access.pointer = nullptr;
        data.points_to.node = nullptr;
    }

    inline bool compare_exchange_weak(AtomicLockFreeNodePointer & comperand, AtomicLockFreeNodePointer & value) volatile
    {
        return Atomic::compare_exchange_weak_128(data.as_atomic, comperand.data.as_atomic, value.data.access.as_atomic, value.data.points_to.as_atomic);
    }

    void operator=(const volatile AtomicLockFreeNodePointer &other)
    {
        data.access.as_atomic = other.data.access.as_atomic;
        data.points_to.node = other.data.points_to.node;
    }

    Data data;

};
static_assert(sizeof(AtomicLockFreeNodePointer<bool, DefaultMemInterface>) == sizeof(Address) * 2, "Size of AtomicLockFreeNodePointer is incorrect.");


template<typename T, class MemInterface>
class LockFreeNodeStack : public MemInterface
{
    typedef LockFreeNode<T, MemInterface> Node;
    typedef AtomicLockFreeNodePointer<T, MemInterface> AtomicNodePointer;

public:
    LockFreeNodeStack()
    {
        head.clear();
        DEBUGONLY(debug.counter = 0;);
    }

    void push_front(Node* _node)
    {
        DEBUGONLY(assert(_node->next.node == nullptr););
        AtomicNodePointer copy, newNode;
        do
        {
            copy = head;
            newNode.data.access.as_atomic = copy.data.access.as_atomic + 1;
            newNode.data.points_to.node = _node;
            _node->next.node = head.data.points_to.node;
        } while (!head.compare_exchange_weak(copy, newNode));
        DEBUGONLY(Atomic::increment(debug.counter););
    }

    Node* pop_front()
    {
        AtomicNodePointer copy, incCopy;
        do
        {
            copy = head;
            if (copy.data.points_to.node == nullptr)
            {
                return nullptr;
            }

            // NOTE: Memory reclamation is difficult in this context.  If another thread breaks in here
            // and pops the head, and then frees it, then pHead->m_next is an invalid operation.  One solution
            // would be to use hazard pointers (http://researchweb.watson.ibm.com/people/m/michael/ieeetpds-2004.pdf).

            incCopy.data.access.as_atomic = copy.data.access.as_atomic + 1;
            incCopy.data.points_to.node = copy.data.points_to.node->next.node;

        } while (!head.compare_exchange_weak(copy, incCopy));

        DEBUGONLY(Atomic::decrement(debug.counter););
        DEBUGONLY(copy.data.points_to.node->next.node = nullptr;);
        return copy.data.points_to.node;
    }

    bool empty()
    {
        return head.data.points_to.node == nullptr;
    }

private:
    AtomicNodePointer head;

    struct Debug
    {
        int32_t counter;
    };
    DEBUGONLY(Debug debug;);
};

template<typename T, class MemInterface = DefaultMemInterface>
class LockFreeNodeDispenser : public MemInterface
{
    typedef LockFreeNode<T, MemInterface> Node;
    typedef LockFreeNodeStack<T, MemInterface> NodeStack;
    typedef vector<Node, Allocator<T, MemInterface>> NodeVector;

public:

    LockFreeNodeDispenser(uint32_t _startCount = 0)
    {
        if (_startCount)
        {
            // Array requested
            array.reserve(_startCount);
            while (_startCount--)
            {
                dispenser.push_front(&array[_startCount]);
            }
        }
    }

    ~LockFreeNodeDispenser()
    {
        if (!array.size())
        {
            LockFreeNode<T, MemInterface>* node = dispenser.pop_front();
            while (node)
            {
                delete(node);
                node = dispenser.pop_front();
            }
        }
    }

    static inline LockFreeNodeDispenser* Instance() { return nullptr; }

    inline Node* NewNode()
    {
        Node* ret = dispenser.pop_front();
        if (ret == nullptr)
        {
            if (!array.size())
            {
                ret = new Node();
            }
            else
            {
                cout << "Insufficient number of pre-allocated Nodes" << endl;
            }
        }

        DEBUGONLY(ret->next.node = nullptr;);
        return ret;
    }

    inline void FreeNode(Node* _node)
    {
        assert(_node->next.node == nullptr);
        dispenser.push_front(_node);
    }

private:
    NodeStack dispenser;
    NodeVector array;
};

/// Multi Producer Multi Consumer Lock-free queue implementation
/*!
Elements are contained into single-chained nodes provided by a LockFreeNodeDispenser.
\param T Name of the type of object in the container
*/
template<typename T, class MemInterface, class Dispenser>
class MultiProducerMultiConsumer
{
    typedef LockFreeNode<T, MemInterface> Node;
    typedef AtomicLockFreeNode<T, MemInterface> AtomicNode;
    typedef AtomicLockFreeNodePointer<T, MemInterface> AtomicNodePointer;
public:

    MultiProducerMultiConsumer(Dispenser* _dispenser = 0) :
        dispenser(_dispenser)
    {
        endNode.node = (Node*)(this); //Magic Value for the end node
        DEBUGONLY(debug.counter = 1);
        Node* sentinelle = dispenser->NewNode();
        head.data.points_to.node = sentinelle;
        head.data.access.as_atomic = 0;
        tail.data.points_to.node = sentinelle;
        tail.data.access.as_atomic = 0;
        sentinelle->next.node = endNode.node;
    }

    ~MultiProducerMultiConsumer()
    {
        clear();
        assert(head.data.points_to.node == tail.data.points_to.node);
        assert(head.data.points_to.node->next.node == endNode.node); // Check if list is empty
        DEBUGONLY(head.data.points_to.node->next.node = nullptr;)
        dispenser->FreeNode(head.data.points_to.node);
    }

    /*! Add an object in the queue
    \param _value Object to add
    */
    inline bool push_back(const T& _value)
    {
        AtomicNode newNode;
        newNode.node = dispenser->NewNode();
        newNode.node->store(_value);
        assert(newNode.node->next.node == nullptr);
        newNode.node->next.node = endNode.node;

        AtomicNodePointer tailSnapshot;
        tailSnapshot = tail;
        DEBUGONLY(Atomic::increment(debug.counter););
        while (endNode.as_atomic != Atomic::compare_exchange_weak(tail.data.points_to.node->next.as_atomic, endNode.as_atomic, newNode.as_atomic))
        {
            DEBUGONLY(Atomic::decrement(debug.counter););
            UpdateTail(tailSnapshot);
            tailSnapshot = tail;
            DEBUGONLY(Atomic::increment(debug.counter););
        }

        // If the tail points to what we thought was the last LockFreeNode
        // then update the tail to point to the new LockFreeNode.
        AtomicNodePointer newTail;
        newTail.data.access.as_atomic = tailSnapshot.data.access.as_atomic + 1;
        newTail.data.points_to.node = newNode.node;
        tail.compare_exchange_weak(tailSnapshot, newTail);

        return true;
    }

    /*! Retrieve the next object from the queue without removing it from the queue
    \param _out Object retrieved from the queue
    \return Returns false if the queue is empty or desynchronized; see the comment of the return
    value of Remove().
    */
    inline bool peek(T& _out)
    {
        T value = T();
        AtomicNodePointer headSnapshot;
        Node * nextSnapshot;
        bool ret = true;

        do
        {
            headSnapshot = head;
            nextSnapshot = headSnapshot.data.points_to.node->next;

            if (headSnapshot.data.access != head.data.access)
            {
                continue;
            }

            if (nextSnapshot == endNode.node)
            {
                // Removed as it's not completely true as the may have changed
                // during reading the setup as we only check if the head
                // changed not the tail
                _out = T();
                ret = false;
                break;
            }

            DEBUGONLY(if (!nextSnapshot) continue;)
                value = nextSnapshot->load();

            // Check if the head pointer changed. If so try to read it again
            // this will ensure we have a proper value and not something that
            // changed concurrently with this method
        } while (!head.compare_exchange_weak(headSnapshot, headSnapshot));

        _out = value;

        return ret;
    }

    /*! Remove an object from the queue
    \param _out Object removed from the queue
    \return Returns true if an object is removed from the queue. In fact, most of the time a false
    value would mean an empty queue, but it can also mean that the internal state of the queue is
    desynchronized by another thread who is also manipulating the state of the queue. This is
    perfectly legal and the queue will resynchronize itself during a subsequent function call other
    than IsEmpty().
    */
    inline bool pop_front(T& _out)
    {
        Node* node = InternalRemove();
        if (node == nullptr)
            return false;

        _out = node->load();
        dispenser->FreeNode(node);

        return true;
    }

    /*! Remove the next object from the queue only if it is the one specified
    \param _out Object to remove from the queue
    */
    inline void pop_back(const T& _out)
    {
        T value = T();
        AtomicNodePointer pHead, pTail, newHead;;
        Node * pNext;
        bool bSuccess = true;

        for (;;)
        {
            pHead = head;
            pNext = pHead.data.points_to.node->next;
            pTail = tail;

            if (pHead.data.access != head.data.access)
            {
                continue;
            }

            if (pNext == endNode.node)
            {
                // Removed as it's not completely true as the may have changed during reading the setup
                // as we only check if the head changed not the tail
                //assert( pHead.data.m_node == pTail.data.m_node );
                bSuccess = false;
                break;
            }

            // Check if the queue is empty.
            if (pHead.data.points_to.node == pTail.data.points_to.node)
            {
                // Special case if the queue has nodes but the tail
                // is just behind. Move the tail off of the head.
                UpdateTail(pTail);
                continue;
            }

            DEBUGONLY(if (!pNext) break; );
            value = pNext->get();

            // If it's not the one we want to remove, bail out, it's already gone
            if (value != _out) break;

            // Move the head pointer, effectively removing the LockFreeNode
            newHead.data.access = pHead.data.access + 1;
            newHead.data.points_to.node = pNext;
        } while (!head.compare_exchange_weak(pHead, newHead));

        if (bSuccess)
        {
            assert(Atomic::decrement(debug.counter));
        }
    }

    /// \return Returns true if the queue is empty
    inline bool empty() const
    {
        return head.data.points_to.node->next.node == endNode.node;
    }

    /// Remove all objects from the queue.
    void clear()
    {
        Node* node = InternalRemove();
        while (node)
        {
            dispenser->FreeNode(node);
            node = InternalRemove();
        }
    }

private:

    inline void UpdateTail(AtomicNodePointer& _tail)
    {
        AtomicNodePointer newTail;
        newTail.data.access.as_atomic = _tail.data.access.as_atomic + 1;
        newTail.data.points_to.node = _tail.data.points_to.node->next.node;
        if (newTail.data.points_to.node != endNode.node)
        {
            tail.compare_exchange_weak(_tail, newTail);
        }
    }

    Node* InternalRemove()
    {
        T value = T();
        AtomicNodePointer pHead, pTail, newHead;
        Node *pNext;
        bool bSuccess = true;

        do {
            pHead = head;
            pNext = pHead.data.points_to.node->next.node;
            pTail = tail;

            if (pHead.data.access.as_atomic != head.data.access.as_atomic)
            {
                continue;
            }

            if (pNext == endNode.node)
            {
                // Removed as it's not completely true as the may have changed during reading the setup
                // as we only check if the head changed not the tail
                //GEAR_BLOCKING_ASSERT( pHead.data.m_node == pTail.data.m_node );
                pHead.data.points_to.node = nullptr;
                bSuccess = false;
                break;
            }

            // Check if the queue is empty.
            if (pHead.data.points_to.node == pTail.data.points_to.node)
            {
                // Special case if the queue has nodes but the tail
                // is just behind. Move the tail off of the head.
                UpdateTail(pTail);
                continue;
            }

            DEBUGONLY(if (!pNext) continue;)
                value = pNext->load();

            // Move the head pointer, effectively removing the LockFreeNode
            newHead.data.access.as_atomic = pHead.data.access.as_atomic + 1;
            newHead.data.points_to.node = pNext;
        } while (!head.compare_exchange_weak(pHead, newHead));

        if (bSuccess)
        {
            assert(Atomic::decrement(debug.counter));
        }

        if (pHead.data.points_to.node != nullptr)
        {
            pHead.data.points_to.node->store(value);
            DEBUGONLY(pHead.data.points_to.node->next.node = nullptr;);
        }

        return pHead.data.points_to.node;
    }

private:
    AtomicNodePointer volatile head;
    AtomicNodePointer volatile tail;
    AtomicNode  endNode;
    Dispenser *dispenser;
    struct Debug
    {
        volatile int32_t counter;
    };
    DEBUGONLY(Debug debug;);
};

template<class Policy, class T, class MemInterface, class Param = void*>
class LockFreeQueue : public MemInterface
{
public:
    LockFreeQueue()
    {

    }

    LockFreeQueue(Param param) :
        queue(param)
    {

    }

    bool push_back(T newData)
    {
        return queue.push_back(newData);
    }

    bool push_front(T newData)
    {
        return queue.push_front(newData);
    }

    bool pop_front(T& val)
    {
        return queue.pop_front(val);
    }

    bool pop_back(T& val)
    {
        return queue.pop_front(val);
    }

    bool empty() const
    {
        return queue.empty();
    }

    Policy queue;
};
