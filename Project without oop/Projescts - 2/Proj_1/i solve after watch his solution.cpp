#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
enum enWinner {Player = 1, Computer = 2, Draw=3};
enum enChoices {Stone = 1, Paper = 2, Sicssor = 3};

struct stRound
{
    short rounds = 0;
    enChoices playerChoice;
    enChoices ComputerChoice;
    enWinner Winner;
    string WinnerName = "";
};
struct stGamesRes
{
    short rounds = 0;
    short playerTimes = 0;
    short ComputerTimes = 0;
    short drawTims = 0;
    enWinner Winner;
    string WinnerName = "";
};
int RandomNumber(int From, int To)
{
    return rand() % (To - From) + From;
}
string getWinnerName(enWinner winner)
{
    string winners[3] = {"player1","Computer","No Winner"};
    return winners[winner - 1];
}
string getchoiceName(enChoices ch)
{
    string choices[3] = {"Stone","Paper","Sicssor"};
    return choices[ch - 1];
}
string Tabs(int howTabs)
{
    string t = "";
    for(int i = 1 ; i < howTabs ; i++)
    {
        t= t + "\t";
        cout << t;
    }
    return t;
}
enChoices getComputerChoice()
{
    return (enChoices)RandomNumber(1,3);
}

enChoices getPlayerChoice()
{
    int choice = 1;

    do
    {
        cout << "\nYour choice [1]:Stone, [2]:Paper, [2]:Sicssor ? ";
        cin >> choice;
    }
    while(choice < 1 || choice > 3);

    return (enChoices)choice;
}

short ReadHowManyRound()
{
    short howRounds = 1;
    do
    {
        cout << "\n How many rounds 1 To 10 ? ";
        cin >> howRounds;
    }
    while(howRounds < 1 || howRounds > 10);
    return howRounds;
}
enWinner getWhoWonTheRound(stRound roundInf)
{
    if(roundInf.ComputerChoice == roundInf.playerChoice) return enWinner::Draw;

    switch(roundInf.playerChoice)
    {
    case enChoices::Paper:
    {
        if(roundInf.ComputerChoice == enChoices::Stone)
            return enWinner::Player;
    }
    case enChoices::Sicssor:
    {
        if(roundInf.ComputerChoice == enChoices::Paper)
            return enWinner::Player;
    }
    case enChoices::Stone:
    {
        if(roundInf.ComputerChoice == enChoices::Sicssor)
            return enWinner::Player;
    }
    }

    return enWinner::Computer;
}
void setColor(enWinner winner)
{
    switch(winner)
    {
    case enWinner::Computer:
    {
        system("color 4F");
        cout << "\a";
    }
    break;
    case enWinner::Player:
        system("color 2F");
        break;
    default:
        system("color 6F");
    }

}
void printResultsOnScreen(stRound roundInfo)
{
    cout << "\n________________Round["<<   roundInfo.rounds << "]_______________\n";
    cout << "Player1 Choice: " << getchoiceName(roundInfo.playerChoice) << "\n";
    cout << "Computer Choice: " << getchoiceName(roundInfo.ComputerChoice) << "\n";
    cout << "Round Winner   : " << roundInfo.WinnerName << "\n";
}
enWinner getWinner(short playerTimes,short computerTimes)
{
    if(playerTimes > computerTimes) return enWinner::Player;
    else if (playerTimes < computerTimes) return enWinner::Computer;
    else return enWinner::Draw;
}
stGamesRes fillGameResults(short HowManyRound,short playerTimes,short computerTimes,short drawTimes)
{
    stGamesRes gamesST;
    gamesST.rounds = HowManyRound;
    gamesST.playerTimes = playerTimes;
    gamesST.ComputerTimes = computerTimes;
    gamesST.drawTims = drawTimes;
    gamesST.Winner =getWinner(playerTimes,computerTimes);
    gamesST.WinnerName = getWinnerName(gamesST.Winner);
    return gamesST;
}
stGamesRes playGame(short HowManyRound)
{
    stRound RoundINFO;
    short playerTimes = 0, computerTimes = 0, drawTimes = 0;
    for(int GameCounter = 1 ; GameCounter <= HowManyRound ; GameCounter++ )
    {
        cout << "\n Round ["<< GameCounter << "] begins: \n";
        RoundINFO.rounds = GameCounter;
        RoundINFO.playerChoice = getPlayerChoice();
        RoundINFO.ComputerChoice = getComputerChoice();
        RoundINFO.Winner = getWhoWonTheRound(RoundINFO);
        RoundINFO.WinnerName = getWinnerName(RoundINFO.Winner);

        // increas win/draw
        if(RoundINFO.Winner == enWinner::Computer)computerTimes++;
        else if(RoundINFO.Winner == enWinner::Player)playerTimes++;
        else drawTimes++;

        printResultsOnScreen(RoundINFO);
        setColor(RoundINFO.Winner);
    }
    return fillGameResults(HowManyRound,playerTimes,computerTimes,drawTimes);
}
void ResetGame()
{
    system("color 0F");
    system("cls");
}
void GameOver()
{
    cout << endl<< Tabs(2) << "________________________________________________________________\n\n";
    cout <<endl  << Tabs(2) << "                    +++ Game Over +++ \n";
    cout <<endl  << Tabs(2) << "________________________________________________________________\n\n";
}
void printFinalGame(stGamesRes st)
{
    cout << Tabs(2) << "_______________________[Game Result]_______________________________\n\n";
    cout << Tabs(2)<< "Game Rounds      : " <<st.rounds << "\n";
    cout << Tabs(2)<<"Player1 won times : " << st.playerTimes << "\n";
    cout << Tabs(2)<<"Computer won times: " << st.ComputerTimes << "\n";
    cout << Tabs(2)<<"Draw times        : " <<st.drawTims << "\n";
    cout << Tabs(2)<<"Final Winner      : " <<st.WinnerName << "\n";
    setColor(st.Winner);
}
void startGame()
{
    char starting = 'Y';
    do
    {
        ResetGame();
        stGamesRes st = playGame(ReadHowManyRound());
        GameOver();
        printFinalGame(st);
        cout << Tabs(2) <<"Do you want to play again ? ";
        cin >> starting;
    }
    while(starting == 'Y' || starting == 'y');
}
main()
{

    srand((unsigned) time(NULL));
    startGame();

    return 0;
}

