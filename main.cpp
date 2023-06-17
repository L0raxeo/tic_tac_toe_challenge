#include <iostream>

const int BOARD_SIZE = 3;
char board[BOARD_SIZE][BOARD_SIZE];
const char EMPTY_SLOT = ' ';

char playerTurn = 'X';
bool playing = true;

// noughts = O
// crosses = X
void drawBoard() {
    std::cout << "Current Board: " << std::endl;
    std::cout << "    0     1     2" << std::endl;
    std::cout << "       |     |    " << std::endl;
    std::cout << "0   " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  " << std::endl;
    std::cout << "  -----+-----+-----" << std::endl;
    std::cout << "1   " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  " << std::endl;
    std::cout << "  -----+-----+-----" << std::endl;
    std::cout << "2   " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  " << std::endl;
    std::cout << "       |     |    " << std::endl;
}

void reset() {
    for (auto & r : board) {
        for (char & c : r) {
            c = EMPTY_SLOT;
        }
    }
}

void tie() {
    std::cout << "Tie! Nobody won!" << std::endl;
    playing = false;
}

void checkTie() {
    bool hasTie = true;

    for (auto &row : board) {
        for (char column : row) {
            if (column == EMPTY_SLOT)
                hasTie = false;
        }
    }

    if (hasTie) tie();
}

void win(char player) {
    std::cout << "Player " << player << " won!" << std::endl;
    playing = false;
}

bool checkDiagonals() {
    char diagonalSlots[3];
    for (int i = 0; i < BOARD_SIZE; i++) {
        diagonalSlots[i] = board[i][i];
    }

    bool isDiagonalConnection =
            diagonalSlots[0] != EMPTY_SLOT &&
            diagonalSlots[0] == diagonalSlots[1] &&
            diagonalSlots[1] == diagonalSlots[2];

    if (isDiagonalConnection) {
        win(diagonalSlots[0]);
        return true;
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        diagonalSlots[i] = board[i][BOARD_SIZE - 1 - i];
    }

    isDiagonalConnection =
            diagonalSlots[0] != EMPTY_SLOT &&
            diagonalSlots[0] == diagonalSlots[1] &&
            diagonalSlots[1] == diagonalSlots[2];

    if (isDiagonalConnection) {
        win(diagonalSlots[0]);
        return true;
    }

    return false;
}

bool checkColumns() {
    for (int column = 0; column < BOARD_SIZE; column++) {
        char lastCharacter = board[0][column];
        int patternOccurrences = 1;
        if (lastCharacter == EMPTY_SLOT) continue;
        for (int row = 1; row < BOARD_SIZE; row++) {
            char currentCharacter = board[row][column];
            if (currentCharacter != lastCharacter) break;
            patternOccurrences++;
        }

        if (patternOccurrences == 3) {
            win(lastCharacter);
            return true;
        }
    }

    return false;
}

bool checkRow() {
    for (auto & row : board) {
        char lastCharacter = row[0];
        int patternOccurrences = 1;
        if (lastCharacter == EMPTY_SLOT) continue;
        for (int column = 1; column < BOARD_SIZE; column++) {
            char currentCharacter = row[column];
            if (currentCharacter != lastCharacter) break;
            patternOccurrences++;
        }

        if (patternOccurrences == 3) {
            win(lastCharacter);
            return true;
        }
    }

    return false;
}

void checkForWins() {
    bool won = checkDiagonals();
    if (!won)
        won = checkColumns();
    if (!won)
        won = checkRow();
    if (!won)
        checkTie();
}

void place() {
    int cPlace;
    int rPlace;

    std::cout << "It's your turn " << playerTurn << "!" << std::endl;
    std::cout << "Type in column [0, 2]" << std::endl;
    std::cin >> cPlace;
    std::cout << "Type in row [0, 2]" << std::endl;
    std::cin >> rPlace;

    bool outOfBounds = cPlace > 2 || rPlace > 2;
    bool alreadyMarked = board[rPlace][cPlace] != EMPTY_SLOT;
    if (alreadyMarked || outOfBounds) {
        if (outOfBounds)
            std::cout << "Invalid slot" << std::endl;
        else std::cout << "Place is already taken by " << board[rPlace][cPlace] << "!" << std::endl;
        place();
    }

    board[rPlace][cPlace] = playerTurn;
    drawBoard();
    playerTurn = playerTurn == 'X' ? 'O' : 'X';
    checkForWins();
}

void run() {
    drawBoard();
    while (playing) place();

    std::cout << "Keep Playing? [Y/n]" << std::endl;
    char input;
    std::cin >> input;
    playing = input != 'n';
    if (playing) {
        reset();
        run();
    }
}

int main() {
    reset();
    run();

    return 0;
}
