class TicTacToe{
public:
    TicTacToe();
    int* getBoard();
    void displayBoard();
    void move(int pos);
    bool isGameDone();
    bool getTurn();
    int getGameStatus();
    int getP1Reward();

private:
    int board[9];
    bool turn;
    int movesLeft;
    int gameDone;
    int P1Reward;
    int P2Reward;
    bool illegalMove = false;
};
