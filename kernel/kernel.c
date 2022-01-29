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

#include "colors.h"
#include "keyboard.h"
#include "ports.h"
#include "screen.h"
#include "string.h"
#include "util.h"
#include "disk.h"
#include "mem.h"
#include "power.h"

#include "./cpu/idt.h"
#include "./cpu/isr.h"
#include "./cpu/timer.h"
#include "./cpu/cpu.h"
#include "./cpu/types.h"

#include "fs/gffs/gffs.h"

#define KERNEL_VERSION "1.0.0"
#define KERNEL_NAME "GoofKernel"
#define OS_NAME "GoofOS"
#define KERNEL_DATE __DATE__
#define KERNEL_TIME __TIME__

void initializing_kernel() {
    outb(0x3d4, 14); 
    int position = inb(0x3d5);
    position = position << 8; 

    outb(0x3d4, 15); 
    position += inb(0x3d5);
    
    clear_screen();

    better_print_color("\n>>> ", 0x9);
    better_print("Running kernel \n");
    wait();
    better_print_color(">>> ", 0x9);
    better_print("Init video \n");
    wait();
    isr_install();
    better_print_color(">>> ", 0x9);
    better_print("Install ISR \n");
    wait();
    irq_install();
    better_print_color(">>> ", 0x9);
    better_print("Install IRQ \n");
    wait();
    init_gffs();
    better_print_color(">>> ", 0x9);
    better_print("Initializing File System (GFFS) \n");
    wait();
    keyboard_mode(NONE_MODE);
    better_print_color(">>> ", 0x9);
    better_print("Starting keyboard driver \n");
    wait();
    floppy_disk_detect();
    better_print_color(">>> ", 0x9);
    better_print("Detecting floppy disks \n");
    wait();
    better_print_color(">>> ", 0x9);
    better_print("Detected producer of processor ");
    better_print(detect_cpu_type());
    better_print("\n");
    wait();
    better_print_color(">>> ", 0x9);
    better_print("Kernel builded ");
    better_print(KERNEL_DATE);
    better_print(" at ");
    better_print(KERNEL_TIME);
    better_print("\n");
    better_print_color(">>> ", 0x9);
    better_print("Kernel version ");
    better_print(KERNEL_VERSION);
    better_print("\n");
    wait();
    better_print_color(">>> ", 0x9);
    better_print("Initializing shell");
    better_print("\n");
    wait();
    wait();
    wait();
    wait();
    return;
}

char* first;

// typedef struct TOKENS {
//     char* value;
// } TOKENS;

// int lexer_tokens_len;
// TOKENS* tokens;

// TOKENS create_token(char* value) {
//     TOKENS token;
//     token.value = value;

//     return token;
// }

// void lexer(char* msg) {
//     int space = 0;

//     for (int i = 0; i < strlen(msg); i++) {
//         if (msg[i] == ' ') {
//             space+=1;
//         } else {
//             if (space == 0) {
//                 if (lexer_tokens_len-1 == -1) {
//                     tokens[lexer_tokens_len] = create_token((char*)msg[i]);
//                     lexer_tokens_len++;
//                 } else {
//                     append(tokens[lexer_tokens_len].value, msg[i]);
//                 }
//             } else {
//                 tokens[lexer_tokens_len] = create_token((char*)msg[i]);
//                 lexer_tokens_len++;
//                 space-=0;
//             }
//         }
//     }
// }

int touchR = 0;

void input(char* message) {
    first = strtok(message, ' ');

    if (strcmp(first, "clear") == 1) {
        clear_screen();
        better_print("\n");
    } else if (strcmp(first, "reboot") == 1) {
        reboot();
    } else if (strcmp(first, "shutdown") == 1) {
        shutdown();
    } else if (strcmp(first, "ls") == 1) {
        print_files();
    } else if (strcmp(first, "touch") == 1) {
        better_print("Give file name!: ");
        touchR = 1;
        clsstr(first);
        return;
    } 

    clsstr(first);
    prompt();
}

void prompt() {
    better_print_color(">>> ", 0x9);
    better_print_color("goof", 0x2);
    better_print("@");
    better_print_color("root", 0x4);
    better_print(":~$ ");

}

void initializing_shell() {
    clear_screen();

    better_print_color("\n                                       ,...                     \n", 0x9);
    better_print_color("      .g8\"\"\"bgd                      .d' \"\".g8\"\"8q.    .M\"\"\"bgd \n", 0x9);
    better_print_color("    .dP'     `M                      dM` .dP'    `YM. ,MI    \"Y \n", 0x9);
    better_print_color("    dM'       `   ,pW\"Wq.   ,pW\"Wq. mMMmmdM'      `MM `MMb.     \n", 0x9);
    better_print_color("    MM           6W'   `Wb 6W'   `Wb MM  MM        MM   `YMMNq. \n", 0x9);
    better_print_color("    MM.    `7MMF'8M     M8 8M     M8 MM  MM.      ,MP .     `MM \n", 0x9);
    better_print_color("    `Mb.     MM  YA.   ,A9 YA.   ,A9 MM  `Mb.    ,dP' Mb     dM \n", 0x9);
    better_print_color("      `\"bmmmdPY   `Ybmd9'   `Ybmd9'.JMML.  `\"bmmd\"'   P\"Ybmmd\"  \n", 0x9);          
    better_print("\n\n");

    prompt();
    keyboard_mode(SHELL_MODE);

}

void start_kernel() {
    initializing_kernel();
    initializing_shell();
}