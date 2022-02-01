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

#include "pcspk.h"

#include "../../ports.h"
#include "../../util.h"

void pcspk_play_sound(unsigned int nFrequence) {
    unsigned int Div;
    unsigned char tmp;

    Div = 1193180 / nFrequence;
    outb(0x43, 0xb6);
    outb(0x42, (unsigned char) (Div) );
    outb(0x42, (unsigned char) (Div >> 8));

    tmp = inb(0x61);
    if (tmp != (tmp | 3)) {
        outb(0x61, tmp | 3);
    }
}

void pcspk_stop_sound() {
    unsigned char tmp = inb(0x61) & 0xFC;

    outb(0x61, tmp);
}

void pcspk_beep() {
    pcspk_play_sound(1000);
    wait();
    wait();
    pcspk_stop_sound();
}
