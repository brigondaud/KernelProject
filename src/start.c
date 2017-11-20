#include "cpu.h"
#include "stdio.h"
#include "process.h"
#include "start.h"
#include "test_queue.h"

void kernel_start(void)
{
  // /* Unhides the 0 IRQ to the PIC to receive PIT signal */
  hide_IRQ(0, 0);
  
  // /* Registering the handler to display uptime */
  init_handler_IT(32, &traitant_IT_32);

  pit_init();

  erase_screen();

  /* Init all the processes that will be executed. */
  init_process();

  /* Runing the default process */
  idle();
  
}
