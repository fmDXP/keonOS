# keonOS 🚀

A monolithic 64-bit x86_64 operating system built from scratch in C++ and Assembly.

---

## 🏗️ Architecture & Core Features

### 🧠 Advanced Memory Management
- **Higher Half Kernel:** The kernel sits now at `0xC0000000`, neatly separating the kernel addresses with the user ones (for future development).
- **Boot-time Paging:** Implemented a log of bootstrapping in Assembly to map critical pages before going to the Higher Half.
- **Custom VMM & PFA:** Advance management of physical frames and of virtual addressed with support of recorsive mapping.
- **Kernel Heap:** Fully functional dynamic memory management with support for `kmalloc`, `kfree`, and C++ `new`/`delete` operators.

### 🎭 Multitasking & Scheduling
- **Cooperative Multitasking:** Round-robin scheduler handling multiple kernel threads.
- **Process Control:** Built-in support for process listing (`ps`) and thread termination (`pkill`).
- **Post-Mortem Debugging:** Advanced **Kernel Panic** system that captures CPU registers and performs a full stack hex-dump upon failure.

### 💻 Interactive Shell
- **User Interface:** A custom shell with advanced features:
  - **Command History:** Navigate previous commands with Up/Down arrows.
  - **Tab-Completion:** Quick command execution.
  - **System Diagnostics:** Real-time stats for paging, heap, and uptime.

### 🔌 Hardware Drivers
- **VGA:** Text mode driver with custom color schemas.
- **Keyboard:** Interrupt-based driver with scancode-to-ASCII mapping.
- **PIT & CMOS:** Programmable Interval Timer for system ticks and timing.
- **PC Speaker:** Frequency-based audio feedback.

### 📂 Virtual File System (VFS) & Storage
- **Unified VFS Layer:** An abstract interface that allows the system to interact with different file systems via standard operations like `vfs_open`, `vfs_read`, and `vfs_readdir`.
- **KeonFS (Ramdisk):** A custom RAM-based file system loaded as a Multiboot module. It supports packed file headers and linear scanning for fast resource access during boot.
- **Mount System:** Support for mounting multiple file systems under a virtual root (`/`), enabling structured access to system resources (e.g., `/initrd`).

### 📚 Standard Library (LibC)
- **File I/O:** Implementation of standard C functions such as `fopen`, `fread`, `fclose`, and `fseek` to bridge the gap between user-level logic and the VFS.
- **String Manipulation:** A growing suite of memory and string functions (`memcpy`, `memset`, `strcmp`, `strcpy`) optimized for kernel performance.

---

## 🛠️ Build & Development

### Prerequisites
You will need an `i686-elf` cross-compiler toolchain, `nasm`, and `qemu`.

### Tooling
- **Ramdisk Packer:** Includes a custom Python script (`scripts/pack_keonfs.py`) that automatically bundles assets into a KeonFS image during the build process.

### Compilation
```bash
make        # Compiles the kernel
make iso    # Creates the ISO
make run    # Boots the OS in QEMU
```

All-in-one command:
```bash
make && make iso && make run
```

There's also 
```bash
make clean  # Cleans all the object files, the ISO and the logs (qemu.log)
```

---

## 📝 License

keonOS is licensed under the GNU General Public License v3.0 (GPLv3) with Additional Terms as permitted by Section 7 of the license.

Copyright (c) 2025-2026 fmdxp
Additional Terms (Per Section 7 of the GNU GPLv3):

* Attribution: Original author attributions (fmdxp) must be preserved in all copies and substantial portions of the software.

* Modifications: Modified versions must be clearly marked as different from the original version.

* Branding: The name "keonOS" or the author's name "fmdxp" cannot be used for publicity or promotional purposes without explicit prior written permission.

The software is provided "AS IS", without warranty of any kind. See the LICENSE file for the full text of the GPLv3.
