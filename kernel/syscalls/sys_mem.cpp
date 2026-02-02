/*
 * keonOS - kernel/syscalls/sys_mem.cpp
 * Copyright (C) 2025-2026 fmdxp
 */

#include <kernel/syscalls/syscalls.h>
#include <kernel/arch/x86_64/thread.h>
#include <kernel/arch/x86_64/paging.h>
#include <stdint.h>

uint64_t sys_sbrk(uint64_t increment, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6) 
{
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    thread_t* current = thread_get_current();
    if (!current || !current->is_user) return -1;

    uintptr_t old_break = current->user_heap_break;
    if (increment == 0) return old_break;

    // Allocate new pages if needed
    uintptr_t new_break = old_break + increment;
    
    // Page-align calculations
    uintptr_t start_page = (old_break + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
    uintptr_t end_page = (new_break + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);

    for (uintptr_t addr = start_page; addr < end_page; addr += PAGE_SIZE) 
    {
        void* frame = pfa_alloc_frame();
        if (!frame) return -1; // Out of memory
        paging_map_page((void*)addr, frame, PTE_PRESENT | PTE_RW | PTE_USER);
    }

    current->user_heap_break = new_break;
    return old_break;
}
