# ENCE260 Embedded Systems: Snake Game

## Overview
This project is a two-player version of the classic game *Snake*, developed as part of the ENCE260 Embedded Programming course for Semester 2, 2024. The game is built for the UCFK4 microcontroller boards and demonstrates key concepts of embedded systems programming, including modular C design, hardware abstraction using APIs, and inter-board communication using IR.

**Due Date**: Week 6 of Term 4, 2024  
**Group**: 214

## Group Members
- **Auron Walker**
- **Yumeng Shi**

## How to Play

### Game Objective
Each player controls a snake on their own UCFK4 board. The objective is to eat as much food as possible without colliding with the walls or your own snakes tail. The player who surives the longest wins.

### Controls
- **Navswitch Up**: Move the snake up.
- **Navswitch Down**: Move the snake down.
- **Navswitch Left**: Move the snake left.
- **Navswitch Right**: Move the snake right.

Each player controls their snake using the navswitch on their UCFK4 board.

### Game Rules
- The snake moves in the direction indicated by the navswitch.
- Players collect food items that appear randomly on the display. Each time a food item is eaten, the snake grows longer.
- If a snake collides with the wall, or itself, the game is over, and the other player wins.

## Hardware Requirements
- 2 x UCFK4 microcontroller boards
- USB connection to Erskine Lab computers running avr-gcc 5.4.0