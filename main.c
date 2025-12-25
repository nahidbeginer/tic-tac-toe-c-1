#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global board
char board[3][3];

// Function declarations
void initializeBoard();
void drawBoard();
void playerMove(char player);
int checkWin(char player);
int checkDraw();
void saveResult(char result[]);

int main() {
    char currentPlayer = 'X';
    int gameOver = 0;

    initializeBoard();

    while (!gameOver) {
        drawBoard();
        printf("\nPlayer %c turn\n", currentPlayer);

        playerMove(currentPlayer);

        if (checkWin(currentPlayer)) {
            drawBoard();
            printf("\n🎉 Player %c wins!\n", currentPlayer);

            if (currentPlayer == 'X')
                saveResult("Player X Wins");
            else
                saveResult("Player O Wins");

            gameOver = 1;
        }
        else if (checkDraw()) {
            drawBoard();
            printf("\n🤝 Game Draw!\n");
            saveResult("Game Draw");
            gameOver = 1;
        }
        else {
            // Switch player
            if (currentPlayer == 'X')
                currentPlayer = 'O';
            else
                currentPlayer = 'X';
        }
    }

    return 0;
}

// Initialize board with numbers
void initializeBoard() {
    char num = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = num++;
        }
    }
}

// Draw the board
void drawBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" ");
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2)
                printf("|");
        }
        printf("\n");
        if (i < 2)
            printf(" ---+---+---\n");
    }
}

// Player move
void playerMove(char player) {
    int choice;
    int row, col;

    while (1) {
        printf("Enter your choice (1-9): ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 9) {
            printf("❌ Invalid input! Try again.\n");
            continue;
        }

        row = (choice - 1) / 3;
        col = (choice - 1) % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("❌ Position already taken! Try again.\n");
        } else {
            board[row][col] = player;
            break;
        }
    }
}

// Check win condition
int checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        // Rows and columns
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return 1;
    }

    // Diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return 1;

    return 0;
}

// Check draw
int checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
        }
    }
    return 1;
}

// Save result in file
void saveResult(char result[]) {
    FILE *fp;
    time_t t;
    time(&t);

    fp = fopen("result.txt", "a");

    if (fp == NULL) {
        printf("❌ File error!\n");
        return;
    }

    fprintf(fp, "Result: %s\n", result);
    fprintf(fp, "Time: %s\n", ctime(&t));
    fprintf(fp, "------------------------\n");

    fclose(fp);
}

