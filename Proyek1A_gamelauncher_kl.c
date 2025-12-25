#include <stdio.h>
#include <stdlib.h>

void mainMenu();
void snake();
void ticTacToe();
void hangman();
void clearScreen();
void pauseScreen();


int main() {
    mainMenu();
    return 0;
}


void mainMenu() {
    int choice;

    do {
        clearScreen();

        printf("===== GAME LAUNCHER =====\n");
        printf("1. Snake\n");
        printf("2. Tic Tac Toe\n");
        printf("3. Hangman\n");
        printf("4. Exit\n");
        printf("=========================\n");
        printf("Pilih game: ");

        if (scanf("%d", &choice) != 1) {
            // Clear invalid input
            while (getchar() != '\n');
            choice = 0;
        }

        switch (choice) {
            case 1:
                snake();
                break;
            case 2:
                ticTacToe();
                break;
            case 3:
                hangman();
                break;
            case 4:
                printf("Terima kasih sudah bermain!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                pauseScreen();
        }
    } while (choice != 4);
}


void snake() {
    clearScreen();
    printf("Upcoming!\n");
    pauseScreen();
}

void ticTacToe() {
    clearScreen();
    printf("upcoming!\n");
    pauseScreen();
}

void hangman() {
    clearScreen();
    printf("Upcoming!\n");
    pauseScreen();
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void pauseScreen() {
    printf("\nTekan ENTER untuk kembali ke menu...");
    while (getchar() != '\n');
    getchar();
}

