#include "semaphore.h"

void  nanvix_mutex_destroy (gomp_mutex_t *mutex)
{

   nanvix_mutex_unlock (mutex);

}
