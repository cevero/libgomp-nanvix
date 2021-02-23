//#include "config/nanvix/workaround.h"
#include <nanvix/sys/mutex.h>
#include "libgomp.h"


///// pthread functions ///////
//void* pthread_getspecific (pthread_key_t key)
//{
//    //uprintf("%s numero_thread = %d \n",__func__,tls_omp[key]->data->ts.team_id);
//    return tls_omp[key]->data;
//}

//void pthread_setspecific (pthread_key_t  key, void *__pointer)
//{
//    //*tls_omp[key]->key = key;
//    tls_omp[key]->data = __pointer;
//}
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
//int  pthread_key_create (pthread_key_t * key,void (*destructor)(void*))
//{
//    
//    *tls_omp[(int)*key]->key=kthread_self();
//
//    return 0;
//}
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


inline int nanvix_mutex_destroy(nanvix_mutex_t *lock) {

    int destroy =  nanvix_mutex_unlock(lock);
    ufree(lock);
    return destroy;

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

