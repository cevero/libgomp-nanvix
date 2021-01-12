#include "config/workaround.h"


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
