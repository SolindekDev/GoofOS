#ifndef VIDEO_H
    #define VIDEO_H 0x1

    #define MAX_ROWS 25
    #define MAX_COLS 80

    #define VIDEO_ADDRESS 0xb8000

    #define REG_SCREEN_CTRL 0x3d4
    #define REG_SCREEN_DATA 0x3d5

    int get_cursor_offset();
    void set_cursor_offset(int offset);
    void set_cursor(int x, int y);
    int print_char(char c, int col, int row, char attr);
    int get_offset(int col, int row);
    int get_offset_row(int offset);
    int get_offset_col(int offset);

#endif