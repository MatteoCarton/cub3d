# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Cub3D is a raycasting project inspired by Wolfenstein 3D, implementing a first-person 3D maze renderer using the MinilibX graphics library. The project requires creating a dynamic view within a labyrinth using raycasting techniques.

## Build Commands

```bash
# Compile the project
make

# Compile with bonus features
make bonus

# Clean object files
make clean

# Clean everything including binary
make fclean

# Recompile everything
make re

# Run the program
./cub3D maps/[map_file].cub
```

## Project Architecture

### Core Components

1. **Raycasting Engine** - Implements the raycasting algorithm to render 3D walls from a 2D map
2. **Map Parser** - Parses .cub files containing map layout and texture configurations
3. **Texture Manager** - Loads and manages wall textures (North, South, East, West)
4. **Input Handler** - Manages keyboard inputs for player movement and rotation
5. **Window Manager** - Handles MinilibX window creation and events

### Key Technical Requirements

- **Graphics Library**: MinilibX (mandatory)
- **Allowed Functions**: open, close, read, write, printf, malloc, free, perror, strerror, exit, all math library functions (-lm)
- **Map Format**: .cub files with specific syntax for textures, colors, and map layout
- **Map Characters**: 0 (empty space), 1 (wall), N/S/E/W (player spawn and orientation)

### Mandatory Features

1. Different wall textures based on orientation (N/S/E/W)
2. Different floor and ceiling colors
3. Smooth window management (minimize, focus changes)
4. Player movement with W/A/S/D keys
5. Camera rotation with left/right arrow keys
6. ESC key and window close button properly exit the program
7. Complete map validation (must be closed/surrounded by walls)

### Bonus Features (only if mandatory part is perfect)

- Wall collision detection
- Minimap system
- Doors that can be opened/closed
- Sprite animations
- Mouse rotation control

## Development Guidelines

1. **Norm Compliance**: All code must follow the 42 Norm
2. **Memory Management**: No memory leaks allowed
3. **Error Handling**: Graceful error messages for invalid maps or configurations
4. **Map Validation**: Thoroughly validate map format and ensure it's properly enclosed

## Map File Format (.cub)

Example structure:
```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

## Testing Approach

1. Test various map configurations for proper validation
2. Verify texture loading and rendering
3. Test all movement and rotation inputs
4. Check window management events
5. Memory leak testing with valgrind
6. Norm compliance check