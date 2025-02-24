# dos-adventure-game

A graphical adventure game in point and click DOS style.

## Requirements

Running the game:

- MS/DOS or compatible
- A DOS Protected Mode Interface, e.g. [CWSDPMI](http://sandmann.dotster.com/cwsdpmi/)
- 386DX 33MHz (or better) with VGA
- At least 4MB of RAM
- Sound Blaster (or no sound)

Development:

- GNU Make
- DJGPP C (using GCC 5.5.0; other may work)
- Allegro 4.2.3.1 (latest with DOS support)
- DOSBOX
- RHIDE 1.5

For DJGPP and Allegro I used this [environment](http://eliasorz-1.epizy.com/blog/2019/05/dos-game-programming-the-old-school-way/?i=1).

You can build the game with `make -f GAME.MAK` (or compile from RHIDE) and run it in DOSBOX with `GAME.EXE`.

## Author

This was made by Warrior