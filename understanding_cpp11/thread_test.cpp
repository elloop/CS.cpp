#include "thread_test.h"

#include <unistd.h>
#include <atomic>
#include <thread>
#include <pthread.h>

USING_NS_STD;
USING_NS_ELLOOP;

void testSpinLock();

//---------------------------------- enter ------------------------------------
ThreadTest* ThreadTest::run() {

  testSpinLock();

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
    LOG("waiting from thread %d\n", n);
  }
  LOG("thread %d starts working\n", n);
}

void releaseWaiting(int n) {
  LOG("thread %d going to work\n", n);
  lock.clear();
  LOG("thread %d starts working\n", n);

}

void testSpinLock() {
  lock.test_and_set();
  thread t1(threadWaiting, 1);
  thread t2(releaseWaiting, 2);

  t1.join(); // t1 is waiting for t2 to release lock.
  usleep(100);
  t2.join();
}

