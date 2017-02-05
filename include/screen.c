#include "screen.h"
#include "portio.h"
#include "util.h"

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

  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset));

}

int handle_scrolling(int cursor_offset){
  if (cursor_offset < MAX_ROWS*MAX_COLS*2){
    return cursor_offset;
  }

  for(int i = 1; i < MAX_ROWS; i++){
    memory_copy(get_screen_offset(0, i)*2 + VIDEO_ADDRESS,
                get_screen_offset(0, i-1)*2 + VIDEO_ADDRESS,
                MAX_COLS*2);
  }

  char* last_line = get_screen_offset(0, MAX_ROWS-1)*2 + VIDEO_ADDRESS;
  for(int i = 0; i<MAX_ROWS*2; i++){
    last_line[i]=0;
  }

  cursor_offset -= 2*MAX_COLS;
  return cursor_offset;
}

void print_char_at(char c, int offset, char attribute_byte){
  if(attribute_byte <= 0){
    attribute_byte = WHITE_ON_BLACK;
  }
  if(offset<0){
    offset = get_cursor();
  }

  if(c == '\n'){
    int line_num = offset / MAX_COLS;
    offset = (line_num+1)*MAX_COLS;
    set_cursor(handle_scrolling(offset*2)/2);
    return;
  }

  set_cursor(offset+1);

  char* vidmem = (char*) VIDEO_ADDRESS;
  vidmem[offset*2] = c;
  vidmem[offset*2+1] = attribute_byte;

  set_cursor(handle_scrolling((offset+1)*2)/2);

}

void print_at(char* txt, int offset, char attribute_byte){
  if(offset < 0){
    offset = get_cursor();
  }

  set_cursor(offset);
  int i = 0;
  while (txt[i]) {
    print_char_at(txt[i++], -1, attribute_byte);
  }
}

void print(char* txt){
  print_at(txt, -1, -1);
}

void clear_screen(){
  for(int row = 0; row<MAX_ROWS; row++){
    for(int col = 0; col<MAX_COLS; col++){
      print_char_at(' ', get_screen_offset(col, row), WHITE_ON_BLACK);
    }
  }

  set_cursor(get_screen_offset(0, 0));
}
