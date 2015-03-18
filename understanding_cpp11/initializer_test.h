_Pragma("once")

#include <initializer_list>
#include <vector>
NS_ELLOOP_BEGIN

class InitializerTest {
  public:
    InitializerTest(std::initializer_list<int> iv) {
      auto i=iv.begin();
      while (i != iv.end()) {
        data_.push_back(*i);
        ++i;
      }
    }

  private:
    std::vector<int> data_;
};

NS_ELLOOP_END
