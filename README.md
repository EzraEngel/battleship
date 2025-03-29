# Battleship (C++ Console Game)

This is a console-based implementation of the classic game **Battleship**, written in C++ as a warm-up project to reacquaint myself with the language after several years away.

I completed this over the course of a few days (~10 hours total), focusing on **object-oriented design**, **state management**, and clear separation of responsibilities across game components. While it's not intended to be production-grade code, it reflects how I approach systems design even in small-scope personal projects.

## Areas of focus

- **Object-oriented programming**: The game logic is encapsulated across cleanly defined classes (`Board`, `Player`, etc.), each with a clear role.
- **Stateful turn-based gameplay**: The game handles player turns, ship placement, hit/miss tracking, and victory conditions.
- **Encapsulation and abstraction**: Internal data is protected via private class members, and exposed via well-defined public interfaces.
- **Basic terminal UX**: The user interacts with the game entirely through the console, with visual board feedback and prompts.

## 🔧 How to Run

```bash
g++ -std=c++17 *.cpp -o battleship
./battleship
