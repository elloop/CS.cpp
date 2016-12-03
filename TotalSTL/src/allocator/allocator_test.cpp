#include "inc.h"

#include <new>              // placement new
#include <cstddef>          // ptrdiff_t, size_t
#include <cstdlib>          // exit
#include <climits>          // UINTMAX_MAX

#include <vector>

using namespace std;

NS_BEGIN(elloop);


//
// a simple allocator should at least:
// type:
//      value_type
//      pointer
//      const_pointer
//      reference
//      const_reference
//      size_type
//      difference_type
// memeber:
//      rebind
//      allocator()
//      allocator(const allocator&)
//      ~allocator()
//      address(reference x): return pointer
//      address(const_reference x): return const_pointer
//      allocate()
//      deallocate()
//      max_size()
//      construct()
//      destroy()

template <typename T>
inline T* _allocate(ptrdiff_t size, T*) {
    set_new_handler(0);
    T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
    if (!tmp) {
        cerr << "out of memory" << endl;
        exit(1);
    }
    return tmp;
}

template <typename T>
inline void _deallocate(T* buffer) {
    ::operator delete(buffer);
}

template <typename T1, typename T2>
inline void _construct(T1* p, const T2& value) {
    new(p) T1(value);                               // todo: placement new cpp primer 
}

template <typename T>
inline void _destroy(T* ptr) {
    ptr->~T();
}

template <typename T>
class allocator {
public:
    typedef T           value_type;
    typedef T*          pointer;
    typedef const T*    const_pointer;
    typedef T&          reference;
    typedef const T&    const_reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;

    template <typename U>
    struct rebind {
        typedef allocator<U> other;
    };

    pointer allocate(size_type n, const void* hint=0) {
        pv("allocate %d for type %s\n", n, typeid(T).name());
        return _allocate((difference_type)n, (pointer)0);
    }

    void deallocate(pointer p, size_type n) {
        pv("deallocate %d for type %s\n", n, typeid(*p).name());
        _deallocate(p);
    }

    void destroy(pointer p) {
        _destroy(p);
    }

    pointer address(reference x) {
        return (pointer)&x;
    }

    const_pointer address(const_reference x) {
        return (const_pointer)&x;
    }

    size_type max_size() const {
        return size_type(UINTMAX_MAX / sizeof(T));
    }
};

BEGIN_TEST(AllocatorTest, SimpleAllocator, @@);

vector<int, elloop::allocator<int>> iv{1, 2, 3, 4, 5, 6};
printContainer(iv, "iv = ");  // iv = 1, 2, 3, 4, 5, 6

/* 
 * output with clang++ compiler:
 *
 * allocate 6 for type i
 * _allocate 6 for type: i
 * iv = 1 2 3 4 5 6
 * deallocate 6 for type i
*/

END_TEST;


NS_END(elloop);
