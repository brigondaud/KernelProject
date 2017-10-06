#ifndef __START_H__
#define __START_H__

#define FIRST_STACK_SIZE 16384
#define FIRST_VECTOR_HANDLER_ADDR 0x1000
#define CMD_PIC_PORT 0x21

#ifndef ASSEMBLER

#include "inttypes.h"
#include "segment.h"
#include "time.h"

extern char first_stack[FIRST_STACK_SIZE];

/* Prototype for traitant_IT_32 in traitants.S */
extern void traitant_IT_32(void);

/* The kernel entry point */
void kernel_start(void);

/* (Un)hides an IT to the PIC */
void hide_IRQ(uint32_t num_IRQ, uint8_t hide);

/* Init the handler for an IT using the IT number and its handler */
void init_handler_IT(int32_t num_IT, void (*handler)(void));

#endif

#endif
