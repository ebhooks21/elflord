# Procedural Generation Design Addendum

## Project Context

This document extends the design for the DOS semi-open-world RPG built
with **DJGPP + GRX in C** and a custom raycasting engine.

The goal is to allow dungeons and selected non-static areas to be
**procedurally generated at runtime** without requiring major changes to
the renderer or core game systems.

The central architectural principle is:

> **Maps are runtime data, not necessarily files.**

The raycaster should operate on the same `Map` structure regardless of
whether that map was loaded from disk or generated at runtime.

------------------------------------------------------------------------

# 1. Core Procedural Generation Architecture

A static map currently follows a conceptual flow like:

``` text
MAP FILE
   |
   v
load_map()
   |
   v
64x64 tile arrays
   |
   v
raycaster
```

Procedural areas should add another route:

``` text
Random Seed
   |
   v
generate_map()
   |
   v
64x64 tile arrays
   |
   v
raycaster
```

Everything below the map-generation/loading layer should remain
essentially identical.

The renderer should not know or care whether a map came from disk or was
generated moments ago.

------------------------------------------------------------------------

# 2. Add a Map Structure

Rather than allowing the renderer to depend directly on global tile
arrays, define a map structure.

``` c
#define MAP_WIDTH  64
#define MAP_HEIGHT 64

typedef struct {
    unsigned char wall[MAP_HEIGHT][MAP_WIDTH];
    unsigned char floor[MAP_HEIGHT][MAP_WIDTH];
    unsigned char ceiling[MAP_HEIGHT][MAP_WIDTH];
    unsigned char flags[MAP_HEIGHT][MAP_WIDTH];

    int start_x;
    int start_y;

    int exit_x;
    int exit_y;
} Map;
```

The active world can reference:

``` c
Map *current_map;
```

The structure may be populated by:

``` c
load_map_from_file();
```

or:

``` c
generate_dungeon();
```

The raycaster and gameplay systems then operate on the same
representation.

------------------------------------------------------------------------

# 3. Give Every Procedural Area a Seed

Every generated dungeon should have a deterministic seed.

``` c
typedef struct {
    unsigned long seed;
    int dungeon_type;
    int difficulty;
    int depth;
} DungeonInfo;
```

Generation then becomes:

``` c
generate_dungeon(&map, dungeon.seed);
```

If a particular seed always creates the same dungeon, the save file does
not necessarily need to contain the complete generated map.

Instead, it can store:

``` text
Dungeon ID
Seed
Changes made by the player
```

For example:

``` text
seed = 1849271

chest 4 = opened
enemy 17 = dead
door 9 = unlocked
```

Loading becomes:

``` text
generate dungeon from seed
        |
        v
apply saved changes
        |
        v
continue game
```

This is especially useful for reducing save-game size.

------------------------------------------------------------------------

# 4. Use a Game-Specific PRNG

For deterministic generation, avoid depending entirely on the C
library's `rand()` implementation.

A small custom pseudo-random number generator is sufficient.

``` c
static unsigned long rng_state;

void rng_seed(unsigned long seed)
{
    rng_state = seed;
}

unsigned long rng_next(void)
{
    rng_state = rng_state * 1664525UL + 1013904223UL;
    return rng_state;
}
```

A range helper can be:

``` c
int rng_range(int min, int max)
{
    return min + (rng_next() % (max - min + 1));
}
```

The generator only needs to be:

-   Fast
-   Deterministic
-   Small
-   Reproducible

Deterministic seeds also make debugging much easier.

A bug report involving:

``` text
Dungeon seed 392864
```

can reproduce the exact same generated dungeon.

------------------------------------------------------------------------

# 5. Dungeon Archetypes

Avoid making one generator responsible for every environment.

Define dungeon archetypes such as:

``` text
GEN_CRYPT
GEN_CAVE
GEN_RUINS
GEN_KEEP
GEN_SEWERS
GEN_PURGATORY
```

Different generators can then use different algorithms.

``` c
switch (dungeon_type) {

case DUNGEON_CRYPT:
    generate_rooms_and_corridors(map);
    break;

case DUNGEON_CAVE:
    generate_cellular_cave(map);
    break;

case DUNGEON_KEEP:
    generate_structured_rooms(map);
    break;
}
```

This allows different areas to feel structurally distinct without
complicating the raycaster.

------------------------------------------------------------------------

# 6. Room-and-Corridor Generation

This should probably be the first procedural-generation algorithm
implemented.

It is:

-   Simple
-   Reliable
-   Easy to debug
-   Naturally compatible with grid raycasting

Start with a map filled entirely with walls.

``` text
################################################################
################################################################
################################################################
################################################################
################################################################
```

Randomly carve rectangular rooms.

``` text
################################################
################################################
#####.........##################################
#####.........##################################
#####.........##################################
################################################
########################.......#################
########################.......#################
################################################
```

Then connect those rooms with corridors.

``` text
################################################
################################################
#####.........##################################
#####.........################................##
#####..........................................##
############.###########.......................##
############.###################################
############........................############
################################################
```

This is already enough to create functional randomized dungeons.

------------------------------------------------------------------------

# 7. Represent Rooms Explicitly

Use temporary room structures during generation.

``` c
typedef struct {
    int x;
    int y;
    int width;
    int height;

    int center_x;
    int center_y;
} Room;
```

Maintain a fixed-size room pool.

``` c
#define MAX_ROOMS 32

Room rooms[MAX_ROOMS];
int room_count;
```

A basic generation process becomes:

``` text
Fill map with walls

Repeat:
    Choose random room size
    Choose random position

    If room does not overlap:
        Carve room
        Store room

Connect rooms

Choose start room

Choose exit room

Decorate dungeon

Place monsters

Place treasure
```

------------------------------------------------------------------------

# 8. Prevent Room Overlap

Before placing a room, compare its rectangle with all existing rooms.

A one-tile padding region around rooms is useful.

This prevents accidental one-tile walls and malformed room combinations
unless they are intentionally allowed.

------------------------------------------------------------------------

# 9. Connecting Rooms

The simplest reliable approach is to connect each room to the previous
room.

``` c
for (i = 1; i < room_count; i++) {
    connect_rooms(&rooms[i - 1], &rooms[i]);
}
```

Use simple L-shaped corridors.

The major advantage is that the dungeon is automatically connected.

A first version does not require complicated graph algorithms.

------------------------------------------------------------------------

# 10. Add Extra Connections

Sequential room connections can make dungeons overly linear.

After creating the guaranteed connections, occasionally connect
additional random rooms.

``` c
for (i = 0; i < extra_connections; i++) {

    int a = rng_range(0, room_count - 1);
    int b = rng_range(0, room_count - 1);

    connect_rooms(&rooms[a], &rooms[b]);
}
```

This introduces:

-   Loops
-   Alternate routes
-   Shortcuts
-   More exploration

------------------------------------------------------------------------

# 11. Cave Generation

Caves can eventually use a cellular automaton.

Initially, randomly mark cells as either walls or floors.

``` text
##########...######
####.#..........###
###..............##
####.............##
#####.........#####
```

Then repeatedly smooth the map based on neighboring walls.

Conceptually:

``` c
if (neighbor_walls >= 5)
    new_tile = WALL;
else
    new_tile = FLOOR;
```

After several passes, this produces organic-looking cave systems.

The primary difficulty is ensuring connectivity.

For the first procedural implementation, room-and-corridor generation is
safer.

------------------------------------------------------------------------

# 12. Flood-Fill Validation

Add a flood-fill routine that starts at the player's spawn point.

``` c
flood_fill(start_x, start_y);
```

Use it to mark every reachable tile.

Then verify that important locations are reachable.

Examples:

``` text
Exit
Boss room
Quest item
Required key
Special chamber
```

If required content cannot be reached, reject the generated dungeon and
regenerate it.

A 64x64 map is small enough that this validation is inexpensive.

------------------------------------------------------------------------

# 13. Use Multiple Generation Passes

Do not generate geometry, enemies, treasure, and decoration
simultaneously.

Use a pipeline.

``` text
PASS 1
Geometry

PASS 2
Connectivity

PASS 3
Doors

PASS 4
Special rooms

PASS 5
Enemies

PASS 6
Treasure

PASS 7
Decorations

PASS 8
Validation
```

The code can follow the same structure.

``` c
generate_geometry(map);

connect_rooms(map);

place_doors(map);

place_special_rooms(map);

populate_enemies(map);

populate_items(map);

decorate_map(map);

validate_map(map);
```

This is substantially easier to debug.

------------------------------------------------------------------------

# 14. Generate Geometry Before Gameplay Content

The geometry generator should not decide enemy or treasure placement
while carving rooms.

Generate the layout first.

Then analyze the resulting rooms.

Room structures can later gain flags.

``` c
typedef struct {
    int x;
    int y;
    int width;
    int height;

    unsigned int flags;
} Room;
```

Possible room roles:

``` text
ROOM_START
ROOM_EXIT
ROOM_TREASURE
ROOM_BOSS
ROOM_NORMAL
ROOM_SECRET
```

This keeps layout generation separate from gameplay generation.

------------------------------------------------------------------------

# 15. Special Rooms

Purely random rooms become repetitive quickly.

Procedural dungeons should intentionally contain special locations.

A crypt might contain:

``` text
Entrance
Shrine
Burial chamber
Treasure room
Boss chamber
Exit
```

Conceptually:

``` text
Entrance
   |
Crypt
 /   \
A     B
|     |
Shrine
  |
Burial Chamber
  |
Boss
```

The procedural system can generate ordinary geometry around these
required room roles.

This makes the dungeon feel designed rather than arbitrary.

------------------------------------------------------------------------

# 16. Separate Layout From Appearance

Generated maps should preferably contain abstract tile types.

For example:

``` text
TILE_WALL
TILE_FLOOR
TILE_DOOR
```

A dungeon theme then translates those into actual textures.

## Crypt

``` text
TILE_WALL  -> Gray stone
TILE_DOOR  -> Iron gate
TILE_FLOOR -> Dark stone
```

## Ruins

``` text
TILE_WALL  -> Cracked masonry
TILE_DOOR  -> Rotten wood
TILE_FLOOR -> Dirt
```

## Purgatory

``` text
TILE_WALL  -> Black marble
TILE_DOOR  -> Magical barrier
TILE_FLOOR -> Purple stone
```

The same structural generator can therefore produce several visually
distinct environments.

------------------------------------------------------------------------

# 17. Dungeon Theme Definitions

Theme data can be stored in tables.

``` c
typedef struct {
    int wall_texture;
    int floor_texture;
    int ceiling_texture;
    int door_texture;

    int enemy_table;
    int treasure_table;

    int light_level;
} DungeonTheme;
```

Example:

``` c
DungeonTheme themes[] = {
    {
        TEX_CRYPT_WALL,
        TEX_CRYPT_FLOOR,
        TEX_CRYPT_CEILING,
        TEX_IRON_DOOR,
        ENEMY_TABLE_UNDEAD,
        TREASURE_TABLE_CRYPT,
        40
    }
};
```

This fits naturally with the data-driven C architecture.

------------------------------------------------------------------------

# 18. Procedural Enemy Placement

Do not place enemies at completely arbitrary coordinates.

Instead:

``` text
Choose room
Choose free tile inside room
Verify tile
Place enemy
```

Example:

``` c
void populate_room(Room *room, int difficulty)
{
    int count = rng_range(0, difficulty + 1);

    while (count--) {
        place_random_enemy(room);
    }
}
```

Enemy selection can use weighted tables.

Example crypt table:

``` text
Skeleton       60%
Rat            25%
Wraith         10%
Necromancer     5%
```

Deeper levels can use different weights.

------------------------------------------------------------------------

# 19. Encounter Budgets

An encounter-budget system provides better balancing than simply
choosing a random number of monsters.

Example enemy costs:

``` text
Rat             1
Skeleton        2
Cultist         3
Wraith          4
Knight          6
```

A room with:

``` text
budget = 6
```

might contain:

``` text
3 Skeletons
```

or:

``` text
1 Wraith + 2 Rats
```

or:

``` text
2 Cultists
```

This produces more controlled difficulty.

------------------------------------------------------------------------

# 20. Item and Treasure Tables

Loot can also use weighted tables.

``` c
typedef struct {
    int item_id;
    int weight;
} LootEntry;
```

Example crypt loot:

``` text
Gold             40
Healing potion   25
Mana potion      15
Arrows             8
Magic scroll       7
Rare artifact      5
```

------------------------------------------------------------------------

# 21. Keep Quest-Critical Content Mostly Static

Do not procedurally generate everything.

Procedural generation is especially appropriate for:

-   Crypts
-   Caves
-   Mines
-   Ruins
-   Wilderness encounters
-   Optional dungeons

Important narrative locations should generally remain handcrafted.

Examples:

-   King's castle
-   Elven barrier
-   Major temples
-   Important settlements
-   Critical story chambers
-   Final encounters

This preserves control over storytelling and pacing.

------------------------------------------------------------------------

# 22. Hybrid Dungeons

A strong compromise is to combine handmade and generated areas.

``` text
Handmade Entrance
       |
Procedural Interior
       |
Handmade Story Chamber
       |
Procedural Interior
       |
Handmade Boss Room
```

This provides replayable exploration without sacrificing important
narrative moments.

------------------------------------------------------------------------

# 23. Room Templates and Prefabs

Another useful DOS-era technique is to build predefined room templates.

Examples:

``` text
room_a.dat
room_b.dat
room_c.dat
shrine.dat
crypt.dat
library.dat
```

A room might be represented as:

``` text
########
#......#
#..##..#
#..##..#
#......#
#......#
########
```

The generator can select and connect these predefined chunks.

This can produce better results than purely rectangular random rooms.

------------------------------------------------------------------------

# 24. Advantages of Prefab Generation

Room templates provide:

-   Better-looking layouts
-   Better combat encounters
-   Intentional sight lines
-   Easier secret placement
-   Better environmental storytelling
-   Less validation work

A relatively small library could include:

``` text
8 normal room templates
3 hallway templates
3 shrine templates
3 treasure rooms
2 trap rooms
2 boss rooms
```

Their combinations can produce many different layouts.

------------------------------------------------------------------------

# 25. Procedural Dungeon Graphs

A more advanced system can generate the logical dungeon structure before
generating geometry.

Example:

``` text
          [Treasure]
              |
Entrance -- Hall -- Crypt
              |
           Shrine
              |
            Boss
              |
             Exit
```

A node might be:

``` c
typedef struct {
    int type;
    int connections[4];
} DungeonNode;
```

The graph is then converted into physical rooms and corridors.

This allows guaranteed structures such as:

``` text
Entrance
    |
Locked Door
    |
Key Room
    |
Boss
```

This is useful long term, but should be considered an upgrade rather
than the first implementation.

------------------------------------------------------------------------

# 26. Multi-Level Dungeons

Large dungeons can contain several independently generated floors.

``` text
Crypt Level 1
      |
    Stairs
      |
Crypt Level 2
      |
    Stairs
      |
Crypt Level 3
      |
     Boss
```

Each floor remains a normal 64x64 map.

A dungeon level might be represented as:

``` c
typedef struct {
    unsigned long seed;
    unsigned char dungeon;
    unsigned char depth;
} DungeonLevel;
```

Floor seeds can be derived from the dungeon seed.

``` c
floor_seed = dungeon_seed ^ (depth * 7919UL);
```

------------------------------------------------------------------------

# 27. Persistent Dungeons

Once a dungeon has been generated, its layout should normally remain
stable for that playthrough.

First visit:

``` text
Generate seed
Save seed
Generate dungeon
```

Future visits:

``` text
Load saved seed
Regenerate same dungeon
Apply saved changes
```

This makes procedural areas feel like persistent locations rather than
constantly changing roguelike levels.

------------------------------------------------------------------------

# 28. Save Only Differences

The save file does not necessarily need the complete generated map.

Suppose the generated dungeon contains:

``` text
12 enemies
5 treasure containers
3 doors
```

The player kills:

``` text
Enemy 2
Enemy 4
Enemy 7
```

and opens:

``` text
Chest 1
Chest 4
```

The save data can record only those changes.

For small collections, bitsets may work.

``` c
unsigned long dead_enemies;
unsigned long opened_chests;
unsigned long unlocked_doors;
```

Larger dungeons can use arrays or multiple bitsets.

------------------------------------------------------------------------

# 29. Deterministic Object IDs

Generated objects need stable IDs.

For example:

``` text
enemy #0
enemy #1
enemy #2
...
```

must be generated in the same order every time.

The save system can then store:

``` text
enemy #7 is dead
```

After regenerating the dungeon, the engine can apply that state to the
correct enemy.

------------------------------------------------------------------------

# 30. Separate Random Streams

A useful refinement is to use separate random streams for different
systems.

For example:

``` text
Geometry RNG
Enemy RNG
Loot RNG
Decoration RNG
```

Seeds can be derived from the base seed.

``` c
geometry_seed   = base_seed ^ 0x1234;
enemy_seed      = base_seed ^ 0x2345;
loot_seed       = base_seed ^ 0x3456;
decoration_seed = base_seed ^ 0x4567;
```

This prevents unrelated changes from affecting the entire generated
dungeon.

For example, adding one extra random torch should not change every
monster and treasure placement.

------------------------------------------------------------------------

# 31. Procedural Decorations

After functional content has been placed, run a decoration pass.

## Crypt

-   Coffins
-   Bones
-   Torches
-   Statues
-   Blood decals

## Cave

-   Rocks
-   Mushrooms
-   Pools
-   Stalagmites

## Ruins

-   Rubble
-   Broken furniture
-   Banners
-   Fallen columns

Most decorations can be sprites, allowing the underlying map geometry to
remain simple.

------------------------------------------------------------------------

# 32. Controlled Randomness

The best procedural generation should feel authored within rules rather
than completely random.

Avoid thinking only in terms of:

``` text
Random room
Random monster
Random item
```

Instead use:

``` text
Dungeon theme
      |
      v
Layout rules
      |
      v
Room roles
      |
      v
Enemy ecosystem
      |
      v
Treasure rules
      |
      v
Decorations
```

A crypt generator might know:

-   Large rooms occasionally contain shrines
-   Dead ends often contain treasure
-   Boss rooms should be far from the entrance
-   Wraiths prefer burial chambers
-   Rats are common near entrances

Small amounts of contextual logic can make generated content feel much
more intentional.

------------------------------------------------------------------------

# 33. Distance From Entrance

After generating the dungeon, calculate approximate distances from the
entrance with flood fill or breadth-first search.

This can influence enemy placement.

``` text
Distance 0–10:
    Rats
    Skeletons

Distance 10–30:
    Skeletons
    Wraiths

Distance 30+:
    Elite undead
    Treasure
    Boss
```

The exit can also be selected as one of the rooms furthest from the
entrance.

This naturally creates a sense of progression.

------------------------------------------------------------------------

# 34. Secret Rooms

Procedural generation works especially well for secrets.

A generator can:

``` text
Choose unused space adjacent to a corridor
Carve a small room
Mark the connecting wall as secret
```

Example:

``` text
###########
#.........#
#.........#
#####S#####
#####...###
#####...###
###########
```

Where:

``` text
S = secret wall
```

The player's `Sight` spell could help reveal these areas.

This directly connects procedural generation to the existing magic
system.

------------------------------------------------------------------------

# 35. Procedural Wilderness

The same principles can eventually be applied to outdoor areas.

Avoid creating an infinite procedural world.

Instead, generate individual wilderness maps such as:

``` text
Forest encounter
Swamp encounter
Mountain pass
Ruined road
```

A wilderness generator can place:

-   Trees
-   Rocks
-   Water
-   Paths
-   Ruins
-   Enemies
-   Encounters

while guaranteeing a traversable route between the entrance and exit.

------------------------------------------------------------------------

# 36. Generated Travel Encounters

A useful semi-open-world structure is to keep major world locations
static while generating occasional travel maps.

For example:

``` text
Village
   |
Forest ----- Ruins
   |
Capital
```

Travel between locations might occasionally generate:

``` text
Forest encounter
```

or:

``` text
Bandit ambush
```

or:

``` text
Abandoned shrine
```

This can make the world feel substantially larger without requiring many
handcrafted maps.

------------------------------------------------------------------------

# 37. Areas That Should Remain Handmade

For this game, the following should probably remain static:

-   Main towns
-   Story NPC interiors
-   Elven barrier
-   Major story temples
-   Important boss arenas
-   Cursed-sword awakening encounters
-   Final areas of purgatory

These locations are too narratively important to leave entirely to
randomness.

------------------------------------------------------------------------

# 38. Suggested Module Additions

Add procedural-generation modules to the existing source layout.

``` text
src/

    procgen.c
    procgen.h

    dungeon.c
    dungeon.h

    random.c
    random.h
```

Optional later additions:

``` text
roomgen.c
roomgen.h

cavegen.c
cavegen.h
```

## `random.c`

Responsibilities:

``` text
PRNG
Seeding
Random ranges
Weighted selection
```

## `procgen.c`

Responsibilities:

``` text
Common generation utilities
Flood fill
Validation
Tile placement
Distance maps
```

## `dungeon.c`

Responsibilities:

``` text
Room generation
Corridors
Special rooms
Enemy placement
Treasure placement
```

The renderer should remain largely untouched.

------------------------------------------------------------------------

# 39. Suggested Runtime Flow

Entering a procedural dungeon could resemble:

``` c
void enter_dungeon(int dungeon_id)
{
    DungeonState *dungeon;

    dungeon = &game.dungeons[dungeon_id];

    if (!dungeon->initialized) {
        dungeon->seed = create_seed();
        dungeon->initialized = 1;
    }

    generate_dungeon(&world.map,
                     dungeon->seed,
                     dungeon->type,
                     dungeon->depth);

    apply_dungeon_state(dungeon);

    world.current_map = &world.map;
}
```

Conceptually:

``` text
Enter dungeon
     |
Does it have a seed?
   /     \
 no      yes
 |        |
create    use saved
 seed     seed
   \      /
 generate map
      |
apply persistent state
      |
start gameplay
```

------------------------------------------------------------------------

# 40. Generation Failure Handling

Never assume generated content is valid.

The generator should be allowed to fail.

``` c
for (attempt = 0; attempt < 20; attempt++) {

    generate_dungeon(...);

    if (validate_dungeon(...))
        return 1;
}
```

If all attempts fail:

``` text
Use fallback map
```

The fallback can be a small predefined dungeon.

This prevents generation bugs from making the game impossible to
continue.

------------------------------------------------------------------------

# 41. Validation Checklist

Before accepting a generated level, verify:

-   Player spawn is valid
-   Exit exists
-   Exit is reachable
-   Boss is reachable
-   Required keys exist
-   Keys appear before their corresponding locked doors
-   Quest items are reachable
-   Player does not spawn inside an enemy
-   Enemies are not inside walls
-   Treasure is not inside walls
-   Doors connect valid spaces
-   Required room count exists

If validation fails:

``` text
Reject map
Regenerate
```

------------------------------------------------------------------------

# 42. Realistic Implementation Stages

For a three-month jam, procedural generation should be introduced
gradually.

## Stage 1

Generate only:

``` text
Rectangular rooms
+
L-shaped corridors
```

## Stage 2

Add:

``` text
Enemy placement
Treasure
Start
Exit
```

## Stage 3

Add:

``` text
Room types
Special rooms
Doors
```

## Stage 4

Add:

``` text
Theme definitions
Difficulty scaling
Secrets
```

## Stage 5 --- Optional

Add:

``` text
Caves
Wilderness
Room templates
```

Do not attempt procedural caves, villages, wilderness, quests, enemies,
loot, and story generation simultaneously.

------------------------------------------------------------------------

# 43. Recommended Hybrid World Structure

For this project, a hybrid structure is probably the strongest option.

``` text
              STATIC WORLD
                   |
          +--------+--------+
          |                 |
       Towns             Roads
          |                 |
   Handmade quests     Random encounters
          |
    Story dungeon
          |
 Handmade entrance
          |
 Procedural floors
          |
 Handmade story room
          |
 Procedural floor
          |
 Handmade boss room
```

This combines:

-   Authored RPG storytelling
-   Procedural exploration
-   Persistent locations
-   Controlled scope
-   Replayability

It also fits well with the project's *Daggerfall*-inspired design goals.

------------------------------------------------------------------------

# 44. Core Architectural Rule

The most important addition to the engine design is:

> **Maps are runtime data, not necessarily files.**

A map should simply be a `Map` structure.

That structure may be populated by:

``` text
Disk loader
Dungeon generator
Cave generator
Wilderness generator
Level editor
```

Everything else in the engine should operate on the resulting map
identically.

This abstraction allows procedural generation to become another source
of map data rather than a separate engine or rendering system.

------------------------------------------------------------------------

# 45. Procedural Generation Priorities

For the game jam, prioritize procedural-generation work in this order:

1.  **Create a common runtime `Map` representation.**
2.  **Implement a deterministic PRNG and dungeon seeds.**
3.  **Generate rectangular rooms and corridors.**
4.  **Guarantee connectivity with flood-fill validation.**
5.  **Place entrances, exits, enemies, and treasure.**
6.  **Persist generated dungeons through saved seeds.**
7.  **Save player-caused differences such as dead enemies and opened
    chests.**
8.  **Add dungeon themes and special rooms.**
9.  **Add prefab rooms if time permits.**
10. **Only then consider caves and procedural wilderness.**

The procedural-generation system should increase the amount of playable
content without becoming a larger engineering project than the RPG
itself.
