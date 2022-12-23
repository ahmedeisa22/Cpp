#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
enum enGameChoice {Stone = 1, Paper = 2, Scissor = 3};
enum enWinner {Player1 = 1, Computer = 2, Draw = 3};


struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{

    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};
int RandomNumber(int From, int To)
{
    return rand() % (To - From ) + From;
}
short ReadHowManyRound()
{
    short GameRound = 1;

    do
    {
        cout << "How many Rounds 1 to 10: ";
        cin >> GameRound;
    }
    while(GameRound < 1 || GameRound > 10);
    return GameRound;
}
string Tabs(int Number)
{
    string t = "";
    for(int i =0 ; i < Number ; i++)
    {
        t+= "\t";
        //cout << t;
    }
    return t;
}
string WinnerName(enWinner winner)
{
    string winers[3] = {"Player1","Computer","No Winner"};
    return winers[winner - 1];
}
string getChoice(enGameChoice choice)
{
    string choices[3] = {"Stone","Paper","Scissor"};
    return choices[choice - 1];
}
enGameChoice ReadPlayerChoice()
{
    short cho = 1;

    do
    {
        cout << "\n Your Choice: [1]:Stone, [2]:Paper, [3]:Sicssor ? ";
        cin >> cho;
    }
    while(cho < 1 || cho > 3);
    return (enGameChoice)cho;
}
enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1,3);
}

enWinner WhoWinTheRound(stRoundInfo roundInfo)
{
    if(roundInfo.PlayerChoice == roundInfo.ComputerChoice)
        return enWinner::Draw;

    switch(roundInfo.PlayerChoice)
    {
    case enGameChoice::Paper:
    {
        if(roundInfo.ComputerChoice == enGameChoice::Scissor)
            return enWinner::Computer;
    }
    case enGameChoice::Scissor:
    {
        if(roundInfo.ComputerChoice == enGameChoice::Stone)
            return enWinner::Computer;
    }
    case enGameChoice::Stone:
    {
        if(roundInfo.ComputerChoice == enGameChoice::Paper)
            return enWinner::Computer;
    }

    }

    return enWinner::Player1;
}
void SetWinnerScreenColor(enWinner winner)
{
    switch(winner)
    {
    case enWinner::Computer:
        system("color 4F"); //turn screen to Red
            cout << "\a";
        break;
    case enWinner::Player1:
        system("color 2F");
        break;
    default:
        system("color 6F"); //turn screen to Yellowbreak;
        break;
    }
}
void printRoundInfo(stRoundInfo roundInfo)
{

    cout << "_______________________Round[" << roundInfo.RoundNumber << "]_______________\n";
    cout << "Player1 Choice: " <<getChoice(roundInfo.PlayerChoice) << "\n";
    cout << "Computer Choice: " <<getChoice(roundInfo.ComputerChoice) << "\n";
    cout << "Round Winner: [" << roundInfo.WinnerName << "]\n";
    SetWinnerScreenColor(roundInfo.Winner);
}
enWinner WhoWonTheGame(short player1Times,short computerTimes)
{
    if(player1Times > computerTimes) return enWinner::Player1;
    else if(player1Times < computerTimes) return enWinner::Computer;
    else return enWinner::Draw;
}
stGameResults FillGameResults(short gameRounds,short player1Times,short computerTimes,short drawTimes)
{

    stGameResults GameResults;

    GameResults.GameRounds = gameRounds;
    GameResults.PlayerWinTimes = player1Times;
    GameResults.ComputerWinTimes = computerTimes;
    GameResults.DrawTimes = drawTimes;
    GameResults.GameWinner = WhoWonTheGame(player1Times,computerTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;

}
stGameResults PlayGame(short howManyGame)
{
    stRoundInfo roundInfo;

    short player1WinTimes  = 0, ComputerWinTimes = 0, drawTimes = 0;
    for(short GameRound = 1 ; GameRound <= howManyGame ; GameRound++)
    {

        cout << "\nRound [" <<GameRound << "] begins:\n";
        roundInfo.RoundNumber = GameRound;
        roundInfo.PlayerChoice = ReadPlayerChoice();
        roundInfo.ComputerChoice = GetComputerChoice();
        roundInfo.Winner = WhoWinTheRound(roundInfo);
        roundInfo.WinnerName = WinnerName(roundInfo.Winner);

        //increase win/draw computer or user
        if(roundInfo.Winner == enWinner::Computer) ComputerWinTimes++;
        else if(roundInfo.Winner == enWinner::Player1) player1WinTimes++;
        else drawTimes++;

        printRoundInfo(roundInfo);
    }

    return FillGameResults(howManyGame,player1WinTimes,ComputerWinTimes,drawTimes);
}
void ResetScreen()
{
    system("color 0F");
    system("cls");
}
void showGameOverScreen()
{
    cout << Tabs(2) << "__________________________________________________\n\n";
    cout << Tabs(2) << "               +++ Game Over +++ \n";
    cout << Tabs(2) << "__________________________________________________\n\n";
}
void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
    cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times  : " << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "___________________________________________________________\n";
    SetWinnerScreenColor(GameResults.GameWinner);
}
void startGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRound());
        showGameOverScreen();
        ShowFinalGameResults(GameResults);
        cout << endl << Tabs(3) << "Do you want to play again? [Y||N]: ";
        cin >> PlayAgain;
    }
    while(PlayAgain == 'Y' || PlayAgain == 'y');
}
main()
{
    srand((unsigned) time(NULL));
    startGame();

    return 0;
}

