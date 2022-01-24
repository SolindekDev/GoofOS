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

#include "./print.h"

#include "../utils/ports.h"
#include "./video.h"

void cputs(unsigned char __c, unsigned char forecolour, unsigned char backcolour, int x, int y) {
    int attrib = (backcolour << 4) | (forecolour & 0x0F);
    volatile int * where;
    where = (volatile int *)0xB8000 + (y * 80 + x) ;
    *where = __c | (attrib << 8);
}

void print(char* __str) {

}

void println(char* __str) {

}