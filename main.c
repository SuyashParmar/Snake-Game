#include "snake.h"
#include <unistd.h> // for usleep
#include <time.h>   // for time()
#include <fcntl.h>  // for open(), file system I/O

int show_main_menu(int high_score) {
    screen_clear();
    screen_set_color(COLOR_GREEN);
    screen_draw_string(10, 5, "====================");
    screen_draw_string(10, 6, "      SNAKE C       ");
    screen_draw_string(10, 7, "====================");
    screen_reset_color();
    
    screen_set_color(COLOR_YELLOW);
    screen_draw_string(12, 10, "Press 'S' to Start");
    screen_draw_string(12, 12, "Press 'Q' to Quit ");

    char hs_str[32];
    custom_itoa(high_score, hs_str, 10);
    screen_draw_string(12, 14, "High Score: ");
    screen_draw_string(24, 14, hs_str);

    screen_reset_color();

    while (1) {
        if (kb_hit()) {
            char key = kb_get_key();
            if (key == 's' || key == 'S') return 1;
            if (key == 'q' || key == 'Q') return 0;
        }
        usleep(50000);
    }
    return 0;
}

int main(void) {
    // 1. Initialize math/rng
    math_srand(time(NULL));

    // 2. Initialize terminal (screen & keyboard)
    kb_init();
    screen_hide_cursor();

    // File System requirement: Load highscore (POSIX)
    int high_score = 0;
    int fd = open("highscore.txt", O_RDONLY);
    if (fd >= 0) {
        char buf[32];
        int bytes = read(fd, buf, 31);
        if (bytes > 0) {
            buf[bytes] = '\0';
            int val = 0;
            // Basic manual atoi without stdlib
            for (int i = 0; i < bytes && buf[i] >= '0' && buf[i] <= '9'; i++) {
                val = val * 10 + (buf[i] - '0');
            }
            high_score = val;
        }
        close(fd);
    }

    // Show menu
    if (!show_main_menu(high_score)) {
        screen_clear();
        screen_show_cursor();
        kb_restore();
        return 0;
    }
    
    screen_clear();

    // 3. Game state initialization
    int game_over = 0;
    int score = 0;
    char dir = DIR_RIGHT;

    // Snake initial position (center)
    struct Node* head = mem_alloc_node(WIDTH / 2, HEIGHT / 2);
    struct Node* tail = head;

    // Food initial position
    int food_x = math_rand_range(1, WIDTH);
    int food_y = math_rand_range(1, HEIGHT);

    screen_draw_grid(WIDTH, HEIGHT);

    // Initial draw
    screen_set_color(COLOR_GREEN);
    screen_draw_char(head->x + 1, head->y + 1, 'O');
    screen_set_color(COLOR_RED);
    screen_draw_char(food_x + 1, food_y + 1, '*');
    screen_reset_color();

    // 4. Game Loop
    while (!game_over) {
        // Handle input
        if (kb_hit()) {
            char key = kb_get_key();
            if (key == DIR_UP && dir != DIR_DOWN) dir = DIR_UP;
            else if (key == DIR_DOWN && dir != DIR_UP) dir = DIR_DOWN;
            else if (key == DIR_LEFT && dir != DIR_RIGHT) dir = DIR_LEFT;
            else if (key == DIR_RIGHT && dir != DIR_LEFT) dir = DIR_RIGHT;
            else if (key == 'q') game_over = 1; // Quit
        }

        // Calculate new head position
        int new_x = head->x;
        int new_y = head->y;

        if (dir == DIR_UP) new_y = math_sub(new_y, 1);
        else if (dir == DIR_DOWN) new_y = math_add(new_y, 1);
        else if (dir == DIR_LEFT) new_x = math_sub(new_x, 1);
        else if (dir == DIR_RIGHT) new_x = math_add(new_x, 1);

        // Check boundary collision
        if (math_check_bounds(new_x, new_y, WIDTH, HEIGHT)) {
            game_over = 1;
            break;
        }

        // Check if food eaten
        int ate_food = 0;
        if (new_x == food_x && new_y == food_y) {
            score = math_add(score, 1);
            ate_food = 1;
            // Respawn food
            food_x = math_rand_range(1, WIDTH);
            food_y = math_rand_range(1, HEIGHT);
            screen_set_color(COLOR_RED);
            screen_draw_char(food_x + 1, food_y + 1, '*');
            screen_reset_color();
        }

        // Allocate new head string to new position
        struct Node* new_head = mem_alloc_node(new_x, new_y);
        new_head->next = head;
        head = new_head;

        // Draw new head
        screen_set_color(COLOR_GREEN);
        screen_draw_char(head->x + 1, head->y + 1, 'O');
        screen_reset_color();

        if (!ate_food) {
            // Remove tail
            struct Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            
            // Clear tail from screen
            screen_draw_char(tail->x + 1, tail->y + 1, ' ');

            // Free tail memory
            mem_free_node(tail);
            tail = current;
            tail->next = 0; // NULL
        }

        // Draw score
        char score_str[32];
        custom_itoa(score, score_str, 10);
        screen_set_color(COLOR_YELLOW);
        screen_draw_string(2, HEIGHT + 3, "Score: ");
        screen_draw_string(9, HEIGHT + 3, score_str);
        
        char hs_str_disp[32];
        int disp_hs = (score > high_score) ? score : high_score;
        custom_itoa(disp_hs, hs_str_disp, 10);
        screen_draw_string(20, HEIGHT + 3, "Best: ");
        screen_draw_string(26, HEIGHT + 3, hs_str_disp);
        screen_reset_color();

        // Sleep to control game speed
        // 100,000 microseconds = 0.1 seconds
        usleep(100000); 
    }

    // 5. Clean up & Exit
    int is_new_hs = 0;
    if (score > high_score) {
        is_new_hs = 1;
        int wfd = open("highscore.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (wfd >= 0) {
            char new_hs_str[32];
            custom_itoa(score, new_hs_str, 10);
            write(wfd, new_hs_str, custom_strlen(new_hs_str));
            close(wfd);
        }
    }

    screen_clear();
    screen_show_cursor();
    screen_move_cursor(1, 1);
    
    char final_score_str[32];
    custom_itoa(score, final_score_str, 10);
    screen_draw_string(1, 1, "Game Over! Final Score: ");
    screen_draw_string(25, 1, final_score_str);
    if (is_new_hs) {
        screen_set_color(COLOR_GREEN);
        screen_draw_string(30, 1, " [NEW HIGH SCORE!]");
        screen_reset_color();
    }
    screen_draw_string(1, 2, ""); // Newline basically

    // Write actual newline for terminal neatness
    write(STDOUT_FILENO, "\n", 1);

    kb_restore();
    mem_free_list(head);

    return 0;
}
