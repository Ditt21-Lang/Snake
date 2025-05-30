<p align="center">
  <img src="https://github.com/user-attachments/assets/5e6a4e1e-7342-4e65-baff-c316c5219785" alt="ssGameplay2" width="600">
</p>

# 🐍 Snave - Snake Cave

**Snave** (short for *Snake Cave*) is a game inspired by the legendary classic *Snake*, but reimagined with modern twists and exciting new features that make the gameplay more thrilling and challenging.

Unlike the typical Snake game, **Snave** takes you into a cave full of surprises, portals, and bullets! You won’t just be avoiding walls — you'll dodge moving obstacles and enemies too!

# ✨ Features
- **Endless Mode:** Play like the classic *Snake* game and aim for the highest score possible!
- **Stage Mode:** Reach a score of 1000 to advance to the next level — up to level 5! The higher the level, the harder the enemies and obstacles become.
- **Reverse Snake:** Instantly swap your head to the tail position for a quick turnaround! (Stage Mode)
- **Portal:** Shoot portals at walls and use them strategically to teleport across the map! (Stage Mode)

# 🎮 Gameplay Instructions

- **Movement**
  - Use the arrow keys (Up, Down, Left, Right) to move in the desired direction.
  - The snake moves continuously in the last chosen direction until you change it.

- **Game Over**
  - There are 4 things that can cause a game over: Walls, stone obstacles, your own body, and enemies (_minecarts_).
  - If the snake hits a wall or its own body, the game ends instantly regardless of remaining lives.
  - If it hits a stone or enemy, 1 life will be lost. The game ends when your lives reach 0.

- **Mode**
  - In endless mode, you can grow your snake as big as you want and reach higher score until you cover all the map and game over. 
  - In stage mode, there is 5 level in total. Each level will get more difficult and in order to get to the next level, the player must reach 1000 score by eating food.

# 👥 Team Member
| Name | Account | Contributions |
|----------|----------|----------|
| Dwika Bayu | byebay | Asset, Main Menu |
| Emir Althaf | Zerokarahajimaru | Portal |
| Gilang Aditya | Ditt21-Lang | Snake, Check Collision |
| Hilmi Mahdani | hilmimahdani | Reverse, Check Collision |
| Marrely Salsa | marrelykasih | Obstacle, Food, Draw Visual |

# 🛠️ How to build and run
- Use raylib, if you don't have one you can download it at https://www.raylib.com/.
- Your compiler must have raylib.h in your repective compiler "include" file.
- Also, put libraylib.a in your respective compiler "lib" file.
- Compile the all the .c files in this github using the linker -lraylib -lwinmm -lgdi32 -lopengl32.
- For ex.: gcc -o main.exe main.c Gilang.c Bayu.c emir.c Marrely.c Hilmi.c -lraylib -lwinmm -lgdi32 -lopengl32.
- After compile, run the game in the terminal using: ./main.exe and enjoy.

# 📝 License

This project is licensed under the [MIT License](LICENSE).
