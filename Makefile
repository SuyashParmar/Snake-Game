CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

SRCS = main.c math.c string.c memory.c screen.c keyboard.c
OBJS = $(SRCS:.c=.o)
TARGET = snake

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c snake.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
