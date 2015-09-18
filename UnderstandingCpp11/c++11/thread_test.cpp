#include "thread_test.h"

#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <atomic>
#include <cassert>
#include <thread>
//#include <pthread.h>

USING_NS_STD;

NS_ELLOOP_BEGIN

void testSpinLock();
void testMemoryOrderWithoutOrderLimit();
void testMemoryOrderRelax();
void testReleaseAcquire();
void testReleaseConsume();

//---------------------------------- enter ------------------------------------
ThreadTest* ThreadTest::run() {

  int i {10};
  while (i-- > 0) {
    testReleaseConsume();
    LOGD("end of %d turn\n", i+1);
    sleep(2);
  }

  // testReleaseAcquire();

  // testMemoryOrderRelax();

  /* int i {0}; */
  // for ( i=0; i < 100; ++i) {
    // testMemoryOrderWithoutOrderLimit();
    // // sleep(1);
    // // usleep(2000000);
  // }

  // testSpinLock();

  // testAtomic();

  // testWithCpp11();

  // testWithPthread();

  return this;
}

//----------------------------------------------------------------------
// use pthread.
//----------------------------------------------------------------------
static long long total = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* func(void*) {
  long long i;
  for ( i=0; i < 10000LL; ++i) {
    // pthread_mutex_lock(&m);
    total += 1;
    // pthread_mutex_unlock(&m);
  }
}

void ThreadTest::testWithPthread() {
  pthread_t t1, t2;
  if (pthread_create(&t1, nullptr, &func, nullptr)) {
    throw; 
  }

  if (pthread_create(&t2, nullptr, &func, nullptr)) {
    throw; 
  }
  pthread_join(t1, nullptr);
  pthread_join(t2, nullptr);

  psln(total);
}

//----------------------------------------------------------------------
// use std::thread.
//----------------------------------------------------------------------
atomic_llong atomic_total {0};

void funcForThread(int) {
  for ( long long i = 0; i < 10000LL; ++i ) {
    atomic_total += 1;
  }
}
  
void ThreadTest::testWithCpp11() {
  thread t1(funcForThread, 0);
  thread t2(funcForThread, 0);

  t1.join();
  t2.join();

  psln(atomic_total);
}

//----------------------------------------------------------------------
// test atomic: atomic<T> is noncopyable.
//----------------------------------------------------------------------
void ThreadTest::testAtomic() {
  // common(atomic-integral-type and atomic<intergral-type>) operation:
  // load, store, exchange, compare_exchange_weak + strong, fetch_add(+=), fetch_sub(-=), 
  //  fetch_and(&=), fetch_xor(^=), ++, --.
  // test_and_set, clear for atomic_flag.
  // fetch_or(|=),

  atomic<int> a_i {100};
  psln(a_i);
  int i {a_i};
  psln(i);

  atomic<int> a_i2 {i};
  psln(a_i2);
  // atomic<int> a_i_copy {a_i}; // error: noncopyable.

  psln(a_i.load());
  a_i.store(190);
  psln(a_i.load());

  atomic_flag flag;
  psln(flag.test_and_set());
  flag.clear();
  psln(flag.test_and_set());
}

//----------------------------------------------------------------------
// a spinlock using atomic_flag.
//----------------------------------------------------------------------
atomic_flag lock = ATOMIC_FLAG_INIT;

void threadWaiting(int n) {
  while (lock.test_and_set(memory_order_acquire)) {
    LOGD("waiting from thread %d\n", n);
  }
  LOGD("thread %d starts working\n", n);
}

void releaseWaiting(int n) {
  LOGD("thread %d going to work\n", n);
  lock.clear();
  LOGD("thread %d starts working\n", n);

}

void testSpinLock() {
  lock.test_and_set();
  thread t1(threadWaiting, 1);
  thread t2(releaseWaiting, 2);

  t1.join(); // t1 is waiting for t2 to release lock.
  usleep(100);
  t2.join();
}

//----------------------------------------------------------------------
// sequential consistent assumption.(顺序一致性假设)
// strong ordered: x86...
// weak ordered:  powerPC...
// in cpp11, default atomic operation's memory_order is memory_order_seq_cst.
//----------------------------------------------------------------------
atomic<int> ta {0};
atomic<int> tb {0};
void setValue(int) {
  int t = 1;
  ta = t;   // equal to ta.store(t, memory_order_seq_cst);
  tb = 2;   // equal to tb.store(t, memory_order_seq_cst);
  // memory_order_seq_cst restrict cpu to optimize instructions order. even insert memory barrirers into asm or machine codes.
}

int observe(int) {
  LOGD("observe: a, b =(%d, %d)\n", ta.load(), tb.load());
}

void testMemoryOrderWithoutOrderLimit() {
  thread t1(setValue, 0);
  thread t2(observe, 0);

  t1.join();
  t2.join();

  // LOGD("final a,b = (%d, %d)\n", ta.load(), tb.load());
}

//----------------------------------------------------------------------
// relaxed memory order.
//----------------------------------------------------------------------
void setValueRelax(int) {
  int t = 1;
  ta.store(t, memory_order_relaxed);
  tb.store(2, memory_order_relaxed);  // this may execute before ta.store().
}

int observeWait(int) {
  while (tb.load(memory_order_relaxed) != 2) {
    // LOGD("waiting tb == 2\n");
    // waiting...
  }
  LOGD("a now is: %d\n", ta.load(memory_order_relaxed)); // ta maybe == 0 in some hardware platform.
}

void testMemoryOrderRelax() {
  thread t1(setValueRelax, 0);
  thread t2(observeWait, 0);

  t1.join();
  t2.join();
}

//----------------------------------------------------------------------
// release-acquire.
//----------------------------------------------------------------------
void setValueReleaseAcquire(int) {
  int t =1;
  ta.store(t, memory_order_relaxed);
  tb.store(2, memory_order_release);  // this will not execute until all atomic done. that is to say, when execute this, ta must be t(1).
}

int observeWaitAcquire(int) {
  while (tb.load(memory_order_acquire) != 2) {  // all other atomic will not execute until this operation is done.
    LOGD("memory_order_acquire waiting in tb == 2\n");
    // waiting...
  }
  LOGD("a now is: %d\n", ta.load(memory_order_relaxed)); // ta can't be 0 , because of the memory_order_acquire in tb.load().
}

void testReleaseAcquire() {
  thread t1(setValueReleaseAcquire, 0);
  thread t2(observeWaitAcquire, 0);

  t1.join();
  t2.join();

}
//----------------------------------------------------------------------
// release-consume. less limit than release-acquire.
//----------------------------------------------------------------------
atomic<string*> ptr;
atomic<int> data;

void produce() {
  string *p = new string("hello");
  data.store(42, memory_order_relaxed);
  ptr.store(p, memory_order_release);
}

void consume() {
  string * p2;
  // memory_order_consume only require the same type atomic operation is executed after it, data.load() may be execute before prt.load().
  while (!(p2 = ptr.load(memory_order_consume))) {
    LOGD("waiting ptr not null use memory_order_consume\n");
  }

  assert(*p2 == "hello");   // always equal.
  assert(data.load(memory_order_relaxed) == 42);  // may fail.
}

void testReleaseConsume() {
  thread t1(produce);
  thread t2(consume);

  t1.join();
  t2.join();
}

NS_ELLOOP_END