#include "screen.h"

/* Information about the current cursor position */
static uint32_t current_cursor_line;
static uint32_t current_cursor_column;

//TODO: memorize the color of the text and the background

uint16_t *ptr_mem(uint32_t lig, uint32_t col)
{
  uint16_t *ptr_mem;
  ptr_mem = (uint16_t*)(FIRST_VID_ADDR + 2*(lig*SCREEN_WIDTH+col));
  return ptr_mem;
}

void write_char(uint32_t lig, uint32_t col, char c, uint8_t text_color, uint8_t back_color)
{
  uint16_t *screen_ptr;
  screen_ptr = ptr_mem(lig, col);
  /* Set the screen_ptr memory to zero */
  *screen_ptr = 0x0000;
  /* Set the c value in the LS byte */
  *screen_ptr |= c;
  /* Set the format in the MS Byte */
  uint8_t format = 0x00;
  format |= (back_color << 4);
  format |= text_color;
  *screen_ptr |= format << 8;
}

void erase_screen(void)
{
  for (uint8_t i = 0; i < SCREEN_HEIGHT; i++) {
    for (uint8_t j = 0; j < SCREEN_WIDTH; j++) {
      write_char(i, j, ' ', DEFAULT_TEXT_COLOR, DEFAULT_BACK_COLOR);
    }
  }
}

void cursor_move(uint32_t lig, uint32_t col)
{
  /* Changing the current cursor position */
  current_cursor_line = lig;
  current_cursor_column = col;

  uint16_t cursor_pos = current_cursor_column + current_cursor_line * SCREEN_WIDTH;
  /* Sending LS Byte */
  outb(0x0F, CMD_CURSOR_PORT);
  outb((uint8_t)cursor_pos, DATA_CURSOR_PORT);
  /* Sending MS Byte */
  outb(0X0E, CMD_CURSOR_PORT);
  outb((uint8_t)(cursor_pos>>8), DATA_CURSOR_PORT);

}

void scroll(void)
{
  /* Moving the lines in memory*/
  memmove(ptr_mem(0, 0), ptr_mem(1, 0), (SCREEN_HEIGHT-1)*SCREEN_WIDTH*sizeof(uint16_t));
  /* Erasing the last line */
  for (uint8_t i = 0; i < SCREEN_WIDTH; i++) {
    write_char(SCREEN_WIDTH-1, i, ' ', DEFAULT_TEXT_COLOR, DEFAULT_BACK_COLOR);
  }
}

void handle_char(char c)
{
  /* If a control char */
  if (c < 32 || c == 127) {
    switch (c) {
      
      case '\b':
        if (current_cursor_column != 0) {
          current_cursor_column -= 1;
          cursor_move(current_cursor_line, current_cursor_column);
        }
        break;
  
      case '\t':
        /* The new position */
        current_cursor_column = (current_cursor_column / TAB_LENGTH + 1) * TAB_LENGTH;
        if (current_cursor_column > SCREEN_WIDTH) { /* If out of the screen */
          current_cursor_column = SCREEN_WIDTH - 1;
        }
        cursor_move(current_cursor_line, current_cursor_column);
        break;

      case '\n':
        current_cursor_column = 0;
        if (current_cursor_line == SCREEN_HEIGHT - 1) {
          scroll();
          current_cursor_line = SCREEN_HEIGHT - 1;
        } else {
          current_cursor_line += 1;
        }
        cursor_move(current_cursor_line, current_cursor_column);
  
        break;
  
      case '\f':
        erase_screen();
        cursor_move(0, 0);
  
        break;
  
      case '\r':
        cursor_move(current_cursor_line, 0);
        break;

      default:
        /* The other control char are not handled */
        break;
  
    }
  } else {
    /* Handle as a normal char */
    uint32_t prev_cursor_line = current_cursor_line;
    uint32_t prev_cursor_column = current_cursor_column;

    if (current_cursor_column == SCREEN_WIDTH - 1) {
      current_cursor_column = 0;
      if (current_cursor_line == SCREEN_HEIGHT - 1) {
        current_cursor_line = SCREEN_HEIGHT - 1;
        scroll();
      } else {
        current_cursor_line += 1;
      }
    } else {
      current_cursor_column += 1;
    }
    write_char(prev_cursor_line, prev_cursor_column, c, DEFAULT_TEXT_COLOR, DEFAULT_BACK_COLOR);
    cursor_move(current_cursor_line, current_cursor_column);
  }
}

void uptime_write(char *uptime)
{
  /* The uptime format is HH:MM:SS */
  char *c = uptime;
  for (int i = 0; i < 8; i++, c++) {
    write_char(0, SCREEN_WIDTH-1-i, *c, UPTIME_TEXT_COLOR, UPTIME_BACK_COLOR);
  }
}
