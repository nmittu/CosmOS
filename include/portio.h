#ifndef PORTIO_H
#define PORTIO_H

#include "util.h"

#define port_byte_in inb
#define port_byte_out outb
#define port_word_in inw
#define port_word_out outw

//unsigned char inb ( unsigned short port );
//void outb ( unsigned short port , unsigned char data );
//unsigned short inw ( unsigned short port );
//void outw ( unsigned short port , unsigned short data );

#endif
