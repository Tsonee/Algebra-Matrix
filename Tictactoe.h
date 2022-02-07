#define MAXBOARDSPACE 9

//Makros//



//definitions//
typedef enum {TURN_O,TURN_X}TURN;

enum {NONE,X,O};

enum {INPLAY, X_WIN, O_WIN, DRAW};

typedef struct{

	int board[MAXBOARDSPACE];

	TURN turn;

	int turn_count;

}BOARD;

//GLOBALS//

int x_score;
int o_score;

//function definitions//

void init(BOARD* board);
void printBoard(BOARD* board);
void makeMove(BOARD* board,int move);
int resCheck(BOARD* board);
void winCheck(BOARD* board,int game_status);
void scoreReset();