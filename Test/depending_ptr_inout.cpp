#include "common.hpp"
#include "depending_ptr.hpp"
#include <assert.h>
#include <chrono>
#include <iostream>
#include <pthread.h>
#include <thread>

void* thread0(void* unused)
{
    rcutest* p;

    p = new rcutest();
    assert(p);
    p->a = 42;
    rcu_store_release(&gp, p);

    p = new rcutest();
    assert(p);
    p->a = 43;
    rcu_store_release(&gsgp, p);

    return nullptr;
}

depending_ptr<rcutest> thread1_help(depending_ptr<rcutest> p)
{
    if (p)
        assert(p->a == 42);
    return rcu_consume(&gsgp);
}

void* thread1(void* unused)
{
    depending_ptr<rcutest> p;

    // std::this_thread::sleep_for(std::chrono::seconds(1));
    p = rcu_consume(&gp);
    p = thread1_help(p);
    if (p)
        assert(p->a == 43);
    return nullptr;
}

int main(int argc, char** argv)
{
    pthread_t tid0;
    pthread_t tid1;

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
