# SDL2 Voxel Game (Minecraft-like)

A simple **3D voxel game written in C++ using SDL2**, inspired by Minecraft.  
The game uses **software rendering only** — **no OpenGL, no Vulkan, no DirectX** — everything is drawn manually via SDL2.

This project is primarily for **learning purposes**, focusing on:
- 3D math
- voxel rendering
- performance optimization
- game engine fundamentals

---

## Features

- 🧱 Voxel-based world (blocks)
- 📐 Custom 3D projection (no GPU acceleration)
- 🎮 First-person camera
- 🧮 Manual perspective calculations
- ⚙️ Written fully in C++
- 🚫 No OpenGL / Vulkan / DirectX

---

## Controls

| Key | Action |
|---|---|
| W / A / S / D | Move |
| Mouse | Look around |
| Mouse clicks | Place/break blocks |
| Space | Jump |
| Shift | Run |
| Left Ctrl | Sneak |
| E | Open/close inventory |
| R | Fast building/breaking |
| ESC | Exit |

---

## Tech Stack

- **Language:** C++
- **Rendering:** SDL2 (software rendering)
- **Libraries:**
  - SDL2
  - SDL2_image 

---

## Building the Project

### Requirements

- C++17 or newer
- SDL2
- SDL2_image (if used)

---

### Windows (MinGW / MSVC)

1. Download SDL2 from the official repo  
   https://github.com/libsdl-org/SDL/releases

2. Extract SDL2 and SDL2_image
3. Add inc and lib folders with SDL2 files to the project folder (where main.cpp is)
4. Make sure these DLLs are next to the executable when running:
   - `SDL2.dll`
   - `SDL2_image.dll`

---

### Linux

```bash
sudo apt install libsdl2-dev libsdl2-image-dev
```
---

## Building

### g++ (Linux / MinGW)

```bash
g++ -Llib -O3 \
main.cpp \
game/*.cpp \
game/common/*.cpp \
game/inventory/*.cpp \
game/world/*.cpp \
game/world/block/*.cpp \
game/world/chunk/*.cpp \
game/world/entity/*.cpp \
game/world/world_loader/*.cpp \
-lSDL2 -lSDL2_image
```

---

### clang++ (Linux / macOS)

```bash
clang++ -Llib -O3 \
main.cpp \
game/*.cpp \
game/common/*.cpp \
game/inventory/*.cpp \
game/world/*.cpp \
game/world/block/*.cpp \
game/world/chunk/*.cpp \
game/world/entity/*.cpp \
game/world/world_loader/*.cpp \
-lSDL2 -lSDL2_image
```

---

## MinGW g++ (Windows)

```bash
x86_64-w64-mingw32-g++ -Llib -O3 \
main.cpp \
game/*.cpp \
game/common/*.cpp \
game/inventory/*.cpp \
game/world/*.cpp \
game/world/block/*.cpp \
game/world/chunk/*.cpp \
game/world/entity/*.cpp \
game/world/world_loader/*.cpp \
-lSDL2 -lSDL2_image
```

---

## MSVC (Visual Studio)

```bash
cl /O2 /EHsc ^
main.cpp ^
game\*.cpp ^
game\common\*.cpp ^
game\inventory\*.cpp ^
game\world\*.cpp ^
game\world\block\*.cpp ^
game\world\chunk\*.cpp ^
game\world\entity\*.cpp ^
game\world\world_loader\*.cpp ^
/I include ^
/link /LIBPATH:lib SDL2.lib SDL2_image.lib
```