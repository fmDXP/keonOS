; *****************************************************************************
; * keonOS - kernel/arch/x86_64/asm/paging_flush.asm
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

global paging_load_directory
global paging_enable
global paging_disable

paging_load_directory:
    mov cr3, rdi
    ret

paging_enable:
    mov rax, cr0
    or rax, 0xFFFFFFFF80000000
    mov cr0, rax
    jmp .flush
.flush:
    ret


; paging_disable:
;     mov rax, cr0
;     and rax, 0x7FFFFFFF
;     mov cr0, rax
;     ret