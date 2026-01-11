; *****************************************************************************
; * keonOS - kernel/arch/i386/asm/paging_flush.asm
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

global paging_load_directory
global paging_enable
global paging_disable

paging_load_directory:
    push ebp
    mov ebp, esp
    mov eax, [esp + 8]  
    mov cr3, eax
    mov esp, ebp
    pop ebp
    ret

paging_enable:
    mov eax, cr0      
    or eax, 0x80000000  
    mov cr0, eax      
    jmp .flush
.flush:
    ret

paging_disable:
    mov eax, cr0       
    and eax, 0x7FFFFFFF 
    mov cr0, eax        
    ret

