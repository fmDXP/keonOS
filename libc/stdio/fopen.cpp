/*
 * keonOS - libc/stdio/fopen.cpp
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

#include <stdio.h>
#include <stdlib.h>
#include <fs/vfs.h>
#include <mm/heap.h>


extern "C" FILE* fopen(const char* filename, [[maybe_unused]] const char* mode)
{
    VFSNode* node = vfs_open(filename);
    if (!node) return NULL;
	
    FILE* stream = (FILE*)kmalloc(sizeof(FILE));
    if (!stream) {
        vfs_close(node);
        return NULL;
    }

    stream->fd = (uintptr_t)node;
    stream->offset = 0;
    stream->size = node->size;
    stream->error = 0;

    return stream;
}