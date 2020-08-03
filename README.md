# The_Snake_Game

Implementation of the classic Snake Game from scratch with C++ and g++ compilers in UNIX.
The game has several "states" that it can exist in. 

One of the main feature was to have a main start-menu that lets the user decide what the program 
will do with a certain command (start, end, or pause the game). 

In order to implement this, I used a state-machine in order to let the user hop between 
the pause menu state, idle state, game start state, and end games state via switch statement.

For the actual commands, the user can either hop between menus using number keys, change the direction 
of the snake using w-a-s-d keys, among other features.

To make the user interface much more realistic, I used curses in order to interrupt the user input so
that the user does not have to press the enter key in order to input a key into the program for instance 
when trying to change the direction that the snake travels. 
This way, it actually feels like a realistic game rather than a terminal program. 

The program can be compiled in a UNIX/LINUX environment using g++. 
However, the g++ compiler and the curses library must be installed on the operating system prior to compilation 
and link the library in the compilation command. 

If you're unsure, you could use these commands below to compile my game source code:

```$ sudo apt install g++```

```$ sudo apt-get install libncurses5-dev libncursesw5-dev```

```$ g++ -std=c++11 -o The_Snake_Game Snake.cpp -lncurses```

These commands will produce an executable called "The_Snake_Game" which is the game executable. 
Run this executable and you're good to go!

- WindowsDefender
