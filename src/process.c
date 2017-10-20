#include "process.h"


void idle(void)
{
  for (;;) {
    printf("[%s] pid = %i\n", get_name(), get_pid());
    schedule();
  }
}
void proc1(void) {
  for (;;) {
    printf("[%s] pid = %i\n", get_name(), get_pid());
    schedule();
  }
}

int get_pid()
{
  return working_process->pid;
}

char* get_name()
{
  return working_process->name;
}

void init_process(void)
{
  process_table[0] = (struct process) {
    .pid = 0,
    .name = "idle",
    .state = RUNNING
  };
  
  process_table[1] = (struct process) {
    .pid = 1,
    .name = "proc1",
    .state = WAITING
  };

  process_table[1].execution_stack[STACK_SIZE-1] = (int)proc1;
  process_table[1].register_save[ESP_IDX] = (int)(&process_table[1].execution_stack[STACK_SIZE-1]);
  
  working_process = &process_table[0];
}