#include "test_queue.h"

void test_waiting_queue()
{   
    erase_screen();
    create_process(NULL, "proc0");
    create_process(NULL, "proc1");
    struct process *proc1 = pop(&tail_waiting, &head_waiting);
    struct process *proc2 = pop(&tail_waiting, &head_waiting);
    struct process *proc0 = pop(&tail_waiting, &head_waiting);
    if (proc1->pid == 1 && proc2->pid == 2 && proc0 == NULL) {
        printf("Test waiting queue: PASSED\n");
    } else {
        printf("Test waiting queue: FAILED\n");
    }
}

void test_sleeping_queue(void) {
    erase_screen();
    create_process(NULL, "proc1");
    create_process(NULL, "proc2");
    create_process(NULL, "proc3");
    struct process *proc1 = pop(&tail_waiting, &head_waiting);
    struct process *proc2 = pop(&tail_waiting, &head_waiting);
    struct process *proc3 = pop(&tail_waiting, &head_waiting);
    proc1->waking_time = get_time() + 10000;
    proc2->waking_time = get_time() + 0;
    proc3->waking_time = get_time() + 5000;
    push_sleeping(&proc1);
    push_sleeping(&proc2);
    push_sleeping(&proc3);
    struct process *proc2b = pop(&tail_sleeping, &head_sleeping);
    struct process *proc3b = pop(&tail_sleeping, &head_sleeping);
    struct process *proc1b = pop(&tail_sleeping, &head_sleeping);
    if(proc1b->pid == 1 &&
        proc2b->pid == 2 &&
        proc3b->pid == 3) {
        printf("Test sleeping queue: PASSED\n");
    } else {
        printf("Test sleeping queue: FAILED\n");
    }
}

