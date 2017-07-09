# C++ Piscine Rush00
## ft\_retro

## Current Status:

Fly through text-space dodging rouge `@` symbols!

Press the space bar to shoot bullets `-` at them!

Hoo-rah! We have a basic game working!

The game is meeting the requirements listed below!

We took inspiration and content from this source:

https://github.com/fundamelon/terminal-game-tutorial

We have a few ideas for moving forward:

* Clock based time via `clock_t clock (void)`
* Window / Area to show score, game messages and story
* Scoring for destroyed `@` and time spent alive.

Here are our old ideas:

* player drops stuff
* ground grows to try and kill the player
* good falling stuff / bad falling stuff
* story ??? :)

## Game Ideas:

??? - Space Dodger (Just like the tutorial for now!)
??? - Collector / Bomber (Get ammo, drop bombs to stop death plants)

## Authors:
* qho
* myoung

## Intructions:

* Make sure this is a `C++` program not a `C` or `C+` program.
* Make sure all functions are in Copliens Form.
* Your program must be compiled with a Makefile
* The executable must be named ft\_retro

The goal of this project is to implement a simplistic shoot-em-up
style game in your terminal.

You will use a screen made up of a grid of 'squares'.
These can be equated to the characters on your terminal.
Entities of your game are each represented by a character on the screen.

### Steps:

* Acquire input
* Update game entities
* Render display
* Repeat until end of game

---

### Basic Requirements:

* Single-player mode
* Display using the ncurses library
* Horizontal or vertical scrolling
* Random Enemies
* The player can shoot at enemies
* Basic collision handling (if an enemy touches you, you die!)
* Game entities occupy one 'square' of the map only.
* Frame-based timing

### Advanced Requirements:

* Display score, time, number of lives on the screen
* Clock-based timing using whatever system facilty or library you like
* Entities that can occupy multiple squares
* Enemies can also shoot
* Scenery (Collidable objects or simple background)

### Bonus Requirements:

* Large and hard-to-beat boss enemies
* Enemies have a scripted behaviour
* Multiplayer, either local keyboard or network.
* Scripted game worlds with pre-determinded batches of enemies.
