# Minesweeper in C++

This is a console-based implementation of the classic **Minesweeper** game written in C++. The game includes three difficulty levels (Easy, Medium, and Hard) and features basic gameplay elements such as revealing cells, flagging mines, and determining win/loss conditions.

---

## Features

- **Three Difficulty Levels**:
  - **Easy**: 5x5 grid with 5 mines.
  - **Medium**: 8x8 grid with 15 mines.
  - **Hard**: 12x12 grid with 30 mines.
- **Gameplay Mechanics**:
  - Reveal cells to uncover numbers indicating nearby mines.
  - Flag cells to mark suspected mines.
  - Win by revealing all non-mine cells or lose by hitting a mine.
- **Dynamic Board**:
  - Mines are placed randomly each time the game starts.

---

## How to Play

1. Run the program:

   ```bash
   g++ minesweeper.cpp -o minesweeper
   ./minesweeper
   ```

2. Select a difficulty level:
   - Enter `1` for Easy.
   - Enter `2` for Medium.
   - Enter `3` for Hard.

3. Play the game:
   - Use `r <row> <column>` to reveal a cell (e.g., `r 3 4`).
   - Use `f <row> <column>` to flag/unflag a cell (e.g., `f 2 1`).

4. The game ends when:
   - You reveal all non-mine cells (you win).
   - You hit a mine (game over).

---

## How It Works

1. **Board Setup**:
   - The board size and number of mines are determined by the selected difficulty level.
   - Mines are placed randomly on the grid.

2. **Game Logic**:
   - If you reveal a cell with no adjacent mines, the game automatically reveals all connected cells without mines.
   - Numbers indicate the count of adjacent mines.
   - Flagging a cell is a manual action to mark suspected mines.

3. **Winning/Losing**:
   - Win: Reveal all non-mine cells.
   - Lose: Reveal a mine.

---

## Files

- `minesweeper.cpp`: Main program containing all game logic.

---

## Future Enhancements

- Add a timer to track how quickly the game is completed.
- Include a leaderboard to record high scores.
- Implement graphical interface using a library like SFML or SDL.
