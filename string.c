#include "snake.h"

// Reversing string in-place
static void reverse(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void custom_itoa(int value, char* str, int base) {
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly
    if (value == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (value < 0 && base == 10) {
        isNegative = 1;
        value = -value;
    }

    // Process individual digits
    while (value != 0) {
        int rem = math_mod((unsigned int)value, (unsigned int)base);
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        value = math_div((unsigned int)value, (unsigned int)base);
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';
    reverse(str, i);
}

int custom_strlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
