#ifndef SNAKE_H
#define SNAKE_H

#define WIDTH 40
#define HEIGHT 20

// Game configurations
#define DIR_UP 'w'
#define DIR_LEFT 'a'
#define DIR_DOWN 's'
#define DIR_RIGHT 'd'

// Core Snake Data Structure
struct Node {
    int x;
    int y;
    struct Node* next;
};

// UI Colors (ANSI codes)
#define COLOR_RESET 0
#define COLOR_RED 31
#define COLOR_GREEN 32
#define COLOR_YELLOW 33
#define COLOR_BLUE 34
#define COLOR_CYAN 36

// --- math.c ---
// Adds/Subtracts values, generating positions or rng
int math_add(int a, int b);
int math_sub(int a, int b);
unsigned int math_mul(unsigned int a, unsigned int b);
unsigned int math_div(unsigned int dividend, unsigned int divisor);
unsigned int math_mod(unsigned int dividend, unsigned int divisor);
void math_srand(unsigned int seed);
int math_rand_range(int min, int max);
int math_check_bounds(int x, int y, int width, int height);

// --- string.c ---
void custom_itoa(int value, char* str, int base);
int custom_strlen(const char* str);

// --- memory.c ---
struct Node* mem_alloc_node(int x, int y);
void mem_free_node(struct Node* node);
void mem_free_list(struct Node* head);

// --- screen.c ---
void screen_clear(void);
void screen_move_cursor(int x, int y);
void screen_draw_char(int x, int y, char c);
void screen_draw_string(int x, int y, const char* str);
void screen_hide_cursor(void);
void screen_show_cursor(void);
void screen_flush(void);
void screen_draw_grid(int width, int height);
void screen_set_color(int color);
void screen_reset_color(void);

// --- keyboard.c ---
void kb_init(void);
void kb_restore(void);
int kb_hit(void);
char kb_get_key(void);

#endif // SNAKE_H
