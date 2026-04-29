# 🐍 Bare-Metal Snake in C

A terminal-based Snake game written entirely in C from scratch. What makes this project unique is its **complete independence from standard C libraries**. There are no `#include <stdlib.h>`, `#include <stdio.h>`, or `#include <math.h>` statements, and the project even avoids using built-in hardware math operators like multiplication (`*`), division (`/`), and modulo (`%`).

Everything from dynamic memory management to basic arithmetic and random number generation has been hand-coded from the ground up!

## ✨ Features
* **Zero Standard Library Dependencies:** Built exclusively with low-level logic and POSIX system calls.
* **Custom Memory Allocator:** Implements a custom static memory pool (`memory.c`) to avoid using `malloc()` and `free()`.
* **Bitwise Math Library:** All complex arithmetic (`math_mul`, `math_div`, `math_mod`) is handled using bitwise shifts and addition/subtraction.
* **Custom RNG:** Random food placement is generated using a custom Linear Congruential Generator seeded by `/dev/urandom`.
* **Asynchronous Input:** Uses `termios.h` and the `select()` system call to handle real-time, non-blocking keyboard input without pressing "Enter".
* **ANSI Terminal Graphics:** Uses direct UTF-8 and ANSI escape sequence outputs to render colors and the game grid.
* **Progressive Difficulty:** The snake's speed increases every time it eats a regular food.
* **Bonus Mechanics:** A 20% chance to spawn a timed, high-value "Bonus Food" (`★`) that increases the snake's length by 2 segments at once!
* **High Score Persistence:** Reads and writes high scores directly to the filesystem using `open()`, `read()`, and `write()`.

## 🎮 How to Play
### Controls
* `W` - Move Up
* `A` - Move Left
* `S` - Move Down
* `D` - Move Right
* `Q` - Quit the Game

### Elements
* `@` : The Snake's Head (Yellow)
* `o` : The Snake's Body (Green)
* `*` : Regular Food (Red) - Awards 1 point and slightly increases speed.
* `★` : Bonus Food (Magenta) - Awards 5 points, grows the snake by 2 segments, but disappears after 30 moves!

## 🚀 Building and Running
Because the project uses standard POSIX system calls for input and output, it runs natively on macOS and Linux environments.

1. Clone the repository:
   ```bash
   git clone https://github.com/SuyashParmar/Snake-Game.git
   cd Snake-Game
   ```
2. Build the game using the provided Makefile:
   ```bash
   make
   ```
3. Run the executable:
   ```bash
   ./snake
   ```

## 🛠 How the Makefile Works
The project uses a standard `Makefile` to compile all the custom `.c` files into a single executable efficiently.
* **Compiler Flags (`CFLAGS`)**: It compiles using `gcc` with strict warnings (`-Wall -Wextra`), enforces the C99 standard (`-std=c99`), and applies performance optimization (`-O2`).
* **Object Compilation**: It first converts each `.c` source file (like `math.c`, `memory.c`) into an intermediate `.o` object file. If you only modify one file, running `make` again will only recompile that specific file, saving time!
* **Linking**: It links all the compiled `.o` files together to create the final `snake` executable.
* **Clean Command**: You can run `make clean` to delete all generated `.o` files and the executable, keeping your workspace tidy.

## 📂 Project Structure
* `main.c` - The core game loop, state management, and rendering logic.
* `snake.h` - Global configurations, structures, and function declarations.
* `keyboard.c` - Terminal manipulation to enable raw, asynchronous input.
* `math.c` - Custom bitwise arithmetic and random number generation.
* `memory.c` - Static memory pool for the snake's linked list node allocation.
* `screen.c` - Screen clearing, cursor movement, and grid rendering.
* `string.c` - Custom integer-to-string (`itoa`) parsing.

## 🤝 Contributors
* SuyashParmar
* Samyak2605
* Harshkesharwani789
