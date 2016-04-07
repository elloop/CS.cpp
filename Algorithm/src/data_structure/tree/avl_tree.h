_Pragma( "once" )

#include "inc.h"

NS_BEGIN( elloop )

template <typename T>
class AvlNode {
public:
  AvlNode( const T& value ) :
      value_( value ), 
      left_( nullptr ), 
      right_( nullptr ), 
      height_( 1 )
  {}

  ~AvlNode() {}

  size_t height() const {
    return std::max( left_->height(), right_->height() ) + 1;
  }

  // disable copy and move semantics.
  AvlNode( const AvlNode & other )              = delete;
  AvlNode( AvlNode&& other )                    = delete;
  AvlNode& operator=( const AvlNode & other )   = delete;
private:
  T         value_;
  AvlNode*  left_;
  AvlNode*  right_;
  size_t    height_;
};

template <typename T>
class AvlTree {
public:

  typedef AvlNode<T> Node;

  AvlTree( Node* root = nullptr ) :
      root_( root ), 
      nodeCounts_( root_ == nullptr ? 0 : 1 ) 
  {}

  size_t height() const {
    return ( root_ == nullptr ) ? 0 : root_->height();
  }

private:
  Node*     root_;
  size_t    nodeCounts_;

};

NS_END( elloop )