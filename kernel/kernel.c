// #########################################################################
//
//  Copyright 2021 SolindekDev
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// 
// ########################################################################

// #include "colors.h"
// #include "ports.h"
// #include "screen.h"
// #include "string.h"
// #include "util.h"
// #include "disk.h"
// #include "power.h"

// #include "cpu/idt.h"
// #include "cpu/isr.h"
// #include "cpu/timer.h"
// #include "cpu/cpu.h"
// #include "cpu/types.h"

// #include "drivers/io/keyboard.h"
// #include "drivers/storage/ata.h"
// #include "drivers/speakers/pcspk.h"
// #include "drivers/speakers/sb16.h"

// #include "fs/gffs/gffs.h"

// #define KERNEL_VERSION "1.0.0"
// #define KERNEL_NAME "GoofKernel"
// #define OS_NAME "GoofOS"
// #define KERNEL_DATE __DATE__
// #define KERNEL_TIME __TIME__

// #define NULL ((void *)0)

// void initializing_kernel() {
//     outb(0x3d4, 14); 
//     int position = inb(0x3d5);
//     position = position << 8; 

//     outb(0x3d4, 15); 
//     position += inb(0x3d5);
    
//     clear_screen();

//     better_print_color("\n>>> ", 0x9);
//     better_print("Running kernel \n");
//     wait();
//     better_print_color(">>> ", 0x9);
//     better_print("Init video \n");
//     wait();
//     isr_install();
//     better_print_color(">>> ", 0x9);
//     better_print("Install ISR \n");
//     wait();
//     irq_install();
//     better_print_color(">>> ", 0x9);
//     better_print("Install IRQ \n");
//     wait();
//     init_gffs();
//     better_print_color(">>> ", 0x9);
//     better_print("Initializing File System (GFFS) ");
//     better_print_color("BETA \n", 0x4);
//     wait();
//     // sb16_init();
//     // better_print_color(">>> ", 0x9);
//     // better_print("Starting sb16 driver\n");
//     // better_print_color("BETA \n", 0x4);
//     keyboard_mode(NONE_MODE);
//     better_print_color(">>> ", 0x9);
//     better_print("Starting keyboard driver \n");
//     wait();
//     floppy_disk_detect();
//     better_print_color(">>> ", 0x9);
//     better_print("Detecting floppy disks \n");
//     wait();
//     better_print_color(">>> ", 0x9);
//     better_print("Detected producer of processor ");
//     better_print(detect_cpu_type());
//     better_print("\n");
//     wait();
//     better_print_color(">>> ", 0x9);
//     better_print("Kernel builded ");
//     better_print(KERNEL_DATE);
//     better_print(" at ");
//     better_print(KERNEL_TIME);
//     better_print("\n");
//     better_print_color(">>> ", 0x9);
//     better_print("Kernel version ");
//     better_print(KERNEL_VERSION);
//     better_print("\n");
//     wait();
//     better_print_color(">>> ", 0x9);
//     better_print("Initializing shell");
//     better_print("\n");
//     wait();
//     wait();
//     wait();
//     wait();
//     return;
// }

// void input(char* message) {
//     char *token;
//     char *search = " ";

//     char* first_arg;
//     char* second_arg;

//     token = strtok(message, search);
//     first_arg = token;
//     token = strtok(NULL, search);
//     second_arg = token;

//     if (strcmp(first_arg, "clear") == 1) {
//         clear_screen();
//         better_print("\n");
//     } else if (strcmp(first_arg, "reboot") == 1) {
//         reboot();
//     } else if (strcmp(first_arg, "shutdown") == 1) {
//         shutdown();
//     } else if (strcmp(first_arg, "ls") == 1) {
//         print_files();
//     } else if (strcmp(first_arg, "cat") == 1) {
//         if (strcmp(second_arg, "") == 1 || strcmp(second_arg, " ") == 1 || strcmp(second_arg, "help") == 1 || strcmp(second_arg, "h") == 1) {
//             better_print("cat - Builded in GoofOS tool to read files in shell...\n");
//         } else {
//             char* filename;
//             memory_copy(second_arg, filename, strlen(second_arg)+1);
//             char* value = read_file(filename);
//             better_print(value);
//             better_print("\n");
//         }
//     } else if (strcmp(first_arg, "touch") == 1) {
//         if (strcmp(second_arg, "") == 1 || strcmp(second_arg, " ") == 1 || strcmp(second_arg, "help") == 1 || strcmp(second_arg, "h") == 1) {
//             better_print("touch - Builded in GoofOS tool to create files in shell...\n");
//         } else {
//             char* filename;
//             memory_copy(second_arg, filename, strlen(second_arg)+1);
//             int state = create_file(filename);
//             if (state == 0) 
//                 better_print("File already exists\n");
//             else
//                 better_print(second_arg);
//                 better_print(" file created\n");
//         }
//     } else if (strcmp(first_arg, "beep") == 1) {
//         pcspk_beep();
//     } else if (strcmp(first_arg, "music") == 1) {
//         pcspk_play_sound(2);
//         wait();
//         pcspk_play_sound(20);
//         wait();
//         pcspk_play_sound(280);
//         wait();
//         pcspk_play_sound(500);
//         wait();
//         pcspk_play_sound(280);
//         wait();
//         pcspk_play_sound(20);
//         wait();
//         pcspk_play_sound(2);
//         wait();
//         pcspk_stop_sound();
//     }

//     clsstr(first_arg);
//     clsstr(second_arg);
//     prompt();
// }

// void prompt() {
//     better_print_color(">>> ", 0x9);
//     better_print_color("goof", 0x2);
//     better_print("@");
//     better_print_color("root", 0x4);
//     better_print(":~$ ");

// }

// void initializing_shell() {
//     clear_screen();

//     better_print_color("\n                                       ,...                     \n", 0x9);
//     better_print_color("      .g8\"\"\"bgd                      .d' \"\".g8\"\"8q.    .M\"\"\"bgd \n", 0x9);
//     better_print_color("    .dP'     `M                      dM` .dP'    `YM. ,MI    \"Y \n", 0x9);
//     better_print_color("    dM'       `   ,pW\"Wq.   ,pW\"Wq. mMMmmdM'      `MM `MMb.     \n", 0x9);
//     better_print_color("    MM           6W'   `Wb 6W'   `Wb MM  MM        MM   `YMMNq. \n", 0x9);
//     better_print_color("    MM.    `7MMF'8M     M8 8M     M8 MM  MM.      ,MP .     `MM \n", 0x9);
//     better_print_color("    `Mb.     MM  YA.   ,A9 YA.   ,A9 MM  `Mb.    ,dP' Mb     dM \n", 0x9);
//     better_print_color("      `\"bmmmdPY   `Ybmd9'   `Ybmd9'.JMML.  `\"bmmd\"'   P\"Ybmmd\"  \n", 0x9);          
//     better_print("\n\n");

//     prompt();
//     keyboard_mode(SHELL_MODE);

// }

// void start_kernel() {
//     initializing_kernel();
//     initializing_shell();
// }

void input() {}

void start_kernel() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'X';
    return;
}