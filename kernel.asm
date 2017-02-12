%macro pushAll 0
      push   rax
      push   rcx
      push   rdx
      push   rbx
      push   rbp
      push   rsi
      push   rdi
%endmacro

%macro popAll 0
      pop      rdi
      pop      rsi
      pop      rbp
      pop      rbx
      pop      rdx
      pop      rcx
      pop      rax
%endmacro


section .text
[bits 64]



global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ;sti
    ret

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

%macro ISR_NOCODE 1
	isr%1:
		cli
		push byte 0
		push byte %1
		jmp isr_common_stub
%endmacro

%macro ISR_CODE 1
	isr%1:
		cli
		push byte %1
		jmp isr_common_stub
%endmacro


;Divide By Zero Exception
ISR_NOCODE 0

;Debug Exception
ISR_NOCODE 1

;Non Maskable Interrrupt Exception
ISR_NOCODE 2

;Breakpoint Exception
ISR_NOCODE 3

;Into Detected Overflow Exception
ISR_NOCODE 4

;Out of Bounds Exception
ISR_NOCODE 5

;Invalid Opcode Exception
ISR_NOCODE 6

;No Coprocessor Exception
ISR_NOCODE 7

;Double Fault Exception
ISR_CODE 8

;Coprocessor Segment Overrun Exception
ISR_NOCODE 9

;Bad TSS Exception
ISR_CODE 10

;Segment Not Present Exception
ISR_CODE 11

;Stack Fault Exception
ISR_CODE 12

;General Protection Fault Exception
ISR_CODE 13

;Page Fault Exception
ISR_CODE 14

;Unknown Interrupt Exception
ISR_NOCODE 15

;Coprocessor Fault Exception
ISR_NOCODE 16

;Alignment Check Exception
ISR_NOCODE 17

;Machine Check Exception
ISR_NOCODE 18

;Reserved
ISR_NOCODE 19

;Reserved
ISR_NOCODE 20

;Reserved
ISR_NOCODE 21

;Reserved
ISR_NOCODE 22

;Reserved
ISR_NOCODE 23

;Reserved
ISR_NOCODE 24

;Reserved
ISR_NOCODE 25

;Reserved
ISR_NOCODE 26

;Reserved
ISR_NOCODE 27

;Reserved
ISR_NOCODE 28

;Reserved
ISR_NOCODE 29

;Reserved
ISR_NOCODE 30

;Reserved
ISR_NOCODE 31

extern fault_handler
isr_common_stub:
    pushAll

    mov ax, ds
    push rax

    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call fault_handler

    pop rbx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popAll
    add rsp, 8   ; Cleans up the pushed error code and pushed ISR number
    iretq         ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

%macro make_irq 1
	irq%1:
		cli
		push byte 0
		push byte %1+32
		jmp irq_common_stub
%endmacro

make_irq 0
make_irq 1
make_irq 2
make_irq 3
make_irq 4
make_irq 5
make_irq 6
make_irq 7
make_irq 8
make_irq 9
make_irq 10
make_irq 11
make_irq 12
make_irq 13
make_irq 14
make_irq 15

extern irq_handler

; This is a stub that we have created for IRQ based ISRs. This calls
; '_irq_handler' in our C code. We need to create this in an 'irq.c'
irq_common_stub:
    pushAll

    mov ax, ds
    push rax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop rbx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    ;pop rax
    popAll
    add rsp, 8
    iretq
