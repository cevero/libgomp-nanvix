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


typedef enum omp_proc_bind_t
{
  omp_proc_bind_false = 0,
  omp_proc_bind_true = 1,
  omp_proc_bind_master = 2,
  omp_proc_bind_close = 3,
  omp_proc_bind_spread = 4
} omp_proc_bind_t;
