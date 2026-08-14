# DOS Semi-Open World RPG Design Document

## Project Summary

A semi-open-world fantasy RPG for DOS, built with:

- **DJGPP**
- **GRX / GRX20**
- **C**
- A custom **raycasting engine**
- Development performed on Linux
- Compilation and testing performed inside DOSBox

The game follows an **elf prince** who was outside the Elven realm when the rest of his people became trapped in a form of magical purgatory.

The protagonist carries:

- A normal sword
- A cursed sword that can only be drawn at particular moments
- A bow
- A limited selection of magic

The goal is to create a game that feels appropriate for a **mid-1990s to early-2000s DOS-era RPG**, while keeping the scope manageable for a **three-month game jam**.

---

# 1. Primary Design Philosophy

The central principle should be:

> Build a small RPG on top of a reliable raycaster rather than attempting to build a general-purpose RPG engine.

The game should create the **illusion of a large world** without actually simulating one.

Favor:

- Small interconnected regions
- Strong atmosphere
- Meaningful quests
- Reusable systems
- Limited but distinct abilities
- Data-driven content
- Simple AI
- Fast loading
- Small assets

Avoid:

- Massive seamless worlds
- Complex NPC simulation
- Large skill trees
- Elaborate scripting systems
- Sophisticated physics
- Large object-oriented hierarchies
- Complex vertical geometry

---

# 2. Approximate Technological Target

Treat the game as though it were designed around approximately **1995–1998 PC hardware and conventions**.

Possible characteristics:

- DOS protected mode through DJGPP
- GRX framebuffer graphics
- Software rendering
- VGA or SVGA resolutions
- Keyboard-first controls
- Mouse support optional
- Sound Blaster / OPL / MIDI audio if time permits
- Limited animation frames
- Compact binary resources
- Separate save-game files
- Level-based world loading

Possible resolutions:

- 320×200
- 320×240
- 640×400
- 640×480

For performance and aesthetic reasons, something around **320×200 or 320×240** would be especially appropriate.

---

# 3. Language Choice: C vs C++

## Recommended Choice: C

C fits this project particularly well.

C++ would provide:

- Classes
- Inheritance
- Polymorphism
- Constructors
- Encapsulation
- Templates

However, most of those features are unnecessary for a three-month DOS RPG.

C gives you:

- Predictable memory usage
- Straightforward binary structures
- Easier serialization
- Smaller conceptual overhead
- Historically appropriate architecture
- Simple integration with DJGPP and GRX

Instead of complex object hierarchies, use:

- Structs
- Enums
- Lookup tables
- Function pointers where appropriate
- Fixed-size arrays
- Data-driven definitions

---

# 4. World Structure

Do not create a truly seamless open world.

Instead, create a collection of connected maps.

Example:

```text
World
 |
 +-- Human Border Kingdom
 |    +-- Capital Town
 |    +-- Forest
 |    +-- Abandoned Mine
 |
 +-- Western Marches
 |    +-- Village
 |    +-- Ruined Keep
 |
 +-- Haunted Vale
 |    +-- Wilderness
 |    +-- Necromancer Crypt
 |
 +-- Elven Barrier
      +-- Final Dungeon
      +-- Purgatory
```

Each area should be an independent raycaster map.

Transitions may simply display something like:

```text
Entering the Western Marches...
```

Then load the next level.

This provides several benefits:

- Only one map needs to remain in memory
- Saves are easier
- Level design is easier
- Different regions can have unique texture sets
- World size is no longer directly tied to memory usage

---

# 5. Semi-Open World Design

The player should have some freedom in deciding which locations to explore.

A simple structure could be:

```text
              Mountain Pass
                    |
Forest -------- Main Town -------- Old Road
                    |
                  Marsh
```

Each region may contain:

- One settlement
- One dungeon
- One major quest
- Several optional encounters

The game therefore feels open without requiring a massive simulation.

---

# 6. Central Gameplay Mechanic: The Cursed Sword

The cursed sword should be more than a stronger weapon.

It should be the central mechanical and narrative feature of the game.

## Normal Sword

Characteristics:

- Always usable
- Moderate damage
- Reliable
- General combat weapon
- No resource cost

## Cursed Sword

Characteristics:

- Extremely powerful
- Cannot normally be unsheathed
- Responds to specific events
- Connected to the Elven curse
- Especially effective against supernatural enemies

Attempting to equip it during normal gameplay might produce:

```text
The blade will not answer you.
```

During important moments:

```text
Something stirs within the scabbard...
```

The player may suddenly be able to draw it.

This mechanic is inexpensive to implement while giving the weapon significant personality.

---

# 7. Cursed Sword Progression

The cursed sword can also function as the game's main progression system.

Possible states:

```text
0 - Dormant
1 - Stirring
2 - Awakened
3 - Purified
```

Example structure:

```c
typedef struct {
    int purification;
    int stage;
    int drawable;
} CursedSword;
```

Certain quests increase purification.

Example progression:

```text
0–2 significant deeds:
Dormant

3–5:
Occasionally responds

6–8:
Can be drawn against supernatural enemies

9+:
Purified
```

The purified sword ultimately allows the protagonist to break through the barrier around the Elven realm.

---

# 8. Combat Design

Combat should remain intentionally straightforward.

The player already has four useful combat categories:

1. Normal Sword
2. Cursed Sword
3. Bow
4. Magic

Each should occupy a different tactical role.

| Weapon | Range | Damage | Cost | Role |
|---|---:|---:|---:|---|
| Normal Sword | Melee | Medium | None | General combat |
| Cursed Sword | Melee | Very High | Restricted | Story/supernatural combat |
| Bow | Long | Medium | Arrows | Ranged combat |
| Magic | Medium/Long | Variable | Mana | Utility/control |

---

# 9. Magic System

Keep magic deliberately small.

Four spells could easily be enough.

## Ember

- Simple offensive projectile
- Low mana cost
- Useful against weak enemies

## Heal

- Restores health
- Medium mana cost

## Ward

- Temporary defensive effect

## Sight

- Reveals secrets
- Detects magic
- Highlights hidden objects

Four useful spells are preferable to dozens of nearly identical abilities.

---

# 10. Character Statistics

Because there is only one protagonist, there is little need for an elaborate class system.

Example:

```c
typedef struct Player {
    int health;
    int max_health;

    int mana;
    int max_mana;

    int strength;
    int agility;
    int magic;

    int level;
    int experience;

    int gold;
    int arrows;

    int weapon;
} Player;
```

Possible statistic effects:

```text
Strength
    Sword damage

Agility
    Bow accuracy/damage

Magic
    Spell effectiveness
```

Levels could even be removed completely.

Major quests could directly improve statistics instead.

---

# 11. Entity Architecture

Avoid large C++-style inheritance hierarchies.

Instead of:

```text
Entity
 └── Monster
      ├── Orc
      ├── Skeleton
      └── Mage
```

use an entity type enumeration.

```c
typedef enum {
    ENTITY_ORC,
    ENTITY_SKELETON,
    ENTITY_MAGE
} EntityType;
```

Then use a generic entity structure.

```c
typedef struct {
    EntityType type;

    int x;
    int y;

    int health;
    int state;

    int sprite;
} Entity;
```

Enemy properties can be stored separately.

```c
typedef struct {
    int health;
    int damage;
    int speed;
    int sprite;
} EnemyDef;
```

Example definition table:

```c
EnemyDef enemy_defs[] = {
    { 30, 5, 2, SPR_ORC },
    { 20, 7, 2, SPR_SKELETON },
    { 15, 4, 1, SPR_MAGE }
};
```

---

# 12. Definition Data vs Runtime Data

Separate permanent definitions from active game state.

## Definition Data

Examples:

```text
MonsterDef
ItemDef
WeaponDef
SpellDef
QuestDef
```

These describe what something is.

Example:

```c
typedef struct {
    const char *name;
    int hp;
    int damage;
    int sprite;
} MonsterDef;
```

## Runtime Data

Examples:

```text
Monster
Item
Projectile
QuestState
```

These describe the current state.

Example:

```c
typedef struct {
    unsigned char type;
    short x;
    short y;
    short hp;
    unsigned char state;
} Monster;
```

Runtime entities only need to contain information that changes.

---

# 13. Use Numeric IDs

Prefer IDs over interconnected pointer structures.

Examples:

```text
Monster ID
Item ID
Quest ID
Map ID
NPC ID
Spell ID
```

Example:

```c
#define NPC_BLACKSMITH 7
#define QUEST_MISSING_CHILD 12
```

Or:

```c
typedef enum {
    QUEST_FIND_HERBS,
    QUEST_RESCUE_MERCHANT,
    QUEST_BROKEN_SHRINE
} QuestId;
```

This makes save games significantly easier.

For example:

```text
quest[12] = COMPLETE
```

is considerably easier to serialize than an object graph.

---

# 14. Raycaster World Model

Internally, keep the world fundamentally two-dimensional.

The player sees:

```text
3D-looking world
```

but the engine stores:

```text
2D map
+
sprites
+
raycasting calculations
```

Example map:

```c
unsigned char map[64][64];
```

Example tile definitions:

```text
0 - Empty
1 - Stone wall
2 - Wooden wall
3 - Door
4 - Secret wall
5 - Water
```

The player and enemies simply have two-dimensional positions.

```text
player.x
player.y

enemy.x
enemy.y
```

Collision detection should occur in this 2D space.

---

# 15. Map Size

A **64×64 tile map** is a good practical starting point.

A single byte per tile means:

```text
64 × 64 = 4096 bytes
```

Additional layers could include:

```text
Walls       4096 bytes
Floor       4096 bytes
Ceiling     4096 bytes
Flags       4096 bytes
```

Total:

```text
Approximately 16 KB
```

before entities.

This is quite manageable.

---

# 16. Level Geometry

Design levels around geometry that raycasters handle naturally.

Good candidates:

- Hallways
- Rooms
- Courtyards
- Caves
- Crypts
- Ruins
- Forest paths
- Fortresses
- Villages

Avoid relying heavily on:

- Rooms above other rooms
- Spiral staircases
- Complex bridges
- Large vertical spaces
- Overlapping floors

Stairs can simply be map transitions.

For example:

```text
You descend into the crypt.
```

Then load another map.

---

# 17. Quest System

Use a state-based quest system rather than creating a scripting language.

```c
typedef enum {
    QUEST_NOT_STARTED,
    QUEST_ACTIVE,
    QUEST_COMPLETE,
    QUEST_FAILED
} QuestStatus;
```

Then:

```c
QuestStatus quests[MAX_QUESTS];
```

NPC dialogue can check quest status.

```c
if (quests[QUEST_SHRINE] == QUEST_COMPLETE)
    dialogue = TEXT_SHRINE_THANKS;
```

---

# 18. Global Game Flags

Global Boolean-style flags are extremely useful.

Examples:

```c
#define FLAG_MET_KING        0
#define FLAG_FOUND_SHRINE    1
#define FLAG_BANDITS_DEAD    2
```

Flags can control:

- Dialogue
- Doors
- Enemy spawning
- Quest progression
- Map transitions
- Boss encounters
- Story events
- Cursed sword availability

Hundreds of Boolean flags require very little memory.

---

# 19. Dialogue System

Keep dialogue heavily constrained.

Example interface:

```text
[Portrait]

"Bandits have occupied the old tower."

1. Where is the tower?
2. What is the reward?
3. I'll handle it.
4. Goodbye.
```

Dialogue trees can be relatively small.

Text is inexpensive compared with graphical content, so dialogue is an excellent way to increase the apparent size and complexity of the world.

---

# 20. NPC Design

Avoid attempting full NPC simulation.

A blacksmith does not need:

```text
Home
Family
Sleep schedule
Meal schedule
Economic simulation
Daily pathfinding
```

He probably only needs:

```text
Position
Sprite
Dialogue
Quest flags
Shop inventory
```

The goal is to create convincing NPCs rather than fully simulate them.

---

# 21. Enemy AI

Use a small state machine.

Possible states:

```text
IDLE
PATROL
CHASE
ATTACK
HURT
DEAD
```

Example:

```c
switch (enemy->state) {

case AI_IDLE:

    if (can_see_player(enemy))
        enemy->state = AI_CHASE;

    break;

case AI_CHASE:

    move_toward_player(enemy);

    if (close_to_player(enemy))
        enemy->state = AI_ATTACK;

    break;

case AI_ATTACK:

    attack_player(enemy);

    break;
}
```

Sophisticated pathfinding is unnecessary initially.

Simple grid movement or direct movement toward the player may be sufficient.

---

# 22. Enemy Roster

Keep the roster relatively small.

Suggested target:

```text
6–10 normal enemies

2–4 elite variants

3–5 bosses
```

Possible enemies:

- Bandit
- Wolf
- Goblin
- Skeleton
- Cultist
- Wraith
- Corrupted Knight
- Demon

Variants can reuse sprites and behavior.

Example:

```text
Skeleton
Ancient Skeleton
Burning Skeleton
```

may share most of their implementation.

---

# 23. Reusing Artwork

Asset reuse is essential.

Use:

- Palette swaps
- Shared animation frames
- Shared enemy skeletons
- Texture variations
- Recolored clothing
- Reused environmental props

For example:

```text
Guard
Bandit
Cultist
```

could potentially share several animation frames.

This was common in older games and is entirely appropriate for this project.

---

# 24. Main Game Loop

Keep the main loop simple.

```c
while (running) {

    poll_input();

    update_player();
    update_entities();
    update_projectiles();

    render_world();
    render_sprites();
    render_weapon();
    render_hud();

    present_frame();
}
```

Avoid embedding unrelated functionality inside the primary game loop.

---

# 25. Suggested Source Layout

```text
src/

    main.c

    game.c
    game.h

    player.c
    player.h

    world.c
    world.h

    render.c
    render.h

    raycast.c
    raycast.h

    entity.c
    entity.h

    combat.c
    combat.h

    magic.c
    magic.h

    quest.c
    quest.h

    dialogue.c
    dialogue.h

    save.c
    save.h

    input.c
    input.h

    sound.c
    sound.h
```

Avoid placing the entire project inside one massive source file.

---

# 26. Memory Allocation Strategy

Dynamic memory allocation is available through DJGPP, but fixed-size pools can make many systems easier.

Example:

```c
#define MAX_ENTITIES 128

Entity entities[MAX_ENTITIES];
```

Other fixed pools could include:

```text
Projectiles
Items
Particles
NPCs
Temporary effects
```

Benefits include:

- Predictable memory usage
- Easier debugging
- Less fragmentation
- Easier save/load handling

---

# 27. Memory Optimization Priorities

DJGPP uses 32-bit protected mode, so there is no need to design the entire project around a 64 KB memory limit.

More important areas to optimize include:

- Texture memory
- Sprite memory
- Audio data
- Map data
- Framebuffer memory
- Rendering performance
- Asset file size

Do not sacrifice code clarity simply to save a few bytes of executable size.

---

# 28. Fixed-Point Mathematics

Fixed-point math may be useful for rendering performance on older hardware.

Example:

```c
typedef int fixed;

#define FIX_SHIFT 16
#define FIX_ONE (1 << FIX_SHIFT)
```

A 16.16 fixed-point representation can be used for:

```text
Player position
Enemy position
Ray calculations
Movement
```

Normal integers remain appropriate for:

```text
Health
Mana
Stats
Inventory
Quest states
UI
```

A hybrid approach is reasonable.

---

# 29. Rendering Pipeline

A possible rendering pipeline:

```text
1. Clear viewport

2. Draw ceiling

3. Draw floor

4. Raycast walls

5. Store wall depth

6. Sort visible sprites

7. Render sprites

8. Render player weapon

9. Render HUD
```

A depth buffer only needs one value per screen column for a traditional raycaster.

Example:

```c
fixed zbuffer[SCREEN_WIDTH];
```

This can be used to clip sprite columns behind walls.

---

# 30. Sprite-Based World Objects

Whenever possible, represent objects as sprites.

Examples:

- Enemies
- NPCs
- Trees
- Torches
- Barrels
- Tables
- Treasure
- Spell effects
- Arrows
- Corpses
- Plants

Only walls and structural geometry need to be handled directly by the raycaster.

---

# 31. HUD Design

A permanent HUD is both stylistically appropriate and useful for performance.

Example:

```text
+--------------------------------------------------+
|                                                  |
|                 3D WORLD                         |
|                                                  |
|                                                  |
+--------------------------------------------------+
| HP 82/100 | MP 24/40 | Arrows 18 | Gold 142    |
|                                                  |
|                  [Weapon]                        |
+--------------------------------------------------+
```

A 320×200 screen might only devote:

```text
320×150
```

pixels to the 3D viewport.

The remainder can contain:

- Health
- Mana
- Weapon
- Inventory information
- Character portrait
- Status effects

Rendering fewer world pixels can substantially improve performance.

---

# 32. Story Structure

## Act I — The Exiled Prince

The protagonist is outside the Elven realm when the barrier forms.

Initially, no one knows exactly what happened.

Early locations could include:

- Human border town
- Forest
- Abandoned shrine
- Bandit hideout

Gradually, the protagonist discovers:

```text
The elves are not dead.

They are trapped.

The barrier is magical.

The cursed sword reacts to the barrier.
```

The cursed sword first awakens during an act involving sacrifice, mercy, or protection.

---

## Act II — The Broken World

The protagonist travels through several regions searching for information about the barrier.

Possible locations:

- Human Kingdom
- Haunted Vale
- Ruined Dwarven Fortress
- Mage Enclave
- Borderlands

Each major region contains an important quest.

Completing these quests gradually purifies the cursed sword.

The protagonist learns that the Elven rulers were involved in a dangerous pact.

The sword may itself originate from that pact.

---

## Act III — The Purgatory

The player finally returns to the Elven boundary.

The purified sword can cut through the barrier.

The final region is the corrupted Elven realm.

Visually, it should contrast sharply with the outside world.

Normal world:

```text
Stone
Wood
Green forests
Brown earth
Blue skies
```

Purgatory:

```text
Black architecture
Purple skies
Distorted textures
Ghostly enemies
Corrupted statues
Unnatural lighting
```

The rendering technology can remain identical.

Different artwork alone can make the location feel dramatically different.

---

# 33. Suggested Content Scope

For a three-month project, a reasonable target might be:

```text
5–8 major maps

5–10 smaller maps or interiors

6–10 enemy types

4 spells

3 primary weapons

10–15 significant NPCs

8–12 quests

3–4 major bosses
```

If additional time remains, expand from there.

Do not begin with dozens of towns or hundreds of quests.

---

# 34. Build a Vertical Slice First

Before building the complete world, create one miniature version of the entire game.

The vertical slice should contain:

```text
1 town

1 NPC

1 quest

1 outdoor area

1 dungeon

2 enemy types

Normal sword

Bow

1 spell

1 cursed sword event

Save/load
```

If that works correctly, nearly every major system required for the final game already exists.

Development after that becomes primarily content creation.

---

# 35. Three-Month Development Schedule

## Week 1

Build:

- GRX initialization
- Framebuffer
- Keyboard handling
- Main game loop

Goal:

Display graphics and move something on screen.

---

## Week 2

Build:

- Raycaster
- Player movement
- Collision
- Textured walls

Goal:

Walk around a textured first-person environment.

---

## Week 3

Build:

- Sprites
- Enemies
- Basic enemy AI
- Basic combat

Goal:

Player can fight enemies.

---

## Week 4

Build:

- Normal sword
- Bow
- Projectiles
- Initial magic system

Goal:

Core combat is functional.

---

## Week 5

Build:

- Map loading
- Doors
- Map transitions
- NPCs

Goal:

Multiple locations are playable.

---

## Week 6

Build:

- Dialogue
- Quest system
- Inventory

Goal:

Functional RPG gameplay loop.

---

## Week 7

Build:

- Save/load
- Shops
- Items

Goal:

Game progression persists.

---

## Week 8

Build:

- Cursed sword mechanics
- Boss support
- Major story events

Goal:

Unique game mechanics are complete.

---

## Weeks 9–10

Focus almost entirely on:

- Maps
- Quests
- NPC dialogue
- Enemy placement
- Story implementation
- Art

These should be the primary content-production weeks.

---

## Week 11

Add or improve:

- Sound
- Music
- HUD
- Visual polish
- Menus
- Effects

---

## Week 12

Focus exclusively on:

- Testing
- Bug fixes
- Performance
- Balancing
- Packaging
- Documentation

Avoid introducing large new systems during the final week.

---

# 36. Linux and DOSBox Workflow

Keep the development repository on Linux.

Example:

```text
dos-rpg/

    src/
    assets/
    tools/
    maps/
    Makefile
    README.md
```

Mount the project directory directly into DOSBox.

Example:

```text
mount c ~/projects/dos-rpg
c:
```

Edit source files from Linux.

Example terminal:

```text
nvim src/game.c
```

Then compile from DOSBox:

```text
make
game.exe
```

Git should remain on the Linux side.

There is little reason to run Git under DOS.

---

# 37. Neovim vs VS Code

Either editor is suitable.

## Neovim Advantages

- Lightweight
- Fast startup
- Excellent keyboard workflow
- Easy terminal integration
- clangd support
- Git integration
- Grep and tags
- Minimal distraction

Useful tools include:

- clangd
- ctags
- ripgrep
- Git
- Makefile syntax support

## VS Code Advantages

- Easier project browsing
- Integrated file search
- Convenient C navigation
- Graphical Git support
- Easier asset inspection
- Potentially easier custom task configuration

Because compilation occurs inside DOSBox, neither editor is likely to provide perfectly seamless debugging.

Use whichever environment allows the fastest iteration.

---

# 38. Modern Development Tools Are Acceptable

The shipped game should follow the jam's technological restrictions.

The development pipeline does not necessarily need to.

Modern Linux tools can be used to create assets.

For example:

```text
PNG
 ↓
Python converter
 ↓
DOS texture format
```

Useful offline conversion tools could include:

```text
PNG → indexed texture

PNG spritesheet → sprite data

JSON map → binary map

Text dialogue → packed dialogue resource

WAV → DOS-compatible sound format
```

This is historically appropriate in spirit.

Commercial games often used development tools that were significantly more capable than the machines running the games.

---

# 39. Asset Packing

During early development, leave resources as individual files.

For example:

```text
textures/
sprites/
maps/
sounds/
```

Once the game works, resources may optionally be packed into something like:

```text
GAME.DAT
```

A simple archive table might use:

```c
typedef struct {
    char name[12];
    long offset;
    long size;
} ArchiveEntry;
```

The final release could therefore resemble:

```text
GAME.EXE
GAME.DAT
SETUP.EXE
README.TXT
```

Do not build the archive system until it provides an actual benefit.

---

# 40. Recommended Engine Architecture

Organize the software into approximately four conceptual layers.

```text
             GAME
      quests / combat / NPCs
               |
             WORLD
      maps / entities / items
               |
             ENGINE
    raycasting / input / sound
               |
            PLATFORM
          GRX / DJGPP
```

## Platform Layer

Contains DOS-specific code.

Examples:

- GRX initialization
- Keyboard polling
- Timers
- Sound hardware
- File handling where necessary

## Engine Layer

Contains reusable technology.

Examples:

- Raycaster
- Sprite renderer
- Collision detection
- Input abstraction
- Audio interface

## World Layer

Contains world representation.

Examples:

- Maps
- Entities
- Items
- Doors
- Projectiles

## Game Layer

Contains game-specific logic.

Examples:

- Quests
- NPC dialogue
- Cursed sword
- Combat rules
- Story progression

---

# 41. Maintain Portability

Avoid allowing GRX calls to spread throughout the entire program.

Bad:

```c
GrPlot(...);
```

appearing inside quest, combat, NPC, and inventory systems.

Prefer:

```c
draw_sprite(...);
draw_text(...);
draw_rect(...);
```

Your renderer should be the primary code that knows about GRX.

That way a future port could replace:

```text
GRX Renderer
```

with:

```text
SDL
OpenGL
Modern software renderer
```

without rewriting the game logic.

---

# 42. Make the World Feel Larger Than It Is

Worldbuilding can create scale without requiring additional maps.

NPCs can discuss:

- Distant kingdoms
- Wars
- Trade routes
- Other races
- Political conflicts
- Foreign cities
- Ancient ruins
- Regions the player cannot visit

Road signs can reinforce this.

Example:

```text
NORTH — TALERON, 180 MILES

WEST — SILVER COAST

EAST — ELVEN BORDER
```

Only one of those roads actually needs to lead somewhere playable.

The player's imagination creates much of the world.

---

# 43. Systems Priority

The following systems are essential.

## Tier 1 — Must Exist

- GRX graphics
- Input
- Raycaster
- Player movement
- Collision
- Map loading
- Sprites
- Enemies
- Combat
- Dialogue
- Quests
- Save/load

## Tier 2 — Important

- Bow
- Magic
- Cursed sword
- Inventory
- Shops
- Multiple regions
- Bosses

## Tier 3 — Optional Polish

- Music
- Sound effects
- Mouse support
- Detailed inventory UI
- Particle effects
- Automap
- Advanced enemy AI
- Complex lighting
- Animated textures

Anything in Tier 3 should be cut before sacrificing the completion of Tier 1.

---

# 44. Scope Rule

Whenever considering a new feature, ask:

> Does this feature produce more player-visible value than another map, quest, enemy, or hour of testing?

If the answer is no, postpone it.

Examples of systems that can easily consume the jam:

- Generic scripting languages
- ECS implementations
- Elaborate OOP architectures
- Dynamic lighting systems
- Portal-based geometry
- Advanced AI navigation
- Physics systems
- Complicated inventory grids
- Procedural world generation
- Fully simulated economies

These are interesting engineering projects but may not help finish the RPG.

---

# 45. Overall Target

The final game should feel like:

> A small first-person CRPG pretending to be a much larger adventure.

Its strongest elements should be:

- Atmospheric raycast environments
- Exploration
- Compact but memorable regions
- Simple melee and ranged combat
- Limited useful magic
- The cursed sword mechanic
- Strong environmental storytelling
- A clear progression toward freeing the Elven realm

Technologically, the project can draw inspiration from games such as:

- *Wolfenstein 3D*
- *Ultima Underworld*
- *Daggerfall*
- Early *Might & Magic*
- Early first-person dungeon crawlers

The goal should not be to reproduce their scale.

Instead, reproduce the **feeling** of exploring a mysterious, dangerous fantasy world using technology that plausibly belongs to the DOS era.

---

# 46. Core Project Mantra

During the three-month jam, keep these rules in mind:

1. **Finish the raycaster before expanding the RPG.**
2. **Build one vertical slice before building the world.**
3. **Use data instead of elaborate code whenever possible.**
4. **Reuse assets aggressively.**
5. **Fake simulation when the player cannot tell the difference.**
6. **Use maps and loading transitions to create scale.**
7. **Keep combat simple.**
8. **Make the cursed sword the game's defining mechanic.**
9. **Separate GRX/DOS code from game logic.**
10. **Cut systems before cutting completion.**

A finished eight-hour-looking RPG that actually provides two or three strong hours of gameplay is far more successful for this project than an unfinished engine capable of theoretically supporting fifty hours.
