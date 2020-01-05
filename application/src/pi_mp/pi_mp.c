#include <stdio.h>
#include "acPthread.h"

// global variables in shared memory
volatile mutex_t *mutex = (volatile mutex_t *)0x52ff0000; // 4-byte: 0x52ff0000 - 0x52ff0003
volatile barrier_t *barr = (volatile barrier_t *)0x52ff0004; // 16-byte: 0x52ff0004 - 0x52ff0013

volatile float *pi_over_4 = (volatile float *)0x50000000; // 4-byte: 0x50000000 - 0x50000004

int get_id();

int main(int argc, char *argv[]) {

  /////////////////////////////
  // thread and barrier init //
  /////////////////////////////
  int PROCESSORS = 4;
  barrier_init(barr,PROCESSORS);

  /////////////////////////
  // calculate local sum //
  /////////////////////////
  unsigned total_terms = 300;
  unsigned nc = 4;

  unsigned num_terms_per_thread = (total_terms + nc - 1 ) / nc;
  unsigned begin_idx = num_terms_per_thread * get_id();
  unsigned end_idx;

  if (get_id() == nc - 1) {
    end_idx = total_terms;
  } else {
    end_idx = begin_idx + num_terms_per_thread;
  }

  double factor = begin_idx % 2 ? -1.0 : 1.0;

  double local_sum = 0, i;
  for (i = begin_idx ; i < end_idx; i++, factor = -factor) {
    local_sum += factor / (2 * i + 1);
  }

  /////////////////////////////////////////
  // accumulate local sum to shared data //
  /////////////////////////////////////////
  mutex_init(mutex, NULL);
  mutex_lock(mutex);  
  *pi_over_4 += local_sum;
  mutex_unlock(mutex); 
  
  ////////////////////////////
  // barrier to synchronize //
  ////////////////////////////
  barrier(barr);

  if(get_id() == 0) {
    printf("core%d, Pi = %f\n", get_id(), (*pi_over_4)*4);
  }

  return 0;
}
