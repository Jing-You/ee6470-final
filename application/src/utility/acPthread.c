#ifndef acPthread_H_
#include "acPthread.h"
#endif

unsigned volatile int *lock                 = (unsigned volatile int *)0x43000000;

///////////////
// Functions //
///////////////
void AcquireGlobalLock() {
  while (*lock);
}

void ReleaseGlobalLock() {
  (*lock) = 0;
}

/////////////////////
// Mutex Functions //
/////////////////////
void busywait(int wait_time) {
  for(int i = 0; i < wait_time; i++);
}

void mutex_init(volatile mutex_t *m_lock,
                        const mutexattr_t *attr) {
  AcquireGlobalLock();
  m_lock->value = 0;
  ReleaseGlobalLock();
}

int mutex_lock(volatile mutex_t *m_lock) {
  int status, i;
  AcquireGlobalLock();

  // Trying to acquire the lock state
  while (m_lock->value == 1) {
    ReleaseGlobalLock();
    busywait(500);
    AcquireGlobalLock();
  }

  // Acquiring the lock state
  m_lock->value = 1;

  ReleaseGlobalLock();

  status = 0;

  return status;
}

int mutex_unlock(volatile mutex_t *m_lock) {
  AcquireGlobalLock();
  m_lock->value = 0;
  ReleaseGlobalLock();
  return 0;
}

///////////////////////
// Barrier Functions //
///////////////////////
void barrier_init(volatile barrier_t *barrier, int count) {
  AcquireGlobalLock();
  barrier->ctrl = 0;
  barrier->counter = count;
  barrier->initial_counter = count;
  ReleaseGlobalLock();
}

void barrier(volatile barrier_t *barrier) {
  int status, ctrl;

  AcquireGlobalLock();
  ctrl = barrier->ctrl;

  if (--barrier->counter == 0) {
    barrier->ctrl = !barrier->ctrl;
    barrier->counter = barrier->initial_counter;
    ReleaseGlobalLock();
    status = 1;
  } else {
    ReleaseGlobalLock();
    while (ctrl == barrier->ctrl)
      ;
    status = 1;
  }
}

