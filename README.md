# Snake Game (OpenGL/GLUT)

A simple, classic Snake game implemented in C++ using **OpenGL** and **GLUT**. It renders a grid-based board, spawns food at random cells, and lets you control the snake via keyboard **(t/h/g/f)** or mouse clicks. Lightweight, dependency-minimal, and great for learning event-driven rendering loops.

---

## ✨ Features

- Grid-based snake movement with smooth redraws using GLUT's timer.
- Random food placement that never overlaps the snake.
- Score counter and clean **Game Over** screen with restart prompt.
- **Pause/Unpause** during gameplay.
- Optional **mouse steering**: click a cell to steer the snake head toward it.
- Compact single-file core (`main.cpp`), easy to read and modify.

---

## 🎮 Controls

- **t** → Move **Up**
- **h** → Move **Right**
- **g** → Move **Down**
- **f** → Move **Left**
- **P** → **Pause/Unpause**
- **R** → **Restart** after Game Over
- **Left Mouse Click** → Steer toward the clicked grid cell

> The controls are mapped to `t/h/g/f` to avoid arrow-key focus issues on some GLUT setups. You can easily remap them inside `keyboardFunc`.

---

## 🧠 Game Rules

- Eating food increases **score** by `+1` and grows the snake by `+1` segment.
- Colliding with the **wall** or with your own **body** ends the game.
- The board size is `600 × 600` pixels with a logical grid of `30 × 30` cells (each cell is `20 × 20` pixels).

---

## 🗂️ Project Structure

```
.
├── main.cpp            # Game logic & rendering (OpenGL/GLUT)
├── smakegame.cbp       # (Optional) Code::Blocks project file
└── smakegame.depend    # (Optional) Build dependency file
```

---

## ⚙️ Build & Run

> You need a C++ compiler and OpenGL + GLUT (or freeglut) development headers.

### Windows (MSYS2 / MinGW-w64)
1. Install MSYS2 and run the MSYS2 MinGW shell (64-bit).
2. Install packages:
   ```bash
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-freeglut
   ```
3. Build:
   ```bash
   g++ main.cpp -o snake -lfreeglut -lopengl32 -lglu32
   ```
4. Run:
   ```bash
   ./snake.exe
   ```

### Linux (Debian/Ubuntu)
1. Install dependencies:
   ```bash
   sudo apt-get update
   sudo apt-get install g++ freeglut3-dev
   ```
2. Build:
   ```bash
   g++ main.cpp -o snake -lglut -lGL -lGLU
   ```
3. Run:
   ```bash
   ./snake
   ```

### macOS (Intel/Apple Silicon)
> Note: Apple deprecated GLUT, but it still works for simple demos. Alternatively, use **freeglut** via Homebrew or port to GLFW/GLUT alternatives.

1. With system GLUT:
   ```bash
   g++ main.cpp -o snake -framework OpenGL -framework GLUT
   ./snake
   ```
2. With Homebrew freeglut:
   ```bash
   brew install freeglut
   g++ main.cpp -o snake -I/opt/homebrew/include -L/opt/homebrew/lib -lglut -lGLU -framework OpenGL
   ./snake
   ```

---

## 🔧 Key Constants (tweak gameplay)

Inside `main.cpp`:

- `WINDOW_WIDTH`, `WINDOW_HEIGHT` → Window size (default `600 × 600`).
- `GRID_SIZE` → Logical grid dimension (default `30`). Each cell is `WINDOW_WIDTH / GRID_SIZE` pixels.
- `MAX_SNAKE_LENGTH` → Upper limit for segments (default `100`).
- `glutTimerFunc(200, update, 0)` → Game tick every **200 ms** (lower is faster).

---

## 🧩 How it Works (High-level)

- **Rendering**: `display()` draws food, snake segments, score text, and overlays (Pause/Game Over).
- **Input**: `keyboardFunc()` reads t/h/g/f + P + R; `mouseFunc()` maps clicks to a direction.
- **Updates**: `update()` advances the snake by shifting body segments, moves the head, checks collisions, and grows on food.
- **Food**: `generateFood()` keeps choosing random cells until it finds one not occupied by the snake.

---

## 📸 Screenshots


```

---[recording.webm](https://github.com/user-attachments/assets/c83c7a34-3b98-4a71-9c09-d1ce6caa2a91)

<img width="453" height="468" alt="Screenshot 2025-08-31 171923" src="https://github.com/user-attachments/assets/887c68b5-c94d-4518-b1db-efc0a9dd3b51" />

## 🗒️ TODO Ideas

- Replace `t/h/g/f` with **arrow keys** or **WASD**.
- Add **levels**, **speed-up** over time, or **wrap-around** mode.
- Draw a **grid background** or add simple **textures**.
- Play a sound on **eat** and **game over**.
- Persist **high scores**.
- Add **unit tests** for utility logic.

---

## 📄 License

This repository is provided for learning and demo purposes. You can add an MIT License if you intend to open-source it.

---

## 🙌 Credits

Built with C++ and OpenGL/GLUT. Happy Coding!

