#include "config/workaround.h"
#include <nanvix/sys/mutex.h>



///// pthread functions ///////


void* pthread_getspecific (pthread_key_t key)
{
    uprintf("_FUNC_ %d\n",key);
    return NULL;
}

void* pthread_setspecific (pthread_key_t key,const void *__pointer)
{
    (void) __pointer;
    uprintf("_FUNC_ %d\n",key);
    return NULL;
}
extern int pthread_attr_destroy (pthread_attr_t *__attr)
{
    (void) __attr;
    uprintf("_FUNC_ \n");
    return 0;
}

int pthread_attr_getstacksize (pthread_attr_t *__attr,int * stacksize)
{
    (void) __attr;
    (void) stacksize;
    uprintf("_FUNC_ \n");
    return 0;
}
int pthread_attr_setstacksize (pthread_attr_t *__attr,size_t  stacksize)
{
    (void) __attr;
    (void) stacksize;
    uprintf("_FUNC_ \n");
    return 0;
}
extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
			      const pthread_condattr_t *__restrict __cond_attr)
{
    (void) __cond;
    (void) __cond_attr;
    uprintf("_FUNC_ \n");
    return 0;
}
extern int pthread_detach (kthread_t __th)
{
    (void) __th;
    uprintf("_FUNC_ \n");
    return 0;
}

extern void fputs(char* str, void* var)
{
    (void) str;
    (void) var;
    uprintf("_FUNC_ \n");
}
extern void fputc(char str, void* c)
{
    (void) str;
    (void) c;
    uprintf("_FUNC_ \n");
}

int pthread_key_delete (pthread_key_t __key)// __THROW;
{
    (void) __key;
    uprintf("_FUNC_ \n");
    return 0;
}

////NANVIX DEFINITIONS//////


inline int nanvix_mutex_destroy(nanvix_mutex_t *lock) {return 0;}

int nanvix_cond_wait(pthread_cond_t *cond, nanvix_mutex_t *mutex)
{

    (void) cond;
    (void) mutex;
    uprintf("_FUNC_ \n");
}

int nanvix_cond_signal(pthread_cond_t *__cond)
{
    (void) __cond;
    uprintf("_FUNC_ \n");
    return 0;
}

int nanvix_cond_destroy(pthread_cond_t *__cond)

{
    (void) __cond;
    uprintf("_FUNC_ \n");
    return 0;
}

int nanvix_mutex_trylock(nanvix_mutex_t *__mutex)
{
    (void) __mutex;
    uprintf("_FUNC_ \n");
    return 0;
}

int nanvix_mutexattr_init (pthread_mutexattr_t *__attr)
{
    (void) __attr;
    uprintf("_FUNC_ \n");
    return 0;
}

int nanvix_mutexattr_destroy (pthread_mutexattr_t *__attr)
{
    (void) __attr;
    uprintf("_FUNC_ \n");
    return 0;
}


int nanvix_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
{
    (void) __attr;
    (void) __kind;
    uprintf("_FUNC_ \n");
    return 0;
}
