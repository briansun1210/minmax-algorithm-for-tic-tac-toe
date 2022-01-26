using namespace std;
#include <iostream>

// Returns the optimal value a maximizer can obtain. 
// depth is current depth in game tree. 
// nodeIndex is index of current node in scores[]. 
// isMax is true if current move is 
// of maximizer, else false 
// scores[] stores leaves of Game tree. 

/*
int minimax(int depth, int nodeIndex, bool isMax, int scores[], int h);
int log2(int n); // A utility function to find Log n in base 2 

int main() {
    // The number of elements in scores must be 
    // a power of 2. 
    int scores[] = { 3, 5, 2, 9, 12, 5, 23, 23 };
    int n = sizeof(scores) / sizeof(scores[0]);
    int h = log2(n);                              // the max height of the tree
    int res = minimax(0, 0, true, scores, h);
    cout << "The optimal value is : " << res << endl;
    return 0;
}

int minimax(int depth, int nodeIndex, bool isMax, int scores[], int h){
    // Terminating condition. i.e 
    // leaf node is reached 
    if (depth == h)
        return scores[nodeIndex];

    //  If current move is maximizer, 
    // find the maximum attainable 
    // value 
    if (isMax)
        return max(minimax(depth + 1, nodeIndex * 2, false, scores, h),
            minimax(depth + 1, nodeIndex * 2 + 1, false, scores, h));

    // Else (If current move is Minimizer), find the minimum 
    // attainable value 
    else
        return min(minimax(depth + 1, nodeIndex * 2, true, scores, h),
            minimax(depth + 1, nodeIndex * 2 + 1, true, scores, h));
}

int log2(int n) {
    return (n == 1) ? 0 : 1 + log2(n / 2);
}
*/

struct Move
{
    int row, col;
};

char player = 'x', opponent = 'o';

// This function returns true if there are moves 
// remaining on the board. It returns false if 
// there are no moves left to play. 
bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

// This is the evaluation function as discussed 
// in the previous article ( http://goo.gl/sJgv68 ) 
int evaluate(char b[3][3])
{
    // Checking for Rows for X or O victory. 
    for (int row = 0; row < 3; row++)
    {
        if (b[row][0] == b[row][1] &&
            b[row][1] == b[row][2])
        {
            if (b[row][0] == player)
                return +10;
            else if (b[row][0] == opponent)
                return -10;
        }
    }

    // Checking for Columns for X or O victory. 
    for (int col = 0; col < 3; col++)
    {
        if (b[0][col] == b[1][col] &&
            b[1][col] == b[2][col])
        {
            if (b[0][col] == player)
                return +10;

            else if (b[0][col] == opponent)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory. 
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
    {
        if (b[0][0] == player)
            return +10;
        else if (b[0][0] == opponent)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
    {
        if (b[0][2] == player)
            return +10;
        else if (b[0][2] == opponent)
            return -10;
    }

    // Else if none of them have won then return 0 
    return 0;
}

// This is the minimax function. It considers all 
// the possible ways the game can go and returns 
// the value of the board 
int minimax(char board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);

    // If Maximizer has won the game return his/her 
    // evaluated score 
    if (score == 10)
        return score;

    // If Minimizer has won the game return his/her 
    // evaluated score 
    if (score == -10)
        return score;

    // If there are no more moves and no winner then 
    // it is a tie 
    if (isMovesLeft(board) == false)
        return 0;

    // If this maximizer's move 
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells 
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty 
                if (board[i][j] == '_')
                {
                    // Make the move 
                    board[i][j] = player;

                    // Call minimax recursively and choose 
                    // the maximum value 
                    best = max(best,
                        minimax(board, depth + 1, !isMax));

                    // Undo the move 
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }

    // If this minimizer's move 
    else
    {
        int best = 1000;

        // Traverse all cells 
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty 
                if (board[i][j] == '_')
                {
                    // Make the move 
                    board[i][j] = opponent;

                    // Call minimax recursively and choose 
                    // the minimum value 
                    best = min(best,
                        minimax(board, depth + 1, !isMax));

                    // Undo the move 
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

Move findBestMove(char board[3][3]) {
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Traverse all cells, evaluate minimax function for 
    // all empty cells. And return the cell with optimal 
    // value. 
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Check if cell is empty 
            if (board[i][j] == ' ')
            {
                // Make the move 
                board[i][j] = player;

                // compute evaluation function for this 
                // move. 
                int moveVal = minimax(board, 0, false);

                // Undo the move 
                board[i][j] = ' ';

                // If the value of the current move is 
                // more than the best value, then update 
                // best/ 
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    printf("The value of the best Move is : %d\n\n",
        bestVal);

    return bestMove;
}

const int SIZE = 3;

void makeBoard(char b[][SIZE]);
void showBorad(char b[][SIZE]);
void updateBoard(int y, int x, int r, char b[][SIZE]);

int main() {
    char board[SIZE][SIZE];
    int col = 0, row = 0, round = 0;
    Move bestMove = findBestMove(board);
    makeBoard(board);
    showBorad(board);


    while (true) {
        if (round % 2 == 0) {
            cout << "enter your col and row: ";
            cin >> col >> row;

            updateBoard(row, col, round, board);
        }
        else {
            bestMove = findBestMove(board);
            updateBoard(bestMove.row, bestMove.col, round, board);
            printf("ROW: %d COL: %d\n\n", bestMove.row,
                bestMove.col);
        }
        round++;
        showBorad(board);


    }



    printf("The Optimal Move is :\n");
    printf("ROW: %d COL: %d\n\n", bestMove.row,
        bestMove.col);

    return 0;
}

void makeBoard(char b[][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            b[j][i] = ' ';
        }
    }
}

void showBorad(char b[][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            cout << b[j][i];
            if (i < 2)
                cout << " | ";
        }
        cout << endl;
    }
}

void updateBoard(int y, int x, int r, char b[][SIZE]) {
    if (r % 2 == 0)
        b[y-1][x-1] = player;
    else
        b[y][x] = opponent;
}