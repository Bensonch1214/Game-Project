# Introduction to Programming II Final Project
> A C++ tower defense game built with the Allegro5 library, developed as the final project for **Introduction to Programming II** at NTHU.

## 🎮 Gameplay Overview

Defend your base by strategically placing towers along the enemy's path. Survive all waves of monsters and enemies across multiple levels to win!

- Place towers on the map to shoot incoming enemies
- Control a **Hero** character that can move freely and attack
- Manage your gold to build and upgrade your defenses
- Complete all 4 levels with increasing difficulty

---

## 🗺️ Game Screens

| State | Description |
|-------|-------------|
| Menu | Main menu with Start / Guide / Story / Setting / Quit |
| Story | Background lore of the game |
| Guide | How to play instructions |
| Setting | Difficulty selection (Easy / Hard) |
| Level | Main gameplay — place towers, fight enemies |
| Pause | Pause mid-game |
| Game Over | Triggered when the base is destroyed |

---

## 🗼 Towers

| Tower | Description |
|-------|-------------|
| Arcane | Magic beam, balanced stats |
| Archer | Fast attack speed, low cost |
| Canon | High damage, slow fire rate |
| Poison | Applies damage over time |
| Storm | Area effect attacks |

Each tower has a price; manage your gold wisely!

---

## 👾 Enemies & Monsters

**Enemies** spawn in waves defined per level. **Monsters** are stronger units with animated sprites:

- CaveMan
- DemonNinja
- Wolf
- WolfKnight

---

## 🦸 Hero

A controllable hero character (Dragonite) that you can move around the map and use to fight enemies directly alongside your towers.

---

## 📁 Project Structure

```
├── Main.cpp / Game.cpp / Game.h     # Game entry & main loop
├── Level.cpp / Level.h              # Level management & road path
├── Player.cpp / Player.h            # Player stats (HP, gold)
├── Hero.cpp / Hero.h                # Controllable hero character
├── UI.cpp / UI.h                    # HUD and interface rendering
├── towers/                          # Tower classes (Arcane, Archer, Canon, Poison, Storm)
├── enemies/                         # Enemy classes
├── monsters/                        # Monster classes with animations
├── data/                            # Resource centers (Image, Sound, Font, GIF)
├── shapes/                          # Geometry helpers (Point, Rectangle, Circle)
├── assets/
│   ├── image/                       # Sprites, backgrounds, UI images
│   ├── sound/                       # BGM and sound effects
│   ├── gif/                         # Animated GIF sprites
│   ├── font/                        # Game fonts
│   └── level/                       # Level map data files
└── algif5/                          # GIF rendering library for Allegro5
```

---

## 🛠️ Build & Run

### Requirements
- C++17 or later
- [Allegro5](https://github.com/liballeg/allegro5/releases)
- MinGW (Windows) or g++ (Linux/Mac)

### Build
```bash
make
```

### Run
```bash
./game
```

> The `.dll` files (Allegro, libgcc, libstdc++, libwinpthread) are included for Windows users so no separate installation is needed.

---

## 🎵 Assets

- Background music and sound effects included under `assets/sound/`
- All sprite images under `assets/image/`
- Level maps defined as text files under `assets/level/`

---

## 📚 References

- [Allegro5 Releases](https://github.com/liballeg/allegro5/releases)
- [Allegro5 Install (Mac)](https://hackmd.io/@Jiza/BkZ5a5yL2)
- [Allegro5 Documentation](https://www.allegro.cc/manual/5/index.html)
- [GIF Converter](https://ezgif.com/video-to-gif)


