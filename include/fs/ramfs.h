/*
 * keonOS - include/fs/ramfs.h
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

#ifndef RAMFS_H
#define RAMFS_H

#include <stdint.h>

/*
 * KeonFS Magic Number
 * Used to verify the integrity of the RAM disk image.
 */
#define KEONFS_MAGIC 0x4B454F4E // "KEON"

/*
 * KeonFS File Header
 * Represents a single file entry within the archive.
 * Each header points to the next one to allow linear scanning.
 */
struct KeonFS_FileHeader 
{
    uint32_t magic;         // Identifier (KEONFS_MAGIC)
    char name[64];          // Null-terminated filename
    uint32_t size;          // Actual file size in bytes
    uint32_t offset;        // Absolute offset of data within the RAM image
    uint32_t next_header;   // Offset to the next header (0 if it's the last file)
    uint32_t reserved;      // Reserved for alignment/future use
} __attribute__((packed));


/*
 * KeonFS Superblock (Info)
 * Located at the very beginning (offset 0) of the initrd.img.
 */
struct KeonFS_Info 
{
    uint32_t magic;         // Global filesystem identifier
    uint32_t total_files;   // Number of files contained in the image
    uint32_t version;       // Format version
    uint32_t fs_size;       // RAMDISK size
    uint32_t reserved[4];   // Padding for future metadata
} __attribute__((packed));

#endif // RAMFS_H