#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printBoard(char **storeVals) {

	printf(" %c | %c | %c\n", *storeVals[0], *storeVals[1], *storeVals[2]);
	printf("---+---+---\n");
	printf(" %c | %c | %c\n", *storeVals[3], *storeVals[4], *storeVals[5]);
	printf("---+---+---\n");
	printf(" %c | %c | %c\n", *storeVals[6], *storeVals[7], *storeVals[8]);
	
}

int checkWin(char **storeVals, char *player) {//player paramater to determine if the opponents win is checked vs player

	int win = 1;
	
	if(strcmp(storeVals[0], player) == 0 && strcmp(storeVals[1], player) == 0  && strcmp(storeVals[2], player)==0) {//row 1 horz check
		win = 0;
	}
	if(strcmp(storeVals[3],  player) == 0 && strcmp(storeVals[4],  player) == 0  && strcmp(storeVals[5], player)==0) {//row 2  horz check
		win = 0;
	}
	if(strcmp(storeVals[6],  player) == 0 && strcmp(storeVals[7],  player) == 0  && strcmp(storeVals[8], player)==0) {//row 3  horz check
		win = 0;
	}

	if(strcmp(storeVals[0], player) == 0 && strcmp(storeVals[3], player) == 0  && strcmp(storeVals[6], player)==0) {//row 1 vert check
		win = 0;
	}
	if(strcmp(storeVals[1],  player) == 0 && strcmp(storeVals[4],  player) == 0  && strcmp(storeVals[7], player)==0) {//row 2  vert check
		win = 0;
	}
	if(strcmp(storeVals[2],  player) == 0 && strcmp(storeVals[5],  player) == 0  && strcmp(storeVals[8], player)==0) {//row 3  vert check
		win = 0;
	}

	if(strcmp(storeVals[0], player) == 0 && strcmp(storeVals[4], player) == 0  && strcmp(storeVals[8], player)==0) {//diagonal checks
		win = 0;
	}
	if(strcmp(storeVals[2],  player) == 0 && strcmp(storeVals[4],  player) == 0  && strcmp(storeVals[6], player)==0) {
		win = 0;
	}
	
	return win;
}

int isLegal(int playerMove, char **storeVals) {

	int legality = 0; //variable to store whether or not the move is valid

	if(playerMove == -1) {
		return 1;
	}

	else if(playerMove > 8 || playerMove < 0) { //exception handling
		return 1;
	}
	
	else if(strcmp(storeVals[playerMove], "_") == 0 && strcmp(storeVals[playerMove], "O") != 0) { //check that space is blank
		legality = 0;
	}
	else {
		legality = 1;
	}
	return legality;
}

int minimax(char **storeVals, char *p, int depth) {

	int score=0;
	char *p1 = "X"; //player 1
	char *opponent = "O"; // opponent

	if(checkWin(storeVals, p1) == 0 && checkWin(storeVals, opponent) == 0) { //draw case
		score = 0;
		return score;
	}
	if(checkWin(storeVals, p1) == 0) {//check if X wins
		score = 10 - depth;
		return score;
	}
	if(checkWin(storeVals, opponent) == 0) {//check if O wins
		score = -10 + depth;
		return score;
	}

	if(strcmp(p, "X")) {

		score = -100; //set a value lower than lowest possible  value

		for(int i = 0; i < 9; i++) { //iterate through all Free positions to place X

			if(strcmp(storeVals[i],"_")) {

			storeVals[i] = p;
			
			int tmp = minimax(storeVals, opponent, depth + 1);

			if(tmp > score) {
				score = tmp;
			}
			
			storeVals[i] = "_";
			
			}
		}
	}

	else {
	
		score = 100;
		
		for(int i = 0; i < 9; i++) {

			if(strcmp(storeVals[i],"_")) {

				storeVals[i] = p;
				int tmp = minimax(storeVals, p, depth + 1); //find lowest score

				if(tmp < score) {

					score = tmp;
				}
				
				storeVals[i] = "_";
		}
	}

	}
	return score;

	
}

void findBestMove(char **storeVals, char *player, int *position) {

	char *opponent = "O";
	
	int score = 100;

	for(int i = 0; i < 9; i++) { //iterate through all Free positions to place X

		if(strcmp(storeVals[i],"_")) {

		storeVals[i] = opponent;
		int tmp = minimax(storeVals,player, 0);
		storeVals[i] = "_";

		if(tmp < score) {
			score = tmp;
			*position = i;
		}
		
	}
}

	switch(*position) { //use switch cases to print the correct grid positions of best possible value
		case 0:
			printf("O: 0 0");
			break;
		case 1:
			printf("O: 0 1");
			break;
		case 2:
			printf("O: 0 2");
			break;
		case 3:
			printf("O: 1 0");
			break;
		case 4:
			printf("O: 1 1");
			break;
		case 5:
			printf("O: 1 2");
			break;
		case 6:
			printf("O: 2 0");
			break;
		case 7:
			printf("O: 2 1");
			break;
		case 8:
			printf("O: 2 2");
			break;
		
	}
}

int runGame(char **storeVals) {

	char *player = "X";
	char *opponent = "O";
	
	int playerWin = checkWin(storeVals, player); //check if the player or opponent has a win
	int opponentWin = checkWin(storeVals, opponent);

	if(playerWin == 0 && opponentWin == 0) {
		printf("Draw\n");
		return 1;
	}

	if(playerWin == 0) {
		printf("X Wins\n");
		return 1;
	}

	if(opponentWin == 0) {
		printf("O Wins\n");
		return 1;
	}
	
	int playerMove = -1;
	int opponentMove = -1;
	
	while(isLegal(playerMove, storeVals) != 0) { //loop until the user inputs a valid position
		printf("Your Move (X): ");
		scanf("%d", &playerMove);
		}
	
	storeVals[playerMove] = "X";
	printBoard(storeVals);
	
	//opponent finds best movein minimax, store it in storeVals, then printboard

	if(strcmp(storeVals[0],"_") != 0  && strcmp(storeVals[1],"_") != 0  && strcmp(storeVals[2],"_") != 0  && strcmp(storeVals[3],"_") != 0  && strcmp(storeVals[4],"_") != 0  && strcmp(storeVals[5],"_") != 0  && strcmp(storeVals[6],"_") != 0  && strcmp(storeVals[7],"_") != 0  && strcmp(storeVals[8],"_") != 0) {
		return 1;		
}
	while(isLegal(opponentMove, storeVals) != 0) { //loop until the user inputs a valid position
		printf("Your Move (X): ");
		scanf("%d", &opponentMove);
		}

	 storeVals[opponentMove] = "O";
	 printBoard(storeVals);

	if(strcmp(storeVals[0],"_") != 0  && strcmp(storeVals[1],"_") != 0  && strcmp(storeVals[2],"_") != 0  && strcmp(storeVals[3],"_") != 0  && strcmp(storeVals[4],"_") != 0  && strcmp(storeVals[5],"_") != 0  && strcmp(storeVals[6],"_") != 0  && strcmp(storeVals[7],"_") != 0  && strcmp(storeVals[8],"_") != 0) {
		return 1;		
}
	return 0;
	
}

int main(int argc, char *argv[]) {

	char *player = "X";
	int position = -1;
	
	 if (argc > 10) { //verify input

		printf("invalid input: too many values");
		
	 }  else if (argc > 2) { //find the next best value

		char *storeVals[9]; //array to store board values

		for (int i = 1; i < argc; i++) { //feed values into storeVals array

			storeVals[i - 1] = argv[i];
		}

		printBoard(storeVals);
		findBestMove(storeVals, "X", &position);
	
	 } else if (argc == 1) { //play against minimax algorithm
		
		int isRunning = 0;
		char *storeVals[9]; //array to store board values
		
		for (int i = 0; i < 9; i++) { //feed values into storeVals array

			storeVals[i] = "_";
		}
		printBoard(storeVals); //display initial board

		while(isRunning == 0) {

			if(runGame(storeVals) == 1) { //launch the game and run until complete

				printf("Game end\n");
				isRunning = 1;
				return 1;
			}
		}


	}
	return 0;
}





