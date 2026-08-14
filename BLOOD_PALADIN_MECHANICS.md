# Blood Paladin Mechanics Design Addendum

## Project Context

Desryn is a trained and ordained **Paladin**, but he is also an
oathbreaker because he was bitten by a vampire and deliberately chose
not to seek a cure. His Elven nature suppresses the worst vampiric urges
and allows him to function as a **daywalker**, provided he avoids strong
sunlight.

Desryn believes the benefits of his condition---greater speed, strength,
durability, and supernatural capabilities---can help him free the Elven
people. He therefore tends to believe that the **ends justify the
means**.

He hides several truths:

-   He is an elf.
-   He is a vampire.
-   He is the missing Elven prince.

This can fit the three-month game-jam scope if vampirism is implemented
primarily as a **modifier to existing RPG systems**, rather than as a
separate vampire simulation.

------------------------------------------------------------------------

# 1. Core Character Design

``` text
                 DESRYN

         /          |          \
        /           |           \
       v            v            v

    PALADIN       VAMPIRE    CURSED SWORD
       |             |            |
     Oath           Power        Destiny
     Duty           Blood       Redemption
     Mercy        Corruption    Elven Curse
       \             |            /
        \            |           /
         +-----------+----------+
                     |
                  PLAYER
                  CHOICE
```

The key contrast is:

> The cursed sword is a power Desryn **cannot use whenever he wants**.

while:

> Vampirism is a power Desryn **can use when he wants, but perhaps
> should not**.

His normal sword, bow, and Paladin magic represent his conventional
abilities.

------------------------------------------------------------------------

# 2. Avoid a Separate Vampire Mode

Vampirism should modify systems that already exist.

  Ability           Normal Desryn       Blood Paladin Effect
  ----------------- ------------------- --------------------------
  Movement          Normal              Faster
  Melee             Normal              Stronger
  Defense           Normal              More durable
  Healing           Potions/magic       Can drain enemies
  Vision            Limited             Enhanced in darkness
  Magic             Paladin abilities   Blood abilities
  Sunlight          Normal              Penalizes vampire powers
  NPC interaction   Normal              Risk of discovery

Most of these effects require only numerical modifiers, flags, and a few
additional actions.

------------------------------------------------------------------------

# 3. Blood as a Resource

Introduce one primary vampiric resource:

``` text
BLOOD
```

The HUD might display:

``` text
HP     78/100
MP     32/50
BLOOD  64/100
```

Example state:

``` c
typedef struct {
    int blood;
    int max_blood;
    int vampire_level;
    int exposed;
    int sunlight;
} VampireState;
```

Blood should primarily be **spent when Desryn deliberately invokes
vampiric powers**. Avoid making it a constantly draining hunger meter,
which risks turning the RPG into a survival game.

------------------------------------------------------------------------

# 4. Limit Vampire Powers

For the jam version, Desryn should probably have only three or four
active vampiric abilities.

## Blood Rush

Temporarily increases movement speed.

``` text
Blood Cost: 10
Duration: 10 seconds
```

Implementation can be as simple as:

``` c
if (blood_rush_active)
    move_speed = BASE_SPEED * BLOOD_SPEED_MULTIPLIER;
```

## Blood Strength

Temporarily increases melee damage.

``` c
damage += vampire_bonus;
```

## Blood Resilience

Temporarily reduces incoming damage or helps Desryn survive otherwise
fatal attacks.

## Feed

Allows Desryn to recover blood from suitable living creatures.

------------------------------------------------------------------------

# 5. Feeding and Consequences

Different targets can provide different amounts of blood:

``` text
Animals:
    Small amount

Monsters:
    Variable amount

Hostile humans:
    Large amount

Innocent humans:
    Large amount + serious consequences
```

The game should remain completable without murdering innocents for
blood. Doing so may nevertheless be mechanically convenient, creating
temptation rather than mandatory evil behavior.

------------------------------------------------------------------------

# 6. Avoid Mandatory Hunger

Use:

``` text
Blood = optional supernatural power resource
```

rather than:

``` text
Blood = constant survival timer
```

This preserves the RPG focus.

------------------------------------------------------------------------

# 7. Paladin Oath and Moral State

Rather than a generic GOOD/EVIL meter, track important deeds:

``` c
typedef struct {
    int innocents_killed;
    int innocents_fed_on;
    int people_saved;
    int promises_broken;
    int merciful_actions;
} MoralState;
```

Systems can react to concrete actions rather than an abstract morality
number.

------------------------------------------------------------------------

# 8. Let the Player Decide Whether the Ends Justify the Means

Example situation: Desryn needs blood before entering a dangerous
dungeon.

``` text
1. Feed on a prisoner.
2. Buy livestock from a farmer.
3. Enter the dungeon weakened.
4. Search the forest for animals.
```

The easiest option can conflict with his Paladin ideals.

A choice does not need a huge branching storyline. It may simply set a
flag such as:

``` c
FLAG_FED_ON_PRISONER
```

which influences later dialogue or a cursed-sword event.

------------------------------------------------------------------------

# 9. Connect Vampirism to the Cursed Sword

The sword can react to Desryn's behavior.

For example:

``` text
Your hand closes around the hilt.

For a moment, the blade yields.

Then it recoils.

Not from the enemy.

From you.
```

Implementation could be as simple as:

``` c
if (moral.innocents_killed > threshold)
    sword.drawable = 0;
```

This creates systemic complexity by allowing two simple systems to
interact.

------------------------------------------------------------------------

# 10. Avoid Permanent Unwinnable States

Do not allow several bad choices to permanently prevent completion.

A recoverable corruption/purification loop could be:

``` text
Use vampiric power
       |
       v
Gain advantage
       |
       v
Potential corruption
       |
       v
Perform acts consistent with oath
       |
       v
Purification
       |
       v
Sword responds more strongly
```

------------------------------------------------------------------------

# 11. Sunlight Mechanics

Maps can use simple environmental flags:

``` c
#define MAP_INDOORS     0x01
#define MAP_NIGHT       0x02
#define MAP_SUNLIGHT    0x04
```

Because Desryn is an Elven daywalker, sunlight should not necessarily
damage him directly.

Strong sunlight could instead:

-   Reduce movement bonuses
-   Reduce vampire melee bonuses
-   Increase Blood ability costs
-   Reduce vampire regeneration
-   Disable selected Blood powers

The principle is:

> Daylight makes Desryn closer to normal.

> Darkness lets his vampiric nature become much more powerful.

------------------------------------------------------------------------

# 12. Vampirism and Procedural Dungeons

This works especially well with procedural dungeons.

``` text
OUTDOORS / STRONG SUNLIGHT
            |
            v
Reduced vampiric power
```

versus:

``` text
CRYPT / DUNGEON
      |
      v
No sunlight
      |
      v
Full vampiric abilities
```

Most fantasy characters become more vulnerable when entering dark
crypts. Desryn becomes more dangerous.

------------------------------------------------------------------------

# 13. Avoid Full Day/Night Simulation for the Jam

Do not immediately add:

-   Dynamic clock
-   NPC schedules
-   Shop schedules
-   Guard schedules
-   Dynamic lighting
-   Time-dependent monster populations

For the jam, simply mark maps or story situations as:

``` text
DAY
NIGHT
INDOORS
```

A full clock can be added after the jam.

------------------------------------------------------------------------

# 14. Hiding Desryn's Elven Identity

A full disguise system is unnecessary.

Establish narratively that Desryn conceals his Elven features and track
exposure with flags:

``` c
int elf_exposed;
```

or per-NPC knowledge:

``` c
npc_flags[NPC_CAPTAIN] |= KNOWS_ELF;
```

------------------------------------------------------------------------

# 15. Hiding Desryn's Vampirism

Use the same lightweight knowledge system:

``` c
#define KNOWS_ELF       0x01
#define KNOWS_VAMPIRE   0x02
#define KNOWS_PRINCE    0x04
```

Important NPCs can have:

``` c
unsigned char knowledge;
```

Different NPCs can therefore know different parts of Desryn's identity.

------------------------------------------------------------------------

# 16. Authored Exposure Events

Do not make every NPC dynamically witness every supernatural action.

Create a few authored situations where secrecy matters.

Example:

``` text
"What in the gods' name was that?"

1. You imagined it.
2. Elven magic.
3. It's complicated.
4. [Threaten him]
```

A handful of strong scenes can create the impression of a much deeper
secrecy system.

------------------------------------------------------------------------

# 17. Desryn's Multiple Identities

``` text
Public Identity
      |
      v
Foreign Warrior

Secret #1
      |
      v
Elf

Secret #2
      |
      v
Vampire

Secret #3
      |
      v
Elven Prince
```

NPCs can react differently to each revelation. Most of this can be
implemented through dialogue and flags.

------------------------------------------------------------------------

# 18. Avoid a Full Reputation System

Do not build separate numerical reputations for every faction.

Instead, track important events:

``` text
FLAG_SAVED_VILLAGE
FLAG_KILLED_PRIEST
FLAG_REVEALED_TO_MAGE
FLAG_CAPTAIN_KNOWS_VAMPIRE
```

This is easier to implement, save, debug, and test.

------------------------------------------------------------------------

# 19. Paladin Magic vs Blood Magic

The small magic system can reinforce Desryn's dual nature.

## Paladin Abilities

``` text
Heal
Ward
Smite
```

## Blood Abilities

``` text
Blood Rush
Drain
Blood Sight
```

Keep the total number of active magical and supernatural abilities
relatively small---roughly six total would provide substantial variety.

------------------------------------------------------------------------

# 20. Blood Sight

Blood Sight is well suited to an indexed-color raycaster.

Activating it could temporarily modify the palette:

``` text
Environment = darkened
Living enemies = bright
Blood = highly visible
```

It could reveal:

-   Living enemies
-   Blood trails
-   Secret doors
-   Magical objects

One inexpensive graphical effect can therefore serve several gameplay
purposes.

------------------------------------------------------------------------

# 21. Vampire Durability

Instead of simply increasing maximum HP, Blood could prevent death.

``` text
HP reaches 0

if BLOOD >= 20:
    consume 20 Blood
    restore 15 HP
```

Desryn becomes difficult to kill while well-fed, making Blood
strategically important.

------------------------------------------------------------------------

# 22. Feeding During Combat

Feeding can work as a combat finisher:

``` text
Enemy health < 20%
        +
Enemy is living
        +
Player is in melee range
        |
        v
FEED
```

Feeding could:

``` text
Kill enemy
Restore Blood
Restore a small amount of HP
```

Desryn could be briefly immobilized during the action, making feeding
safe against isolated enemies but dangerous in groups.

------------------------------------------------------------------------

# 23. Weapon Choice and Secrecy

Equipment can gain social as well as combat roles:

``` text
Normal Sword
    Conventional combat

Bow
    Safe ranged combat

Paladin Magic
    Socially acceptable supernatural ability

Blood Powers
    Powerful but potentially revealing

Cursed Sword
    Mysterious and story-dependent
```

The player is choosing not only damage output, but how much of Desryn's
true nature to reveal.

------------------------------------------------------------------------

# 24. Suggested Blood Paladin State

``` c
typedef struct {

    /* Vampire resources */
    int blood;
    int max_blood;

    /* Current effects */
    int blood_rush;
    int blood_strength;
    int blood_resilience;

    /* Moral state */
    int corruption;
    int purification;

    /* Identity */
    int elf_exposed;
    int vampire_exposed;

} BloodPaladinState;
```

NPC knowledge can remain separate.

------------------------------------------------------------------------

# 25. Scope-Safe Features

Reasonable for the three-month jam:

-   Blood meter
-   Feeding
-   Two or three vampire powers
-   Sunlight modifier
-   Blood Sight visual effect
-   NPC knowledge flags
-   A handful of authored exposure events
-   Vampirism/cursed-sword interaction
-   Several vampirism-specific dialogue choices

------------------------------------------------------------------------

# 26. Features Likely to Explode Scope

Avoid during the jam:

-   Fully simulated hunger
-   Dynamic day/night cycle
-   NPC schedules
-   General-purpose witness detection
-   Crime system
-   Dynamic rumors
-   Large faction-reputation system
-   Vampire transformations
-   Multiple vampire forms
-   Vampire clans
-   Full stealth/disguise system
-   Procedurally generated social consequences
-   Large morality tree
-   Completely branching storyline based on every action

These could easily become larger than the original RPG.

------------------------------------------------------------------------

# 27. Revised Core Game Pillars

``` text
                 DESRYN

         /          |          \
        /           |           \
       v            v            v

    PALADIN       VAMPIRE    CURSED SWORD
       |             |            |
     Oath           Power        Destiny
     Duty           Blood       Redemption
     Mercy        Corruption    Elven Curse
       \             |            /
        \            |           /
         +-----------+----------+
                     |
                  PLAYER
                  CHOICE
```

The strength of the design is that these identities do not completely
agree.

Desryn's Paladin oath limits what he should do. His vampirism provides
extremely effective ways to violate those limits. The cursed sword
appears to judge him according to rules he does not fully understand.

His objective remains sympathetic:

> Free the Elven people.

The thematic question becomes:

> **If the ends justify the means, which means are acceptable---and how
> far is Desryn willing to go?**

------------------------------------------------------------------------

# 28. Recommended Jam Feature Budget

Impose a hard budget of approximately:

``` text
1 Blood resource

3 vampire powers

1 feeding mechanic

1 sunlight rule

NPC knowledge flags

Several authored exposure events

Cursed-sword interaction
```

This is enough to make Desryn mechanically distinctive without turning
vampirism into a separate game.

------------------------------------------------------------------------

# 29. Design Principle

The Blood Paladin mechanics should follow the same principle as the rest
of the project:

> **Create systemic depth by allowing a small number of simple systems
> to interact.**

For example:

``` text
Blood
  +
Feeding
  +
Paladin deeds
  +
NPC knowledge
  +
Cursed sword state
```

can create much richer situations than any of those mechanics could
produce independently.

The goal is not to simulate every aspect of being a vampire. The goal is
to make the player consistently feel that Desryn is simultaneously:

-   A Paladin
-   An oathbreaker
-   A vampire
-   An elf hiding among humans
-   A prince separated from his people
-   The bearer of a cursed sword
-   Someone willing to use dangerous powers for what he believes is a
    righteous purpose

That identity can become one of the game's strongest distinguishing
features without exceeding the practical limits of the DOS engine or the
three-month jam.
