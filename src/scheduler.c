#include "scheduler.h"

/**
 * The scheduler moves the awakened processes to the waiting processes
 * and takes the head of the waiting process to make it the working process.
 */
void schedule(void)
{
  /* Switching policy: round-robin: current_pid + 1)[MAX_PROC] */
  // int next_pid;
  // do {
  //   next_pid = (working_process->pid + 1)%MAX_PROC;
  // } while(!process_table[next_pid]);

  // struct process *next_process = process_table[next_pid];

  // working_process->state = WAITING;
  // next_process->state = RUNNING;

  // /* Store the last process which is needed to switch context */
  // struct process *last_process = working_process;

  // working_process = next_process;

  /* Move all the awaken processes to the waiting procesq queue. */
  //TODO:

  /* Take the last waiting process and make it the working process */

  // ctx_sw(last_process->register_save, working_process->register_save);
}