#include <screen.h>

uint16_t *ptr_mem(uint32_t lig, uint32_t col)
{
  uint16_t *ptr_mem;
  ptr_mem = (uint16_t*)(FIRST_VID_ADDR + 2*(lig*SCREEN_WIDTH+col));
  return ptr_mem;
}

void ecrit_car(uint32_t lig, uint32_t col, char c, uint8_t text_color, uint8_t back_color)
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

void efface_ecran(void)
{
  for (uint8_t i = 0; i < SCREEN_HEIGHT; i++) {
    for (uint8_t j = 0; j < SCREEN_WIDTH; j++) {
      ecrit_car(i, j, ' ', DEFAULT_TEXT_COLOR, DEFAULT_BACK_COLOR);
    }
  }
}

void place_curseur(uint32_t lig, uint32_t col)
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
  outb((uint8_t)(cursor_pos<<8), DATA_CURSOR_PORT);

}

void traite_car(char c)
{
  switch (c) {

    case '\b':
      if (current_cursor_column != 0) {
        current_cursor_column -= 1;
        place_curseur(current_cursor_line, current_cursor_column);
      }
      break;

    case '\t':
      

      break;

    case '\n':

      break;

    case '\f':

      break;

    case '\r':

      break;

    default:

  }
}
