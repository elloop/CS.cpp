#include "modifying_algorithms.h"

template <typename T>
class AddVal {
public:
  AddVal(const T& val) : val_(val) {}

  void operator() (T & val) {
    val += val_;
  }

private:
  T val_;
};

class MeanValue {
public:
  MeanValue() : count_(0), sum_(0) {}
  void operator() (int val) {
    sum_ += val;
    ++count_;
  }

  operator double() {
    if (count_ <= 0) {
      return 0;
    }
    return sum_ / count_;
  }
private:
  double sum_;
  int count_;
};

NS_BEGIN(elloop)
TEST(ModifyingAlgorithm, ForEach) {
  pcln("for_each");

  using std::vector;

  // for_each
  vector<int> coll;
  insertElements(coll, 1, 10);
  print_container(coll, "coll: ");  // coll: 1 2 3 4 5 6 7 8 9 10

  pcln("changing coll use lambda");
  for_each(coll.begin(), coll.end(),
    [](int& elem) {
      elem += 50;
    }
  );
  print_container(coll, "coll: ");  //coll: 51 52 53 54 55 56 57 58 59 60


  pcln("changing coll use Functor");
  for_each(coll.begin(), coll.end(),
    AddVal<int>(50));
  print_container(coll, "coll: ");//coll: 101 102 103 104 105 106 107 108 109 110

  pcln("use return value of for_each");
  vector<int> coll2{ 1, 2, 3, 4, 5 };
  print_container(coll2, "coll2:");   // coll2: 1 2 3 4 5

  //for_each returns a copy of MeanValue(), then use operator double().
  // same with:
  // MeanValue mv = for_each(coll2.begin(), coll2.end(), MeanValue());
  // double meanValue = mv;
  double meanValue = for_each(coll2.begin(), coll2.end(),
    MeanValue());                     
  psln(meanValue);                    // meanValue = 3
  // validate result using numeric.
  using std::accumulate;
  double sum(0);
  sum = accumulate(coll2.begin(), coll2.end(), sum);
  EXPECT_EQ(sum / coll2.size(), meanValue);

}



NS_END(elloop)