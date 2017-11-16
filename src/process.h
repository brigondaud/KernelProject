#ifndef __PROCESS_H__
#define __PROCESS_H__

#define ESP_IDX 1
#define NAME_LENGTH 255
#define REGS 5
#define STACK_SIZE 512
#define MAX_PROC 8

#include "cpu.h"
#include "stdio.h"
#include "inttypes.h"
#include "scheduler.h"
#include "time.h"

/**
 * Context switch: saves and restores contexts for two processes
*/
extern void ctx_sw(int *former_context, int *new_context);

/**
 * The different states of a process
 */
typedef enum {
  RUNNING,
  WAITING,
  SLEEPING
} proc_state;

/**
 * Process structure. In this case, the processes are threads since they have a common
 * allocated memory space
 */
struct process {
  int32_t pid;
  char name[NAME_LENGTH];
  proc_state state;
  int32_t register_save[REGS];
  int32_t execution_stack[STACK_SIZE];
  struct process *next;
  int32_t waking_time;
};

/**
 * Table containing all processes
 */
struct process *process_table[MAX_PROC];

/**
 * Pointer to the working process
 */
struct process *working_process;

/**
 * The last pid created
 */
int32_t last_pid;

/**
 * Put a process in sleep for sec seconds.
 */
void sleep(uint32_t sec);

/**
 * FIFO for waiting processes
 */
struct process *tail_waiting;
struct process *head_waiting;

/**
 * FIFO for sleeping processes
 */
struct process *tail_sleeping;
struct process *head_sleeping;

/**
 * Get the next process in the given queue
 */
struct process *pop_waiting(struct process *head_queue);

/**
 * Add a process to the given queue
 */
void push_waiting(struct process *proc, struct process *tail_queue);

/**
 * Idle process
 */
void idle(void);

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

/**
 * Creates a process with a given pid and a name
 */
int32_t create_process(void (*function)(void), char *name);

#endif
