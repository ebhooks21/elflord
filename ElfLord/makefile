CC = gcc
OBJECTS = BUILD\ElfLord.o BUILD\Mcell.o BUILD\Entity.o BUILD\Enemy.o BUILD\Espritet.o BUILD\Texprov.o BUILD\Msga.o BUILD\Keyb.o BUILD\Inv.o BUILD\Gtex.o BUILD\Gimage.o BUILD\Player.o BUILD\Menuopt.o BUILD\Stryscr.o BUILD\Titlescr.o BUILD\Charscr.o BUILD\Map.o BUILD\Maplo.o BUILD\Gpscr.o BUILD\Game.o BUILD\Mouse.o BUILD\Screen.o BUILD\Ccscr.o BUILD\Item.o
TOBJECTS = BUILD\Testm.o BUILD\Mcell.o BUILD\Entity.o BUILD\Enemy.o BUILD\Espritet.o BUILD\Texprov.o BUILD\Msga.o BUILD\Keyb.o BUILD\Inv.o BUILD\Gtex.o BUILD\Gimage.o BUILD\Player.o BUILD\Menuopt.o BUILD\Stryscr.o BUILD\Titlescr.o BUILD\Charscr.o BUILD\Map.o BUILD\Maplo.o BUILD\Gpscr.o BUILD\Game.o BUILD\Mouse.o BUILD\Screen.o BUILD\Ccscr.o BUILD\Item.o
LIBS = -lgrx20

clean: clean-assets
	del BUILD\*.o 
	del BUILD\ELFLORD.EXE

clean-assets:
	del BUILD\ASSET\CEIL\*.*
	del BUILD\ASSET\CHARS\*.*
	del BUILD\ASSET\DOORS\*.*
	del BUILD\ASSET\FLOORS\*.*
	del BuILD\ASSET\WALLS\*.*
	del BUILD\ASSET\MAPS\*.*
	del BUILD\ASSET\*.*
	rmdir BUILD\MAPS
	rmdir BUILD\ASSET\CEIL
	rmdir BUILD\ASSET\CHARS
	rmdir BUILD\ASSET\DOORS
	rmdir BUILD\ASSET\FLOORS
	rmdir BUILD\ASSET\WALLS
	rmdir BUILD\ASSET

clean-obj:
	del BUILD\*.o

release: clean build clean-obj

run:
	BUILD\ELFLORD.EXE

runtest:
	BUILD\TESTM.EXE

build: BUILD\ELFLORD.EXE

cleanbuild: clean build

buildtest: BUILD\TESTM.EXE

assets: clean-assets
	mkdir BUILD\ASSET
	mkdir BUILD\ASSET\MAPS
	mkdir BUILD\ASSET\CEIL
	mkdir BUILD\ASSET\CHARS
	mkdir BUILD\ASSET\DOORS
	mkdir BUILD\ASSET\FLOORS
	mkdir BUILD\ASSET\WALLS
	copy ASSET\*.* BUILD\ASSET
	copy ASSET\MAPS\*.* BUILD\ASSET\MAPS
	copy ASSET\CEIL\*.* BUILD\ASSET\CEIL
	copy ASSET\CHARS\*.* BUILD\ASSET\CHARS
	copy ASSET\DOORS\*.* BUILD\ASSET\DOORS
	copy ASSET\FLOORS\*.* BUILD\ASSET\FLOORS
	copy ASSET\WALLS\*.* BUILD\ASSET\WALLS

BUILD\TESTM.EXE: $(TOBJECTS) assets
	$(CC) -o BUILD\TESTM.EXE $(TOBJECTS) $(LIBS)

BUILD\ELFLORD.EXE: $(OBJECTS) assets
	$(CC) -o BUILD\ELFLORD.EXE $(OBJECTS) $(LIBS)

BUILD\ElfLord.o: SRC\ElfLord.c
	$(CC) -c SRC\ElfLord.c -o BUILD\ElfLord.o

BUILD\Mcell.o: SRC\Mcell.c
	$(CC) -c SRC\Mcell.c -o BUILD\Mcell.o

BUILD\Entity.o: SRC\Entity.c
	$(CC) -c SRC\Entity.c -o BUILD\Entity.o

BUILD\Enemy.o: SRC\Enemy.c
	$(CC) -c SRC\Enemy.c -o BUILD\Enemy.o

BUILD\Espritet.o: SRC\Espritet.c
	$(CC) -c SRC\Espritet.c -o BUILD\Espritet.o

BUILD\Texprov.o: SRC\Texprov.c
	$(CC) -c SRC\Texprov.c -o BUILD\Texprov.o

BUILD\Msga.o: SRC\Msga.c
	$(CC) -c SRC\Msga.c -o BUILD\Msga.o

BUILD\Game.o: SRC\Game.c
	$(CC) -c SRC\Game.c -o BUILD\Game.o

BUILD\Menuopt.o: SRC\Menuopt.c
	$(CC) -c SRC\Menuopt.c -o BUILD\Menuopt.o

BUILD\Screen.o: SRC\Screen.c
	$(CC) -c SRC\Screen.c -o BUILD\Screen.o

BUILD\Ccscr.o: SRC\Ccscr.c
	$(CC) -c SRC\Ccscr.c -o BUILD\Ccscr.o

BUILD\Keyb.o: SRC\Keyb.c
	$(CC) -c SRC\Keyb.c -o BUILD\Keyb.o

BUILD\Player.o: SRC\Player.c
	$(CC) -c SRC\Player.c -o BUILD\Player.o

BUILD\Gtex.o: SRC\Gtex.c
	$(CC) -c SRC\Gtex.c -o BUILD\Gtex.o

BUILD\Gimage.o: SRC\Gimage.c
	$(CC) -c SRC\Gimage.c -o BUILD\Gimage.o

BUILD\Stryscr.o: SRC\Stryscr.c
	$(CC) -c SRC\Stryscr.c -o BUILD\Stryscr.o

BUILD\Titlescr.o: SRC\Titlescr.c
	$(CC) -c SRC\Titlescr.c -o BUILD\Titlescr.o

BUILD\Charscr.o: SRC\Charscr.c
	$(CC) -c SRC\Charscr.c -o BUILD\Charscr.o

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
