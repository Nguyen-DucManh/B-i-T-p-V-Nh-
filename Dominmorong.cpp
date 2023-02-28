#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_SIZE = 10;

int main() {
    int m, n, k;
    int board[MAX_SIZE][MAX_SIZE] = {0};
    bool opened[MAX_SIZE][MAX_SIZE] = {false};
    int revealedCount = 0;

    cout << "Enter the size of the board (m, n): ";
    cin >> m >> n;

    cout << "Enter the number of mines: ";
    cin >> k;

    srand(time(0)); // seed the random number generator

    // randomly place mines on the board
    int minesPlaced = 0;
    while (minesPlaced < k) {
        int i = rand() % m;
        int j = rand() % n;
        if (board[i][j] != -1) {
            board[i][j] = -1;
            minesPlaced++;
        }
    }

    // main game loop
    while (revealedCount < m * n - k) {
        // print the board
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (opened[i][j]) {
                    if (board[i][j] == -1) {
                        cout << " * ";
                    } else {
                        cout << " " << board[i][j] << " ";
                    }
                } else {
                    cout << " . ";
                }
            }
            cout << endl;
        }

        // get user input
        int x, y;
        cout << "Enter a cell to open (x, y): ";
        cin >> x >> y;

        // check if the cell has a mine
        if (board[x][y] == -1) {
            cout << "YOU'RE DEAD!" << endl;
            // reveal all the mines
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (board[i][j] == -1) {
                        cout << " * ";
                    } else {
                        cout << " . ";
                    }
                }
                cout << endl;
            }
            break;
        } else {
            // reveal the cell
            opened[x][y] = true;
            revealedCount++;

            // reveal the adjacent cells if they don't have mines
            if (board[x][y] == 0) {
                for (int i = max(0, x-1); i <= min(x+1, m-1); i++) {
                    for (int j = max(0, y-1); j <= min(y+1, n-1); j++) {
                        if (board[i][j] != -1 && !opened[i][j]) {
                            opened[i][j] = true;
                            revealedCount++;
                        }
                    }
                }
            }

            // update the board with the number of adjacent mines
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (board                [i][j] != -1 && opened[i][j]) {
                    int count = 0;
                    for (int a = max(0, i-1); a <= min(i+1, m-1); a++) {
                        for (int b = max(0, j-1); b <= min(j+1, n-1); b++) {
                            if (board[a][b] == -1) {
                                count++;
                            }
                        }
                    }
                    board[i][j] = count;
                }
            }
        }
    }
}

return 0;
}


