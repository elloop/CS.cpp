#include "stash.h"
#include "inc.h"
USING_NS_ELLOOP;

Stash::Stash () : head_ ( 0 ) { }

Stash::~Stash() {
    cleanup();
}

void Stash::Link::initialize ( void * data, Link * link ) {
	Stash::Link::data = data;
	Stash::Link::link = link;
}

void Stash::push ( void * data ) {
	Link * link = new Link();
	link->initialize ( data, head_ );
	head_ = link;
}

void * Stash::peek() {
	if ( !head_ ) {
		return 0;
	}
	return head_->data;
}

void * Stash::pop() {

	if ( !head_ ) {
		return 0;
	}
	Link * oldHead = head_;
	head_ = oldHead->link;
	void * data = oldHead->data;
	delete oldHead;
    oldHead = 0;
	return data;
}

bool Stash::empty() {
	return ( head_ == 0 );
}

void Stash::cleanup() {
    Link * temp = head_;
    while (temp != 0) {
        head_ = temp->link;
        delete temp;
        temp = head_;
    }
}

