#ifndef KBD_H
#define KBD_H
#include "isr.h"
#include "screen.h"
//#include "shell.h"
void keyboard_handler(struct regs *r);
void pause();
#endif
