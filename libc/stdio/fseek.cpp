/*
 * keonOS - libc/stdio/fseek.cpp
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

extern "C" int fseek(FILE* stream, long offset, int whence) 
{
    if (!stream) return -1;

    switch (whence) 
    {
        case SEEK_SET:
            if (offset < 0) return -1;
            stream->offset = (uint32_t)offset;
            break;

        case SEEK_CUR:
            if (offset < 0 && (uint32_t)(-offset) > stream->offset) return -1;
            stream->offset += offset;
            break;

        case SEEK_END:
            if (offset > 0) return -1;
            if ((uint32_t)(-offset) > stream->size) return -1;
            stream->offset = stream->size + offset;
            break;

        default:
            return -1;
    }

    stream->error = 0;
    return 0;
}