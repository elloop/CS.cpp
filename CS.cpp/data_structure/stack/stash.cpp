#include "stash.h"
#include "inc.h"

NS_BEGIN( elloop )


#ifdef _MSC_VER
void Stash::push( void * data ) _NOEXCEPT{
  head_ = new Link( data, head_ );
}
#else
void Stash::push( void * data ) noexcept {
  head_ = new Link( data, head_ );
}
#endif // _MSC_VER


void * Stash::peek() {
  if ( nullptr == head_ ) {
    return nullptr;
  }
  return head_->data_;
}

void * Stash::pop() {

  if ( head_ == nullptr) {
    return nullptr;
  }
  Link * oldHead = head_;
  head_ = oldHead->link_;
  void * data = oldHead->data_;
  delete oldHead;
  oldHead = nullptr;
  return data;
}

bool Stash::empty() {
  return ( head_ == nullptr );
}

void Stash::cleanup() {
  auto temp = head_;
  while ( temp != nullptr ) {
    head_ = temp->link_;
    delete temp;
    temp = head_;
  }
}

NS_END( elloop )