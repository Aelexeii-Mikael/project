# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
# include <ctype.h>
# include <windows.h>

# define height 20
# define width 40


int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
int gameover;
int key;
int score;

int x;
int y;
int fruitX;
int fruitY;

void setup() {
	gameover = 0;
	
	x = width / 2;
	y = height / 2;
	
	fruitX = rand() % width;
	fruitY = rand() % height;
	while (fruitX == 0)
		fruitX = rand() % width;
	while (fruitY == 0)
		fruitY = rand() % height;
		
		score = 0;
}

void draw() {
	system("cls");
	
	for (int i = 0 ; i < width + 2 ; i++)
		printf("#");
	printf("\n");
	
	for (int i = 0 ; i < height ; i++) {
		for (int j = 0 ; j <= width ; j++) {
			if (j == 0 || j == width)
			printf("#");
			
			if (i == y && j == x)
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
		
		for (int i = 0 ; i < width + 2 ; i++)
			printf("-");
		printf("\n");
		
		printf("score = %d", score);
		printf("\n");
		printf("Press W, A, S, D for movement. \n");
		printf("Press X to quit.");
	}
		
		void input() { 
			if (kbhit()) {
				switch (tolower(getch())) {
					case 'w' :
						if (key != 4)
						key = 3;
						break;
					case 'a' :
						if (key != 2)
						key = 1;
						break;
					case 's' :
						if (key != 3)
						key = 4;
						break;
					case 'd' :
						if (key != 1)
						key = 2;
						break;
					case 'x' :
						gameover = 1;
						break;
				}
			}
		}
	
	void logic () {
		int prevX = snakeTailX[0];
		int prevY = snakeTailY[0];
		int prev2X, prev2Y;
		
		snakeTailX[0] = x;
		snakeTailY[0] = y;
		
		for (int i = 1 ; i < snakeTailLen ; i++) {
			prev2X = snakeTailX[i];
			prev2Y = snakeTailY[i];
			snakeTailX[i] = prevX;
			snakeTailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
		
		switch(key) {
			case 1:
				x--;
				break;
			case 2:
				x++;
				break;
			case 3:
				y--;
				break;
			case 4:
				y++;
				break;
			default:
				break;
		}
		
		// untuk gameover
		if (x < 0 || x >= width || y < 0 || y >= height)
		gameover = 1;
		
		for (int i = 0 ; i < snakeTailLen ; i++) {
			if (snakeTailX[i] == x && snakeTailY[i] == y)
			gameover = 1;
		}
		
		if (x == fruitX && y == fruitY) {
			fruitX = rand() % width;
			fruitY = rand () % height;
			while (fruitX == 0)
				fruitX = rand() % width;
				
			while (fruitY == 0)
				fruitY = rand() % height;
			score += 10;
			snakeTailLen++;
		}
	}
	
	void main() {
		setup ();
		key = 0;
		snakeTailLen = 0;
		
		while (!gameover) {
			draw();
			input();
			logic();
			Sleep(33);
			
		}
	}
	


