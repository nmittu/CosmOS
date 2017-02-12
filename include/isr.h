#ifndef ISR_H
#define ISR_H

//#include "screencontroller.h"
#include "idt.h"
#include "error.h"

struct regs{
    unsigned long long ds;      /* pushed the segs last */
    unsigned long long rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax;  /* pushed by 'pusha' */
    unsigned long long int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned long long eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */
} __attribute__((packed));

void isrs_install();

void fault_handler(struct regs *r);

#endif
