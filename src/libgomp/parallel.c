/*
 *
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
#include "libgomp.h"
#include "limits.h"
/**
 * @brief Creates a parallel region.
 */

unsigned
gomp_resolve_num_threads (unsigned specified, unsigned count)
{
  uprintf("%d",specified);
  struct gomp_thread *thr = gomp_thread ();
  struct gomp_task_icv *icv;
  unsigned threads_requested, max_num_threads, num_threads;
  unsigned long busy;
  struct gomp_thread_pool *pool;
//
  icv = gomp_icv (false);
//
//  if (specified == 1)
//    return 1;
//  else if (thr->ts.active_level >= 1 && !icv->nest_var)
//    return 1;
//  else if (thr->ts.active_level >= gomp_max_active_levels_var)
//    return 1;
//
//  /* If NUM_THREADS not specified, use nthreads_var.  */
//  if (specified == 0)
//    threads_requested = icv->nthreads_var;
//  else
//    threads_requested = specified;
//
//  max_num_threads = threads_requested;
//
//  /* If dynamic threads are enabled, bound the number of threads
//     that we launch.  */
//  if (icv->dyn_var)
//    {
//      unsigned dyn = gomp_dynamic_max_threads ();
//      if (dyn < max_num_threads)
//	max_num_threads = dyn;
//
//      /* Optimization for parallel sections.  */
//      if (count && count < max_num_threads)
//	max_num_threads = count;
//    }
//
//  /* UINT_MAX stands for infinity.  */
//  if (__builtin_expect (icv->thread_limit_var == UINT_MAX, 1)
//      || max_num_threads == 1)
//    return max_num_threads;
//
//  /* The threads_busy counter lives in thread_pool, if there
//     isn't a thread_pool yet, there must be just one thread
//     in the contention group.  If thr->team is NULL, this isn't
//     nested parallel, so there is just one thread in the
//     contention group as well, no need to handle it atomically.  */
//  pool = thr->thread_pool;
//  if (thr->ts.team == NULL || pool == NULL)
//    {
//      num_threads = max_num_threads;
//      if (num_threads > icv->thread_limit_var)
//	num_threads = icv->thread_limit_var;
//      if (pool)
//	pool->threads_busy = num_threads;
//      return num_threads;
//    }
//
//#ifdef HAVE_SYNC_BUILTINS
//  do
//    {
//      busy = pool->threads_busy;
//      num_threads = max_num_threads;
//      if (icv->thread_limit_var - busy + 1 < num_threads)
//	num_threads = icv->thread_limit_var - busy + 1;
//    }
//  while (__sync_val_compare_and_swap (&pool->threads_busy,
//				      busy, busy + num_threads - 1)
//	 != busy);
//#else
//  gomp_mutex_lock (&gomp_managed_threads_lock);
//  num_threads = max_num_threads;
//  busy = pool->threads_busy;
//  if (icv->thread_limit_var - busy + 1 < num_threads)
//    num_threads = icv->thread_limit_var - busy + 1;
//  pool->threads_busy += num_threads - 1;
//  gomp_mutex_unlock (&gomp_managed_threads_lock);
//#endif
//
  //edited 
  unsigned num_threads = count;
  //
  return num_threads;
}

void GOMP_parallel_end(void)
{
//  struct gomp_task_icv *icv = gomp_icv (false);
//  if (__builtin_expect (icv->thread_limit_var != UINT_MAX, 0))
//    {
//      struct gomp_thread *thr = gomp_thread ();
//      struct gomp_team *team = thr->ts.team;
//      unsigned int nthreads = team ? team->nthreads : 1;
//      gomp_team_end ();
//      if (nthreads > 1)
//	{
//	  /* If not nested, there is just one thread in the
//	     contention group left, no need for atomicity.  */
//	  if (thr->ts.team == NULL)
//	    thr->thread_pool->threads_busy = 1;
//	  else
//	    {
//#ifdef HAVE_SYNC_BUILTINS
//	      __sync_fetch_and_add (&thr->thread_pool->threads_busy,
//				    1UL - nthreads);
//#else
//	      gomp_mutex_lock (&gomp_managed_threads_lock);
//	      thr->thread_pool->threads_busy -= nthreads - 1;
//	      gomp_mutex_unlock (&gomp_managed_threads_lock);
//#endif
//	    }
//	}
//    }
//  else
//    gomp_team_end ();
//    return;
}
ialias (GOMP_parallel_end)

//void
//GOMP_parallel_start (void (*fn) (void *), void *data, unsigned num_threads)
//{
////  num_threads = gomp_resolve_num_threads (num_threads, 0);
////  gomp_team_start (fn, data, num_threads, 0, gomp_new_team (num_threads),
////		   NULL);
//    uprintf("parallel start %d, %d", num_threads);
//    fn (data);
//}
void
GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads,

	       unsigned int flags)
{
    uprintf("parallel  %d, %d", num_threads,flags);
    num_threads = gomp_resolve_num_threads (num_threads, 0);
//    gomp_team_start (fn, data, num_threads, flags, gomp_new_team (num_threads),
//		   NULL);
    fn (data);
  ialias_call (GOMP_parallel_end) ();
}

