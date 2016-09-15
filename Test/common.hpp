#include <errno.h>
#include <pthread.h>

typedef pthread_mutex_t spinlock_t;

static __inline__ void spin_lock_init(spinlock_t* sp)
{
    int ret;

retry:
    ret = pthread_mutex_init(sp, nullptr);
    if (ret) {
        if (ret == EINTR)
            goto retry;
        std::cerr << "spin_lock_init:pthread_mutex_init " << ret;
        abort();
    }
}

static __inline__ void spin_lock(spinlock_t* sp)
{
    if (pthread_mutex_lock(sp) != 0) {
        perror("spin_lock:pthread_mutex_lock");
        abort();
    }
}

static __inline__ void spin_unlock(spinlock_t* sp)
{
    if (pthread_mutex_unlock(sp) != 0) {
        perror("spin_unlock:pthread_mutex_unlock");
        abort();
    }
}

struct rcutest {
    int a;
    int b;
    int c;
    spinlock_t lock;
};

struct rcutest1 {
    int a;
    rcutest rt;
};

std::atomic<rcutest*> gp;
std::atomic<rcutest1*> g1p;
std::atomic<int*> gip;
rcutest* gslp; /* Global scope, local usage. */
std::atomic<rcutest*> gsgp;
