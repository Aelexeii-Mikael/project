# include <stdio.h>
# include <conio.h>
# include <stdlib.h>
# include <ctype.h>
# include <time.h>
# include <string.h>

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

void displayHangman(int tries) {
	
	
	switch(tries){
		case 0:
			printf("\n\n");
			printf("   +------+\n");
			printf("   |      |\n");
			printf("          |\n");
			printf("          |\n");
			printf("          |\n");
			printf("-----------\n");
			break;
			
		case 1:
		printf("\n\n");
			printf("   +------+\n");
			printf("   |      |\n");
			printf("   o      |\n");
			printf("          |\n");
			printf("          |\n");
			printf("-----------\n");
			break;
		
		case 2:
		printf("\n\n");
			printf("   +------+\n");
			printf("   |      |\n");
			printf("   o      |\n");
			printf("   |      |\n");
			printf("          |\n");
			printf("-----------\n");
			break; 
			
		case 3:
		printf("\n\n");
			printf("   +------+\n");
			printf("   |      |\n");
			printf("   o      |\n");
			printf("  /|      |\n");
			printf("          |\n");
			printf("-----------\n");
			break; 
		
		case 4:
			printf("\n\n");
			printf("   +------+\n");
			printf("   |      |\n");
			printf("   o      |\n");
			printf("  /|\\     |\n"); // ini di tambah spasi nya supaya pas di run sejajar, ditambah 1 spasi soalnya ada dua backslash
			printf("          |\n");
			printf("-----------\n");
			break;
			
		case 5:
			printf("\n\n");
			printf("   +------+\n");
			printf("   |      |\n");
			printf("   o      |\n");
			printf("  /|\\     |\n"); // ini di tambah spasi nya supaya pas di run sejajar, ditambah 1 spasi soalnya ada dua backslash
			printf("  /       |\n");
			printf("-----------\n");
			break;
			
		case 6:
			printf("\n\n");
			printf("   +------+\n");
			printf("   |      |\n");
			printf("   o      |\n");
			printf("  /|\\     |\n"); // ini di tambah spasi nya supaya pas di run sejajar, ditambah 1 spasi soalnya ada dua backslash
			printf("  / \\     |\n"); // ini di tambah spasi nya supaya pas di run sejajar, ditambah 1 spasi soalnya ada dua backslash
			printf("-----------\n");
			break;
		
	}
}


int main () {
	
	srand(time(NULL));
	char word[50];
	char guessed[50];
	int wordlen, tries = 0, i, correctGuess = 0;
	
	strcpy(word, words[rand()%10]);
	wordlen = strlen(word);
	
	for(i = 0 ; i <wordlen ; i++){
		guessed[i] = '_';
	}
	guessed[wordlen] = '\0';
	
	printf("Welcome to Hangman\n");
	printf("Guess the word: %s\n", guessed);
	
	while(tries < 6) {
		char guess;
		printf("\nEnter a letter: ");
		scanf(" %c", &guess);
		guess = tolower(guess);
		
		int found = 0;
		for (i = 0 ; i < wordlen ; i++) {
			if (word[i] == guess && guessed [i] == '_'){
			guessed[i] = guess;
			found = 1;
			correctGuess++;
		}
	}
	
	if(!found) {
		tries++;
		displayHangman(tries);
		printf("Incorrect guess! %d tries left", 6 - tries);
	}
	else {
		printf("Correct guess!\n");
	}
	printf("word: %s\n", guessed);
	
	if (correctGuess == wordlen) {
		printf("Congratulations! you have guessed the word %s\n", word);
		break;
	}
	
}

	if (tries == 6) { 
		printf("Sorry, you have ran out of tries. The word was %s\n", word);

		displayHangman(tries);	
}

	return 0;

}
