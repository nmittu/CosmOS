section .text
[bits 32]
global start
start:
  mov eax, p3_table
  or eax, 0b11
  mov dword [p4_table], eax

  mov eax, p2_table
  or eax, 0b11
  mov dword [p3_table], eax

  mov ecx, 0
  map_p2_table:
    mov eax, 0x200000
    mul ecx
    or eax, 0b10000011
    mov [p2_table + ecx * 8], eax

    inc ecx
    cmp ecx, 512
    jne map_p2_table

  mov eax, p4_table
  mov cr3, eax

  ;enable p4_table

  mov eax, cr4
  or eax, 1 << 5
  mov cr4, eax

  ; set the long mode bit
  mov ecx, 0xc0000080
  rdmsr
  or eax, 1 << 8
  wrmsr

  ; enable paging
  mov eax, cr0
  or eax, 1 << 31
  or eax, 1 << 16
  mov cr0, eax

  ;Load GDT
  lgdt [gdt64.pointer]

  ; update selectors
  mov ax, gdt64.data
  mov ss, ax
  mov ds, ax
  mov es, ax

  jmp gdt64.code:long_mode_start

  ;call kmain
  ;jmp $

  ;;mov  dword [0xb8000], 0x2f4b2f4f
  ;;hlt

section .bss

align 4096

p4_table:
    resb 4096
p3_table:
    resb 4096
p2_table:
    resb 4096

section .rodata
gdt64:
  dq 0
.code: equ $ - gdt64
  dq (1<<44) | (1<<47) | (1<<41) | (1<<43) | (1<<53)
.data: equ $ - gdt64
  dq (1<<44) | (1<<47) | (1<<41)
.pointer:
  dw .pointer - gdt64 - 1
  dq gdt64

section .text
bits 64
[extern kmain]
long_mode_start:
  mov rax, 0x2f592f412f4b2f4f
  mov qword [0xb8000], rax
  call kmain
  hlt
