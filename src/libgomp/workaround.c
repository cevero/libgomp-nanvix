#include "config/nanvix/workaround.h"
#include <nanvix/sys/mutex.h>



///// pthread functions ///////
void* tls[THREAD_MAX] = {NULL,};

void* pthread_getspecific (pthread_key_t key)
{
//    uprintf("%s %d\n",__func__,key);
    
    return tls[key];
}

void* pthread_setspecific (pthread_key_t key,const void *__pointer)
{
 //   uprintf("%s %d\n",__func__,key);
    tls[key] = &__pointer;

}
extern int pthread_attr_destroy (pthread_attr_t *__attr)
{
    (void) __attr;
    uprintf("%s \n",__func__);
    return 0;
}

int pthread_attr_getstacksize (pthread_attr_t *__attr,int * stacksize)
{
    (void) __attr;
    (void) stacksize;
    uprintf("%s \n",__func__);
    return 0;
}
int pthread_attr_setstacksize (pthread_attr_t *__attr,size_t  stacksize)
{
    (void) __attr;
    (void) stacksize;
    uprintf("%s \n",__func__);
    return 0;
}
int  pthread_key_create (pthread_key_t * key,void (*destructor)(void*))
{
    *key=kthread_self();
    return 0;
}
extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
			      const pthread_condattr_t *__restrict __cond_attr)
{
    (void) __cond;
    (void) __cond_attr;
    uprintf("%s \n",__func__);
    return 0;
}
extern int pthread_detach (kthread_t __th)
{
    (void) __th;
    uprintf("%s \n",__func__);
    return 0;
}

extern void fputs(char* str, void* var)
{
    (void) str;
    (void) var;
    uprintf("%s \n",__func__);
}
extern void fputc(char str, void* c)
{
    (void) str;
    (void) c;
    uprintf("%s \n",__func__);
}

int pthread_key_delete (pthread_key_t __key)// __THROW;
{
    (void) __key;
    uprintf("%s \n",__func__);
    return 0;
}

////NANVIX DEFINITIONS//////


inline int nanvix_mutex_destroy(nanvix_mutex_t *lock) {return 0;}

int nanvix_cond_wait(pthread_cond_t *cond, nanvix_mutex_t *mutex)
{

    (void) cond;
    (void) mutex;
    uprintf("%s \n",__func__);
}

int nanvix_cond_signal(pthread_cond_t *__cond)
{
    
    (void) __cond;
    uprintf("%s \n",__func__);
    return 0;
}

int nanvix_cond_destroy(pthread_cond_t *__cond)

{
    (void) __cond;
    uprintf("%s \n",__func__);
    return 0;
}

int nanvix_mutex_trylock(nanvix_mutex_t *__mutex)
{
    (void) __mutex;
    uprintf("%s \n",__func__);
    return 0;
}

int nanvix_mutexattr_init (pthread_mutexattr_t *__attr)
{
    (void) __attr;
    uprintf("%s \n",__func__);
    return 0;
}

int nanvix_mutexattr_destroy (pthread_mutexattr_t *__attr)
{
    (void) __attr;
    uprintf("%s \n",__func__);
    return 0;
}


int nanvix_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
{
    (void) __attr;
    (void) __kind;
    uprintf("%s \n",__func__);
    return 0;
}

int pthread_attr_init (pthread_attr_t *__attr)
{

    (void) __attr;
    uprintf("%s \n",__func__);
    return 0;

}

