#if defined(_MSC_VER)
#pragma once
#else
_Pragma("once")
#endif

#include "inc.h"
#include <string>
#include <ostream>

NS_BEGIN(elloop);

class PeoplePutInConainter {
public:
    //field 'age_' will be initialized after field 'name_' [-Werror,-Wreorder]
  explicit PeoplePutInConainter(const std::string& name = "", int age = 0)
    : name_(name), age_(age) {}
  ~PeoplePutInConainter() {
    LOGD("deleting %s\n", name_.c_str());
  }
  // use for compare.
  bool operator < (const PeoplePutInConainter& other) const {
    if (name_ == other.name_) {
      //return age_ <= other.age_;  // this will cause set contains two same objs.
      return age_ < other.age_;
    }
    else {
      return name_ < other.name_;
    }
  }

  bool operator >(const PeoplePutInConainter& other) const {
    return !(this->operator==(other)) && !(this->operator<(other));
  }

  bool operator == (const PeoplePutInConainter& other) const {
    return (name_ == other.name_) && (age_ == other.age_);
  }
  // default copy semantics.

  // for output
  void acceptVisitor(std::ostream& os) const {
    os << "(" << name_ << ", " << age_ << ")";
  }

private:
  std::string name_;
  int age_;

};

std::ostream& operator<<(std::ostream& os, const PeoplePutInConainter& people);

NS_END(elloop);
