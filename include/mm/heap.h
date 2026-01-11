/*
 * keonOS - include/mm/heap.h
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

#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <stddef.h>

struct heap_block
{
	size_t size;
	bool free;
	struct heap_block* next;
};

struct heap_stats
{
	size_t total_size;
	size_t used_size;
	size_t free_size;
	size_t block_count;
	size_t free_block_count;
};

bool kheap_init(void* start_addrm, size_t size);
void* kmalloc(size_t size);
void kfree(void* ptr);
void kheap_get_stats(struct heap_stats* stats);

inline void* operator new(size_t, void* p) throw() {
    return p;
}

void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
void operator delete(void* ptr, size_t size) noexcept;

heap_block* get_kheap_start();

#endif		// HEAP_H