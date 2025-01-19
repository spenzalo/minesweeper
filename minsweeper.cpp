#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

// Difficulty settings
const int EASY_SIZE = 5;
const int EASY_MINES = 5;
const int MEDIUM_SIZE = 8;
const int MEDIUM_MINES = 15;
const int HARD_SIZE = 12;
const int HARD_MINES = 30;

int GRID_SIZE;
int NUM_MINES;
vector<vector<char>> board;
vector<vector<bool>> revealed;
vector<vector<bool>> mines;
vector<vector<bool>> flagged;

// Function to print the board
void printBoard(bool revealAll = false) {
    cout << "   ";
    for (int i = 0; i < GRID_SIZE; ++i) {
        cout << setw(2) << i << " ";
    }
    cout << endl;

    for (int i = 0; i < GRID_SIZE; ++i) {
        cout << setw(2) << i << " ";
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (revealAll) {
                if (mines[i][j]) {
                    cout << setw(2) << 'M' << " ";
                } else {
                    cout << setw(2) << board[i][j] << " ";
                }
            } else if (flagged[i][j]) {
                cout << setw(2) << 'F' << " ";
            } else if (revealed[i][j]) {
                cout << setw(2) << board[i][j] << " ";
            } else {
                cout << setw(2) << '*' << " ";
            }
        }
        cout << endl;
    }
}

// Function to randomly place mines on the grid
void placeMines() {
    srand(time(0));
    int placed = 0;

    while (placed < NUM_MINES) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;

        if (!mines[x][y]) {
            mines[x][y] = true;
            ++placed;
        }
    }
}

// Count the number of mines adjacent to a cell
int countAdjacentMines(int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE && mines[nx][ny]) {
                ++count;
            }
        }
    }
    return count;
}

// Function to reveal a cell
bool revealCell(int x, int y) {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE || revealed[x][y] || flagged[x][y]) {
        return false;
    }

    revealed[x][y] = true;

    if (mines[x][y]) {
        board[x][y] = 'M';
        return true; // Hit a mine
    }

    int adjacentMines = countAdjacentMines(x, y);
    board[x][y] = (adjacentMines == 0) ? ' ' : '0' + adjacentMines;

    // If no adjacent mines, reveal surrounding cells
    if (adjacentMines == 0) {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx != 0 || dy != 0) {
                    revealCell(x + dx, y + dy);
                }
            }
        }
    }

    return false;
}

// Function to flag or unflag a cell
void flagCell(int x, int y) {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE || revealed[x][y]) {
        cout << "Invalid cell to flag." << endl;
        return;
    }
    flagged[x][y] = !flagged[x][y];
}

// Check if the player has won
bool checkWin() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (!mines[i][j] && !revealed[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Function to clear input buffer after an invalid input
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to initialise the game board based on difficulty
void initialiseGame(int size, int numMines) {
    GRID_SIZE = size;
    NUM_MINES = numMines;

    board.assign(GRID_SIZE, vector<char>(GRID_SIZE, '.'));
    revealed.assign(GRID_SIZE, vector<bool>(GRID_SIZE, false));
    mines.assign(GRID_SIZE, vector<bool>(GRID_SIZE, false));
    flagged.assign(GRID_SIZE, vector<bool>(GRID_SIZE, false));

    placeMines();
}

int main() {
    int difficulty;

    // Prompt user to select difficulty level
    cout << "Select difficulty level:\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";
    cout << "Enter your choice: ";
    cin >> difficulty;

    switch (difficulty) {
        case 1:
            initialiseGame(EASY_SIZE, EASY_MINES);
            break;
        case 2:
            initialiseGame(MEDIUM_SIZE, MEDIUM_MINES);
            break;
        case 3:
            initialiseGame(HARD_SIZE, HARD_MINES);
            break;
        default:
            cout << "Invalid choice. Defaulting to Medium difficulty." << endl;
            initialiseGame(MEDIUM_SIZE, MEDIUM_MINES);
            break;
    }

    bool gameOver = false;
    while (!gameOver) {
        printBoard();
        char action;
        int x, y;
        cout << "Enter action (r for reveal, f for flag) and coordinates (e.g., r 3 4): ";
        cin >> action >> x >> y;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid action and coordinates." << endl;
            clearInputBuffer();
            continue;
        }

        if (action == 'r') {
            if (revealCell(x, y)) {
                gameOver = true;
                cout << "You hit a mine! Game Over." << endl;
                printBoard(true);
            } else if (checkWin()) {
                gameOver = true;
                cout << "Congratulations! You cleared the board." << endl;
                printBoard(true);
            }
        } else if (action == 'f') {
            flagCell(x, y);
        } else {
            cout << "Invalid action. Use 'r' to reveal or 'f' to flag." << endl;
        }
    }

    return 0;
}
