#ifndef __PROCESS_H__
#define __PROCESS_H__

#define ESP_IDX 1
#define MAX_PROC 2

#include "inttypes.h"

/**
 * Context switch: saves and restores contexts for two processes
*/
extern void ctx_sw(int *former_context, int *new_context);

/**
 * The different states of a process
 */
typedef enum {
  RUNNING,
  WAITING
} proc_state;

/**
 * Process structure. In this case, the processes are threads since they have a common
 * allocated memory space
 */
struct process {
  int pid;
  char name[255];
  proc_state state;
  int32_t register_save[5];
  int32_t execution_stack[512];
};

/**
 * Table containing all processes
 */
struct process process_table[MAX_PROC];

/**
 * Pointer to the working process
 */
struct process *working_process;

/**
 * Idle process
 */
void idle(void);

/**
 * proc1 process
 */
void proc1(void);

void init_process(void);

#endif
