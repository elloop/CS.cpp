#include "stash.h"
#include "string-util.h"
using namespace std;
Stash::Stash () : head ( 0 ) { }

Stash::~Stash() {}

void Stash::Link::initialize ( void * data, Link * link ) {
	Stash::Link::data = data;
	Stash::Link::link = link;
}

void Stash::push ( void * data ) {
	Link * link = new Link();
	link->initialize ( data, head );
	head = link;
}

void * Stash::peek() {
	if ( !head ) {
		return 0;
	}
	return head->data;
}

void * Stash::pop() {

	if ( !head ) {
		return 0;
	}
	Link * oldHead = head;
	head = oldHead->link;
	void * data = oldHead->data;
	delete oldHead;
	return data;
}

bool Stash::empty() {
	return ( head == 0 );
}

void Stash::cleanup() {
	if ( head ) {
		pln ( "not clean!" );
	}
	pln ( "clean up!" );
}

