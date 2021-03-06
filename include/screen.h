#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

int get_cursor();
void set_cursor(int offset);
void print_char(char c, char attribute_byte);
void print_attr(char* txt, char attribute_byte);
void print(char* txt);
void clear_screen();
#endif
