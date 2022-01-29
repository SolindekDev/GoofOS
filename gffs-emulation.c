#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

char* strtok2(char* str, char split) {
    char* result = "";
    int r = 0;
    
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == split) {
            if (r == 0)
                r++;
            else
                break;
        } else {
            if (r == 1) {
                append(result, str[i]);
            } else {
                continue;
            }
        }
    }

    return result;
}

int main(int argc, char** argv) {
    // char* r = strtok2("siema siema2", ' ')
    printf("d\n");
}