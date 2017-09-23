#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <inttypes.h>
#include <string.h>
#include <cpu.h>

#define FIRST_VID_ADDR 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define CMD_CURSOR_PORT 0x3D4
#define DATA_CURSOR_PORT 0x3D5
#define DEFAULT_TEXT_COLOR 0
#define DEFAULT_BACK_COLOR 15
#define TAB_LENGTH 4

/* Information about the current cursor position */
static uint32_t current_cursor_line;
static uint32_t current_cursor_column;

/*
* This function returns a pointer to the memory corresponding to the giving
* screen coordinates
*/
uint16_t *ptr_mem(uint32_t lig, uint32_t col);

/*
* This function write the character c to th given coordinates
*/
void ecrit_car(uint32_t lig, uint32_t col, char c, uint8_t front_color, uint8_t back_color);

/*
* Erases the screen
*/
void efface_ecran(void);

/*
* Places the cursor at a given position
*/
void place_curseur(uint32_t lig, uint32_t col);

/*
* Implements an effect if c is a special char, or just prints c
*/
void traite_car(char c);

#endif
