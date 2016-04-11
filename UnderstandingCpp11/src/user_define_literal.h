#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif
#include "inc.h"

NS_ELLOOP_BEGIN

class Person {
public:
    Person(const char * name, int age) : age_(age) {
        setName(name);
    }
    void setName(const char * name) {
        if (name == nullptr || name == name_) {
            return;
        }
        memcpy(name_, name, 20 * sizeof(char));
        name_[19] = 0;
    }
    const char * name() {
        return name_;
    }
    int age() {
        return age_;
    }
	void setAge(int age) {
		age_ = age > 0 ? age : 0;
	}
private:
    char name_[20];
    int age_;
};

void takePersion(Person p);

NS_ELLOOP_END