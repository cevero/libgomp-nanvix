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


//void
//omp_set_num_threads (int n)
//{
//  struct gomp_task_icv *icv = gomp_icv (true);
//  icv->nthreads_var = (n > 0 ? n : 1);
//}

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


//bool
//gomp_target_task_fn (void *data)
//{
//  struct gomp_target_task *ttask = (struct gomp_target_task *) data;
//  struct gomp_device_descr *devicep = ttask->devicep;
//
//  if (ttask->fn != NULL)
//    {
//      void *fn_addr;
//      if (devicep == NULL
//	  || !(devicep->capabilities & GOMP_OFFLOAD_CAP_OPENMP_400)
//	  || !(fn_addr = gomp_get_target_fn_addr (devicep, ttask->fn))
//	  || (devicep->can_run_func && !devicep->can_run_func (fn_addr)))
//	{
//	  ttask->state = GOMP_TARGET_TASK_FALLBACK;
//	  gomp_target_fallback (ttask->fn, ttask->hostaddrs, devicep);
//	  return false;
//	}
//
//      if (ttask->state == GOMP_TARGET_TASK_FINISHED)
//	{
//	  if (ttask->tgt)
//	    gomp_unmap_vars (ttask->tgt, true);
//	  return false;
//	}
//
//      void *actual_arguments;
//      if (devicep->capabilities & GOMP_OFFLOAD_CAP_SHARED_MEM)
//	{
//	  ttask->tgt = NULL;
//	  actual_arguments = ttask->hostaddrs;
//	}
//      else
//	{
//	  ttask->tgt = gomp_map_vars (devicep, ttask->mapnum, ttask->hostaddrs,
//				      NULL, ttask->sizes, ttask->kinds, true,
//				      GOMP_MAP_VARS_TARGET);
//	  actual_arguments = (void *) ttask->tgt->tgt_start;
//	}
//      ttask->state = GOMP_TARGET_TASK_READY_TO_RUN;
//
//      uassert (devicep->async_run_func);
//      devicep->async_run_func (devicep->target_id, fn_addr, actual_arguments,
//			       ttask->args, (void *) ttask);
//      return true;
//    }
//  else if (devicep == NULL
//	   || !(devicep->capabilities & GOMP_OFFLOAD_CAP_OPENMP_400)
//	   || devicep->capabilities & GOMP_OFFLOAD_CAP_SHARED_MEM)
//    return false;
//
//  size_t i;
//  if (ttask->flags & GOMP_TARGET_FLAG_UPDATE)
//    gomp_update (devicep, ttask->mapnum, ttask->hostaddrs, ttask->sizes,
//		 ttask->kinds, true);
//  else if ((ttask->flags & GOMP_TARGET_FLAG_EXIT_DATA) == 0)
//    for (i = 0; i < ttask->mapnum; i++)
//      if ((ttask->kinds[i] & 0xff) == GOMP_MAP_STRUCT)
//	{
//	  gomp_map_vars (devicep, ttask->sizes[i] + 1, &ttask->hostaddrs[i],
//			 NULL, &ttask->sizes[i], &ttask->kinds[i], true,
//			 GOMP_MAP_VARS_ENTER_DATA);
//	  i += ttask->sizes[i];
//	}
//      else
//	gomp_map_vars (devicep, 1, &ttask->hostaddrs[i], NULL, &ttask->sizes[i],
//		       &ttask->kinds[i], true, GOMP_MAP_VARS_ENTER_DATA);
//  else
//    gomp_exit_data (devicep, ttask->mapnum, ttask->hostaddrs, ttask->sizes,
//		    ttask->kinds);
//  return false;
//}


