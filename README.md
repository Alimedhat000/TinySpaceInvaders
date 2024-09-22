# Tiny Space Invaders Clone

This is a simple Space Invaders clone built with C++, utilizing **SFML** (Simple and Fast Multimedia Library). The project is aimed at practicing **Object-Oriented Programming (OOP)** principles in C++ and improving skills with the **SFML** library for game development.

## Features
- Basic player movement using the keyboard and mouse.
- Simple animation system for player sprites.
- Object-Oriented structure for players and future enemies/bullets.
- Modular code with separate classes for game entities like `Player` and `Animation`.
- Expandable structure to add enemies, projectiles, and more game features.

## Screenshots
*(Include screenshots of the game here if available)*

## Installation & Setup

### Prerequisites
- C++ compiler (like `g++`)
- **SFML** library (version 2.5 or above)

### Installing SFML
1. Install SFML on your system:
   - On Linux (Debian/Ubuntu):
     ```bash
     sudo apt-get install libsfml-dev
     ```
   - On Windows:
     Follow [SFML's official guide](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) to install the library.

### Cloning the Repository
```bash
git clone https://github.com/yourusername/space-invaders-clone.git
cd space-invaders-clone
```
### Building the Project
Use a Makefile or directly compile with the following command:
```bash
g++ main.cpp Player.cpp Animation.cpp -o SpaceInvaders -lsfml-graphics -lsfml-window -lsfml-system
```
### Running the Game 
After building the project, you can run the game with:
```bash
./SpaceInvaders
```
