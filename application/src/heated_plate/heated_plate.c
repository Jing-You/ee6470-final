#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../utility/acPthread.h"

// dimension = M(height) by N(width)
#define M          (32)
#define N          (32)
#define thread_cnt (4)

// absolute value
#define absVal(val) ((val)<0 ? -(val) : (val))

// function prototypes
void *p_cal_heat (int rank);
int get_id();

// global variables in shared memory
volatile mutex_t *mutex = (volatile mutex_t *)0x52ff0000; // 4-byte: 0x52ff0000 - 0x52ff0003
volatile barrier_t *barr      = (volatile barrier_t *)0x52ff0004; // 16-byte: 0x52ff0004 - 0x52ff0013

  
volatile double *diff_g                  = (volatile double *)0x50000000; // 8-byte: 0x50000000 - 0x50000007
volatile int *iterations                 = (volatile int *)0x50000008; // 4-byte: 0x50000008 - 0x5000000B
volatile int *iterations_print           = (volatile int *)0x5000000C; // 4-byte: 0x5000000C - 0x50000010

typedef struct array_1d {
  double diff[thread_cnt]; // mem usage: 8-byte * thread_cnt
} shared_1d_array;

volatile shared_1d_array *shared_1d_data = {(volatile shared_1d_array *)0x50000100}; // 256-byte: 0x50000100 - 0x5000001FF

typedef struct array_2d {
  double u[M][N];
  double w[M][N];
} shared_2d_array;

volatile shared_2d_array *shared_data    = (volatile shared_2d_array *)0x50000200; // from 0x50000200

double epsilon = 0.1;

// the main function
int main (int argc, char *argv[]) {

    // Barrier init
    int PROCESSORS = thread_cnt;
    barrier_init(barr,PROCESSORS);

    char output_file[80] = "output";
    double mean;
    int i, j, success;
    FILE *fp;

    if(get_id() == 0) {
      printf("\n");
      printf("HEATED_PLATE\n");
      printf("  C version\n");
      printf("  A program to solve for the steady state temperature distribution\n");
      printf("  over a rectangular plate.\n");
      printf("\n");
      printf("  Spatial grid of %d by %d points.\n", M, N);
      printf("====================================\n");
      printf("M/N/thread_cnt = %d/%d/%d\n", M, N, thread_cnt);
      printf("====================================\n");
      
      printf("\n");
      printf("  The iteration will be repeated until the change is <= %lf\n", epsilon);
      *diff_g = epsilon;
      
      // initialize our plate
      printf("\n");
      printf("  The steady state solution will be written to \"%s\".\n", output_file);
      // set the boundary values, which is fixed
      for (i=1; i<M-1; ++i) shared_data->w[i][0]   = 100.0;
      for (i=1; i<M-1; ++i) shared_data->w[i][N-1] = 100.0;
      for (j=0; j<N;   ++j) shared_data->w[M-1][j] = 100.0;
      for (j=0; j<N;   ++j) shared_data->w[0][j]   = 0.0;
      // average the boundary values,
      // to come up with a reasonable initial value for the interior.
      mean = 0.0;
      for (i=1; i<M-1; ++i) mean += shared_data->w[i][0];
      for (i=1; i<M-1; ++i) mean += shared_data->w[i][N-1];
      for (j=0; j<N;   ++j) mean += shared_data->w[M-1][j];
      for (j=0; j<N;   ++j) mean += shared_data->w[0][j];
      mean /= (double) (2*M + 2*N - 4);
      // initialize the interior solution to the mean value.
      for (i=1; i<M-1; ++i) {
          for (j=1; j<N-1; ++j) {
              shared_data->w[i][j] = mean;
          }
      }
      
      // initialize the diff array
      for (i=0; i<thread_cnt; ++i) shared_1d_data->diff[i] = 0;
      
      // iterate until the new solution "w" differs from the old solution "u" by no more than epsilon.
      *iterations = 0;
      *iterations_print = 1;
      printf("\n");
      printf(" Iteration  Change\n");
      printf("\n");
    }
    barrier(barr);

    // pthread: start
    mutex_init(mutex, NULL);
    for(i = 0; i < thread_cnt; i++) {
      if(get_id() == i)
        p_cal_heat(i);
    }
    
    barrier(barr);
    // pthread: end

    if(get_id() == 0) {
      printf("\n");
      printf("  %8d  %lf\n", *iterations, *diff_g);
      printf("\n");
      printf("  Error tolerance achieved.\n");
      
      // write the solution to the output file.
      fp = fopen(output_file, "w");
      if (fp == NULL) {
          printf("* Error: Fail to open '%s'...\n", output_file);
          return 1;
      }
      fprintf(fp, "%d\n%d\n", M, N);
      for (i=0; i<M; ++i) {
          for (j=0; j<N; ++j) {
              fprintf(fp, "%6.2lf ", shared_data->w[i][j]);
          }
          fputc('\n', fp);
      }
      fclose(fp);
      
      printf("\n");
      printf("  Solution written to the output file \"%s\"\n", output_file);
      printf("\n");
      printf("HEATED_PLATE:\n");
      printf("  Normal end of execution.\n");
    }
    barrier(barr);

    return 0;
}

/**
 * This is the main mypthread function.
 * Each thread will execute this function with a different rank.
 * @param  rank [the thread rank]
 * @return      [a NULL pointer]
 */
void *p_cal_heat (int rank) {
    long i, m, n, my_rank = (long) rank;
    // iterate until it fits our tolerant error
    while (epsilon <= *diff_g) {
        // commit the last time frame
        for (m=my_rank; m<M; m+=thread_cnt) {
            for (n=0; n<N; ++n) {
                mutex_lock(mutex);  
                shared_data->u[m][n] = shared_data->w[m][n];
                mutex_unlock(mutex); 
            }
        }
        barrier(barr);

        // calculate the next time frame
        shared_1d_data->diff[my_rank] = 0.0;
        for (m=my_rank; m<M; m+=thread_cnt) {
            if (m==0 || m==M-1) continue; // skip boundaries
            for (n=1; n<N-1; ++n) {
                // the temperature in the next time frame is the average of its neighbor
                shared_data->w[m][n] = (shared_data->u[m-1][n] + shared_data->u[m+1][n] + shared_data->u[m][n-1] + shared_data->u[m][n+1]) / 4.0;
                if (shared_1d_data->diff[my_rank] < absVal(shared_data->w[m][n] - shared_data->u[m][n])) {
                    mutex_lock(mutex);  
                    shared_1d_data->diff[my_rank] = absVal(shared_data->w[m][n] - shared_data->u[m][n]);
                    mutex_unlock(mutex); 
                }
            }
        }
        barrier(barr);
        // ask thread 0 to find the largest local diff
        // the largest local diff will be stored into the global diff, "*diff_g"
        // other threads just wait thread 0 until it has finished its job
        if (my_rank == 0) {
            *diff_g = 0.0;
            for (i=0; i<thread_cnt; ++i) {
                if (*diff_g < shared_1d_data->diff[i]) {
                    mutex_lock(mutex);  
                    *diff_g = shared_1d_data->diff[i];
                    mutex_unlock(mutex); 
                }
            }
            mutex_lock(mutex);  
            *iterations = *iterations + 1;
            mutex_unlock(mutex); 
            if (*iterations == *iterations_print) {
                printf("  %8d  %lf\n", *iterations, *diff_g);
                mutex_lock(mutex);  
                *iterations_print *= 2;
                mutex_unlock(mutex); 
            }
        }
        barrier(barr);
    }
    return NULL;
}
