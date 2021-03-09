/*
 * MIT License
 *
 * Copyright(c) 2011-2020 The Maintainers of Nanvix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <nanvix/ulib.h>
#include <nanvix/sys/thread.h>
#include <nanvix/sys/condvar.h>
#include <nanvix/sys/mutex.h>
#include "../libgomp/omp.h"

#define NTHREADS  (THREAD_MAX-1)
/**
 * @brief Test Server
 */


#define NTRIALS 10
static struct nanvix_mutex mutex;
static volatile int var;

void*
Hello_omp(void * index){
    int nt;
    nt = (int)((intptr_t)index);
#   pragma omp parallel num_threads(nt)
    {
        uprintf("Hello from thread %d\n",omp_get_thread_num());
    }
    uprintf("SAI DA ZONA PARALELA\n");
}

static void *task3(void *arg)
{
	((void) arg);

	/* Increment a variable many times. */
	for (int i = 0; i < NTRIALS; i++)
	{
		nanvix_mutex_lock(&mutex);

        uprintf("LOCK from thread %d \n",kthread_self());
			var++;
		nanvix_mutex_unlock(&mutex);
        uprintf("UNLOCK from thread %d \n",kthread_self());
	}

	return (NULL);
}

void test_mutex()
{
	kthread_t tids[NTHREADS];
	nanvix_mutex_init(&mutex);

	for (int i = 0; i < NTHREADS; i++)
		kthread_create(&tids[i], task3, NULL) == 0;

	/* Wait for threads. */
	for (int i = 0; i < NTHREADS; i++)
		kthread_join(tids[i], NULL) == 0;

}

int __main2(int argc, const char *argv[])
{
	((void) argc);
	((void) argv);

//    Hello_omp((void*)3);

#   pragma omp parallel num_threads(3)
    {
        uprintf("Hello from thread %d\n",omp_get_thread_num());
    }
    uprintf("SAI DA ZONA PARALELA\n");


    


    return (0);
}

