#include "interrupt.h"

void init_handler_IT(int32_t num_IT, void (*handler)(void))
{  
  int32_t *handler_addr;
  handler_addr = (int32_t*)(FIRST_VECTOR_HANDLER_ADDR + num_IT*8);
  
  int32_t first_word;
  first_word = ((int32_t)handler) & 0x0000FFFF;
  first_word |= KERNEL_CS << 16;

  int32_t second_word;
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