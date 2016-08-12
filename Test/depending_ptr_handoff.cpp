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

	p = (struct rcutest *)malloc(sizeof(*p));
	assert(p);
	p->a = 42;
	assert(p->a != 43);
	rcu_store_release(&gp, p);
	return NULL;
}

void *thread1(void *unused)
{
	depending_ptr<struct rcutest> p;

	// std::this_thread::sleep_for(std::chrono::seconds(1));
	p = rcu_consume(&gp);
	if (p) {
		assert(p->a == 42);
		spin_lock(&p->lock);
		p = std::kill_dependency(p);
		p->a++;
		spin_unlock(&p->lock);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t tid0;
	pthread_t tid1;
	struct rcutest *p;

	if (pthread_create(&tid0, NULL, thread0, NULL)) {
		perror("pthread_create(thread0)");
		return(-1);
	}
	if (pthread_create(&tid1, NULL, thread1, NULL)) {
		perror("pthread_create(thread1)");
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

	p = gp.load();
	std::cout << "p->a = " << p->a << "\n";
	assert(p->a == 42 || p->a == 43);

	return 0;
}
