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

#include "./ports.h"
#include "./screen.h"

void shutdown() {
    // Shtudown virtual machines
    outw(0xB004, 0x2000);
    outw(0xB004, 0x2000);
    outw(0xB004, 0x2000);

    // Shutdown by BIOS
    extern void sht();
    better_print_color(">>> ", 0x4);
    better_print("Can't shutdown the system.. Trying shutdown it by BIOS\n");
    sht();

    better_print_color("\n>>> ", 0x4);
    better_print("Can't shutdown the system by BIOS.. Please shutdown it manualy\n");
}

void reboot(){
    int good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    asm volatile("hlt");
}