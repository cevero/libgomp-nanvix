// parallel //
void
GOMP_parallel_start (void (*fn) (void *), void *data, unsigned num_threads);
void
GOMP_parallel_end (void);

void
GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads,
	       unsigned int flags);
unsigned
GOMP_parallel_reductions (void (*fn) (void *), void *data,
			  unsigned num_threads, unsigned int flags);
bool
GOMP_cancellation_point (int which);
bool
GOMP_cancel (int which, bool do_cancel);

//end parallel
