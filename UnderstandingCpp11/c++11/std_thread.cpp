#include "std_thread.h"
#include <memory>
#include <thread>
NS_BEGIN(elloop)
NS_BEGIN(thread_test)

void taskThreadFunc(std::shared_ptr<Task> pTask) {
	pln("threading running...");
	psln(pTask->_id);
	psln(pTask->_size);
	pln("threading terminating...");
}

TEST(ThreadTest, PassArguments) {

	pcln("ThreadTest --> PassArguments");
	using std::shared_ptr;
	shared_ptr<Task> pTask(new Task);
	pTask->_id = 10;
	pTask->_size = 0;
	using std::thread;
	thread t1(taskThreadFunc, pTask);
	t1.join();
}

NS_END(thread_test)
NS_END(elloop)