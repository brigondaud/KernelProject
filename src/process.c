#include "cpu.h"
#include "stdio.h"
#include "process.h"


void idle(void)
{
  for (int i = 0; i < 3; i++) {
    printf("[idle] je tente de passer la main a proc1...\n");
    ctx_sw(process_table[0].register_save, process_table[1].register_save);
    printf("[idle] proc1 m’a redonne la main\n");
  }
  printf("[idle] je bloque le systeme\n");
  hlt();
}
void proc1(void)
{
  for (;;) {
    printf("[proc1] idle m’a donne la main\n");
    printf("[proc1] je tente de lui la redonner...\n");
    ctx_sw(process_table[1].register_save, process_table[0].register_save);
  }
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

  process_table[1].execution_stack[511] = (int)proc1;
  process_table[1].register_save[ESP_IDX] = (int)(&process_table[1].execution_stack[511]);
}