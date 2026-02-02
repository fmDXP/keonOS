; *****************************************************************************
; * keonOS - kernel/arch/x86_64/asm/syscall_entry.asm
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
global syscall_entry
extern syscall_handler

syscall_entry:
    swapgs
    mov [gs:8], rsp
    mov rsp, [gs:0]

    push qword [gs:8]
    push r11
    push rcx

    push rbp
    push rbx
    push rdi
    push rsi
    push rdx
    push r10
    push r8
    push r9
    push r12
    push r13
    push r14
    push r15

    mov r9, r8      ; Arg 5 U -> Arg 6 C++
    mov r8, r10     ; Arg 4 U -> Arg 5 C++
    mov rcx, rdx    ; Arg 3 U -> Arg 4 C++
    mov rdx, rsi    ; Arg 2 U -> Arg 3 C++
    mov rsi, rdi    ; Arg 1 U -> Arg 2 C++
    mov rdi, rax    ; Num Sys -> Arg 1 C++

    mov rbp, rsp
    and rsp, -16
    call syscall_handler
    mov rsp, rbp

    pop r15
    pop r14
    pop r13
    pop r12
    pop r9
    pop r8
    pop r10
    pop rdx
    pop rsi
    pop rdi
    pop rbx
    pop rbp

    pop rcx
    pop r11
    pop rsp

    swapgs
    o64 sysret