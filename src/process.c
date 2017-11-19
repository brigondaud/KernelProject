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

void sleep(uint32_t sec)
{
  /* Set the waiking time for the working process */
  working_process->waking_time = get_time() + sec;
  /* The process is put in the sleeping queue according to its awaking time. */
  working_process->state = SLEEPING;
  push_sleeping(&working_process);
  schedule();
}

void push_sleeping(struct process **proc)
{
  struct process *current = tail_sleeping;
  if(current == NULL) {
    tail_sleeping = *proc;
    head_sleeping = *proc;
  } else {
    struct process *prec = current;
    while(current != NULL && (*proc)->waking_time < current->waking_time) {
      prec = current;
      current = current->next;
    }
    prec->next = *proc;
    if (!current) {
      head_sleeping = *proc;
      head_sleeping->next = NULL;
    } else {
      (*proc)->next = current;
      if (current == tail_sleeping) /* If proc is inserted in tail. */
        tail_sleeping = *proc;
    }
  }
}

void push_waiting(struct process **proc)
{
  (*proc)->next = tail_waiting;
  tail_waiting = *proc;
  if(!head_waiting)
    head_waiting = *proc;
}

struct process* pop(struct process **tail, struct process **head)
{
  struct process *proc = NULL;
  if (*head == *tail) {
    proc = *head;
    *head = NULL;
    *tail = NULL;
  } else {
    struct process *current = *tail;
    while (current->next != *head) {
      current = current->next;
    }
    proc = *head;
    current->next = NULL;
    *head = current;
  }
  return proc;
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

  /* Push the created process in the waiting queue. */
  push_waiting(&proc);
  return last_pid;
}

void print_process(struct process *proc)
{
  if(!proc) {
    printf("Process is null");
  } else {
    printf("Process: pid: %d, name: %s, state:%d (0: RUNNING, 1:WAITING, 2:SLEEPING)\n", proc->pid, proc->name, proc->state);
  }
}

void init_process(void)
{
  last_pid = -1;
  /* Array to the processes code to execute. */
  void (*process_code[4])(void) = {idle, proc1, proc2, proc3};
  for (int i = 0; i < 4; i++) {
    char name[NAME_LENGTH];
    if(i==0) {
      sprintf(name, "idle");
    }
    else {
      sprintf(name, "proc%d", i+1);
    }
    create_process(process_code[i], name);
  }
  working_process = get_process_in(&tail_waiting, 0);
}

struct process* get_process_in(struct process **queue, int32_t pid)
{
  struct process *current = *queue;
  while(current && current->pid != pid){
    current = current->next;
  }
  return current;
}