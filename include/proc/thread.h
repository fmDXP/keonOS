/*
 * keonOS - include/proc/thread.h
 * Copyright (C) 2025-2026 fmdxp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ADDITIONAL TERMS (Per Section 7 of the GNU GPLv3):
 * - Original author attributions must be preserved in all copies.
 * - Modified versions must be marked as different from the original.
 * - The name "keonOS" or "fmdxp" cannot be used for publicity without permission.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 */

#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>

enum thread_state_t
{
    THREAD_RUNNING,
    THREAD_READY,
    THREAD_SLEEPING,
    THREAD_BLOCKED,
};

struct thread_t 
{
    uint32_t* esp;
    uint32_t  id;
    char      name[16];
    uint32_t* stack_start;
    thread_t* next;
    thread_state_t state;
    uint32_t sleep_ticks;
};

typedef struct 
{
    volatile int locked;
    uint32_t eflags;
} spinlock_t;


extern "C" void switch_context(uint32_t** old_esp, uint32_t** new_esp);

void thread_init();
void spin_lock(spinlock_t* lock);
void spin_unlock(spinlock_t* lock);
void spin_lock_irqsave(spinlock_t* lock);
void spin_unlock_irqrestore(spinlock_t* lock);
void thread_sleep(uint32_t ms);
void thread_wakeup_blocked();
thread_t* thread_add(void(*entry_point)(), const char* name);
thread_t* thread_create(void (*entry_point)(), const char* name);
extern "C" void yield();
void idle_task();
thread_t* thread_get_current();
thread_t* get_idle_thread_ptr();
void thread_print_list();
bool thread_kill(uint32_t id);
uint32_t thread_get_id_by_name(const char* name);
void thread_exit();

#endif      // THREAD_H