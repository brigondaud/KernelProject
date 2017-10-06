#include "cpu.h"
#include "stdio.h"
#include "start.h"
#include "screen.h"

void init_handler_IT(int32_t num_IT, void (*handler)(void))
{  
  int32_t *handler_addr;
  handler_addr = (int32_t*)(FIRST_VECTOR_HANDLER_ADDR + num_IT - 1);
  
  int32_t first_word = 0x00000000;
  first_word = ((int32_t)handler) & 0x0000FFFF;
  first_word |= KERNEL_CS << 16;

  int32_t second_word = 0x00000000;
  second_word = ((int32_t)handler) & 0xFFFF0000;
  second_word |= (int32_t)0x8E00;

  *handler_addr = first_word;
  *(handler_addr+1) = second_word;
}

void hide_IRQ(uint32_t num_IRQ, uint8_t hide)
{
  /* Current hidden IRQs */
  uint8_t IRQ_array = inb(CMD_PIC_PORT);
  /* Setting the bit num_IRQ to given hide value */
  hide = hide << num_IRQ;
  IRQ_array = (IRQ_array & ~(1<<num_IRQ)) | (hide << num_IRQ);
  /* Sending new hidden IRQs */
  outb(IRQ_array, CMD_PIC_PORT);
  
}

void kernel_start(void)
{
  /* Unhides the 0 IRQ to the PIC to receive PIT signal */
  hide_IRQ(0, 0);
  
  /* Registering the handler to display uptime */
  init_handler_IT(32, traitant_IT_32);

  pit_init();

  /* Unhides the IT to the CPU */
  sti();

  while (1) {
      // cette fonction arrete le processeur
      hlt();
  }
}
