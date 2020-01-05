/********************************************************************************
        MPSoCBench Benchmark Suite
        Authors: Liana Duenha
        Supervisor: Rodolfo Azevedo
        Date: July-2012
        www.archc.org/benchs/mpsocbench

        Computer Systems Laboratory (LSC)
        IC-UNICAMP
        http://www.lsc.ic.unicamp.br/


        This source code is part of the MPSoCBench Benchmark Suite, which is a
free
        source-code benchmark for evaluation of Electronic Systemc Level
designs.
        This benchmark is distributed with hope that it will be useful, but
        without any warranty.

*********************************************************************************/

#ifndef acPthread_H_
#define acPthread_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pthread_mutex_tag { int value; } mutex_t;
typedef struct pthread_mutexattr_tag {} mutexattr_t;
typedef struct barrier_tag {
  int valid;
  int initial_counter;
  int counter;
  int ctrl;
} barrier_t;

void AcquireGlobalLock();
void ReleaseGlobalLock();

///////////////
// acPthread //
///////////////
void busywait(int);
void mutex_init(volatile mutex_t *, const mutexattr_t *);
int  mutex_lock(volatile mutex_t *);
int  mutex_unlock(volatile mutex_t *);

void barrier_init(volatile barrier_t *, int);
void barrier(volatile barrier_t *barrier);
#endif
