#include "semaphore.h"
#include <nanvix/ulib.h>
#include "mutex.h"

#ifndef WORKAROUND_H
#define WORKAROUND_H
typedef int nanvix_mutex_t;
typedef unsigned int pthread_key_t;

# define __SIZEOF_PTHREAD_MUTEX_T 24
# define __SIZEOF_PTHREAD_ATTR_T 36
# define __SIZEOF_PTHREAD_RWLOCK_T 32
# define __SIZEOF_PTHREAD_BARRIER_T 20


typedef union pthread_attr_t
{
  char __size[__SIZEOF_PTHREAD_ATTR_T];
  long int __align;
} pthread_attr_t;

extern void* pthread_getspecific (pthread_key_t key)
{
    uprintf("_FUNC_ %d\n",key);
    return NULL;
}

extern void* pthread_setspecific (pthread_key_t key,const void *__pointer)
{
    (void) __pointer;
    uprintf("_FUNC_ %d\n",key);
    return NULL;
}


#define MEMMODEL_SYNC (1<<15)
/* Memory model types for the __atomic* builtins.
   This must match the order in libstdc++-v3/include/bits/atomic_base.h.  */
enum memmodel
{
  MEMMODEL_RELAXED = 0,
  MEMMODEL_CONSUME = 1,
  MEMMODEL_ACQUIRE = 2,
  MEMMODEL_RELEASE = 3,
  MEMMODEL_ACQ_REL = 4,
  MEMMODEL_SEQ_CST = 5,
  MEMMODEL_LAST = 6,
  MEMMODEL_SYNC_ACQUIRE = MEMMODEL_ACQUIRE | MEMMODEL_SYNC,
  MEMMODEL_SYNC_RELEASE = MEMMODEL_RELEASE | MEMMODEL_SYNC,
  MEMMODEL_SYNC_SEQ_CST = MEMMODEL_SEQ_CST | MEMMODEL_SYNC,
  /* Say that all the higher bits are valid target extensions.  */
//  MEMMODEL_MAX = INTTYPE_MAXIMUM (int)
  MEMMODEL_MAX = 0x80000U
};

//gomp_malloc function

void *
gomp_malloc (size_t size)
{
  void *ret = umalloc (size);
  if (ret == NULL)
    uprintf("Out of memory allocating %lu bytes", (unsigned long) size);
  return ret;
}

const int omp_proc_bind_false =0;



#endif
