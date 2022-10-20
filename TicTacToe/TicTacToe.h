class TicTacToe{
public:
    TicTacToe();
    int* getBoard();
    void displayBoard();
    void move(int pos);
    bool isGameDone();
    bool isGameDone(int* board);
    bool getTurn();
    int getGameStatus();
    int getP1Reward();
    bool isMoveAvailable(int pos);
    bool isBlockingWin(int pos);

private:
    int board[9];
    bool turn;
    int movesLeft;
    int gameDone;
    int P1Reward;
    int P2Reward;
    bool illegalMove = false;
};
