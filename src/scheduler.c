#include "scheduler.h"

void schedule(void)
{
  /* Switching policy: (current_pid + 1)[MAX_PROC] */
  int next_pid = (working_process->pid + 1)%MAX_PROC;
  struct process next_process = process_table[next_pid];

  working_process->state = WAITING;
  next_process.state = RUNNING;
  
  ctx_sw(working_process->register_save, next_process.register_save);
}