A classical raycaster RPG adventure game for DOS.

https://github.com/ebhooks21/elflord

This is a playable demo of game features and not the complete game. Please keep this in mind. I do intend to finish this game and will post it here when done.

Install instructions

Read Me

----------------------------------------------------

DosBox:

To play this game, simply copy the contents of this zip file or disk image to a folder on your mounted root and run iotd.exe from that folder.

DOS:

To play this game, simply copy the contents of this zip file or disk image to a folder on C: and run elflord.exe from that folder.

Example:

mkdir c:\elflord

copy *.* c:\elflord

cd elflord

elflord.exe

To build this game from source, you must have DJGPP and the GRX20 headers/libraries installed inside DosBox/your DOS installation.  A makefile is included, with the following options:

make cleanbuild -- performs a clean build of the project, placing everything in the BUILD folder

make build -- performs a build, without deleting .o files, in the BUILD folder

Playing the Game

----------------------------------------------------

Gameplay is relatively simple. A mouse is required for combat.

w/Up Arrow - Move forward.

d/Down Arrow - Move backward.

a/Left Arrow - Rotate left.

d/Right Arrow - Rotate right.

F1 - Open the help screen.

c - Open the character sheet.

Left mouse button - Attack an enemy.

e - Interact with an object.

ESC - Exit the game.

The current goal is simple, since this is a demo: collect all the bags of gold in the dungeon, and then make it back to the dungeon door. The dungeon door cannot be opened until all bags have been collected.