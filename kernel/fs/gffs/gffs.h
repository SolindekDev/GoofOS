#ifndef GFFS_H
    #define GFFS_H 0x1

    #define FILE    0x1
    #define FOLDER  0x2

    void init_gffs();
    int create_file(char* filename);
    void print_files();
    void write_file(char* filename, char* value);
    char* read_file(char* filename);
#endif