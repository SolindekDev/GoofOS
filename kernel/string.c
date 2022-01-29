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

#include "string.h"

#define NULL ((void *)0)

void clsstr(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = '\0';
    }
}

char* strtok_r(char* str, const char* delim, char** saved_str)
{
    if (!str) {
        if (!saved_str)
            return NULL;
        str = *saved_str;
    }

    unsigned long long token_start = 0;
    unsigned long long token_end = 0;
    unsigned long long str_len = strlen(str);
    unsigned long long delim_len = strlen(delim);

    for (unsigned long long i = 0; i < str_len; ++i) {
        int is_proper_delim = 0;

        for (unsigned long long j = 0; j < delim_len; ++j) {
            if (str[i] == delim[j]) {
                // Skip beginning delimiters
                if (token_end - token_start == 0) {
                    ++token_start;
                    break;
                }

                is_proper_delim = 1;
            }
        }

        ++token_end;
        if (is_proper_delim && token_end > 0) {
            --token_end;
            break;
        }
    }

    if (str[token_start] == '\0')
        return NULL;

    if (token_end == 0) {
        *saved_str = NULL;
        return &str[token_start];
    }

    if (str[token_end] == '\0')
        *saved_str = &str[token_end];
    else
        *saved_str = &str[token_end + 1];

    str[token_end] = '\0';
    return &str[token_start];
}

// https://pubs.opengroup.org/onlinepubs/9699919799/functions/strtok.html
char* strtok(char* str, const char* delim)
{
    static char* saved_str;
    return strtok_r(str, delim, &saved_str);
}

// char* strtok(char* str, char splitC) {
//     char* result = "";

//     for (int i = 0; i < strlen(str); i++) {
//         if (splitC == str[i]) {
//             break;
//         } else {
//             append(result, str[i]);
//         }
//     }

//     return result;
// }

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

int strcmp(char s1[], char s2[]) {
    int length_s1 = strlen(s1);
    int length_s2 = strlen(s2);

    if (length_s1 == length_s2) {
        for (int i = 0; i < length_s1; i++) {
            if (s1[i] != s2[i]) {
                return 0;
            }
        }
    } else {
        return 0;
    }

    return 1;
}

void intconvstr(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void hexconvstr(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}