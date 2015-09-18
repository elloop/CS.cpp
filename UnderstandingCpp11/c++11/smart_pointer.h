#ifdef _MSC_VER
#pragma once
#else
_Pragma( "once" )
#endif
#include "inc.h"
#include <memory>

NS_BEGIN( elloop )
NS_BEGIN( smart_pointer )

// old smart pointer auto_ptr<T> is depreciated.

// In cpp11, 
// 1. unique_ptr<T> substitutes auto_ptr<T>.
// it only supports move assignment.(copy ctr and copy assignment are deleted).
// does not support pointer arithmetics.
// see http://www.cplusplus.com/reference/memory/unique_ptr/?kw=unique_ptr for
// more information about unique_ptr<T>.

// 2. shared_ptr<T> is reference-counting pointer. they shared the pointer.
// Objects of shared_ptr types have the ability of taking ownership of 
// a pointer and share that ownership: once they take ownership, the group 
// of owners of a pointer become responsible for its deletion when the last 
// one of them releases that ownership.
// !!!Notice:
// shared_ptr objects can only share ownership by copying their value: If two 
// shared_ptr are constructed(or made) from the same(non - shared_ptr) pointer
// , they will both be owning the pointer without sharing it, causing potential 
// access problems when one of them releases it(deleting its managed object) 
// and leaving the other pointing to an invalid location.
// Other features like aliasing, deleter,
// see: http://www.cplusplus.com/reference/memory/shared_ptr/?kw=shared_ptr

// 3. weak_ptr<T> is able to share pointers with shared_ptr objects without 
// owning them. It can be used to test validity of shared_ptr<T>. see function
// checkValidity() below.

// they are included in header <memory>.

//--------------------------- begin test ---------------------------

// following using declarations are aim at typing less. 
template <typename T>
using u_ptr = std::unique_ptr<T>;

template <typename T>
using s_ptr = std::shared_ptr<T>;

template <typename T>
using w_ptr = std::weak_ptr<T>;

// use weak_ptr to check validity of shared_ptr it shared.
template<typename T>
bool checkValidity(w_ptr<T>& wp) {
	s_ptr<T> sp = wp.lock();
	return (sp != nullptr);
}

class Dog {
public:
    Dog(const char * name) : name_(name) {
		LOGD("dog %s come!\n", name_.c_str());
    }
    ~Dog() {
		LOGD("dog %s is gone!\n", name_.c_str());
    }
	Dog(const Dog& other) {
		LOGD("dog %s copied!\n", name_.c_str());
	}
	Dog(Dog&& other) {
		LOGD("dog %s moved!\n", name_.c_str());
	}
    const std::string & name() const {
        return name_; 
    }
private:
    std::string name_;
};

std::ostream& operator << (std::ostream & os, const Dog & dog);




NS_END(smart_pointer )
NS_END(elloop )
