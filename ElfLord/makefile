CC = gcc
OBJECTS = BUILD\ElfLord.o BUILD\Keyb.o BUILD\Game.o BUILD\Screen.o
LIBS = -lgrx20

clean:
	del BUILD\*.o 
	del BUILD\ELFLORD.EXE
	del BUILD\ASSET\*.*
	rmdir BUILD\ASSET

clean-obj:
	del BUILD\*.o

release: clean build clean-obj

run:
	BUILD\ELFLORD.EXE

build: BUILD\ELFLORD.EXE

BUILD\ELFLORD.EXE: $(OBJECTS)
	$(CC) -o BUILD\ELFLORD.EXE $(OBJECTS) $(LIBS)
	mkdir BUILD\ASSET
	copy ASSET\*.* BUILD\ASSET

BUILD\ElfLord.o: SRC\ElfLord.c
	$(CC) -c SRC\ElfLord.c -o BUILD\ElfLord.o

BUILD\Game.o: SRC\Game.c
	$(CC) -c SRC\Game.c -o BUILD\Game.o

BUILD\Screen.o: SRC\Screen.c
	$(CC) -c SRC\Screen.c -o BUILD\Screen.o

BUILD\Keyb.o: SRC\Keyb.c
	$(CC) -c SRC\Keyb.c -o BUILD\Keyb.o
