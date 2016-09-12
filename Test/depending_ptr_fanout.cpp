#include <iostream>
#include <thread>
#include <chrono>
#include <assert.h>
#include <pthread.h>
#include "depending_ptr.hpp"
#include "common.hpp"

void *thread0(void *unused)
{
	rcutest *p;

	p = new rcutest();
	p->a = 42;
	rcu_store_release(&gp, p);
	return nullptr;
}

void thread1_help1(depending_ptr<rcutest> q)
{
	if (q)
		assert(q->a == 42);
}

void thread1_help2(depending_ptr<rcutest> q)
{
	if (q)
		assert(q->a != 43);
}

void *thread1(void *unused)
{
	depending_ptr<rcutest> p;

	// std::this_thread::sleep_for(std::chrono::seconds(1));
	p = rcu_consume(&gp);
	thread1_help1(p);
	thread1_help2(p);
	return nullptr;
}

int main(int argc, char **argv)
{
	pthread_t tid0;
	pthread_t tid1;
	rcutest *p;

	if (pthread_create(&tid0, nullptr, thread0, nullptr)) {
		perror("pthread_create(thread0)");
		return -1;
	}
	if (pthread_create(&tid1, nullptr, thread1, nullptr)) {
		perror("pthread_create(thread1)");
		return -1;
	}

	if (pthread_join(tid0, nullptr)) {
		perror("pthread_join(tid0)");
		return -1;
	}
	if (pthread_join(tid1, nullptr)) {
		perror("pthread_join(tid1)");
		return -1;
	}

	return 0;
}
