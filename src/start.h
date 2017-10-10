#ifndef __START_H__
#define __START_H__

#define FIRST_STACK_SIZE 16384

#ifndef ASSEMBLER

#include "interrupt.h"

extern char first_stack[FIRST_STACK_SIZE];

#endif

#endif
