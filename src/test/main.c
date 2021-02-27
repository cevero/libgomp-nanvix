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
#include "../libgomp/omp.h"

#define NTHREADS_MAX  (THREAD_MAX-1)
/**
 * @brief Test Server
 */


void*
Hello(void * index){
    int pid;
    pid = (int)((intptr_t)index);
uprintf("Hello from thread%d\n",pid);

}
int __main2(int argc, const char *argv[])
{
	((void) argc);
	((void) argv);
    int a1=1,a2=0;

	struct nanvix_cond_var cond;
    a1 = nanvix_cond_init(&cond);

    int * a = umalloc(9*sizeof(int));
    for(int i=0;i<9;i++)
        a[i]=i;


	#pragma omp parallel num_threads(NTHREADS_MAX)// default(none) shared(a,a1) firstprivate(a2)
    {
#   pragma omp critical
        Hello((void*)kthread_self());

        
    }

    uprintf("SAI DA ZONA PARALELA\n");
    

    ufree(a);

    return (0);
}

