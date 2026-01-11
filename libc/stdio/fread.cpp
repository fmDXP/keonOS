/*
 * keonOS - libc/stdio/fread.cpp
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
#include <fs/vfs.h>

extern "C" size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream) 
{
    if (!stream || stream->fd == 0) return 0;

    VFSNode* node = (VFSNode*)stream->fd;
    uint32_t total_bytes = size * nmemb;

    uint32_t read = vfs_read(node, stream->offset, total_bytes, (uint8_t*)ptr);

    stream->offset += read;

    return (size > 0) ? (read / size) : 0;
}