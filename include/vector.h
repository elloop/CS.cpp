#ifdef _MSC_VER
__pragma("once")
#else
_Pragma("once")
#endif

#include "inc.h"

NS_BEGIN(elloop)
template <typename T>
class Vector {
public:
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T & const_reference;

	Vector() : size_(0), capacity_(0), data_(nullptr) {}

	// getter.
private:
	T * data_;
	size_t size_;
	size_t capacity_;
};
NS_END(elloop)