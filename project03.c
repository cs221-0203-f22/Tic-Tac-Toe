#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int board [9];
char player = 'X';
char opponent = 'O';

void printBoard(board b) {

        printf(" %c | %c | %c\n", b[0], b[1], b[2]);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", b[3], b[4], b[5]);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", b[6], b[7], b[8]);

}

int checkWin(board b, char player) {//player paramater to determine if the opponents win is checked vs player

	int win = 1;
	
	if(b[0] == player && b[1] == player && b[2] == player) {//row 1 horz check
		win = 0;
	}
	if(b[3] == player && b[4] == player && b[5] == player) {//row 2 horz check
		win = 0;
	}
	if(b[6] == player && b[7] == player && b[8] == player) {//row 3 horz check
		win = 0;
	}

	if(b[0] == player && b[3] == player && b[6] == player) {//row 1 vert check
		win = 0;
	}
	if(b[1] == player && b[4] == player && b[7] == player) {//row 2 vert check
		win = 0;
	}
	if(b[2] == player && b[5] == player && b[8] == player) {//row 3 vert check
		win = 0;
	}

	if(b[0] == player && b[4] == player && b[8] == player) {//diag check
		win = 0;
	}
	if(b[2] == player && b[4] == player && b[6] == player) {//anti diagonal check
		win = 0;
	}
	
	return win;
}

int fullBoard(board b) {
    
    int isFull = 0;

    for(int i = 0; i < 9; i++) {
        if(b[i] == '_') { //if any blank space is found, break loop
            isFull = 1;
            break;
        }
    }

    return isFull;

}

int minimax(board b, char p, int depth) {

    int score;
    if(checkWin(b, 'X') == 0) { //X wins case
        score = 10 - depth;
        return score;
    }
    else if(checkWin(b, 'O') == 0) {//O wins case
        score = -10 + depth;
        return score;
    }
    else if(fullBoard(b) == 0) { //if neither player wins, check if board is full
        score = 0;
        return score;
    }

    if (p == 'X') { //maximizer
        score = -100;
        for(int i = 0; i < 9; i++) {
            if(b[i] == '_') { //iterate through the board values and check for empty space
                b[i] = p;
                int tmp = minimax(b, 'O', depth + 1); //each time minimax is called, increase depth
                if(tmp > score) { //find the highest value
                    score = tmp;
                }

                b[i] = '_';
            }
        }
    }

    else { //minimizer
        score = 100;
        for(int i = 0; i < 9; i++) { 
            if(b[i] == '_') {
                b[i] = p;
                int tmp = minimax(b, 'X', depth + 1);
                if(tmp < score) { //find lowest value
                    score = tmp; //store lowest value
                }

                b[i] = '_';
            }
        }
    }
    return score;
}

int findBestMove(board b, char p) {
  
    int score = 100;
    int rPos = -1; //return position variable
    for(int i = 0; i < 9; i++) {
        if(b[i] == '_') { //check if position is empty
            b[i] = p;
            int tmp = minimax(b,'X', 0);
            b[i] = '_'; //clear the position

            if(tmp < score) { //find lowest score, then return position of lowest score
                score = tmp;
                rPos = i;
            }
        }
    }

    return rPos;
}

int isLegal(board b, int pMove) {
	if(pMove == -1) {
		return 1;
	}
	else if(pMove > 8 || pMove < 0) {
		return 1;
	}
	else if(b[pMove] != '_') { //if not empty space
		return 1;
	}
	return 0;
}

int runGame(board b) {

	while(fullBoard(b) == 1) { //while fullBoard function returns 1 (not full), keep running game

		int pMove = -1;
		
		printBoard(b); //display board each time runGame loops
		
		if(checkWin(b, 'X') == 0) {
			printf("X Wins\n");
			return 0;
		}
		else if(checkWin(b, 'O') == 0) {
			printf("O Wins\n");
			return 0;
		}

		while(isLegal(b, pMove) != 0) { //for user input, keep looping until a valid input is put
			printf("Your Move (X): ");
			scanf("%d", &pMove);
		}

		b[pMove] = 'X'; //add X to board;

		pMove = findBestMove(b, 'O'); //get the best O value for this board
		
		b[pMove] = 'O'; //add O value to board;
		
	}

	printf("Draw");
	return 0;
	
}

int main(int argc, char *argv[]) {

    board b;

	if(argc > 10) {
		printf("invalid input: too many values");
	}  
	  
	else if(argc > 2) { //case to give the best possible opponent move

	for(int i = 1; i < argc; i++) {
		b[i - 1] = *argv[i];
	}
	
    printBoard(b);
    int bestPos = findBestMove(b,opponent);

    switch(bestPos) { //switch cases to convert the 1D array values to grid positions, matching test case output
        case 0:
			printf("O: 0 0\n");
			break;
		case 1:
			printf("O: 0 1\n");
			break;
		case 2:
			printf("O: 0 2\n");
			break;
		case 3:
			printf("O: 1 0\n");
			break;
		case 4:
			printf("O: 1 1\n");
			break;
		case 5:
			printf("O: 1 2\n");
			break;
		case 6:
			printf("O: 2 0\n");
			break;
		case 7:
			printf("O: 2 1\n");
			break;
		case 8:
			printf("O: 2 2\n");
			break;
    }
    }

    else if(argc == 1) { //case to play full game

    	for (int i = 0; i < 9; i++) { //feed values into storeVals array
			b[i] = '_';
		}

		runGame(b);
    	
    }
    
    return 0;

}
