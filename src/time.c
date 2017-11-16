#include "time.h"

/* Stores the number of seconds passed */
uint32_t seconds_elapsed = 0;
/* Tics elasped within a second */
uint8_t tics_elapsed = 0;
/* Uptime to print */
char uptime[] = "00:00:00";

void tic_PIT(void)
{
  outb(CMD_HANDLE_DATA, CMD_HANDLE_PORT);
  tics_elapsed ++;
  if (tics_elapsed == CLOCKFREQ) {
    seconds_elapsed++;
    tics_elapsed = 0;
    sprintf(uptime, "%02u:%02u:%02u", seconds_elapsed/3600, (seconds_elapsed/60)%60, seconds_elapsed % 60);
    uptime_write(uptime);
  }
}

void pit_init(void)
{
  outb(CMD_CLOCK_FREQ_DATA, CMD_CLOCK_FREQ_PORT);
  /* Sending LSB */
  outb((QUARTZ / CLOCKFREQ) % 256, CLOCK_FREQ_DATA_PORT);
  /* Sending MSB */
  outb((uint8_t)((QUARTZ / CLOCKFREQ)>>8), CLOCK_FREQ_DATA_PORT);
}

uint32_t get_time(){
  return seconds_elapsed;
}