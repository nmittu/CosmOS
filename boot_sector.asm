
KERNEL_LOC equ 0x1000
[org 0x7c00]
[bits 16]

mov [BOOTDRIVE], dl

mov bp, 0x9000
mov sp, bp

mov bx, BOOTLOADERSTR
call printString

mov bx, 0x9000
mov cl, 2
mov dl, [BOOTDRIVE]
mov dh, 1

call diskLoad
call printString

call load_kernel
call switch_to_pm

jmp $

;functions

printString:
  pusha
  mov ah, 0X0E
printLoop:
  mov al, [bx]
  cmp al, 0
  je endFunc
  int 0x10
  inc bx
  jmp printLoop
endFunc:
  popa
  ret

diskLoad:
  push dx
  mov ah, 0x02
  mov al, dh
  mov ch, 0x00
  mov dh, 0x00
diskLoadGo:
  int 0x13
  jc diskError
  pop dx
  cmp al, dh
  jne diskError
  ret
diskError:
  jmp $

%include "gdt.asm"

switch_to_pm:
  mov bx, TTBITSTR
  call printString
  cli
  lgdt [gdt_descriptor]
  mov eax, cr0
  or eax, 0x1
  mov cr0, eax
  jmp KERNEL_CODE_SEG:pm_switched

load_kernel:
  mov bx, KERNEL_LOC
  mov cl, 3
  mov dl, [BOOTDRIVE]
  mov dh, 30
  call diskLoad
  push bx
  mov bx, LOADEDKERNELSTR
  call printString
  pop bx
  ret

[bits 32]

pm_switched:
  mov ax, KERNEL_DATA_SEG
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ebp, 0x90000
  mov esp, ebp
  call KERNEL_LOC
  jmp $


BOOTDRIVE db 0
BOOTLOADERSTR db "BootLoader for CosmOS v 1.0", 10, 13, "Copyright 2017 MittuDev (Nikhil Mittu)", 10, 13, 10, 13, 0
TTBITSTR db "Entering 32 Bit Protected Mode", 10, 13, 0
LOADEDKERNELSTR db "Loaded Kernel", 10, 13, 0

times 510 - ($ - $$) db 0
DW 0xAA55

db "Drive loaded successfully!", 10, 13, 0

times 1024 - ($ - $$) db 0
