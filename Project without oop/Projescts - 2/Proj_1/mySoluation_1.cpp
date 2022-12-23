#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
enum enChoices {Stone = 1, Paper = 2, Scissor = 3};
enum enUserOrComputer {User = 1, Computer = 2,Draw = 3};
int ReadPoisitveNumber(string str)
{
    int num;
    cout << str;
    cin >> num;
    return num;
}
int RandomNumber(int From, int To)
{
    return rand() % (To - From ) + From;
}
int computerChoice()
{
    return RandomNumber(1,3);
}
int  getChoicePlayer(int i)
{
    cout << "Round [" << i+1 << "] begins: \n\n";
    int num = ReadPoisitveNumber("Your choice: [1]:Stone, [2]:Paper, [3]:Scissor ? ");

    return num;
}
string getChoices(enChoices ch)
{
    switch(ch)
    {
    case enChoices::Stone:
        return "Stone";
    case enChoices::Paper:
        return "Paper";
    case enChoices::Scissor:
        return "Scissor";
    }
}
enUserOrComputer RuleOfGame(int playerChoice,int computerChoice)
{

    if(playerChoice == computerChoice)
        return enUserOrComputer::Draw;
    if(playerChoice == 1 && computerChoice == 2)
        return enUserOrComputer::Computer;
    else if(playerChoice == 1 && computerChoice == 3)
        return enUserOrComputer::User;
    else if(playerChoice == 2 && computerChoice == 1)
        return enUserOrComputer::User;
    else if(playerChoice == 2 && computerChoice == 3)
        return enUserOrComputer::Computer;
    else if(playerChoice == 3 && computerChoice == 1)
        return enUserOrComputer::Computer;
    else if(playerChoice == 3 && computerChoice == 2)
        return enUserOrComputer::User;


}
enUserOrComputer printWinner(enUserOrComputer winner)
{
    if(winner == enUserOrComputer::Computer)
    {
        cout << "Round Winner:   [Computer]\a\n";
        system("color 47");
        return enUserOrComputer::Computer;
    }
    else if(winner == enUserOrComputer::User)
    {
        cout << "Round Winner:   [User]\n";
        system("color 20");
        return enUserOrComputer::User;
    }

    else if(winner == enUserOrComputer::Draw)
    {
        cout << "Round Winner:       [No Winner]\n";
        system("color E0");
        return enUserOrComputer::Draw;
    }

}
void checkWinner(enUserOrComputer winner,int &players1Wins,int &computerWins, int &draws)
{
    if(winner == enUserOrComputer::Computer)
        computerWins++;
    else if(winner == enUserOrComputer::User)
        players1Wins++;
    else if(winner == enUserOrComputer::Draw)
        draws++;

}
void showRound(int i,int playerChoice,int computerChoice,int &players1Wins,int &computerWins, int &draws )
{

    cout << "____________________Round["<< i+1 << "]___________________\n\n";

    cout << "Player1 Choice: " << getChoices((enChoices)playerChoice) << endl;
    cout << "Computer Choice: " << getChoices((enChoices)computerChoice) << endl;
    checkWinner(printWinner(RuleOfGame(playerChoice,computerChoice)),players1Wins,computerWins,draws);
    cout << "________________________________________________\n\n";

}
void printGameOver()
{
    cout << "\n\n\t\t\t_______________________________________________________\n\n\n";
    cout << "\t\t\t\t\t *** Game Over ***\n";
    cout << "\n\t\t\t_______________________________________________________\n\n";
}
void GameOver(int GameRound,int players1Wins,int computerWins, int draws)
{
    cout << "\t\t\t_______________________ [Game Result]_______________________________\n";
    cout << "\t\t\t Game Rounds:\t\t"<<GameRound << "\n";

    cout << "\t\t\t Player1 wins time:\t"<<players1Wins << "\n";
    cout << "\t\t\t Computer wins time:\t"<<computerWins << "\n";
    cout << "\t\t\t Draw Times:\t\t"<<draws << "\n";
    if(players1Wins == computerWins) cout << "\t\t\t Final Winner: \t[No Winner]\n";
    else if(players1Wins > computerWins) cout << "\t\t\t Final Winner: \t[Players1]\n";
    else cout << "\t\t\t Final Winner: \t[Computer]\n";
}
void startGame()
{
    while(true)
    {
        int rounds = ReadPoisitveNumber("How many round 1 to 10: \n");
        int i = 0;
        int palyer =0;
        int copmuter = 0;
        int draw = 0;
        while(i < rounds)
        {
            showRound(i,getChoicePlayer(i),computerChoice(),palyer,copmuter,draw);
            i++;
        }
        printGameOver();
        GameOver(i,palyer,copmuter,draw);

        cout << "Do you want paly again? [Y\\N]: ";
        char ch;
        cin >> ch;
        if(ch == 'N' || ch == 'n')
        {
            break;
        }
        system("color 07");
        system("cls");
    }
}
main()
{
    srand((unsigned) time(NULL));
    startGame();

    return 0;
}

