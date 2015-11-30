#include "gtest/gtest.h"
#include "inc.h"
#include <functional>
#include <type_traits>
#include <fstream>
#include <string>
#include <streambuf>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;

<<<<<<< HEAD
BEGIN_TEST(IteratorTest, AdapterBackInserter, @)
=======
BEGIN_TEST(IteratorTest, AdapterBackInserter, @);
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340
  //pcln("IteratorTest --> AdapterBackInserter");
  //vector<string> vs;
  //pln("input some strings(one per line), ctrl-z to terminate input:");
  //// read strings from standard input.
  //copy(istream_iterator<string>(cin), istream_iterator<string>(), 
  //  back_inserter(vs));

  //// don't do this, error.
  ////copy(istream_iterator<string>(cin), istream_iterator<string>(), vs.begin());

  //// sort
  //sort(vs.begin(), vs.end(), greater<string>());

  //// output by line.
  //copy(vs.begin(), vs.end(), ostream_iterator<string>(cout, "\n"));
<<<<<<< HEAD
END_TEST

BEGIN_TEST(IteratorTest, ISTREAMBUF_ITERATORTEST, @)
=======
END_TEST;


BEGIN_TEST(IteratorTest, ISTREAMBUF_ITERATORTEST, @);
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340

  pcln("IteratorTest --> AdapterBackInserter");
  ifstream in("iterator_test.h", ios::in);
  // read char by char from file stream.
  string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

  // see effective stl item6 for reason why following codes don't work.
  //string data(istreambuf_iterator<char>(in), istreambuf_iterator<char>());

  pln(data);
  in.close();
<<<<<<< HEAD
END_TEST
=======

END_TEST;
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340

NS_END(elloop);