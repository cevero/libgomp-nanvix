
#ifndef LIBGOMP_H 
#define LIBGOMP_H 1

#ifdef HAVE_ATTRIBUTE_ALIAS
# define strong_alias(fn, al) \
  extern __typeof (fn) al __attribute__ ((alias (#fn))) attribute_copy (fn);

# define ialias_ulp	ialias_str1(__USER_LABEL_PREFIX__)
# define ialias_str1(x)	ialias_str2(x)
# define ialias_str2(x)	#x
# define ialias(fn) \
  extern __typeof (fn) gomp_ialias_##fn \
    __attribute__ ((alias (#fn))) attribute_hidden attribute_copy (fn);
# define ialias_redirect(fn) \
  extern __typeof (fn) fn __asm__ (ialias_ulp "gomp_ialias_" #fn) attribute_hidden;
# define ialias_call(fn) gomp_ialias_ ## fn
#else
# define ialias(fn)
# define ialias_redirect(fn)
# define ialias_call(fn) fn
#endif


#include "config/workaround.h"
#include "config/sem.h"
#include "config/mutex.h"
#include <nanvix/sys/semaphore.h>
#include <nanvix/sys/mutex.h>
#include <nanvix/ulib.h>


struct gomp_team_state
{
  /* This is the team of which the thread is currently a member.  */
  struct gomp_team *team;

  /* This is the work share construct which this thread is currently
     processing.  Recall that with NOWAIT, not all threads may be 
     processing the same construct.  */
  struct gomp_work_share *work_share;

  /* This is the previous work share construct or NULL if there wasn't any.
     When all threads are done with the current work sharing construct,
     the previous one can be freed.  The current one can't, as its
     next_ws field is used.  */
  struct gomp_work_share *last_work_share;

  /* This is the ID of this thread within the team.  This value is
     guaranteed to be between 0 and N-1, where N is the number of
     threads in the team.  */
  unsigned team_id;

  /* Nesting level.  */
  unsigned level;

  /* Active nesting level.  Only active parallel regions are counted.  */
  unsigned active_level;

  /* Place-partition-var, offset and length into gomp_places_list array.  */
  unsigned place_partition_off;
  unsigned place_partition_len;

#ifdef HAVE_SYNC_BUILTINS
  /* Number of single stmts encountered.  */
  unsigned long single_count;
#endif

  /* For GFS_RUNTIME loops that resolved to GFS_STATIC, this is the
     trip number through the loop.  So first time a particular loop
     is encountered this number is 0, the second time through the loop
     is 1, etc.  This is unused when the compiler knows in advance that
     the loop is statically scheduled.  */
  unsigned long static_trip;
};




//struct gomp_team
//{
//  /* This is the number of threads in the current team.  */
//  unsigned nthreads;
//
//  /* This is number of gomp_work_share structs that have been allocated
//     as a block last time.  */
//  unsigned work_share_chunk;
//
//  /* This is the saved team state that applied to a master thread before
//     the current thread was created.  */
//  struct gomp_team_state prev_ts;
//
//  /* This semaphore should be used by the master thread instead of its
//     "native" semaphore in the thread structure.  Required for nested
//     parallels, as the master is a member of two teams.  */
//  gomp_sem_t master_release;
//
//  /* This points to an array with pointers to the release semaphore
//     of the threads in the team.  */
//  gomp_sem_t **ordered_release;
//
//  /* List of work shares on which gomp_fini_work_share hasn't been
//     called yet.  If the team hasn't been cancelled, this should be
//     equal to each thr->ts.work_share, but otherwise it can be a possibly
//     long list of workshares.  */
//  struct gomp_work_share *work_shares_to_free;
//
//  /* List of gomp_work_share structs chained through next_free fields.
//     This is populated and taken off only by the first thread in the
//     team encountering a new work sharing construct, in a critical
//     section.  */
//  struct gomp_work_share *work_share_list_alloc;
//
//  /* List of gomp_work_share structs freed by free_work_share.  New
//     entries are atomically added to the start of the list, and
//     alloc_work_share can safely only move all but the first entry
//     to work_share_list alloc, as free_work_share can happen concurrently
//     with alloc_work_share.  */
//  struct gomp_work_share *work_share_list_free;
//
//#ifdef HAVE_SYNC_BUILTINS
//  /* Number of simple single regions encountered by threads in this
//     team.  */
//  unsigned long single_count;
//#else
//  /* Mutex protecting addition of workshares to work_share_list_free.  */
//  gomp_mutex_t work_share_list_free_lock;
//#endif
//
//  /* This barrier is used for most synchronization of the team.  */
//  gomp_barrier_t barrier;
//
//  /* Initial work shares, to avoid allocating any gomp_work_share
//     structs in the common case.  */
//  struct gomp_work_share work_shares[8];
//
//  gomp_mutex_t task_lock;
//  /* Scheduled tasks.  */
//  struct priority_queue task_queue;
//  /* Number of all GOMP_TASK_{WAITING,TIED} tasks in the team.  */
//  unsigned int task_count;
//  /* Number of GOMP_TASK_WAITING tasks currently waiting to be scheduled.  */
//  unsigned int task_queued_count;
//  /* Number of GOMP_TASK_{WAITING,TIED} tasks currently running
//     directly in gomp_barrier_handle_tasks; tasks spawned
//     from e.g. GOMP_taskwait or GOMP_taskgroup_end don't count, even when
//     that is called from a task run from gomp_barrier_handle_tasks.
//     task_running_count should be always <= team->nthreads,
//     and if current task isn't in_tied_task, then it will be
//     even < team->nthreads.  */
//  unsigned int task_running_count;
//  int work_share_cancelled;
//  int team_cancelled;
//
//  /* This array contains structures for implicit tasks.  */
//  struct gomp_task implicit_task[];
//};
//





struct gomp_thread
{
  /* This is the function that the thread should run upon launch.  */
  void (*fn) (void *data);
  void *data;

  /* This is the current team state for this thread.  The ts.team member
     is NULL only if the thread is idle.  */
  struct gomp_team_state ts;

  /* This is the task that the thread is currently executing.  */
  struct gomp_task *task;

  /* This semaphore is used for ordered loops.  */
  gomp_sem_t release;

  /* Place this thread is bound to plus one, or zero if not bound
     to any place.  */
  unsigned int place;

  /* User pthread thread pool */
  struct gomp_thread_pool *thread_pool;

#if defined(LIBGOMP_USE_PTHREADS) \
    && (!defined(HAVE_TLS) \
	|| !defined(__GLIBC__) \
	|| !defined(USING_INITIAL_EXEC_TLS))
  /* pthread_t of the thread containing this gomp_thread.
     On Linux when using initial-exec TLS,
     (typeof (pthread_t)) gomp_thread () - pthread_self ()
     is constant in all threads, so we can optimize and not
     store it.  */
#define GOMP_NEEDS_THREAD_HANDLE 1
  kthread_t handle;
#endif
};


static inline struct gomp_task_icv *gomp_icv (bool write)
{
  struct gomp_task *task = gomp_thread ()->task;
  if (task)
    return &task->icv;
  else if (write)
    return gomp_new_icv ();
  else
    return &gomp_global_icv;
}

#ifdef LIBGOMP_USE_PTHREADS
/* The attributes to be used during thread creation.  */
extern pthread_attr_t gomp_thread_attr;

extern pthread_key_t gomp_thread_destructor;
#endif

#if defined __nvptx__
extern struct gomp_thread *nvptx_thrs __attribute__((shared));
static inline struct gomp_thread *gomp_thread (void)
{
  int tid;
  asm ("mov.u32 %0, %%tid.y;" : "=r" (tid));
  return nvptx_thrs + tid;
}
#elif defined HAVE_TLS || defined USE_EMUTLS
extern __thread struct gomp_thread gomp_tls_data;
static inline struct gomp_thread *gomp_thread (void)
{
  return &gomp_tls_data;
}
#else
extern pthread_key_t gomp_tls_key;
static inline struct gomp_thread *gomp_thread (void)
{
  return pthread_getspecific (gomp_tls_key);
}
#endif






#endif /* LIBGOMP_H */
