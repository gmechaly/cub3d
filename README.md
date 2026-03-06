# cub3D - @42Born2Code

## ✍️ A personal note

**cub3D** has been my favourite project from 42 Common Core. It explores real-time execution with inputs management, memory optimization, and a large liberty to use our creativity. It was the most fun project to do, from discovering the raycasting method to creating funny maps and mazes. This project has made me want to create my own videogame someday.

---

## 💡 About

**cub3D** is a graphical project that explores the foundations of 3D game engines. Using the **MiniLibX** library, this project implements a raycaster to render a dynamic 3D world from a 2D map.

The goal is to master **mathematical projections**, **texture mapping**, and **event-driven programming** to create a fluid first-person perspective.

> "A simple line-casting logic that creates the illusion of a third dimension."

---

## 🛠️ Features

* **3D Perspective**: Smooth first-person movement and rotation.
* **Raycasting Engine**: Precise distance calculation to avoid the "fisheye" effect.
* **Texture Mapping**: Different textures for North, South, East, and West walls.
* **Map Parsing**: Robust `.cub` file parser that validates wall enclosures, player start positions, and color configurations (RGB) for floors and ceilings.
* **Performance**: Optimized rendering loop for high-framerates.

---

## 📐 The Raycasting Logic

The engine works by casting a "ray" for every vertical slice of the screen. By calculating the distance from the player to the first wall hit, we can determine the height of the wall to be drawn.

1. **Calculate Ray Direction**: Based on the player's FOV (Field of View).
2. **DDA Algorithm**: The **Digital Differential Analyzer** is used to jump from one grid line to the next until a wall is hit.
3. **Wall Projection**: Convert the perpendicular distance into wall height on the screen.
4. **Texturing**: Determine exactly which part of the texture should be applied based on where the ray hit the wall.

---

## 🎮 Controls

| Key | Action |
| --- | --- |
| **W / S** | Move **Forward / Backward** |
| **A / D** | **Strafe** Left / Right |
| **Left / Right Arrows / Mouse movement** | **Rotate** the camera |
| **ESC** | **Exit** the game |

---

## 🚀 Usage

### Compilation

To compile the engine, run:

```bash
make

```

### Execution

Run the program with a valid `.cub` map file:

```bash
./cub3D maps/test.cub

```

**Map Example (`.cub`):**

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
111111

```

---

## 🛠️ Bonus Features

* **Wall Collisions**: Prevent the player from walking through walls.
* **Minimap**: A 2D overlay showing the player's position.
* **Mouse Control**: Rotate the view using the mouse.
* **Doors & Sprites**: Interactive doors and animated sprite (gun).

---

## 📋 Requirements

* **MiniLibX**: Correctly installed for your OS (Linux/X11 or macOS/Metal).
* **Math Library**: `-lm` flag for trigonometric functions.
