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

/*
    What is GFFS? It's our own file system, GFFS not write data into disk it just write it into memory
*/

#include "gffs.h"

#include "../../screen.h"
#include "../../mem.h"

typedef struct FILE_GFFS {
    char* filename;
    int type;
    char* value;
} FILE_GFFS;

FILE_GFFS* files;
int file_len = 0;
unsigned int phys_addr;

void init_gffs() {
    files = (FILE_GFFS*)malloc(sizeof(FILE_GFFS) * 1024, 1, &phys_addr);
}

int create_file(char* filename) {
    for (int i = 0; i < file_len; i++) {
        if (filename == files[i].filename) {
            return 0; /* Error code */
        }
    }

    files[file_len].filename = filename;
    files[file_len].type     = FILE;
    files[file_len].value    = "";

    file_len++;

    return 1; /* Success code */
}

void print_files() {
    if (file_len == 0) return better_print("There are any files!\n");

    for (int i = 0; i < file_len; i++) {
        better_print(files[i].filename);
        better_print("\n");
    }
}

void write_file(char* filename, char* value) {
    for (int i = 0; i < file_len; i++) {
        if (filename == files[i].filename) {
            files[i].value = value;
        }
    }
}

char* read_file(char* filename) {
    for (int i = 0; i < file_len; i++) {
        if (filename == files[i].filename) {
            return files[i].value;
        }
    }

    return (char*)0x0;
}
