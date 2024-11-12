//Zac Schmunk - 11/14/2024
//Tic Tac D'Oh

#include <iostream>
#include <string>

using namespace std;

const int BOARD_SIZE = 9;

void displayBoard(char board[]);
void clearBoard(char board[]);
bool isLegalMove(char board[], int location);
void placeMarkOnBoard(char board[], char playerMark, int location);
int getPlayerInput(string playerName);
bool hasThreeInRow(char board[], char playerMark);
void displayGameStats(int ties, int player1Score, int player2Score);

int main() {
    char board[BOARD_SIZE];
    string player1, player2;
    int player1Score = 0, player2Score = 0, ties = 0;
    bool playAgain = true;
    bool player1Starts = true;

    cout << "Enter name of Player 1 (X): ";
    cin >> player1;
    cout << "Enter name of Player 2 (O): ";
    cin >> player2;

    while (playAgain) {
        clearBoard(board);
        bool gameWon = false;
        int moves = 0;

        while (!gameWon && moves < BOARD_SIZE) {
            displayBoard(board);
            string currentPlayer = player1Starts ? player1 : player2;
            char currentMark = player1Starts ? 'X' : 'O';
            int location = getPlayerInput(currentPlayer);

            while (!isLegalMove(board, location)) {
                cout << "Invalid move. Try again." << endl;
                location = getPlayerInput(currentPlayer);
            }

            placeMarkOnBoard(board, currentMark, location);
            moves++;

            if (hasThreeInRow(board, currentMark)) {
                gameWon = true;
                if (player1Starts) {
                    player1Score++;
                    cout << currentPlayer << " wins!" << endl;
                }
                else {
                    player2Score++;
                    cout << currentPlayer << " wins!" << endl;
                }
            }

            player1Starts = !player1Starts;
        }

        if (!gameWon) {
            ties++;
            cout << "It's a tie!" << endl;
        }

        displayGameStats(ties, player1Score, player2Score);
        char choice;
        cout << "Play again? (y/n): ";
        cin >> choice;
        playAgain = (choice == 'y' || choice == 'Y');
    }

    return 0;
}

void displayBoard(char board[]) {
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
    cout << "---+---+---" << endl;
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "---+---+---" << endl;
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
}

void clearBoard(char board[]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = '0' + (i + 1);
    }
}

bool isLegalMove(char board[], int location) {
    return (location >= 1 && location <= 9 && board[location - 1] != 'X' && board[location - 1] != 'O');
}

void placeMarkOnBoard(char board[], char playerMark, int location) {
    board[location - 1] = playerMark;
}

int getPlayerInput(string playerName) {
    int location;
    cout << playerName << "'s turn. Enter position (1-9): ";
    cin >> location;
    return location;
}

bool hasThreeInRow(char board[], char playerMark) {
    return ((board[0] == playerMark && board[1] == playerMark && board[2] == playerMark) || // Row 1
        (board[3] == playerMark && board[4] == playerMark && board[5] == playerMark) || // Row 2
        (board[6] == playerMark && board[7] == playerMark && board[8] == playerMark) || // Row 3
        (board[0] == playerMark && board[3] == playerMark && board[6] == playerMark) || // Column 1
        (board[1] == playerMark && board[4] == playerMark && board[7] == playerMark) || // Column 2
        (board[2] == playerMark && board[5] == playerMark && board[8] == playerMark) || // Column 3
        (board[0] == playerMark && board[4] == playerMark && board[8] == playerMark) || // Diagonal
        (board[2] == playerMark && board[4] == playerMark && board[6] == playerMark));   // Diagonal
}

void displayGameStats(int ties, int player1Score, int player2Score) {
    cout << "Game Stats:" << endl;
    cout << "Ties: " << ties << endl;
    cout << "Player 1 Wins (X): " << player1Score << endl;
    cout << "Player 2 Wins (O): " << player2Score << endl;
}