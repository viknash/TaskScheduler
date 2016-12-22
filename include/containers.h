#pragma once

#include "memory.h"
#include "utils.h"
#include "atomics.h"

#include <istream>
#include <atomic>

namespace task_scheduler {

    union address {
        volatile void* ptr;
        atomics::type as_atomic;
    };

    template <typename T, class TMemInterface>
    struct lock_free_node;

    template <typename T, class TMemInterface>
    struct atomic_lock_free_node : public TMemInterface {
        typedef lock_free_node<T, TMemInterface> node_type;
        union {
            node_type* volatile node;
            atomics::type as_atomic;
        };
    };
    static_assert(sizeof(atomic_lock_free_node<void*, default_mem_interface>) == sizeof(address), "size of atomic_lock_free_node is incorrect.");

    template <typename T, class TMemInterface>
    struct class_alignment lock_free_node : public TMemInterface {
        typedef atomic_lock_free_node<T, TMemInterface> atomic_node;

        explicit operator void*() const { return reinterpret_cast<void*>(this); }

        inline lock_free_node() { next.node = nullptr; }
        inline const T& load() const { return value; }
        inline void store(const T& _value) { value = _value; }

        atomic_node next;
        T value;

        static_assert(sizeof(T) <= sizeof(address), "T must be a POD");
    };
    static_assert(sizeof(lock_free_node<void*, default_mem_interface>) == sizeof(address) * 2, "size of atomic_lock_free_node is incorrect.");

    template <typename T, class TMemInterface>
    struct class_alignment atomic_lock_free_node_ptr : public TMemInterface {
        typedef atomic_lock_free_node<T, TMemInterface> atomic_node;
#pragma warning( push )  
#pragma warning( disable : 4201 )  
        union Data {
            struct
            {
                atomic_node points_to;
                address access;
            };
            atomics::type as_atomic[2];
        };
#pragma warning( pop )  
        inline void clear()
        {
            data.access.ptr = nullptr;
            data.points_to.node = nullptr;
        }

        inline bool compare_exchange_weak(atomic_lock_free_node_ptr& comperand, atomic_lock_free_node_ptr& value) volatile
        {
            return atomics::compare_exchange_weak_128(data.as_atomic, comperand.data.as_atomic, value.data.access.as_atomic, value.data.points_to.as_atomic);
        }

        void operator=(const volatile atomic_lock_free_node_ptr& other)
        {
            data.access.as_atomic = other.data.access.as_atomic;
            data.points_to.node = other.data.points_to.node;
        }

        Data data;
    };
    static_assert(sizeof(atomic_lock_free_node_ptr<bool, default_mem_interface>) == sizeof(address) * 2, "size of atomic_lock_free_node_ptr is incorrect.");

    template <typename T, class TMemInterface>
    class lock_free_node_stack : public TMemInterface {
        typedef lock_free_node<T, TMemInterface> node_type;
        typedef atomic_lock_free_node_ptr<T, TMemInterface> atomic_node_ptr;

    public:
        lock_free_node_stack()
        {
            head.clear();
            ts_debug_only(debug.counter = 0;);
        }

        void push_front(node_type* _node)
        {
            ts_debug_only(assert(_node->next.node == nullptr););
            atomic_node_ptr copy, newNode;
            do {
                copy = head;
                newNode.data.access.as_atomic = copy.data.access.as_atomic + 1;
                newNode.data.points_to.node = _node;
                _node->next.node = head.data.points_to.node;
            } while (!head.compare_exchange_weak(copy, newNode));
            ts_debug_only(atomics::increment(debug.counter););
        }

        node_type* pop_front()
        {
            atomic_node_ptr copy, inc_copy;
            do {
                copy = head;
                if (copy.data.points_to.node == nullptr) {
                    return nullptr;
                }

                inc_copy.data.access.as_atomic = copy.data.access.as_atomic + 1;
                inc_copy.data.points_to.node = copy.data.points_to.node->next.node;

            } while (!head.compare_exchange_weak(copy, inc_copy));

            ts_debug_only(atomics::decrement(debug.counter););
            ts_debug_only(copy.data.points_to.node->next.node = nullptr;);
            return copy.data.points_to.node;
        }

        bool empty()
        {
            return head.data.points_to.node == nullptr;
        }

    private:
        atomic_node_ptr head;

        struct debug_container {
            int32_t counter;
        };
        ts_debug_only(debug_container debug;);
    };

    template <typename T, class TMemInterface = default_mem_interface>
    class lock_free_node_dispenser : public TMemInterface {
        typedef lock_free_node<T, TMemInterface> node_type;
        typedef lock_free_node_stack<T, TMemInterface> node_stack;
        typedef std::vector<node_type, stl_allocator<T, TMemInterface>> node_vector;

    public:
        lock_free_node_dispenser(uint32_t _start_count = 0)
        {
            if (_start_count) {
                // Array requested
                array.reserve(_start_count);
                while (_start_count--) {
                    dispenser.push_front(&array[_start_count]);
                }
            }
        }

        ~lock_free_node_dispenser()
        {
            if (!array.size()) {
                lock_free_node<T, TMemInterface>* node = dispenser.pop_front();
                while (node) {
                    delete (node);
                    node = dispenser.pop_front();
                }
            }
        }

        inline node_type* new_node()
        {
            node_type* ret = dispenser.pop_front();
            if (ret == nullptr) {
                if (!array.size()) {
                    ret = new node_type();
                }
                else {
                    std::cout << "Insufficient number of pre-allocated Nodes" << std::endl;
                }
            }

            ts_debug_only(ret->next.node = nullptr;);
            return ret;
        }

        inline void free_node(node_type* _node)
        {
            assert(_node->next.node == nullptr);
            dispenser.push_front(_node);
        }

    private:
        node_stack dispenser;
        node_vector array;
    };

    // Multi Producer Multi Consumer Lock-free queue implementation
    // Elements are contained into single-chained nodes provided by a lock_free_node_dispenser.
    // param T Name of the type of object in the container

    template <typename T, class TMemInterface, class TDispenser>
    class multi_producer_multi_consumer {
        typedef lock_free_node<T, TMemInterface> node_type;
        typedef atomic_lock_free_node<T, TMemInterface> atomic_node;
        typedef atomic_lock_free_node_ptr<T, TMemInterface> atomic_node_ptr;

    public:
        multi_producer_multi_consumer(TDispenser* _dispenser = 0)
            : dispenser(_dispenser)
        {
            end_node.node = (node_type*)(this); //Magic Value for the end node
            ts_debug_only(debug.counter = 1);
            node_type* sentinelle = dispenser->new_node();
            head.data.points_to.node = sentinelle;
            head.data.access.as_atomic = 0;
            tail.data.points_to.node = sentinelle;
            tail.data.access.as_atomic = 0;
            sentinelle->next.node = end_node.node;
        }

        ~multi_producer_multi_consumer()
        {
            clear();
            assert(head.data.points_to.node == tail.data.points_to.node);
            assert(head.data.points_to.node->next.node == end_node.node); // Check if list is empty
            ts_debug_only(head.data.points_to.node->next.node = nullptr;)
                dispenser->free_node(head.data.points_to.node);
        }

        /*! Add an object in the queue
        \param _value Object to add
        */
        inline bool push_back(const T& _value)
        {
            atomic_node new_node;
            new_node.node = dispenser->new_node();
            new_node.node->store(_value);
            assert(new_node.node->next.node == nullptr);
            new_node.node->next.node = end_node.node;

            atomic_node_ptr tail_snapshot;
            tail_snapshot = tail;
            ts_debug_only(atomics::increment(debug.counter););
            while (end_node.as_atomic != atomics::compare_exchange_weak(tail.data.points_to.node->next.as_atomic, end_node.as_atomic, new_node.as_atomic)) {
                ts_debug_only(atomics::decrement(debug.counter););
                update_tail(tail_snapshot);
                tail_snapshot = tail;
                ts_debug_only(atomics::increment(debug.counter););
            }

            // If the tail remains the same then update the tail
            atomic_node_ptr newTail;
            newTail.data.access.as_atomic = tail_snapshot.data.access.as_atomic + 1;
            newTail.data.points_to.node = new_node.node;
            tail.compare_exchange_weak(tail_snapshot, newTail);

            return true;
        }

        inline bool peek(T& _out)
        {
            T value = T();
            atomic_node_ptr headSnapshot;
            node_type* nextSnapshot;
            bool ret = true;
            bool skip = false;

            do {
                skip = false;
                headSnapshot = head;
                nextSnapshot = headSnapshot.data.points_to.node->next;

                if (headSnapshot.data.access != head.data.access) {
                    skip = true;
                    continue;
                }

                if (nextSnapshot == end_node.node) {
                    _out = T();
                    ret = false;
                    break;
                }

                ts_debug_only(if (!nextSnapshot) continue;);
                value = nextSnapshot->load();

            } while (skip || !head.compare_exchange_weak(headSnapshot, headSnapshot));

            _out = value;

            return ret;
        }

        inline bool pop_front(T& _out)
        {
            node_type* node = internal_remove();
            if (node == nullptr)
                return false;

            _out = node->load();
            dispenser->free_node(node);

            return true;
        }

        // Returns true if the queue is empty
        inline bool empty() const
        {
            return head.data.points_to.node->next.node == end_node.node;
        }

        // Remove all objects from the queue.
        void clear()
        {
            node_type* node = internal_remove();
            while (node) {
                dispenser->free_node(node);
                node = internal_remove();
            }
        }

    private:
        inline void update_tail(atomic_node_ptr& _tail)
        {
            atomic_node_ptr newTail;
            newTail.data.access.as_atomic = _tail.data.access.as_atomic + 1;
            newTail.data.points_to.node = _tail.data.points_to.node->next.node;
            if (newTail.data.points_to.node != end_node.node) {
                tail.compare_exchange_weak(_tail, newTail);
            }
        }

        node_type* internal_remove()
        {
            T value = T();
            atomic_node_ptr ptr_head, ptr_tail, new_head;
            node_type* ptr_next;
            bool success = true;
            bool skip = false;

            do {
                skip = false;
                //Save a local copy of pointers to update them locally
                ptr_head = head;
                ptr_next = ptr_head.data.points_to.node->next.node;
                ptr_tail = tail;

                //Early abort and retry if some other thread has already modified the head
                if (ptr_head.data.access.as_atomic != head.data.access.as_atomic) {
                    skip = true;
                    continue;
                }

                //Abort if head points to the sentinelle
                if (ptr_next == end_node.node) {
                    ptr_head.data.points_to.node = nullptr;
                    success = false;
                    break;
                }

                //Early abort and retry if the queue is empty
                if (ptr_head.data.points_to.node == ptr_tail.data.points_to.node) {
                    //Update tail for the next retry as it could have changed
                    update_tail(ptr_tail);
                    skip = true;
                    continue;
                }

                ts_debug_only(if (!ptr_next) continue;);
                //Save the value to be return if this try is successful
                value = ptr_next->load();

                //Assemble a new head
                new_head.data.access.as_atomic = ptr_head.data.access.as_atomic + 1;
                new_head.data.points_to.node = ptr_next;

                //if the head we worked is the same as the current head, replace it with a new head
            } while (skip || !head.compare_exchange_weak(ptr_head, new_head));

            if (success) {
                assert(atomics::decrement(debug.counter));
            }

            //If we succeeded then return the new value the removed node
            if (ptr_head.data.points_to.node != nullptr) {
                ptr_head.data.points_to.node->store(value);
                ts_debug_only(ptr_head.data.points_to.node->next.node = nullptr;);
            }

            return ptr_head.data.points_to.node;
        }

    private:
        atomic_node_ptr volatile head;
        atomic_node_ptr volatile tail;
        atomic_node end_node;
        TDispenser* dispenser;
        struct debug_container {
            volatile int32_t counter;
        };
        ts_debug_only(debug_container debug;);
    };

    template <class TPolicy, class T, class TMemInterface, class TParam = void*>
    class lock_free_queue : public TMemInterface {
    public:
        lock_free_queue()
        {
        }

        lock_free_queue(TParam param)
            : queue(param)
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

        TPolicy queue;
    };


    template <typename T, class TMemInterface = default_mem_interface>
    class lock_free_fixed_size_array : public TMemInterface {

    public:
        lock_free_fixed_size_array(size_t _reserverd_size, bool _optimize_for_cache_line_size);
        lock_free_fixed_size_array(T* _existing_array, size_t _existing_array_size);
        size_t size() { return array_size; }
        size_t reserved() { return array_flags.reserved_size; }
        ~lock_free_fixed_size_array();
        T& operator[](size_t _index);
        T* operator&();
        void push_back(const T& _new_item);
        void clear();

        template <typename T, class TMemInterface> friend class lock_free_fixed_size_array_batch_dispenser;

        union flags {
            size_t reserved_size : 62;
            size_t read_locked : 1;
            size_t data_owner : 1;
        };

    private: 
        void lock();
        void unlock();
        bool is_locked();

        T* data;
        std::atomic<size_t> array_size;
        flags array_flags;
    };


    template <typename T, class TMemInterface>
    inline lock_free_fixed_size_array<T, TMemInterface>::lock_free_fixed_size_array(size_t _reserved_size, bool _optimize_for_cache_line_size) :
        array_size(0),
        flags(0)
    {
        array_flags.reserved_size = ~0;
        uint64_t max_array_size = array_flags.reserved_size;
        assert(_reserved_size < array_flags.reserved_size); // Requested size is too large
        array_flags.reserved_size = _reserved_size;
        array_flags.data_owner = 1;
        uint32_t cache_line_size = _optimize_for_cache_line_size ? get_cache_line_size() : 1;
        data = new (cache_line_size) T[size];
    }

    template <typename T, class TMemInterface>
    inline lock_free_fixed_size_array<T, TMemInterface>::lock_free_fixed_size_array(T* _existing_array, size_t _existing_array_size) :
        data(_existing_array),
        array_size(_existing_array_size)
    {
        array_flags.reserved_size = _existing_array_size;
        array_flags.data_owner = 0;
    }

    template <typename T, class TMemInterface>
    inline lock_free_fixed_size_array<T, TMemInterface>::~lock_free_fixed_size_array()
    { 
        if (array_flags.data_owner)
        {
            delete[] data;
        }
        ts_debug_only(data = nullptr;);
        ts_debug_only(array_flags = 0;);
        ts_debug_only(array_size = 0;);
    }

    template <typename T, class TMemInterface>
    inline T& lock_free_fixed_size_array<T, TMemInterface>::operator[](size_t _index)
    {
        assert(_index < array_size); // Index out of bounds
        return data + _index;
    }

    template <typename T, class TMemInterface>
    inline void lock_free_fixed_size_array<T, TMemInterface>::push_back(const T& _new_item)
    {
        ++array_size;
        assert(array_size <= array_flags.reserved_size); //Exceeded size of array
        assert(is_locked()); //Array has been locked for reading
        *(data + array_size - 1) = _new_item;
    }

    template <typename T, class TMemInterface>
    inline void lock_free_fixed_size_array<T, TMemInterface>::clear()
    {
        assert(!is_locked()); //Array has been locked for reading
        array_size = 0;
    }

    template <typename T, class TMemInterface>
    inline T* lock_free_fixed_size_array<T, TMemInterface>::operator&()
    {
        assert(!is_locked()); //Array has been locked for reading
        return data;
    }

    template <typename T, class TMemInterface>
    inline void lock_free_fixed_size_array<T, TMemInterface>::lock()
    {
        assert(!array_flags.read_locked); //Array has already been locked before
        array_flags.read_locked = 1;
    }

    template <typename T, class TMemInterface>
    inline void lock_free_fixed_size_array<T, TMemInterface>::unlock()
    {
        assert(array_flags.read_locked); //Array has already been unlocked before
        array_flags.read_locked = 0;
    }

    template <typename T, class TMemInterface>
    inline bool lock_free_fixed_size_array<T, TMemInterface>::is_locked()
    {
        return array_flags.read_locked;
    }


    template <typename T, class TDataType, class TMemInterface = default_mem_interface>
    class lock_free_batch_dispatcher : public TMemInterface {
    public:
        lock_free_batch_dispatcher(TDataType& _data_type);
        ~lock_free_batch_dispatcher();
        T* get_next_batch(size_t _requested_batch_size, size_t& _returned_batch_size);

    private:
        TDataType& data;
        std::atomic<size_t> next_batch_index;
    };


    template <typename T, class TDataType, class TMemInterface>
    inline lock_free_batch_dispatcher<T, TDataType, TMemInterface>::lock_free_batch_dispatcher(TDataType& _lock_free_fixed_size_array) :
        data(_lock_free_fixed_size_array),
        next_batch_index(0)
    {
        data.lock();
    }

    template <typename T, class TDataType, class TMemInterface>
    inline lock_free_batch_dispatcher<T, TDataType, TMemInterface>::~lock_free_batch_dispatcher()
    {
        data.unlock();
        ts_debug_only(next_batch_index = 0;);
    }

    template <typename T, class TDataType, class TMemInterface>
    inline T* lock_free_batch_dispatcher<T, TDataType, TMemInterface>::get_next_batch(size_t _requested_batch_size, size_t& _returned_batch_size)
    {
        size_t current_batch_index = next_batch_index.fetch_add(_requested_batch_size);
        if (current_batch_index < data.array_size)
        {
            _returned_batch_size = std::min(data.array_size - current_batch_index, _requested_batch_size);
            return data + current_batch_index;
        }
        else
        {
            _returned_batch_size = 0;
            return nullptr;
        }
    }

};