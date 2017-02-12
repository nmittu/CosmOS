#include "screen.h"
#include "portio.h"
#include "util.h"

char* vidmem = ((char*)VIDEO_ADDRESS);
int cursorX = 0, cursorY = 0;


int get_screen_offset(int col, int row){
  return (row*MAX_COLS+col);
}

int get_cursor(){
  port_byte_out(REG_SCREEN_CTRL, 14);
  int offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);
}

void set_cursor(int offset){

  cursorY = offset/MAX_COLS;
  cursorX = offset%MAX_COLS;

  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset));

}

void handle_scrolling(){
  if(cursorY >= MAX_ROWS-1){
    for(int i = 1; i < MAX_ROWS; i++){
      memory_copy(get_screen_offset(0, i)*2 + VIDEO_ADDRESS,
                  get_screen_offset(0, i-1)*2 + VIDEO_ADDRESS,
                  MAX_COLS*2);
    }

    char* last_line = get_screen_offset(0, MAX_ROWS-1)*2 + VIDEO_ADDRESS;
    for(int i = 0; i<MAX_COLS*2; i++){
      last_line[i]=0;
    }

    cursorX = 0;
    cursorY--;
    set_cursor(get_screen_offset(cursorX, cursorY));
  }
}

void print_char(char c, char attribute_byte){
  if(attribute_byte <= 0){
    attribute_byte = WHITE_ON_BLACK;
  }

  switch (c) {
    case (0x08):
      if (cursorX > 0) {
        cursorX--;
        vidmem[get_screen_offset(cursorX, cursorY)*2]=0x00;
      }
      break;
    case ('\r'):
      cursorX = 0;
      break;
    case ('\n'):
      cursorX = 0;
      cursorY++;
      break;
    default:
      vidmem[get_screen_offset(cursorX, cursorY)*2] = c;
      vidmem[get_screen_offset(cursorX, cursorY)*2+1] = attribute_byte;
      cursorX++;
      break;

  }
  if (cursorX >= MAX_COLS) {
    cursorX = 0;
    cursorY++;
  }
  set_cursor(get_screen_offset(cursorX, cursorY));
  handle_scrolling();
}

void print_attr(char* txt, char attribute_byte){
  int i = 0;
  while (txt[i]) {
    print_char(txt[i++], attribute_byte);
  }
}

void print(char* txt){
  print_attr(txt, -1);
}

void clear_screen(){
  for(int row = 0; row<MAX_ROWS; row++){
    for(int col = 0; col<MAX_COLS; col++){
      print_char(' ', WHITE_ON_BLACK);
    }
  }

  set_cursor(get_screen_offset(0, 0));
}
