#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif
#include "inc.h"

NS_ELLOOP_BEGIN

namespace union_test {

    // union in cpp11: allow members which is not pod.
    // 
    //--------------------------- basic ---------------------------
    struct NonPod {
        NonPod() {

        }
    };

    struct Pod {};

    union ContainNonPod {
        Pod p;
        //NonPod np;  // error in vs2013 !!! not standard cpp11 compiler.
        int id;
        char name[10];
    };

    //union ContainString {
    //std::string s;

    //};


#ifdef _MSC_VER

#else
    union WithString {
        std::string s;
        int id;
    };
    // WithString ws;  // error: call to implicitly-deleted default constructor of 'elloop::union_test::WithString'
    // error: string is not pod, so WithString' s default constructor
    // is deleted.

    // fix
    union WithString2 {
        std::string s;
        int id;
    public:
        WithString2() {
            // placement new.
            new (&s) std::string();
        }
        ~WithString2() {
            using namespace std; //fix  error: expected the class name after '~' to name a destructor
            s.~string();
        }
    };

    // anonymous union. p.109
    class Person {
    public:
        Person(int id, int age) : age_(age), id_(id){
            (void)age_;
            (void)id_;
        }
    private:
        int age_;
        int id_;
    };

    class Singer {
    public:
        enum Type { Person, Gender, Name};
        Singer(int id, int age) : p(id, age) {
            t = Person; 
        }
        Singer(const char * sname) {
            if (sname != nullptr) {
                memcpy(name, sname, 9 * sizeof(char));
                name[9] = 0;
            }
            else {
                strcpy(name, "noname");
                t = Name;
            }
        }
        Singer(char sgender) : gender(sgender) { 
            t = Gender; 
        }
    private:
        Type t;
        union {
            // Person p;
            class Person p;
            char name[10];
            char gender;
        };
    };
#endif

    class UnlimitedUnionTest {
    public:
    };

} // end of namespace union_test.

NS_ELLOOP_END
