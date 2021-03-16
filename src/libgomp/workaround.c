//#include "config/nanvix/workaround.h"
#include <nanvix/sys/mutex.h>
#include "libgomp.h"



///// pthread functions ///////

/* Return data of a Specific thread called by kthread_self() */
struct gomp_thread* pthread_getspecific (pthread_key_t key)
{
    return tls_omp[kthread_self()].data;
}

/* Set a gomp thread pointer on team to use Thread Local Storage */
void * pthread_setspecific (pthread_key_t  key, struct gomp_thread *__pointer)
{


   tls_omp[key].data = __pointer;

}


//extern int pthread_attr_destroy (pthread_attr_t *__attr)
//{
//    (void) __attr;
//    uprintf("%s \n",__func__);
//    return 0;
//}
//
//int pthread_attr_getstacksize (pthread_attr_t *__attr,int * stacksize)
//{
//    (void) __attr;
//    (void) stacksize;
//    uprintf("%s \n",__func__);
//    return 0;
//}
//int pthread_attr_setstacksize (pthread_attr_t *__attr,size_t  stacksize)
//{
//    (void) __attr;
//    (void) stacksize;
//    uprintf("%s \n",__func__);
//    return 0;
//}

/* create desired thread key values on the team*/
int  pthread_key_create (pthread_key_t * key,void (*destructor)(void*))
{
   for(int i=0;i<100;i++)
   {
        tls_omp[i].key = (kthread_t) i;
        tls_omp[i].data = umalloc(sizeof(struct gomp_thread*));
   }
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


////NANVIX DEFINITIONS//////










