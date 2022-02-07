#include <stdio.h>
#include "Tictactoe.h"

int main()
{
	BOARD board;
next_game:
	init(&board);
	int input = -1;

	int game_status = -1; 

	while((game_status = resCheck(&board)) == INPLAY)
	{
		printBoard(&board);

		int input;

		printf("Your play: ");
		scanf("%d",&input);
		printf("\n");

		makeMove(&board,input-1);
	}

	winCheck(&board,game_status);
again:
	printf("\nDo you wanna play next game(1), reset the score(2), exit the game(0):\n");
	scanf("%d",&input);

	switch(input)
	{
		case 0: goto exit;
		break;
		case 1: goto next_game;
		break;
		case 2:
		scoreReset();
		goto next_game;
		break;
		default: 
		printf("\nWrong command! Please try again\n");
		goto again;
	}


exit:
	return 0;
}


void init(BOARD* board)
{
	for(int i = 0; i < MAXBOARDSPACE; i++)
	{
		*((board -> board) + i) = NONE;
	}
	board -> turn = TURN_X;
	board -> turn_count = 0;
}

void printBoard(BOARD* board)
{

	printf("\nTurn number: %d\n",board -> turn_count);

	if(board -> turn == TURN_X) printf("\nTurn:X\n");
	else printf("\nTurn:O\n");



	printf("\n");

	for(int i = 0; i < MAXBOARDSPACE; i++)
	{
		if(*((board -> board) + i) == NONE)
		{
			if(i == 2 || i == 5 )
			{
				printf("-\n");
			}
			else
			{
				printf("- ");
			}
		}
		else if(*((board -> board) + i) == X)
		{
			if(i == 2 || i == 5 )
			{
				printf("X\n");
			}
			else
			{
				printf("X ");
			}
		}
		else
		{
			if(i == 2 || i == 5 )
			{
				printf("O\n");
			}
			else
			{
				printf("O ");
			}
		}
	}
	printf("\n");
}

void makeMove(BOARD* board,int index)
{
	if(*((board -> board) + index) == NONE)
	{
		if(board -> turn == TURN_X)
		{
			*((board -> board) + index) = X;
		}
		else
		{
			*((board -> board) + index) = O;
		}
		
		if(board -> turn == TURN_X)	board -> turn = TURN_O;
		else if(board -> turn == TURN_O) board -> turn = TURN_X;

		(board -> turn_count)++;
	}
	else
	{
		printf("\nThat space is taken!\n");
	}
}

int resCheck(BOARD* board)
{
    //horizontale 
	if(*((board -> board) + 0) == X && *((board -> board) + 1) == X && *((board -> board) + 2) == X)
	{
		return X_WIN;
	}
	else if(*((board -> board) + 0) == O && *((board -> board) + 1) == O && *((board -> board) + 2) == O)
	{
		return O_WIN;
	}
	else if(*((board -> board) + 3) == X && *((board -> board) + 4) == X && *((board -> board) + 5) == X)
	{
		return X_WIN;
	}
	else if(*((board -> board) + 3) == O && *((board -> board) + 4) == O && *((board -> board) + 5) == O)
	{
		return O_WIN;
	}
	else if(*((board -> board) + 6) == X && *((board -> board) + 7) == X && *((board -> board) + 8) == X)
	{
		return X_WIN;
	}
	else if(*((board -> board) + 6) == O && *((board -> board) + 7) == O && *((board -> board) + 8) == O)
	{
		return O_WIN;
	}
	// vertikale
	else if(*((board -> board) + 0) == X && *((board -> board) + 3) == X && *((board -> board) + 6) == X)
	{
		return X_WIN;
	}
	else if(*((board -> board) + 0) == O && *((board -> board) + 3) == O && *((board -> board) + 6) == O)
	{
		return O_WIN;
	}
	else if(*((board -> board) + 1) == X && *((board -> board) + 4) == X && *((board -> board) + 7) == X)
	{
		return X_WIN;
	}
	else if(*((board -> board) + 1) == O && *((board -> board) + 4) == O && *((board -> board) + 7) == O)
	{
		return O_WIN;
	}
	else if(*((board -> board) + 2) == X && *((board -> board) + 5) == X && *((board -> board) + 8) == X)
	{
		return X_WIN;
	}
	else if(*((board -> board) + 2) == O && *((board -> board) + 5) == O && *((board -> board) + 8) == O)
	{
		return O_WIN;
	}
	//dijagonale
	else if(*((board -> board) + 0) == X && *((board -> board) + 4) == X && *((board -> board) + 8) == X)
	{
		return X_WIN;
	}
	else if(*((board -> board) + 0) == O && *((board -> board) + 4) == O && *((board -> board) + 8) == O)
	{
		return O_WIN;
	}
	else if(*((board -> board) + 2) == X && *((board -> board) + 4) == X && *((board -> board) + 6) == X)
	{
		return X_WIN;
	}
	else if(*((board -> board) + 2) == O && *((board -> board) + 4) == O && *((board -> board) + 6) == O)
	{
		return O_WIN;
	}
	else
	{
		for(int i = 0; i < MAXBOARDSPACE ; i++)
		{
			if(*((board -> board) + i) == NONE) return INPLAY;
		}

		return DRAW;
	}


}

void winCheck(BOARD* board,int game_status)
{
	printBoard(board);

	if(game_status == X_WIN)
	{
		printf("\nThe winner is X!!!\n");
		x_score++;
	}
	else if(game_status == O_WIN)
	{
		printf("\nThe winner is O!!!\n");
		o_score++;
	}
	else
	{
		printf("\nGame is a draw :( \n");
	}

	printf("\nScore - X: %d | O: %d\n",x_score,o_score);
}

void scoreReset()
{
	x_score = 0;
    o_score = 0;
}