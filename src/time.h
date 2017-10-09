#ifndef __TIME_H__
#define __TIME_H__

#include "stdio.h"
#include "inttypes.h"
#include "string.h"
#include "cpu.h"
#include "screen.h"

#define CMD_HANDLE_PORT 0x20
#define CMD_HANDLE_DATA 0x20
#define CMD_CLOCK_FREQ_DATA 0x34
#define CMD_CLOCK_FREQ_PORT 0X43
#define CLOCK_FREQ_DATA_PORT 0x40
#define QUARTZ 0x1234DD
#define CLOCKFREQ 50


/* Init the PIT to PIT_SPEED */
void pit_init(void);

/* Handles the interruption and prints the uptime */
extern void tic_PIT(void);

/*  */

#endif
