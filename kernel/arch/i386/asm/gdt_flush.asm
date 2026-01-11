; *****************************************************************************
; * keonOS - kernel/arch/i386/asm/gdt_flush.asm
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
global gdt_flush

gdt_flush:
    mov eax, [esp + 4]  
    lgdt [eax]      

    mov ax, 0x10        
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush     

.flush:
    ret