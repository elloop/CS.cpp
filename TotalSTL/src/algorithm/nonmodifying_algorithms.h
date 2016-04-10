#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif

#include "inc.h"
#include "stl_headers.h"
NS_BEGIN(elloop)

//#All Algorithms
//- for_each
// 
//```c++
//template<class InputIterator, class Function>
//Function for_each(InputIterator first, InputIterator last, Function fn) {
//  while ( first != last ) {
//    fn(*first);
//    ++first;
//  }
//  return fn;      // or, since C++11: return move(fn);
//}
//```
//
//- count
//
//```c++
//template <class InputIterator, class T>
//typename iterator_traits<InputIterator>::difference_type
//count(InputIterator first, InputIterator last, const T& val) {
//  typename iterator_traits<InputIterator>::difference_type ret = 0;
//  while ( first != last ) {
//    if ( *first == val ) ++ret;
//    ++first;
//  }
//  return ret;
//}
//```
//- min_element
//
//```c++
//template <class ForwardIterator>
//ForwardIterator min_element(ForwardIterator first, ForwardIterator last) {
//  if ( first == last ) return last;
//  ForwardIterator smallest = first;
//
//  while ( ++first != last )
//  if ( *first < *smallest )    // or: if (comp(*first,*smallest)) for version (2)
//    smallest = first;
//  return smallest;
//}
//```
//
//- find
//
//```c++
//template<class InputIterator, class T>
//InputIterator find(InputIterator first, InputIterator last, const T& val) {
//  while ( first != last ) {
//    if ( *first == val ) return first;
//    ++first;
//  }
//  return last;
//}
//```
// 关联式容器自带的find()是O(logn).
//
//- find_first_of
//
//``c++
//template<class InputIterator, class ForwardIterator>
//InputIterator find_first_of(InputIterator first1, InputIterator last1,
//  ForwardIterator first2, ForwardIterator last2) {
//  while ( first1 != last1 ) {
//    for ( ForwardIterator it = first2; it != last2; ++it ) {
//      if ( *it == *first1 )          // or: if (pred(*it,*first)) for version (2)
//        return first1;
//    }
//    ++first1;
//  }
//  return last1;
//}
//```
//


NS_END(elloop)