#include "process.h"
#include "malloc.c.h"

void idle()
{
  for (;;) {
    sti();
    hlt();
    cli();
  }
}
void proc1(void)
{
  for (;;) {
    printf("[temps = %u] processus %s pid = %i\n", get_time(),
    get_name(), get_pid());
    sleep(2);
  }
}
void proc2(void)
{
  for (;;) {
    printf("[temps = %u] processus %s pid = %i\n", get_time(),
    get_name(), get_pid());
    sleep(3);
  }
}
void proc3(void)
{
  for (;;) {
    printf("[temps = %u] processus %s pid = %i\n", get_time(),
    get_name(), get_pid());
    sleep(5);
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

struct process *pop_waiting(struct process *queue)
{
  struct process *proc;
  if (head_waiting == last_waiting) {
    proc = head_waiting;
    head_waiting = NULL;
    last_waiting = NULL;
  } else {
    struct process *head = head_waiting;
    struct process *current = last_waiting;
    while (current->next != head) {
      current = current->next;
    }
    proc = head_waiting;
    head_waiting = current;
  }
  proc->state = RUNNING;
  return proc;
}

void push_waiting(struct process *proc, struct process *tail_queue)
{
  //TODO:
}

int32_t create_process(void (*code)(void), char *name)
{
  if(last_pid == MAX_PROC-1) // Can't create process anymore
    return -1;
  
  last_pid++;
  struct process *proc = malloc(sizeof(struct process));
  proc->pid = last_pid;
  strcpy(proc->name, name);
  proc->state = WAITING;
  proc->execution_stack[STACK_SIZE-1] = (int32_t)code;
  proc->register_save[ESP_IDX] = (int32_t)(&proc->execution_stack[STACK_SIZE-1]);
  proc->waking_time = -1;
  process_table[last_pid] = proc;
  return last_pid;
}

void init_process(void)
{
  last_pid = -1;
  for (int i = 0; i < 8; i++) {
    char name[NAME_LENGTH];
    sprintf(name, "proc%d", i);
    int pid = create_process(proc0, name);
    printf("Init of the process: %d\n", pid);
  }
  working_process = process_table[0];
}