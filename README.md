# Snake Game (C++ with OpenGL/GLUT)

A simple and classic **Snake Game** built in **C++** using **OpenGL/GLUT**.  
Lightweight, beginner-friendly, and fun to play!

## Features
- Snake movement on a grid
- Random food generation
- Score counter
- Pause & Restart options
- Game Over screen
- Keyboard & Mouse controls

## Controls
- **t** → Move Up  
- **h** → Move Right  
- **g** → Move Down  
- **f** → Move Left  
- **P** → Pause / Unpause  
- **R** → Restart  
- **Mouse Click** → Steer toward clicked cell  

## Screenshots

### 🎥 Gameplay Video
https://github.com/user-attachments/assets/c83c7a34-3b98-4a71-9c09-d1ce6caa2a91

### 🖼️ Screenshot
<img width="453" height="468" alt="Snake Game Screenshot" src="https://github.com/user-attachments/assets/887c68b5-c94d-4518-b1db-efc0a9dd3b51" />

## Getting Started

### Prerequisites
- C++ compiler (g++, MinGW, or MSVC)
- OpenGL + GLUT (or freeglut) installed

### How to Run
#### On Linux
```bash
sudo apt-get install g++ freeglut3-dev
g++ main.cpp -o snake -lglut -lGL -lGLU
./snake
