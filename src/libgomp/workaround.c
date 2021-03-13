//#include "config/nanvix/workaround.h"
#include <nanvix/sys/mutex.h>
#include "libgomp.h"



///// pthread functions ///////

struct gomp_thread* pthread_getspecific (pthread_key_t key)
{
    for(int i=0;i<100;i++) 
    {
            if(tls_omp[i].key == key)
            {
                return tls_omp[i].data;
            }
    }
    return NULL;
}

void * pthread_setspecific (pthread_key_t  key, struct gomp_thread *__pointer)
{

            uprintf("id = %u",__pointer->ts.team_id);
   for (int i=0;i<gomp_nthreads_var;i++)
   {
       if(tls_omp[i].key == key)
       {
           tls_omp[i].data = __pointer;
       }
   }

   //if(head == NULL)
   //{
   //    head = ucalloc(1,sizeof(struct tls_data));
   //    head->data = __pointer;
   //    head->key = key;
   //}
   //else
   //{

   //    current = ucalloc(1,sizeof(struct tls_data));
   //    current->data = __pointer;
   //    current->key = key;

   //while (current->key != key)
   //{
   //     if(current->next == NULL)
   //     {
   //         uprintf("cant set without that key");
   //         return NULL;
   //     }
   //     else
   //         current = current->next;
   //}

   //    current->data = __pointer->data;
   //}
   //    return NULL;
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

int  pthread_key_create (pthread_key_t * key,void (*destructor)(void*))
{
   for(int i=0;i<100;i++)
   {
       if(tls_omp[i].data == NULL)
        tls_omp[i].key = (kthread_t) *key;
       return 0;
   }
   return -1;
   //struct tls_data * link = (struct tls_data*) umalloc(sizeof(struct tls_data));

   //link->key = *key;
   //link->next = head;

   //head = link;

   //return 0;
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

//int pthread_key_delete (pthread_key_t __key)
//{
//       //struct tls_data* current = head;
//       //struct tls_data* previous = NULL;
//       //     
//       // if(head == NULL) 
//       // {
//       //     return 0;
//       // }
//
//       // while(current->key != __key) 
//       // {
//
//       //     if(current->next == NULL)
//       //     {
//       //         return 0;
//       //     }
//
//       //     else 
//
//       //     {
//       //         previous = current;
//       //         current = current->next;
//       //     }
//       // }
//
//       // if(current == head)
//
//       // {
//       //     head = head->next;
//       // } 
//       // else
//       // {
//       // //bypass the current link
//       //     previous->next = current->next;
//       // }    
//       // return 0;
//}

////NANVIX DEFINITIONS//////










