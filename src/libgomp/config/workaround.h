#include "semaphore.h"
#include <nanvix/ulib.h>
#include "mutex.h"

#ifndef WORKAROUND_H
#define WORKAROUND_H
typedef int nanvix_mutex_t;
typedef unsigned int pthread_key_t;

extern void* pthread_getspecific (pthread_key_t key)
{
    uprintf("_FUNC_ %d\n",key);
    return NULL;
}

extern void* pthread_setspecific (pthread_key_t key)
{
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

#endif
