# Out of Cash (Sin blanca)

A point and click adventure game for DOS operating system.

## Synopsis

Your favorite rock band is coming to town, but you don't have enough money to buy a ticket. 
You will need to get the money, but the fact that your high school grades have not gone very well will not be of much help to achieve your goal.
When the hard work and put the nose to the grindstone are already ruled out from your plan, the only thing left to do is use deception, mischief and your mug to reach your dream.

Will you be able to achieve it?

Out of Cash  is a hand-drawing MS-DOS "point and click" graphic adventure in a comedy tone set in the high school of the 90s and fulled of cultural references of the time.

## Requirements

Running the game:

- MS/DOS or compatible
- A DOS Protected Mode Interface, e.g. [CWSDPMI](http://sandmann.dotster.com/cwsdpmi/)
- 386DX 33MHz (or better) with VGA
- At least 8MB of RAM
- Sound Blaster (or no sound)

## Development:

- GNU Make
- DJGPP C (using GCC 5.5.0; other may work)
- Allegro 4.2.3.1 (latest with DOS support)
- DOSBOX
- RHIDE 1.5

For the development with DJGPP and Allegro on DOS operating sytem I used this [environment](http://eliasorz-1.epizy.com/blog/2019/05/dos-game-programming-the-old-school-way/?i=1).

You can build the game with `make -f GAME.MAK` (or compile from RHIDE) and run it in DOSBOX with `GAME.EXE`.

I added a makefile for cross-compiling DJGPP compiler from this [repo](https://github.com/andrewwutw/build-djgpp/releases).

You can build the game with `make debug` or `make release`.

You need to edit the makefile `OS_INC_DIR`, `OS_GCC`, `OS_DOSBOX` vars with your actual paths.

If you use C/C++ vscode extension you may edit `c_cpp_properties.json` to point your compiler and library paths.

## Localization

The game has the language hardcoded. There's the master branch with the spanish language and `eng-lang` branch with the english language.

## Author

This was made by Warrior (Warcom Soft.)