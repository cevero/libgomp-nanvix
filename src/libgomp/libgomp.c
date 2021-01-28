#include "libgomp.h"
#include "limits.h"




struct gomp_task_icv gomp_global_icv = {
  .nthreads_var = 1,
  .thread_limit_var = UINT_MAX,
  .run_sched_var = GFS_DYNAMIC,
  .run_sched_chunk_size = 1,
  .default_device_var = 0,
  .dyn_var = false,
  .nest_var = false,
  //.bind_var = omp_proc_bind_false,
  .bind_var = false,
  .target_data = NULL
};




unsigned long gomp_max_active_levels_var = INT_MAX;
bool gomp_cancel_var = false;
int gomp_max_task_priority_var = 0;
#ifndef HAVE_SYNC_BUILTINS
gomp_mutex_t gomp_managed_threads_lock;
#endif
unsigned long gomp_available_cpus = 1, gomp_managed_threads = 1;
unsigned long long gomp_spin_count_var, gomp_throttled_spin_count_var;
unsigned long *gomp_nthreads_var_list, gomp_nthreads_var_list_len;
char *gomp_bind_var_list;
unsigned long gomp_bind_var_list_len;
void **gomp_places_list;
unsigned long gomp_places_list_len;
int gomp_debug_var;
unsigned int gomp_num_teams_var;
bool gomp_display_affinity_var;
char *gomp_affinity_format_var = "level %L thread %i affinity %A";
size_t gomp_affinity_format_len;


//struct gomp_task_icv *
//gomp_new_icv (void)
//{
//  struct gomp_thread *thr = gomp_thread ();
//  struct gomp_task *task = gomp_malloc (sizeof (struct gomp_task));
//  gomp_init_task (task, NULL, &gomp_global_icv);
//  thr->task = task;
//#ifdef LIBGOMP_USE_PTHREADS
//  pthread_setspecific (gomp_thread_destructor, thr);
//#endif
//  return &task->icv;
//}




