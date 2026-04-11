#include "snake.h"

int math_add(int a, int b) {
    return a + b;
}

int math_sub(int a, int b) {
    return a - b;
}

// Simple Linear Congruential Generator (LCG) for RNG
// Avoids using stdlib rand()
static unsigned int next = 1;

void math_srand(unsigned int seed) {
    next = seed;
}

static unsigned int math_rand(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

int math_rand_range(int min, int max) {
    if (max <= min) return min;
    return min + (math_rand() % (max - min));
}

// Returns 1 if out of bounds, 0 if within bounds
int math_check_bounds(int x, int y, int width, int height) {
    if (x < 1 || x > width || y < 1 || y > height) {
        return 1;
    }
    return 0;
}
