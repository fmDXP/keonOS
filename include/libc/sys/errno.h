/*
 * keonOS - include/libc/sys/errno.h
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


#ifndef ERRNO_H
#define ERRNO_H

/* Standard File Descriptors */
#define STDIN   0
#define STDOUT  1
#define STDERR  2


/* POSIX Error Codes */
#define EPERM            1  /* Operation not permitted */
#define ENOENT           2  /* No such file or directory */
#define ESRCH            3  /* No such process */
#define EINTR            4  /* Interrupted system call */
#define EIO              5  /* I/O error */
#define ENXIO            6  /* No such device or address */
#define E2BIG            7  /* Argument list too long */
#define ENOEXEC          8  /* Exec format error */
#define EBADF            9  /* Bad file number */
#define ECHILD          10  /* No child processes */
#define EAGAIN          11  /* Try again / Resource temporarily unavailable */
#define ENOMEM          12  /* Out of memory */
#define EACCES          13  /* Permission denied */
#define EFAULT          14  /* Bad address */
#define ENOTBLK         15  /* Block device required */
#define EBUSY           16  /* Device or resource busy */
#define EEXIST          17  /* File exists */
#define EXDEV           18  /* Cross-device link */
#define ENODEV          19  /* No such device */
#define ENOTDIR         20  /* Not a directory */
#define EISDIR          21  /* Is a directory */
#define EINVAL          22  /* Invalid argument */
#define ENFILE          23  /* File table overflow */
#define EMFILE          24  /* Too many open files */
#define ENOTTY          25  /* Not a typewriter (Inappropriate ioctl) */
#define ETXTBSY         26  /* Text file busy */
#define EFBIG           27  /* File too large */
#define ENOSPC          28  /* No space left on device */
#define ESPIPE          29  /* Illegal seek */
#define EROFS           30  /* Read-only file system */
#define EMLINK          31  /* Too many links */
#define EPIPE           32  /* Broken pipe */
#define EDOM            33  /* Math argument out of domain */
#define ERANGE          34  /* Math result not representable */


/* Advanced Networking & IPC */
#define EDEADLK         35  /* Resource deadlock would occur */
#define ENAMETOOLONG    36  /* File name too long */
#define ENOLCK          37  /* No record locks available */
#define ENOSYS          38  /* Invalid system call number */
#define ENOTEMPTY       39  /* Directory not empty */
#define ELOOP           40  /* Too many symbolic links encountered */
#define ENOMSG          42  /* No message of desired type */
#define EIDRM           43  /* Identifier removed */
#define EPROTO          71  /* Protocol error */
#define EBADMSG         74  /* Not a data message */
#define EOVERFLOW       75  /* Value too large for defined data type */
#define ENOTSOCK        88  /* Socket operation on non-socket */
#define EDESTADDRREQ    89  /* Destination address required */
#define EMSGSIZE        90  /* Message too long */
#define EPROTOTYPE      91  /* Protocol wrong type for socket */
#define ENOPROTOOPT     92  /* Protocol not available */
#define EPROTONOSUPPORT 93  /* Protocol not supported */
#define EOPNOTSUPP      95  /* Operation not supported on transport endpoint */
#define EADDRINUSE      98  /* Address already in use */
#define EADDRNOTAVAIL   99  /* Cannot assign requested address */
#define ENETDOWN       100  /* Network is down */
#define ENETUNREACH    101  /* Network is unreachable */
#define ECONNABORTED   103  /* Software caused connection abort */
#define ECONNRESET     104  /* Connection reset by peer */
#define ENOBUFS        105  /* No buffer space available */
#define EISCONN        106  /* Transport endpoint is already connected */
#define ENOTCONN       107  /* Transport endpoint is not connected */
#define ETIMEDOUT      110  /* Connection timed out */
#define ECONNREFUSED   111  /* Connection refused */
#define EHOSTUNREACH   113  /* No route to host */
#define EALREADY       114  /* Operation already in progress */
#define EINPROGRESS    115  /* Operation now in progress */
#define ESTALE         116  /* Stale file handle */

#endif		// ERRNO_H