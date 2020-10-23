#include "semaphore.h"
#include <nanvix/ulib.h>
#include "mutex.h"

#ifndef WORKAROUND_H
#define WORKAROUND_H
typedef int nanvix_mutex_t;
typedef unsigned int pthread_key_t;

extern void* pthread_getspecific (pthread_key_t key)
{
    uprintf("%d\n",key);
    return NULL;
}

extern void* pthread_setspecific (pthread_key_t key)
{
    uprintf("%d\n",key);
    return NULL;
}

#endif
