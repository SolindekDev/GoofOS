#ifndef STRINGS_H
    #define STRINGS_H

    void clsstr(char* str);
    char* strtok_r(char* str, const char* delim, char** saved_str);
    char* strtok(char* str, const char* delim);
    void reverse(char* s);
    int strlen(char* s);
    void append(char* s, char n);
    void backspace(char* s);
    int strcmp(char* s1, char* s2);
    void intconvstr(int n, char* str);
    void hexconvstr(int n, char* str);
#endif