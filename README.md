# SWGOH Battle Engine (C++)

A modular, data-driven turn-based combat simulation engine inspired by *Star Wars: Galaxy of Heroes*.

This project focuses on building a scalable backend battle system capable of recreating complex character interactions, abilities, and effects in a deterministic environment similar to tools like Pokémon Showdown.

---

## Project Goals

- Reverse-engineer SWGOH-style combat system from scratch
- Design a scalable architecture for future expansion (5v5 battles, buffs, debuffs, status effects, etc.)
- Practice clean C++ system design and modular game engine architecture

## Current Status

This is an early-stage prototype. Core combat loop and damage system are functional, with active development on:

Expanding ability effects (buff/debuff application, healing, etc.)
Passive Abilities and triggering events
Full 5v5 battle system
AI-controlled targeting system
Battle logging system
Optimized performance for large simulations

---

## Current Features

### Core Systems
- Turn-based 1v1 battle loop
- Speed-based turn order system
- Battle unit abstraction layer
- Character stat system (health, offense, speed)
- Modular battle engine structure

### Ability System
- Data-driven ability loading via JSON
- Effect-based ability execution pipeline
- Extensible effect architecture for future expansion

### Data System
- JSON-based character and ability definitions
- Enum parsing system for clean string-to-type conversion
- Modular loaders for characters and abilities

---

## How to Build & Run

### Requirements
- g++ with C++17 support (MinGW / MSYS2 / Linux GCC)
- GNU Make

### Build & Run:

Navigate to the `src` directory to compile using the project Makefile, then execute the compiled binary.

```bash
# Navigate to the source folder
cd src

# Compile the project using Make
make

# Run the battle engine executable
./battle_engine
```

## Sample Output

```text
Boot Loading Characters into Cache...
Character Cache Loaded
====================Battle Start====================

Luke Skywalker used Bullseye on Darth Vader
Critical Hit!
Luke Skywalker attacks Darth Vader for 12123 damage.
Darth Vader Prot: 35705 HP: 51902

----------------------------------------------------

Darth Vader used Force Choke on Luke Skywalker
Darth Vader attacks Luke Skywalker for 5320 damage.
Luke Skywalker Prot: 31655 HP: 51316

----------------------------------------------------

Luke Skywalker used Frontier Marksmanship on Darth Vader
Critical Hit!
Luke Skywalker attacks Darth Vader for 6061 damage.
Darth Vader Prot: 29644 HP: 51902

----------------------------------------------------

Darth Vader used Terrifying Swing on Luke Skywalker
Darth Vader attacks Luke Skywalker for 6901 damage.
Luke Skywalker Prot: 24754 HP: 51316

----------------------------------------------------
```