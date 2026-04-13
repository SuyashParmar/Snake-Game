#include "snake.h"
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

static struct termios orig_termios;

void kb_init(void) {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) return;
    
    struct termios raw = orig_termios;
    // Disable echo and canonical mode
    raw.c_lflag &= ~(ECHO | ICANON);
    // Disable signals like INT (Ctrl+C), though maybe we want Ctrl+C for safety
    // raw.c_lflag &= ~(ISIG); 
    
    // Set non-blocking read
    // raw.c_cc[VMIN] = 0;
    // raw.c_cc[VTIME] = 0;
    
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void kb_restore(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

int kb_hit(void) {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

char kb_get_key(void) {
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) < 0) {
        return 0;
    }
    return c;
}
