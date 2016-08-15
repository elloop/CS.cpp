#include <cstdint>
#include <string>
#include <cassert>
#include "inc.h"

template <typename T>
class HashTable {
public:
    HashTable(uint32_t capacity = kSlotsCapacity) 
        : _capacity(capacity) , _size(0) {
            _slots = new HashNode*[capacity];
            memset(_slots, 0, capacity);
    }

    ~HashTable() {
        if (_slots) {

            elloop::pln("deleting hash nodes...");
            for (size_t i=0; i<_capacity; ++i) {
                pv("deleting slots [%d]\n", i);
                auto p = _slots[i], q = p;
                while (p) {
                    q = p->_next;
                    delete p;
                    p = q;
                }
            }
            elloop::pln("deleting slots...");
            delete [] _slots;
        }
    }
    
    bool search(const T &val) {
        uint32_t index = getIndex(val);
        auto p = _slots[index];
        while (p) {
            if (p->_val == val) {
                return true;
            }
            p = p->_next;
        }
        return false;
    }

    bool insert(const T &val, bool &unique) {
        if (search(val)) {
            unique = false;
            return true;
        }

        uint32_t index = getIndex(val);
        auto newNode   = new HashNode(val, _slots[index]);
        _slots[index]  = newNode;
        unique         = true;
        ++_size;
        return true;
    }


    int32_t size() const {
        return _size;
    }

    uint32_t capacity() const {
        return _capacity;
    }

    HashTable(const HashTable & other) = delete;
    HashTable(HashTable && moved) = delete;

private:
    class HashNode {
        public:
            HashNode(const T &val, HashNode *next) : _val(val), _next(next) { }
            ~HashNode() {
                pv("delete hash node [ val = %s ]\n", _val.c_str());
                if (_next) {
                    // delete _next;
                }
            }

            HashNode(const HashNode & other) = delete;
            HashNode(HashNode && moved) = delete;

            T           _val;
            HashNode    *_next;
    };

    HashNode        **_slots;
    uint32_t        _capacity;
    int32_t         _size;
    static const uint32_t kSlotsCapacity = 100;

    // BKDR hash
    static uint32_t hashFunc(const T &val) {
        uint32_t hash(0), seed(131);
        for (size_t i=0; i<val.length(); ++i) {
            hash = hash * seed + val[i];
        }
        return (hash & 0x7fffffff);
    }

    uint32_t getIndex(const T &val) {
        assert(_capacity != 0);
        return hashFunc(val) % _capacity;
    }
};

