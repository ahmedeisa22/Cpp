#include <iostream>
#include <cstdlib>
#include <string>
#include "MyLib.h"
#include <cmath>
using namespace std;

enum enTheWinner { Player_X = 1, Player_O };
enum enGameChoice { X = 1, O };

short ReadTheGameDimension()
{
    cout << "Please Enter The Game Dimension [3:9]: ";
    return MyLib::ReadNumber(3, 9);
}

short AddItemIn2DArr(char** XOBoard, short R, short C, short Item)
{
    return XOBoard[R - 1][C - 1] = Item;
}

void Create2DDynamicArr(char**& XOBoard, short BoardSize)
{
    for (short i = 0; i < BoardSize; i++)
        XOBoard[i] = new char[BoardSize];
}
void Delete2DDynamicArr(char** XOBoard, short BoardSize)
{
    for (short i = 0; i < BoardSize; i++)
    {
        delete[] XOBoard[i];
    }
    delete[] XOBoard;
}

bool FindItemInSpecificIndexIn2DArr(char** PtrArr, short R, short C, char Item)
{
    return PtrArr[R - 1][C - 1] == enGameChoice::X ? true : PtrArr[R - 1][C - 1] == enGameChoice::O ? true : false;
}

void PrintXO2DArr(char** XOBoard, short Rows, short Cols)
{
    cout << "\n___________________________________________________\n" << endl;
    for (short x = 0; x < Rows; x++)
    {
        for (short y = 0; y < Cols; y++)
        {
            if (XOBoard[x][y] != enGameChoice::X && XOBoard[x][y] != enGameChoice::O)
            {
                cout << "    . ";
            }
            else
            {
                if (XOBoard[x][y] == enGameChoice::X)
                {
                    cout << "    " << 'X' << " ";
                }
                else
                    cout << "    " << 'O' << " ";
            }

        }
        cout << endl << endl;
    }
    cout << "\n___________________________________________________" << endl;
}

short AreTheRowValueEqual(char** XOBoard, short rows, short cols, short RowNumber)
{
    enGameChoice value = (enGameChoice)XOBoard[RowNumber - 1][0];
    for (short i = 1; i < rows; i++)
    {
        if (value != XOBoard[RowNumber - 1][i])
            return false;
    }
    return value;
}

short AreTheColValueEqual(char** XOBoard, short rows, short cols, short ColNumber)
{
    enGameChoice value = (enGameChoice)XOBoard[0][ColNumber - 1];
    for (short i = 1; i < rows; i++)
    {
        if (value != XOBoard[i][ColNumber - 1])
            return false;
    }
    return value;
}

short AreTheDiagonalValueEqual(char** XOBoard, short GameDimension, short rows, short cols, bool InverseDiagonal = false)
{
    if (InverseDiagonal == true)
    {
        short x = 1, y = 0;
        enGameChoice value = (enGameChoice)XOBoard[rows - 1][cols - 1];
        for (short i = 0; i < GameDimension; i++)
        {
            for (short j = 0; j < GameDimension; j++)
            {
                if ((i == y && j == GameDimension - x) && value != XOBoard[i][j])
                    return false;
            }
            x++;
            y++;
        }
        return value;
    }
    else
    {
        char value = XOBoard[0][0];
        for (short i = 1; i < GameDimension; i++)
        {
            for (short j = 1; j < GameDimension; j++)
            {
                if (i == j && value != XOBoard[i][j])
                    return false;
            }
        }
        return value;
    }
}

void CheckAndSavePlayerChoice(char**& XOBoard, short GameDimension, short RowPlayerChoice, short ColPlayerChoice, enGameChoice XorO)
{
    while (FindItemInSpecificIndexIn2DArr(XOBoard, RowPlayerChoice, ColPlayerChoice, XorO))
    {
        cout << "\nInvalid input. Try again. ";
        cout << "\nEnter Empty Location (r, c): ";
        cin >> RowPlayerChoice >> ColPlayerChoice;
    }

    AddItemIn2DArr(XOBoard, RowPlayerChoice, ColPlayerChoice, XorO);
    PrintXO2DArr(XOBoard, GameDimension, GameDimension);
}

enTheWinner IsThereAWinner(char** XOBoard, short GameDimension, short RowPlayerChoice, short ColPlayerChoice)
{
    short TheRowWinner = AreTheRowValueEqual(XOBoard, GameDimension, GameDimension, RowPlayerChoice);
    short TheColWinner = AreTheColValueEqual(XOBoard, GameDimension, GameDimension, ColPlayerChoice);
    short TheDiagonalWinner = AreTheDiagonalValueEqual(XOBoard, GameDimension, RowPlayerChoice, ColPlayerChoice);
    short TheInverseDiagonalWinner = AreTheDiagonalValueEqual(XOBoard, GameDimension, RowPlayerChoice, ColPlayerChoice, true);

    if (TheDiagonalWinner == enTheWinner::Player_X)
        return enTheWinner::Player_X;
    else if (TheDiagonalWinner == enTheWinner::Player_O)
        return enTheWinner::Player_O;
    else if (TheInverseDiagonalWinner == enTheWinner::Player_X)
        return enTheWinner::Player_X;
    else if (TheInverseDiagonalWinner == enTheWinner::Player_O)
        return enTheWinner::Player_O;
    else if (TheColWinner == enTheWinner::Player_X)
        return enTheWinner::Player_X;
    else if (TheColWinner == enTheWinner::Player_O)
        return enTheWinner::Player_O;
    else if (TheRowWinner == enTheWinner::Player_X)
        return enTheWinner::Player_X;
    else if (TheRowWinner == enTheWinner::Player_O)
        return enTheWinner::Player_O;
}

bool IsMatrixFull(char** XOBoard, short BoardDeminsion)
{
    for (short i = 0; i < BoardDeminsion; i++)
    {
        for (short j = 0; j < BoardDeminsion; j++)
        {
            if (XOBoard[i][j] != enGameChoice::X && XOBoard[i][j] != enGameChoice::O)
                return false;
        }
    }
    return true;
}

void PlayGame()
{
    short BoardSize = ReadTheGameDimension();
    char** XOBoard = new char* [BoardSize];

    Create2DDynamicArr(XOBoard, BoardSize);

    short RowPlayerChoice = 0, ColPlayerChoice = 0;
    PrintXO2DArr(XOBoard, BoardSize, BoardSize);

    while (true)
    {
        enTheWinner TheWinner = enTheWinner::Player_O;
        cout << "\nPlayer X Turn. Enter Empty Location (r, c): ";
        cin >> RowPlayerChoice >> ColPlayerChoice;

        while (RowPlayerChoice > BoardSize || ColPlayerChoice > BoardSize)
        {
            cout << "\nInvalid input. Try again.\n";
            cout << "Player X Turn. Enter Empty Location (r, c): ";
            cin >> RowPlayerChoice >> ColPlayerChoice;
        }


        CheckAndSavePlayerChoice(XOBoard, BoardSize, RowPlayerChoice, ColPlayerChoice, enGameChoice::X);
        if (IsMatrixFull(XOBoard, BoardSize))
            break;
        TheWinner = IsThereAWinner(XOBoard, BoardSize, RowPlayerChoice, ColPlayerChoice);

        if (TheWinner == enTheWinner::Player_X)
        {
            cout << "\nPlayer X won\n";
            break;
        }
        cout << "\nPlayer O Turn. Enter Empty Location (r, c): ";
        cin >> RowPlayerChoice >> ColPlayerChoice;

        while (RowPlayerChoice > BoardSize || ColPlayerChoice > BoardSize)
        {
            cout << "\nInvalid input. Try again.\n";
            cout << "Player O Turn. Enter Empty Location (r, c): ";
            cin >> RowPlayerChoice >> ColPlayerChoice;
        }


        CheckAndSavePlayerChoice(XOBoard, BoardSize, RowPlayerChoice, ColPlayerChoice, enGameChoice::O);
        if (IsMatrixFull(XOBoard, BoardSize))
            break;
        TheWinner = IsThereAWinner(XOBoard, BoardSize, RowPlayerChoice, ColPlayerChoice);

        if (TheWinner == enTheWinner::Player_O)
        {
            cout << "\nPlayer O won\n";
            break;
        }
    }
    cout << "\nGame Over.";
    Delete2DDynamicArr(XOBoard, BoardSize);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayGame();
        printf("\n\nDo you Want to Play again? [N/Y]  ");
        cin >> PlayAgain;
    } while (MyLib::CheckChar(PlayAgain));
}

int main()
{
    StartGame();
    return 0;
}
