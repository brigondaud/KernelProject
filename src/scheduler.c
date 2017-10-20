#include "scheduler.h"

void schedule(void)
{
  /* Switching policy: round-robin: current_pid + 1)[MAX_PROC] */
  int next_pid = (working_process->pid + 1)%MAX_PROC;
  struct process *next_process = &process_table[next_pid];

  working_process->state = WAITING;
  next_process->state = RUNNING;

  /* Store the last process which is needed to switch context */
  struct process *last_process = working_process;
  
  working_process = next_process;

  ctx_sw(last_process->register_save, working_process->register_save);
}