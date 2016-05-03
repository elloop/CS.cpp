/*
 * 用法：
 * 1. 创建一个stash
 * 2. 把要存放的指针放入栈顶
 * 3. 返回栈顶指针，同时弹栈
 * 4. 去栈顶元素，不弹栈
 * 5. 清空栈
 * =====================================================================================
 *        Class:  Stash
 *  Description:  a container simulate a link stack
 * =====================================================================================
 */
#ifdef _MSC_VER
__pragma( "once" )
#else
_Pragma( "once" )
#endif

#include "inc.h"

NS_BEGIN( elloop )

// Stash cleans itself, but it's User's duty to clean up data_ in Link.
class Stash {
public:
  Stash() : head_( nullptr ) {}
  ~Stash() { cleanup(); }

  // disallow copy and move and copy assignment.
  Stash( const Stash& other ) = delete;
  Stash( Stash&& other ) = delete;
  Stash& operator=(const Stash& other ) =  delete;

  void* pop();
  void* peek();
#ifdef _MSC_VER
  void push( void* data ) _NOEXCEPT;
#else
  void push( void* data ) noexcept;
#endif // _MSC_VER

  void cleanup();
  bool empty();

protected:
  class Link {
  public:
    Link( void* data, Link* link ) : data_( data ), link_( link ) {}
    void* data_;
    Link* link_;
  }* head_;

}; /* -----  end of class Stash  ----- */

NS_END( elloop )
