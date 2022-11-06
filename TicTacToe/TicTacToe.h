class TicTacToe
{
public:
    int currentMove;
    int board[9];
    bool turn;
    TicTacToe();
    void displayBoard();
    int* getBoard();
    void move(int pos);
    int aiMove();
    static void move(int* board, int pos, bool move);
    static bool isMoveAvailable(int* customBoard, int pos);
    static int isGameDone(int* customBoard);
    static int minimax(int *board, bool maxing);
};