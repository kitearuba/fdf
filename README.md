---

```
# 🌄 **FDF - 3D Wireframe Renderer** 🌄

![FDF](https://img.shields.io/badge/FDF-Project-blue?style=flat-square) ![C Programming](https://img.shields.io/badge/Language-C-green?style=flat-square) ![MiniLibX](https://img.shields.io/badge/Graphics-MiniLibX-purple?style=flat-square) ![42 Network](https://img.shields.io/badge/42Network-FDF-lightblue?style=flat-square)

**FDF** (*Fil de Fer*) is a **3D wireframe visualization program** built using **C and MiniLibX**. It takes a `.fdf` file containing elevation data and **renders a 3D projection** of the terrain in real-time, supporting **dynamic interactions, multiple projection modes, adjustable line thickness, and color gradients**.

This project is part of the **42 School curriculum**, emphasizing **graphics programming**, **event handling**, and **memory management** while following the **42 Norm**.

---

## 📑 **Table of Contents**
1. [Introduction](#introduction)
2. [Features](#features)
3. [Project Structure](#project-structure)
4. [Installation & Compilation](#installation--compilation)
5. [Usage](#usage)
6. [Controls](#controls)
7. [Makefile](#makefile)
8. [Acknowledgments](#acknowledgments)
9. [Author](#author)

---

## 📖 **Introduction**

The **FDF** project is a **3D wireframe visualizer** that renders **terrain elevation data** from a `.fdf` file.  
It implements **isometric and parallel projections**, allowing users to **rotate, zoom, and move** the terrain dynamically.  

This project was built using:
- **MiniLibX** for graphics rendering.
- **Bresenham’s algorithm** for line drawing.
- **Math transformations** for 3D to 2D projection.
- **Event handling** to allow real-time user interaction.

---

## ✨ **Features**

### ✅ **Mandatory Features**
✔ **Reads & Parses `.fdf` map files** (elevation data).  
✔ **Renders a 3D wireframe projection** using MiniLibX.  
✔ **Isometric projection** for 3D visualization.  
✔ **Interactive controls** (zoom, rotation, translation).  
✔ **Error handling & memory management** (no leaks, safe parsing).  

### 🔥 **Bonus Features**
✔ **Parallel projection mode** (toggle between isometric & parallel).  
✔ **Customizable color gradient** (4 different themes).  
✔ **Adjustable line thickness** (increase/decrease with keys).  
✔ **Smooth zooming & panning** for better navigation.  
✔ **Dynamic rotation along X, Y, and Z axes**.  

---

## 📂 **Project Structure**

```bash
.
├── include/              # Header files (FDF structures, macros, prototypes)
│   ├── fdf.h             # Main header with function prototypes
│   ├── fdf_structs.h     # Structure definitions
│   ├── fdf_macros.h      # Project macros
├── libft/                # Custom library (libft) for utility functions
├── src/                  # Source code
│   ├── parsing/          # Functions to parse .fdf files
│   ├── rendering/        # Functions to render the map
│   ├── events/           # Keyboard handling & interaction
│   ├── utils/            # Utility functions (freeing memory, error handling)
├── Makefile              # Compilation script
├── README.md             # Project documentation
└── minilibx-linux/       # MiniLibX graphics library
```

---

## ⚙️ **Installation & Compilation**

### 📥 **Clone the repository**
```sh
git clone https://github.com/yourusername/fdf.git
cd fdf
```

### 🔨 **Compile the project**
```sh
make
```

💡 This will compile `fdf` and link **MiniLibX** and **libft**.

---

## 🚀 **Usage**

### 📌 **Run the program**
```sh
./fdf maps/42.fdf
```
📌 Replace `42.fdf` with any `.fdf` map file.

### 🗺 **Testing with different maps**
The project includes several `.fdf` sample maps to test:
```sh
./fdf maps/julia.fdf
./fdf maps/mars.fdf
./fdf maps/100-6.fdf
```

---

## 🎮 **Controls**

| **Key**      | **Action**                           |
|-------------|------------------------------------|
| `ESC`       | Quit the program                  |
| `←` / `→`   | Move left / right                 |
| `↑` / `↓`   | Move up / down                    |
| `+` / `-`   | Zoom in / out                     |
| `Q` / `W`   | Rotate X-axis                      |
| `A` / `S`   | Rotate Y-axis                      |
| `Z` / `X`   | Rotate Z-axis                      |
| `P`         | Switch to **parallel projection**  |
| `O`         | Switch to **isometric projection** |
| `T` / `Y`   | Increase / decrease line thickness |
| `5` / `6`   | Select **color theme 1 / 2**      |
| `7` / `8`   | Select **color theme 3 / 4**      |

---

## 🛠️ **Makefile**

### 📌 **Available Targets**
- `make` → Compiles the project.
- `make clean` → Removes object files.
- `make fclean` → Cleans object files & executable.
- `make re` → Cleans and recompiles everything.

The **Makefile** ensures **efficient recompilation** by only rebuilding changed files.

---

🔹 OR Add a New Section
🚀 Future Improvements
💡 Planned Enhancements for Later Versions

Use extracted color values from .fdf maps as default rendering colors instead of the current fixed color themes.
Performance optimizations to make rendering faster with large .fdf maps.
Additional user controls for changing color modes dynamically.
📌 Why This Matters?

---

## 🙌 **Acknowledgments**

- **42 School** for designing this challenging and rewarding project.
- **MiniLibX** for providing a simple graphics library for C.
- **libft** for utility functions used throughout the project.

---

## 👨‍💻 **Author**

- **Christian (chrrodri)**  
  [GitHub Profile](https://github.com/kitearuba)

---
