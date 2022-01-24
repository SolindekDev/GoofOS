//
//     Copyright 2022 SolindekDev
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "./video.h"

#include "../utils/ports.h"

void set_cursor(int x, int y) {
    set_cursor_offset(get_offset(x, y));
}

int get_cursor_offset() {
    outb(REG_SCREEN_CTRL, 14);
    int offset = inb(REG_SCREEN_DATA) << 8;
    outb(REG_SCREEN_CTRL, 15);
    offset += inb(REG_SCREEN_DATA);
    return offset * 2; 
}

void set_cursor_offset(int offset) {
    offset /= 2;
    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void set_cursor_offset_pos(int row, int col) {
    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_DATA, col);
    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_DATA, row);
}

int get_offset(int col, int row) { 
    return 2 * (row * MAX_COLS + col); 
}

int get_offset_row(int offset) {
    return offset / (2 * MAX_COLS); 
}

int get_offset_col(int offset) { 
    return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; 
}