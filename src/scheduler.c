#include "scheduler.h"

/**
 * The scheduler moves the awakened processes to the waiting processes
 * and takes the head of the waiting process to make it the working process.
 */
void schedule(void)
{
  printf("scheduling\n");
  /* Move all the awaken processes to the waiting process queue. */
  struct process *sleeping;
  while(head_sleeping && head_sleeping->waking_time <= get_time()) {
    sleeping = pop(&tail_sleeping, &head_sleeping);
    push_waiting(&sleeping);
  }

  /* Take the last waiting process and make it the working process */
  struct process *new_working = pop(&tail_waiting, &head_waiting);
  /* Inverts the new working process and the last working process */
  working_process->state = WAITING;
  push_waiting(&working_process);
  new_working->state = RUNNING;
  struct process *last_process = working_process;
  working_process = new_working;
  /* Scheduler is called from tic_PIT so we must enable IT. */
  sti();
  printf("scheduled ! now switching context\n");
  ctx_sw(last_process->register_save, working_process->register_save);
}