#include <iostream>
#include <array>
#include <random>
int winner(std::array<std::array<char, 3>, 3> &board)
{
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;
    for (auto &row : board)
    {
        for (auto &cell : row)
        {
            if (cell != 'X' && cell != 'O')
            {
                return -99;
            }
        }
    }
    return 0;
}
int minimax(std::array<std::array<char, 3>, 3> &board, bool ismaximizing)
{
    int result = winner(board);
    if (result != -99)
    {
        return result;
    }
    if (ismaximizing)
    {
        int bestScore = INT_MIN;
        int score;
        char copy;
        for (auto &row : board)
        {
            for (auto &cell : row)
            {
                if(cell != 'X' && cell != 'O')
                {

                    copy = cell;
                    cell = 'O';
                    score = minimax(board, false);
                    cell = copy;
                    bestScore = std::max(score, bestScore);
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        int score;
        char copy;
        for (auto &row : board)
        {
            for (auto &cell : row)
            {
                if(cell != 'X' && cell != 'O')
                {

                    copy = cell;
                    cell = 'X';
                    score = minimax(board, true);
                    cell = copy;
                    bestScore = std::min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}
char AImove(std::array<std::array<char, 3>, 3> &board)
{
    int bestScore = INT_MIN;
    char bestMove = '\0';
    int score;
    char copy;
    for (auto &row : board)
    {
        for (auto &cell : row)
        {
            if(cell != 'X' && cell != 'O')
            {

                copy = cell;
                cell = 'O';
                score = minimax(board, false);
                cell = copy;
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = copy;
                }
            }
        }
    }
    return bestMove;
}
bool placeMove(std::array<std::array<char, 3>, 3> &board, char move, int player)
{
    for (auto &row : board)
    {
        for (auto &cell : row)
        {
            if (cell == move)
            {
                if (cell != 'X' && cell != 'O')
                {
                    cell = (player == 0) ? 'X' : 'O';
                    return true;
                }
            }
        }
    }
    return false;
}

void showBoard(const std::array<std::array<char, 3>, 3> &board)
{
    int i = 0;
    for (auto row : board)
    {
        int j = 0;
        for (auto cell : row)
        {
            (j < 2) ? std::cout << " " << cell << " " << "|" : std::cout << " " << cell;
            j++;
        }
        (i < 2) ? std::cout << std::endl
                            << "---|---|---" << std::endl
                : std::cout << std::endl;
        i++;
    }
}
void initializeBoard(std::array<std::array<char, 3>, 3> &board)
{
    int a = '1';
    for (auto &row : board)
    {
        for (auto &col : row)
        {
            col = a;
            a++;
        }
    }
}
int Toss()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    return dist(gen);
}
void finalResult(int result, char win)
{
    if (result == 1 && win == 'X')
    {
        std::cout << "WINNER: X" << std::endl;
        std::cout << "LOOSER: O" << std::endl;
    }
    else if (result == 1 && win == 'O')
    {
        std::cout << "WINNER: O" << std::endl;
        std::cout << "LOOSER: X" << std::endl;
    }
    else if (result == 0)
    {
        std::cout << "MATCH DRAW" << std::endl;
    }
}
void play(std::array<std::array<char, 3>, 3> &board, int toss)
{
    int result = -99;

    char move;

    int player = 0;
    int ai = 1;
    bool isValid;
    char win;
    if (toss == 0)
    {
        while (result == -99)
        {
            std::cout << "Your Turn" << std::endl;
            std::cout << "Enter the position : ";
            std::cin >> move;
            std::cout << std::endl;
            while (move < '1' || move > '9')
            {
                std::cout << "Wrong move. Enter again" << std::endl;
                std::cin >> move;
            }
            isValid = placeMove(board, move, player);
            win = 'X';
            while (isValid == false)
            {
                std::cout << "Invalid position. Try again" << std::endl;
                std::cin >> move;
                isValid = placeMove(board, move, player);
            }
            showBoard(board);
            result = winner(board);
            if (result == -99)
            {
                move = AImove(board);
                isValid = placeMove(board, move, ai);
                win = 'O';
                showBoard(board);
                result = winner(board);
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        while (result == -99)
        {

            move = AImove(board);
            isValid = placeMove(board, move, ai);
            win = 'O';
            showBoard(board);
            result = winner(board);

            if (result == -99)
            {
                std::cout << "Your Turn" << std::endl;
                std::cout << "Enter the position : ";
                std::cin >> move;
                std::cout << std::endl;
                while (move < '1' || move > '9')
                {
                    std::cout << "Wrong move. Enter again" << std::endl;
                    std::cin >> move;
                }
                isValid = placeMove(board, move, player);
                win = 'X';
                while (isValid == false)
                {
                    std::cout << "Invalid position. Try again" << std::endl;
                    std::cin >> move;
                    isValid = placeMove(board, move, player);
                }
                showBoard(board);
                result = winner(board);
            }
            else
            {
                break;
            }
        }
    }
    finalResult(result, win);
}
int main()
{
    std::array<std::array<char, 3>, 3> board;
    initializeBoard(board);
    std::cout << "You : X" << std::endl;
    std::cout << "AI : O" << std::endl;
    showBoard(board);
    int toss = Toss();
    play(board, toss);
    return 0;
}