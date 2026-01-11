; *****************************************************************************
; * keonOS - kernel/arch/i386/asm/idt_flush.asm
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



[BITS 32]

global idt_flush

idt_flush:
    mov eax, [esp + 4] 
    lidt [eax]        
    ret

global isr0
global isr1

isr0:
    cli
    push byte 0       
    push byte 0     
    jmp isr_common_stub

isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

global isr14
isr14:
    cli
    push byte 14      
    jmp isr_common_stub

extern isr_exception_handler
isr_common_stub:
    pusha            

    mov ax, ds
    push eax         

    mov ax, 0x10    
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp        
    call isr_exception_handler
    add esp, 4      

    pop eax          
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa           
    add esp, 8       
    sti
    iret             

global irq0
extern timer_handler

irq0:
    cli
    push byte 0
    push byte 32
    jmp isr_common_stub


global irq1
extern keyboard_handler

irq1:
    cli
    push byte 0
    push byte 33
    jmp isr_common_stub