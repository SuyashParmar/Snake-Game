#include "snake.h"
#include <unistd.h> // for write()

// Convert int to string without standard libraries, useful for escape codes
static void format_escape_code(int arg1, int arg2, char end_char, char* buffer, int* len) {
    buffer[0] = '\033';
    buffer[1] = '[';
    *len = 2;

    if (arg1 >= 0) {
        char num[16];
        custom_itoa(arg1, num, 10);
        int i = 0;
        while (num[i] != '\0') {
            buffer[(*len)++] = num[i++];
        }
    }
    
    if (arg2 >= 0) {
        buffer[(*len)++] = ';';
        char num[16];
        custom_itoa(arg2, num, 10);
        int i = 0;
        while (num[i] != '\0') {
            buffer[(*len)++] = num[i++];
        }
    }
    
    buffer[(*len)++] = end_char;
}

void screen_clear(void) {
    // Esc[2J clears screen
    write(STDOUT_FILENO, "\033[2J", 4);
}

void screen_move_cursor(int x, int y) {
    // Esc[y;xH moves cursor
    // ANSI uses 1-based coordinates
    char buf[32];
    int len;
    format_escape_code(y, x, 'H', buf, &len);
    write(STDOUT_FILENO, buf, len);
}

void screen_draw_char(int x, int y, char c) {
    screen_move_cursor(x, y);
    write(STDOUT_FILENO, &c, 1);
}

void screen_draw_string(int x, int y, const char* str) {
    screen_move_cursor(x, y);
    write(STDOUT_FILENO, str, custom_strlen(str));
}

void screen_hide_cursor(void) {
    write(STDOUT_FILENO, "\033[?25l", 6);
}

void screen_show_cursor(void) {
    write(STDOUT_FILENO, "\033[?25h", 6);
}

void screen_flush(void) {
    // If we used a buffer, we'd write it here.
    // For direct unistd writes, it's mostly unbuffered if stdout is not block buffered,
    // but typically terminal output goes immediately.
}

void screen_set_color(int color) {
    char buf[16];
    int len;
    // format_escape_code with one param: Esc[<color>m
    buf[0] = '\033';
    buf[1] = '[';
    len = 2;
    
    char num[16];
    custom_itoa(color, num, 10);
    int i = 0;
    while (num[i] != '\0') {
        buf[len++] = num[i++];
    }
    buf[len++] = 'm';
    write(STDOUT_FILENO, buf, len);
}

void screen_reset_color(void) {
    write(STDOUT_FILENO, "\033[0m", 4);
}

void screen_draw_grid(int width, int height) {
    screen_set_color(COLOR_CYAN);
    // Draw top and bottom borders
    for (int x = 2; x <= width + 1; x++) {
        screen_draw_string(x, 1, "═");
        screen_draw_string(x, height + 2, "═");
    }
    // Draw left and right borders
    for (int y = 2; y <= height + 1; y++) {
        screen_draw_string(1, y, "║");
        screen_draw_string(width + 2, y, "║");
    }
    // Draw corners
    screen_draw_string(1, 1, "╔");
    screen_draw_string(width + 2, 1, "╗");
    screen_draw_string(1, height + 2, "╚");
    screen_draw_string(width + 2, height + 2, "╝");
    screen_reset_color();
}
