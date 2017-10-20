#ifndef __PROCESS_H__
#define __PROCESS_H__

#define ESP_IDX 1
#define NAME_LENGTH 255
#define REGS 5
#define STACK_SIZE 512
#define MAX_PROC 2

#include "cpu.h"
#include "stdio.h"
#include "inttypes.h"
#include "scheduler.h"

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
  char name[NAME_LENGTH];
  proc_state state;
  int32_t register_save[REGS];
  int32_t execution_stack[STACK_SIZE];
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

/**
 * Init the processes (stack)
 */
void init_process(void);

/**
 * Get the current process pid
 */
int get_pid(void);

/**
 * Get the current process name
 */
char* get_name(void);

#endif
