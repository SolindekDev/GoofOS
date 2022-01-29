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
#include "ports.h"

char* diskTypes[8] = {
    "None",
    "360kB 5.25\"",
    "1.2MB 5.25\"",
    "720kB 3.5\"",
    "1.44MB 3.5\"",
    "2.88MB 3.5\"",
    "Unknown type of disk",
    "Unknown type of disk"
};

void floppy_disk_detect(int print) {
    outb(0x70, 0x10);
    unsigned char disk = inb(0x71);

    if (print == 1) {
        better_print("Floppy drive 0: ", WHITE_ON_BEAUTY_BLUE);
        better_print(diskTypes[disk >> 4], WHITE_ON_BEAUTY_BLUE);
        better_print("\nFloppy drive 1: ", WHITE_ON_BEAUTY_BLUE);
        better_print(diskTypes[disk & 0xf], WHITE_ON_BEAUTY_BLUE);
    }
}