CC = gcc
OBJECTS = BUILD\ElfLord.o BUILD\Keyb.o BUILD\Inv.o BUILD\Player.o BUILD\Menuopt.o BUILD\Stryscr.o BUILD\Titlescr.o BUILD\Map.o BUILD\Maplo.o BUILD\Gpscr.o BUILD\Game.o BUILD\Mouse.o BUILD\Screen.o BUILD\Item.o
TOBJECTS = BUILD\Testm.o BUILD\Keyb.o BUILD\Inv.o BUILD\Player.o BUILD\Menuopt.o BUILD\Stryscr.o BUILD\Titlescr.o BUILD\Map.o BUILD\Maplo.o BUILD\Gpscr.o BUILD\Game.o BUILD\Mouse.o BUILD\Screen.o BUILD\Item.o
LIBS = -lgrx20

clean:
	del BUILD\*.o 
	del BUILD\ELFLORD.EXE
	del BUILD\ASSET\MAPS\*.*
	del BUILD\ASSET\*.*
	rmdir BUILD\MAPS
	rmdir BUILD\ASSET

clean-obj:
	del BUILD\*.o

release: clean build clean-obj

run:
	BUILD\ELFLORD.EXE

runtest:
	BUILD\TESTM.EXE

build: BUILD\ELFLORD.EXE

buildtest: BUILD\TESTM.EXE

assets: clean
	mkdir BUILD\ASSET
	mkdir BUILD\ASSET\MAPS
	copy ASSET\*.* BUILD\ASSET
	copy ASSET\MAPS\*.* BUILD\ASSET\MAPS

BUILD\TESTM.EXE: $(TOBJECTS)
	$(CC) -o BUILD\TESTM.EXE $(TOBJECTS) $(LIBS)
	mkdir BUILD\ASSET
	mkdir BUILD\ASSET\MAPS
	copy ASSET\*.* BUILD\ASSET
	copy ASSET\MAPS\*.* BUILD\ASSET\MAPS

BUILD\ELFLORD.EXE: $(OBJECTS)
	$(CC) -o BUILD\ELFLORD.EXE $(OBJECTS) $(LIBS)
	mkdir BUILD\ASSET
	mkdir BUILD\ASSET\MAPS
	copy ASSET\*.* BUILD\ASSET
	copy ASSET\MAPS\*.* BUILD\ASSET\MAPS

BUILD\ElfLord.o: SRC\ElfLord.c
	$(CC) -c SRC\ElfLord.c -o BUILD\ElfLord.o

BUILD\Game.o: SRC\Game.c
	$(CC) -c SRC\Game.c -o BUILD\Game.o

BUILD\Menuopt.o: SRC\Menuopt.c
	$(CC) -c SRC\Menuopt.c -o BUILD\Menuopt.o

BUILD\Screen.o: SRC\Screen.c
	$(CC) -c SRC\Screen.c -o BUILD\Screen.o

BUILD\Keyb.o: SRC\Keyb.c
	$(CC) -c SRC\Keyb.c -o BUILD\Keyb.o

BUILD\Player.o: SRC\Player.c
	$(CC) -c SRC\Player.c -o BUILD\Player.o

BUILD\Stryscr.o: SRC\Stryscr.c
	$(CC) -c SRC\Stryscr.c -o BUILD\Stryscr.o

BUILD\Titlescr.o: SRC\Titlescr.c
	$(CC) -c SRC\Titlescr.c -o BUILD\Titlescr.o

BUILD\Item.o: SRC\Item.c
	$(CC) -c SRC\Item.c -o BUILD\Item.o

BUILD\Inv.o: SRC\Inv.c
	$(CC) -c SRC\Inv.c -o BUILD\Inv.o

BUILD\Gpscr.o: SRC\Gpscr.c
	$(CC) -c SRC\Gpscr.c -o BUILD\Gpscr.o

BUILD\Map.o: SRC\Map.c
	$(CC) -c SRC\Map.c -o BUILD\Map.o

BUILD\Maplo.o: SRC\Maplo.c
	$(CC) -c SRC\Maplo.c -o BUILD\Maplo.o

BUILD\Mouse.o: SRC\Mouse.c
	$(CC) -c SRC\Mouse.c -o BUILD\Mouse.o

BUILD\Testm.o: SRC\Testm.c
	$(CC) -c SRC\Testm.c -o BUILD\Testm.o
