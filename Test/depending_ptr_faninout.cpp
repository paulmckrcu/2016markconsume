#include <iostream>
#include <thread>
#include <chrono>
#include <assert.h>
#include <pthread.h>
#include "depending_ptr.hpp"
#include "common.hpp"

void *thread0(void *unused)
{
	struct rcutest *p;
	struct rcutest1 *p1;

	p = (struct rcutest *)malloc(sizeof(*p));
	assert(p);
	p->a = 42;
	p->b = 43;
	rcu_store_release(&gp, p);

	p1 = (struct rcutest1 *)malloc(sizeof(*p1));
	assert(p1);
	p1->a = 41;
	p1->rt.a = 42;
	p1->rt.b = 43;
	rcu_store_release(&g1p, p1);

	return NULL;
}

void thread1a_help(depending_ptr<struct rcutest> q)
{
	assert(q->a == 42);
}

void thread1b_help(depending_ptr<struct rcutest> q)
{
	assert(q->b == 43);
}

void thread1_help(depending_ptr<struct rcutest> q)
{
	if (q) {
		thread1a_help(q);
		thread1b_help(q);
	}
}

void *thread1(void *unused)
{
	depending_ptr<struct rcutest> p;

	// std::this_thread::sleep_for(std::chrono::seconds(1));
	p = rcu_consume(&gp);
	thread1_help(p);
	return NULL;
}

void *thread2(void *unused)
{
	depending_ptr<struct rcutest1> p1;

	// std::this_thread::sleep_for(std::chrono::seconds(1));
	p1 = rcu_consume(&g1p);
	thread1_help(&p1->rt);
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t tid0;
	pthread_t tid1;
	pthread_t tid2;
	struct rcutest *p;

	if (pthread_create(&tid0, NULL, thread0, NULL)) {
		perror("pthread_create(thread0)");
		return(-1);
	}
	if (pthread_create(&tid1, NULL, thread1, NULL)) {
		perror("pthread_create(thread1)");
		return(-1);
	}
	if (pthread_create(&tid2, NULL, thread1, NULL)) {
		perror("pthread_create(thread2)");
		return(-1);
	}

	if (pthread_join(tid0, NULL)) {
		perror("pthread_join(tid0)");
		return(-1);
	}
	if (pthread_join(tid1, NULL)) {
		perror("pthread_join(tid1)");
		return(-1);
	}
	if (pthread_join(tid2, NULL)) {
		perror("pthread_join(tid2)");
		return(-1);
	}

	return 0;
}
