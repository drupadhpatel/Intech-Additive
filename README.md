# Simple OpenGL Solar System

A minimal **OpenGL + FreeGLUT** program that demonstrates a 3D **Sun → Earth → Moon** system using **hierarchical modeling**, basic transformations, and lighting.

---

##  Features

- Hierarchical structure using matrix stack (`glPushMatrix` / `glPopMatrix`)
- Orbital motion + self-rotation for Earth and Moon
- Basic point light source positioned at the Sun
- Smooth animation using GLUT timer (~60 FPS)
- Depth testing and face culling for proper 3D rendering

---

##  Requirements

You need:
- C++ Compiler (MinGW-w64 on Windows / GCC on Linux)
- OpenGL libraries (`opengl32`, `GLU`)
- GLUT or **FreeGLUT**

---

##  Windows (MinGW-w64 + FreeGLUT)

1. Install **MinGW-w64** and **FreeGLUT development files**
2. Ensure the following are available in PATH / INCLUDE / LIB:
   - `g++`
   - `freeglut.dll`
   - OpenGL & GLUT headers and libraries
3. From the project root, compile:

```bash
g++ main.cpp -lfreeglut -lopengl32 -lglu32 -o solar_system.exe

