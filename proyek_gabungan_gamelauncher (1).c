#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <windows.h>

/* NOTE: 
untuk windows harus pakai: #ifdef _WIN32 dan #include <windows.h>

tp klo mau bisa dipake di linux bakal butuh #unistd.h 

ini biar game bisa dijalanin di linux atau mac sama window, kira2 bakal gini bentuknya:
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
*/


// kata dalam hangman
char *words[10] = {
    "programming",
    "komputer",
    "mobil",
    "array",
    "pointer",
    "bahasa",
    "python",
    "variable",
    "algoritma",
    "bola"
};

// pendefinisian hal hal yang dipakai dalam snake
#define HEIGHT 20
#define WIDTH 40

int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
int snakeGameover;
int snakeKey;
int snakeScore;
int snakeX, snakeY;
int fruitX, fruitY;

// pendefinisian bagian tic tac toe
int tttWinner = 0, tttCount = 0;
int tttPos[9];


void mainMenu();
void snakeGame();
void ticTacToeGame();
void hangmanGame();
void clearScreen();
void pauseScreen();

void displayHangman(int tries);
void snakeSetup();
void snakeDraw();
void snakeInput();
void snakeLogic();
void tttWin(int player, int winner, int pos[]);

// fungsi main menu
int main() {
    srand(time(NULL)); 
    mainMenu();
    return 0;
}

// main menu
void mainMenu() {
    int choice;

    do {
        clearScreen();

        printf("===== GAME LAUNCHER =====\n");
        printf("1. Snake Game\n");
        printf("2. Tic Tac Toe\n");
        printf("3. Hangman\n");
        printf("4. Exit\n");
        printf("=========================\n");
        printf("Choose game: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
        }

        switch (choice) {
            case 1:
                snakeGame();
                break;
            case 2:
                ticTacToeGame();
                break;
            case 3:
                hangmanGame();
                break;
            case 4:
                printf("Thank you for playing!\n");
                break;
            default:
                printf("Invalid choice!\n");
                pauseScreen();
        }
    } while (choice != 4);
}

// NOTE: INI ADALAH GAME PLACEHOLDER

// game uler
void snakeGame() {
    snakeSetup();
    snakeKey = 0;
    snakeTailLen = 0;
    
    clearScreen();
    printf("Snake Game Starting...\n");
    printf("Use W, A, S, D to move. Press X to quit.\n");
    printf("Press any key to continue...");
    getch();
    
    while (!snakeGameover) {
        snakeDraw();
        snakeInput();
        snakeLogic();
    }
    
    clearScreen();
    printf("=== GAME OVER ===\n");
    printf("Final Score: %d\n", snakeScore);
    printf("\n");
    pauseScreen();
}

void snakeSetup() {
    snakeGameover = 0;
    
    snakeX = WIDTH / 2;
    snakeY = HEIGHT / 2;
    
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    while (fruitX == 0)
        fruitX = rand() % WIDTH;
    while (fruitY == 0)
        fruitY = rand() % HEIGHT;
        
    snakeScore = 0;
}

void snakeDraw() {
    clearScreen();
    
    // menggambar map
    for (int i = 0 ; i < WIDTH + 2 ; i++)
        printf("#");
    printf("\n");
    
    
    for (int i = 0 ; i < HEIGHT ; i++) {
        for (int j = 0 ; j <= WIDTH ; j++) {
            if (j == 0 || j == WIDTH)
                printf("#");
            
            if (i == snakeY && j == snakeX)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("*");
            else {
                int prTail = 0;
                for (int k = 0 ; k < snakeTailLen ; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        printf("o");
                        prTail = 1;
                    }
                }
                if (!prTail)
                    printf(" ");
            }
        }
        printf("\n");
    }
    
    
    for (int i = 0 ; i < WIDTH + 2 ; i++)
        printf("#");
    printf("\n");
    
    printf("Score = %d\n", snakeScore);
    printf("Press W, A, S, D for movement.\n");
    printf("Press X to quit to main menu.\n");
}

void snakeInput() {
    if (kbhit()) {
        switch (tolower(getch())) {
            case 'w':
                if (snakeKey != 4)
                    snakeKey = 3;
                break;
            case 'a':
                if (snakeKey != 2)
                    snakeKey = 1;
                break;
            case 's':
                if (snakeKey != 3)
                    snakeKey = 4;
                break;
            case 'd':
                if (snakeKey != 1)
                    snakeKey = 2;
                break;
            case 'x':
                snakeGameover = 1;
                break;
        }
    }
}

void snakeLogic() {
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    
    snakeTailX[0] = snakeX;
    snakeTailY[0] = snakeY;
    
    for (int i = 1 ; i < snakeTailLen ; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    switch(snakeKey) {
        case 1:
            snakeX--;
            break;
        case 2:
            snakeX++;
            break;
        case 3:
            snakeY--;
            break;
        case 4:
            snakeY++;
            break;
    }
    
    // code game over
    if (snakeX < 0 || snakeX >= WIDTH || snakeY < 0 || snakeY >= HEIGHT)
        snakeGameover = 1;
    
    for (int i = 0 ; i < snakeTailLen ; i++) {
        if (snakeTailX[i] == snakeX && snakeTailY[i] == snakeY)
            snakeGameover = 1;
    }
    
    // logika buah
    if (snakeX == fruitX && snakeY == fruitY) {
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        while (fruitX == 0)
            fruitX = rand() % WIDTH;
        while (fruitY == 0)
            fruitY = rand() % HEIGHT;
        snakeScore += 10;
        snakeTailLen++;
    }
}

// game tic tac toe
void ticTacToeGame() {
    int index, sign, player, flag, i, k;
    
    // pendefinisian
    tttWinner = 0;
    tttCount = 0;
    for(i = 0; i < 9 ; i++) {
        tttPos[i] = ' ';
    }
    
    clearScreen();
    printf("=== TIC TAC TOE ===\n");
    printf("Player 1: X | Player 2: O\n\n");
    
    while(tttCount < 9 && tttWinner != 1){
        flag = 0;
        
        // menggambar map bermain
        printf("\n");
        printf(" %c | %c | %c\n", tttPos[0], tttPos[1], tttPos[2]);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", tttPos[3], tttPos[4], tttPos[5]);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", tttPos[6], tttPos[7], tttPos[8]);
        printf("\n");
        
        if(tttCount % 2 == 0){
            sign = 'X';
            player = 1;
        } else {
            sign = 'O';
            player = 2;
        }
        
        printf("Move for Player %d (1-9): ", player);
        scanf("%d", &index);
        
        // ini untuk inputnya
        if(index < 1 || index > 9 ){
            printf("Allowed positions are 1 to 9\n");
            continue;
        }
        if (tttPos[index - 1] == 'X' || tttPos[index - 1] == 'O'){
            printf("Position is occupied!\n");
            continue;
        }
        
        tttPos[index - 1] = sign;
        tttCount++;
        
        // cek menang kalah dari baris
        for(i = 0 ; i < 9 ; i++) {
            if(i % 3 == 0)
                flag = 0;
            if (tttPos[i] == sign)
                flag++;
            if(flag == 3) {
                tttWinner = 1;
                break;
            }
        }
        
        // Cek menang kalah dari kolom
        flag = 0;
        for (i = 0 ; i < 3 ; i++) {
            for(k = i ; k <= i + 6 ; k += 3) {
                if (tttPos[k] == sign)
                    flag++;
            }
            
            if (flag == 3) {
                tttWinner = 1;
                break;
            }
            flag = 0;
        }
        
        // Cek barisan miringnya
        if((tttPos[0] == sign && tttPos[4] == sign && tttPos[8] == sign) || 
           (tttPos[2] == sign && tttPos[4] == sign && tttPos[6] == sign)) {
            tttWinner = 1;
        }
        
        if (tttWinner) {
            clearScreen();
            printf("=== TIC TAC TOE ===\n");
            printf("\n");
            printf(" %c | %c | %c\n", tttPos[0], tttPos[1], tttPos[2]);
            printf("---+---+---\n");
            printf(" %c | %c | %c\n", tttPos[3], tttPos[4], tttPos[5]);
            printf("---+---+---\n");
            printf(" %c | %c | %c\n", tttPos[6], tttPos[7], tttPos[8]);
            printf("\nPlayer %d wins!\n", player);
            pauseScreen();
            return;
        }
    }
    
    // menggambar X dan O 
    clearScreen();
    printf("=== TIC TAC TOE ===\n");
    printf("\n");
    printf(" %c | %c | %c\n", tttPos[0], tttPos[1], tttPos[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", tttPos[3], tttPos[4], tttPos[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", tttPos[6], tttPos[7], tttPos[8]);
    printf("\nGame ended in a draw!\n");
    pauseScreen();
}

// game Hangman
void hangmanGame() {
    char word[50];
    char guessed[50];
    int wordlen, tries = 0, i, correctGuess = 0;
    
    // logika pemilihan kata secara random
    strcpy(word, words[rand() % 10]);
    wordlen = strlen(word);
    
    // pengecekan input dari pengguna benar atau salah
    for(i = 0 ; i < wordlen ; i++) {
        guessed[i] = '_';
    }
    guessed[wordlen] = '\0';
    
    clearScreen();
    printf("=== HANGMAN GAME ===\n\n");
    displayHangman(tries);
    printf("Guess the word: %s\n", guessed);
    
    while(tries < 6) {
        char guess;
        printf("\nEnter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);
        
        int found = 0;
        for (i = 0 ; i < wordlen ; i++) {
            if (word[i] == guess && guessed[i] == '_') {
                guessed[i] = guess;
                found = 1;
                correctGuess++;
            }
        }
        
        clearScreen();
        printf("=== HANGMAN GAME ===\n\n");
        
        if(!found) {
            tries++;
            printf("Incorrect guess! ");
        } else {
            printf("Correct guess! ");
        }
        printf("%d tries left\n\n", 6 - tries);
        
        displayHangman(tries);
        printf("Word: %s\n", guessed);
        
        if (correctGuess == wordlen) {
            printf("\nCongratulations! You guessed the word: %s\n", word);
            pauseScreen();
            return;
        }
    }
    
    // kode kalau kalah
    printf("\nSorry, you ran out of tries. The word was: %s\n", word);
    pauseScreen();
}

void displayHangman(int tries) {
    switch(tries) {
        case 0:
            printf("\n");
            printf("   +------+\n");
            printf("   |      |\n");
            printf("          |\n");
            printf("          |\n");
            printf("          |\n");
            printf("-----------\n");
            break;
        case 1:
            printf("\n");
            printf("   +------+\n");
            printf("   |      |\n");
            printf("   o      |\n");
            printf("          |\n");
            printf("          |\n");
            printf("-----------\n");
            break;
        case 2:
            printf("\n");
            printf("   +------+\n");
            printf("   |      |\n");
            printf("   o      |\n");
            printf("   |      |\n");
            printf("          |\n");
            printf("-----------\n");
            break;
        case 3:
            printf("\n");
            printf("   +------+\n");
            printf("   |      |\n");
            printf("   o      |\n");
            printf("  /|      |\n");
            printf("          |\n");
            printf("-----------\n");
            break;
        case 4:
            printf("\n");
            printf("   +------+\n");
            printf("   |      |\n");
            printf("   o      |\n");
            printf("  /|\\     |\n");
            printf("          |\n");
            printf("-----------\n");
            break;
        case 5:
            printf("\n");
            printf("   +------+\n");
            printf("   |      |\n");
            printf("   o      |\n");
            printf("  /|\\     |\n");
            printf("  /       |\n");
            printf("-----------\n");
            break;
        case 6:
            printf("\n");
            printf("   +------+\n");
            printf("   |      |\n");
            printf("   o      |\n");
            printf("  /|\\     |\n");
            printf("  / \\     |\n");
            printf("-----------\n");
            break;
    }
}

/* NOTE: dibawah ini fungsi dalam gamelauncher untuk bisa nungguin pengguna milih game, dan untuk main menu
 fungsi untuk refresh screen kalau main snake dan hangman jadi ga turun2 trs dan ga ngeprint trs
 */
void clearScreen() {
    system("cls");
}

// NOTE: ini pokoknya biar screen main menu nya ngefreeze sampai user milih game yg mau dimaenin
void pauseScreen() {
    printf("\nPress ENTER to return to menu...");
    while (getchar() != '\n'); 
    getchar();
}