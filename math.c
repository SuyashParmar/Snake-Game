#include "snake.h"

int math_add(int a, int b) {
    return a + b;
}

int math_sub(int a, int b) {
    return a - b;
}

unsigned int math_mul(unsigned int a, unsigned int b) {
    unsigned int res = 0;
    while (b > 0) {
        if (b & 1) res += a;
        a <<= 1;
        b >>= 1;
    }
    return res;
}

unsigned int math_div(unsigned int dividend, unsigned int divisor) {
    if (divisor == 0) return 0;
    unsigned int quotient = 0;
    while (dividend >= divisor) {
        unsigned int temp_divisor = divisor;
        unsigned int multiple = 1;
        while ((temp_divisor << 1) > temp_divisor && dividend >= (temp_divisor << 1)) {
            temp_divisor <<= 1;
            multiple <<= 1;
        }
        dividend -= temp_divisor;
        quotient += multiple;
    }
    return quotient;
}

unsigned int math_mod(unsigned int dividend, unsigned int divisor) {
    if (divisor == 0) return dividend;
    while (dividend >= divisor) {
        unsigned int temp_divisor = divisor;
        while ((temp_divisor << 1) > temp_divisor && dividend >= (temp_divisor << 1)) {
            temp_divisor <<= 1;
        }
        dividend -= temp_divisor;
    }
    return dividend;
}

// Simple Linear Congruential Generator (LCG) for RNG
// Avoids using stdlib rand()
static unsigned int next_seed = 1;

void math_srand(unsigned int seed) {
    next_seed = seed;
}

static unsigned int math_rand(void) {
    next_seed = math_add(math_mul(next_seed, 1103515245), 12345);
    return math_mod(math_div(next_seed, 65536), 32768);
}

int math_rand_range(int min, int max) {
    if (max <= min) return min;
    return math_add(min, math_mod(math_rand(), math_sub(max, min)));
}

// Returns 1 if out of bounds, 0 if within bounds
int math_check_bounds(int x, int y, int width, int height) {
    if (x < 1 || x > width || y < 1 || y > height) {
        return 1;
    }
    return 0;
}
