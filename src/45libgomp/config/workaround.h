#include "semaphore.h"
#include <nanvix/ulib.h>
#include "mutex.h"
//#include "../omp.h.in"
#include <nanvix/sys/mutex.h>

#ifndef WORKAROUND_H
#define WORKAROUND_H
typedef struct nanvix_mutex nanvix_mutex_t;
typedef unsigned int pthread_key_t;

//# define __SIZEOF_PTHREAD_MUTEX_T 24
# define __SIZEOF_PTHREAD_ATTR_T 36
# define __SIZEOF_PTHREAD_RWLOCK_T 32
# define __SIZEOF_PTHREAD_BARRIER_T 20
#define __SIZEOF_PTHREAD_MUTEXATTR_T 4
#  define __SIZEOF_PTHREAD_MUTEX_T 40
#define stderr 0
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

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


////pthread types////

typedef union
{
  char __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
  int __align;
} pthread_mutexattr_t;

struct __pthread_cond_s
{
  __extension__ union
  {
    __extension__ unsigned long long int __wseq;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __wseq32;
  };
  __extension__ union
  {
    __extension__ unsigned long long int __g1_start;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __g1_start32;
  };
  unsigned int __g_refs[2];
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};

typedef union
{
  struct __pthread_cond_s __data;
  char __size[10];
 // char __size[__SIZEOF_PTHREAD_COND_T];
  __extension__ long long int __align;
} pthread_cond_t;
typedef union
{
  //char __size[__SIZEOF_PTHREAD_CONDATTR_T];
  char __size[10];
  int __align;
} pthread_condattr_t;
typedef union pthread_attr_t
{
  //char __size[__SIZEOF_PTHREAD_ATTR_T];
  char __size[10];
  long int __align;
} pthread_attr_t;


/////end pthread types

//extern int pthread_attr_init (pthread_attr_t *__attr) __THROW __nonnull ((1));
extern int pthread_attr_init (pthread_attr_t *__attr);

/* Destroy thread attribute *ATTR.  */
//extern int pthread_attr_destroy (pthread_attr_t *__attr)
//     __THROW __nonnull ((1));

extern int pthread_attr_destroy (pthread_attr_t *__attr);

extern int pthread_attr_getstacksize (pthread_attr_t *__attr,int * stacksize);
extern int pthread_attr_setstacksize (pthread_attr_t *__attr,size_t  stacksize);

extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
        const pthread_condattr_t *__restrict __cond_attr);

extern void* pthread_getspecific (pthread_key_t key);

extern void* pthread_setspecific (pthread_key_t key,const void *__pointer);

extern int pthread_key_create (pthread_key_t *__key,
			       void (*__destr_function) (void *));


/* Destroy KEY.  */
extern int pthread_key_delete (pthread_key_t __key);// __THROW;

//gomp_malloc function

//void *
//gomp_malloc (size_t size)
//{
//  void *ret = umalloc (size);
//  if (ret == NULL)
//    uprintf("Out of memory allocating %lu bytes", (unsigned long) size);
//  return ret;
//}

//const int omp_proc_bind_false =0;

//meaning?

//extern int pthread_detach (kthread_t __th) __THROW;
extern int pthread_detach (kthread_t __th);


extern void fputs(char* str, void*);
extern void fputc(char str, void*);
extern int nanvix_mutex_destroy( nanvix_mutex_t *lock);
extern int nanvix_cond_wait(pthread_cond_t *cond, nanvix_mutex_t *mutex);
extern int nanvix_cond_signal(pthread_cond_t *__cond);
extern int nanvix_cond_destroy(pthread_cond_t *__cond);
extern int nanvix_mutex_trylock (nanvix_mutex_t *__mutex);
extern int nanvix_mutexattr_init (pthread_mutexattr_t *__attr);
extern int nanvix_mutexattr_destroy (pthread_mutexattr_t *__attr);
extern int nanvix_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind);


#endif
