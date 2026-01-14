; *****************************************************************************
; * keonOS - kernel/arch/x86_64/asm/idt_flush.asm
; * Copyright (C) 2025-2026 fmdxp
; *
; * This program is free software: you can redistribute it and/or modify
; * it under the terms of the GNU General Public License as published by
; * the Free Software Foundation, either version 3 of the License, or
; * (at your option) any later version.
; *
; * ADDITIONAL TERMS (Per Section 7 of the GNU GPLv3):
; * - Original author attributions must be preserved in all copies.
; * - Modified versions must be marked as different from the original.
; * - The name "keonOS" or "fmdxp" cannot be used for publicity without permission.
; *
; * This program is distributed in the hope that it will be useful,
; * but WITHOUT ANY WARRANTY; without even the implied warranty of
; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
; * See the GNU General Public License for more details.
; *****************************************************************************


[BITS 64]

global idt_flush
idt_flush:
    lidt [rdi]
    ret

%macro ISR_NOERRCODE 1
global isr%1
isr%1:
    cli
    push qword 0 
    push qword %1 
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
global isr%1
isr%1:
    cli
    push qword %1
    jmp isr_common_stub
%endmacro

%macro IRQ 2
global irq%1
irq%1:
    cli
    push qword 0
    push qword %2
    jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_ERRCODE   14
IRQ 0, 32
IRQ 1, 33

extern isr_exception_handler



isr_common_stub:
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    mov rdi, rsp

    mov rbp, rsp
    and rsp, -16

    call isr_exception_handler
    
    mov rsp, rbp

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    add rsp, 16
    iretq