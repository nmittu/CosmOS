#ifndef UTIL_H
#define  UTIL_H

typedef char *string;

void memory_copy (char* source, char* dest, int no_bytes);


#define port_byte_in inb
#define port_byte_out outb
#define port_word_in inw
#define port_word_out outw

unsigned char inb ( unsigned short port );
void outb ( unsigned short port , unsigned char data );
unsigned short inw ( unsigned short port );
void outw ( unsigned short port , unsigned short data );


void *memcpy(void *dest, const void *src, int count);
void *memset(void *dest, char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
int strlen(const char *str);
int strcmp(string str1,string str2);
void concat(string a, string b, string c);
void concatc(string a, char b, string c);
void remchar(string a, string b);
int toHex(char a);
int strncmp(string a, string b, int l);
int startswith(string a, string b);
void preparedisk(int disk, int addr);
void strcpy(char a[], char b[]);
char tolower(char a);
void strtolower(char a[], char b[]);
void substring(char a[], char b[], int index);
void int_to_ascii(int n, char str[]);

#endif
