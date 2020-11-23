
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


#include <nanvix/ulib.h>
#include "config/workaround.h"
#include "config/sem.h"
#include "config/mutex.h"
#include <nanvix/sys/semaphore.h>
#include <nanvix/sys/mutex.h>
#include "priority_queue.h"
#include "libgomp_g.h"

//////////////////////////////////////////////////////////////
//declarations dumb                         /////////////////
////////////////////////////////////////////////////////////

#define UINT_MAX 0x80000U
struct priority_queue;

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


enum gomp_schedule_type
{
  GFS_RUNTIME,
  GFS_STATIC,
  GFS_DYNAMIC,
  GFS_GUIDED,
  GFS_AUTO,
  GFS_MONOTONIC = 0x800000U
};







struct gomp_task_icv
{
  unsigned long nthreads_var;
  enum gomp_schedule_type run_sched_var;
  int run_sched_chunk_size;
  int default_device_var;
  unsigned int thread_limit_var;
  bool dyn_var;
  bool nest_var;
  char bind_var;
  /* Internal ICV.  */
  struct target_mem_desc *target_data;
};

// privisory declare
struct gomp_task_icv gomp_global_icv = {
  .nthreads_var = 1,
  .thread_limit_var = UINT_MAX,
  .run_sched_var = GFS_DYNAMIC,
  .run_sched_chunk_size = 1,
  .default_device_var = 0,
  .dyn_var = false,
  .nest_var = false,
  .bind_var = omp_proc_bind_false,
  .target_data = NULL
};

//////
enum gomp_task_kind
{
  /* Implicit task.  */
  GOMP_TASK_IMPLICIT,
  /* Undeferred task.  */
  GOMP_TASK_UNDEFERRED,
  /* Task created by GOMP_task and waiting to be run.  */
  GOMP_TASK_WAITING,
  /* Task currently executing or scheduled and about to execute.  */
  GOMP_TASK_TIED,
  /* Used for target tasks that have vars mapped and async run started,
     but not yet completed.  Once that completes, they will be readded
     into the queues as GOMP_TASK_WAITING in order to perform the var
     unmapping.  */
  GOMP_TASK_ASYNC_RUNNING
};

struct gomp_task_depend_entry
{
  /* Address of dependency.  */
  void *addr;
  struct gomp_task_depend_entry *next;
  struct gomp_task_depend_entry *prev;
  /* Task that provides the dependency in ADDR.  */
  struct gomp_task *task;
  /* Depend entry is of type "IN".  */
  bool is_in;
  bool redundant;
  bool redundant_out;
};

struct gomp_dependers_vec
{
  size_t n_elem;
  size_t allocated;
  struct gomp_task *elem[];
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

struct gomp_task
{
  /* Parent of this task.  */
  struct gomp_task *parent;
  /* Children of this task.  */
  struct priority_queue children_queue;
  /* Taskgroup this task belongs in.  */
  struct gomp_taskgroup *taskgroup;
  /* Tasks that depend on this task.  */
  struct gomp_dependers_vec *dependers;
  struct htab *depend_hash;
  struct gomp_taskwait *taskwait;
  /* Number of items in DEPEND.  */
  size_t depend_count;
  /* Number of tasks this task depends on.  Once this counter reaches
     0, we have no unsatisfied dependencies, and this task can be put
     into the various queues to be scheduled.  */
  size_t num_dependees;

  /* Priority of this task.  */
  int priority;
  /* The priority node for this task in each of the different queues.
     We put this here to avoid allocating space for each priority
     node.  Then we play offsetof() games to convert between pnode[]
     entries and the gomp_task in which they reside.  */
  struct priority_node pnode[3];

  struct gomp_task_icv icv;
  void (*fn) (void *);
  void *fn_data;
  enum gomp_task_kind kind;
  bool in_tied_task;
  bool final_task;
  bool copy_ctors_done;
  /* Set for undeferred tasks with unsatisfied dependencies which
     block further execution of their parent until the dependencies
     are satisfied.  */
  bool parent_depends_on;
  /* Dependencies provided and/or needed for this task.  DEPEND_COUNT
     is the number of items available.  */
  struct gomp_task_depend_entry depend[];
};
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



//struct gomp_task_icv *
//gomp_new_icv (void)
//{
//  struct gomp_thread *thr = gomp_thread ();
//  struct gomp_task *task = gomp_malloc (sizeof (struct gomp_task));
//  gomp_init_task (task, NULL, &gomp_global_icv);
//  thr->task = task;
//#ifdef LIBGOMP_USE_PTHREADS
//  kthread_setspecific (gomp_thread_destructor, thr);
//#endif
//  return &task->icv;
//}
//
//
//
//static inline struct gomp_task_icv *gomp_icv (bool write)
//{
//  struct gomp_task *task = gomp_thread ()->task;
//  if (task)
//    return &task->icv;
//  else if (write)
//    return gomp_new_icv ();
//  else
//    return &gomp_global_icv;
//}
//
//#ifdef LIBGOMP_USE_PTHREADS
///* The attributes to be used during thread creation.  */
//extern pthread_attr_t gomp_thread_attr;
//
//extern pthread_key_t gomp_thread_destructor;
//#endif
//
//

extern struct gomp_task_icv *gomp_new_icv (void);

/* Here's how to access the current copy of the ICVs.  */

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
/* Function prototypes.  */

/* affinity.c */

extern void gomp_init_affinity (void);
#ifdef LIBGOMP_USE_PTHREADS
extern void gomp_init_thread_affinity (pthread_attr_t *, unsigned int);
#endif
extern void **gomp_affinity_alloc (unsigned long, bool);
extern void gomp_affinity_init_place (void *);
extern bool gomp_affinity_add_cpus (void *, unsigned long, unsigned long,
				    long, bool);
extern bool gomp_affinity_remove_cpu (void *, unsigned long);
extern bool gomp_affinity_copy_place (void *, void *, long);
extern bool gomp_affinity_same_place (void *, void *);
extern bool gomp_affinity_finalize_place_list (bool);
extern bool gomp_affinity_init_level (int, unsigned long, bool);
extern void gomp_affinity_print_place (void *);
extern void gomp_get_place_proc_ids_8 (int, int64_t *);
extern void gomp_display_affinity_place (char *, size_t, size_t *, int);

/* affinity-fmt.c */

extern void gomp_print_string (const char *str, size_t len);
extern void gomp_set_affinity_format (const char *, size_t);
extern void gomp_display_string (char *, size_t, size_t *, const char *,
				 size_t);
#ifdef LIBGOMP_USE_PTHREADS
typedef pthread_t gomp_thread_handle;
#else
typedef struct {} gomp_thread_handle;
#endif
extern size_t gomp_display_affinity (char *, size_t, const char *,
				     gomp_thread_handle,
				     struct gomp_team_state *, unsigned int);
extern void gomp_display_affinity_thread (gomp_thread_handle,
					  struct gomp_team_state *,
					  unsigned int) __attribute__((cold));

/* iter.c */

extern int gomp_iter_static_next (long *, long *);
extern bool gomp_iter_dynamic_next_locked (long *, long *);
extern bool gomp_iter_guided_next_locked (long *, long *);

#ifdef HAVE_SYNC_BUILTINS
extern bool gomp_iter_dynamic_next (long *, long *);
extern bool gomp_iter_guided_next (long *, long *);
#endif

/* iter_ull.c */

extern int gomp_iter_ull_static_next (unsigned long long *,
				      unsigned long long *);
extern bool gomp_iter_ull_dynamic_next_locked (unsigned long long *,
					       unsigned long long *);
extern bool gomp_iter_ull_guided_next_locked (unsigned long long *,
					      unsigned long long *);

#if defined HAVE_SYNC_BUILTINS && defined __LP64__
extern bool gomp_iter_ull_dynamic_next (unsigned long long *,
					unsigned long long *);
extern bool gomp_iter_ull_guided_next (unsigned long long *,
				       unsigned long long *);
#endif

/* ordered.c */

extern void gomp_ordered_first (void);
extern void gomp_ordered_last (void);
extern void gomp_ordered_next (void);
extern void gomp_ordered_static_init (void);
extern void gomp_ordered_static_next (void);
extern void gomp_ordered_sync (void);
extern void gomp_doacross_init (unsigned, long *, long, size_t);
extern void gomp_doacross_ull_init (unsigned, unsigned long long *,
				    unsigned long long, size_t);

/* parallel.c */

extern unsigned gomp_resolve_num_threads (unsigned, unsigned);

/* proc.c (in config/) */

extern void gomp_init_num_threads (void);
extern unsigned gomp_dynamic_max_threads (void);

///* task.c */
//
//extern void gomp_init_task (struct gomp_task *, struct gomp_task *,
//			    struct gomp_task_icv *);
//extern void gomp_end_task (void);
//extern void gomp_barrier_handle_tasks (gomp_barrier_state_t);
//extern void gomp_task_maybe_wait_for_dependencies (void **);
//extern bool gomp_create_target_task (struct gomp_device_descr *,
//				     void (*) (void *), size_t, void **,
//				     size_t *, unsigned short *, unsigned int,
//				     void **, void **,
//				     enum gomp_target_task_state);
//extern struct gomp_taskgroup *gomp_parallel_reduction_register (uintptr_t *,
//								unsigned);
//extern void gomp_workshare_taskgroup_start (void);
//extern void gomp_workshare_task_reduction_register (uintptr_t *, uintptr_t *);
//
//static void inline
//gomp_finish_task (struct gomp_task *task)
//{
//  if (__builtin_expect (task->depend_hash != NULL, 0))
//    free (task->depend_hash);
//}
//
/* team.c */

extern struct gomp_team *gomp_new_team (unsigned);
extern void gomp_team_start (void (*) (void *), void *, unsigned,
			     unsigned, struct gomp_team *,
			     struct gomp_taskgroup *);
extern void gomp_team_end (void);
extern void gomp_free_thread (void *);
extern int gomp_pause_host (void);

/* target.c */

extern void gomp_init_targets_once (void);
extern int gomp_get_num_devices (void);
extern bool gomp_target_task_fn (void *);




#endif /* LIBGOMP_H */
