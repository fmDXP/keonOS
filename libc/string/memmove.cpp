/*
 * keonOS - libc/string/memmove.cpp
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

#include <string.h>

void* memmove(void* dstptr, const void* srcptr, size_t size)
{
	unsigned char* dst = reinterpret_cast<unsigned char*>(dstptr);
	const unsigned char* src = reinterpret_cast<const unsigned char*>(srcptr);

	if (dst < src)
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	
	else
		for (size_t i = size; i != 0; i--)
			dst[i - 1] = src [i - 1];
	
	return dstptr;
}