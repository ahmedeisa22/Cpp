#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
enum enQuestionLevel {Easy = 1, Medium = 2, Hard = 3, mix = 4};
enum enOperationType {Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5};
struct stQuiz
{
    short NumberQUiz = 0;
    enQuestionLevel level;
    enOperationType type;
    short Number1 = 0;
    short Number2 = 0;
    int CorrectResult = 0;
    bool isCorrect = true;
    char operation;
};
int RandomNumber(int From, int To)
{
    return rand()% (To - From) + From;
}
string Tabs(short HowManyTabs)
{
    string t = "";
    for(int i = 0 ; i < HowManyTabs ; i++)
    {
        t += "\t";
        cout << t;
    }
    return t;
}
string getQuestionLevel(enQuestionLevel level){
    string levels[4] = {"Easy","Medium","Hard","mix"};
    return levels[level- 1];
}
string getOperationType(enOperationType type){
    string levels[5] = {"Add","Subtract","Multiplication","Division","Mix"};
    return levels[type- 1];
}
char operationChar(enOperationType ch)
{
    char operations[4] = {'+','-','*','/'};
    if(ch == enOperationType::Mix) return operations[RandomNumber(1,4)-1];
    return operations[ch - 1];
}
enQuestionLevel QuestionLevel()
{
    short levelQuiz;

    do
    {
        cout << "\nEnter Question Level [1]:Easy, [2]:Meduim, [3]:Hard, [4]:Mix : ";
        cin >> levelQuiz;
    }
    while(levelQuiz < 0 || levelQuiz > 4);
    return (enQuestionLevel)levelQuiz;
}
enOperationType OperationType()
{
    short opt;

    do
    {
        cout << "Enter Operation Type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix : ";
        cin >> opt;
    }
    while(opt < 0 || opt > 5);
    return (enOperationType)opt;
}
short HowManyQuestion()
{
    short qu;
    do
    {
        cout << "How many Question do you want to answer: ";
        cin >> qu;

    }
    while(qu <= 0 || qu > 1000 );
    return qu;
}
void  printQuestino(short QuestionRound,short HowManyQuiz)
{
    cout << "\nQuestion ["<<QuestionRound << "/"<<HowManyQuiz <<"]\n\n";
}
void PrintFormal(short firstNum, short SecondNum, char op)
{
    cout <<" "<<firstNum << "\n";
    cout << " "<<SecondNum << " " << op << "\n";
    cout <<"____________________\n";
}

void checkLevel(enQuestionLevel level,stQuiz &quiz)
{
    switch(level)
    {
    case enQuestionLevel::Easy:
        quiz.Number1 = RandomNumber(1,10);
        quiz.Number2 = RandomNumber(1,10);
        break;
    case enQuestionLevel::Medium:
        quiz.Number1 = RandomNumber(10,50);
        quiz.Number2 = RandomNumber(10,50);
        break;
    case enQuestionLevel::Hard:
        quiz.Number1 = RandomNumber(100,1000);
        quiz.Number2 = RandomNumber(100,1000);
        break;
    case enQuestionLevel::mix:
        quiz.Number1 = RandomNumber(1,1000);
        quiz.Number2 = RandomNumber(1,1000);
        break;
    }
}
int RighResult(stQuiz &quiz)
{
    switch(quiz.operation)
    {
    case '+':
        return quiz.Number1 + quiz.Number2;
    case '-':
        return quiz.Number1 - quiz.Number2;
    case '*':
        return quiz.Number1 * quiz.Number2;
    case '/':
        return quiz.Number1 / quiz.Number2;
    }
}
void setColorScreen(stQuiz &quiz){
    if(quiz.isCorrect)
    {
        system("color 2F");
        return;
    }
    system("color 4F"); //turn screen to Red
    cout << "\a";
}
bool printResult(stQuiz &quiz)
{
    if(quiz.isCorrect)
    {
        cout << "Right Answers :)\n";
        return true;
    }

    cout << "Wrong Answer :(\n";
    cout << "The right answer is: " << quiz.CorrectResult << "\n";
    return false;
}
bool checkPassed(int right, int wrong){
    return right > wrong;
}
string FinalResult(int right, int wrong)
{
    if(checkPassed(right , wrong)) return "PASSED:)";
    else return "FAILD:(";
}
void PrintFinalResult(int right, int wrong)
{
    cout << "______________________________\n\n";
    cout << " " << "Final result is " << FinalResult(right,wrong) << " \n";
    cout << "______________________________\n\n";
}
void PrintLastResult(stQuiz &quiz,short rights, short wrongs){
  cout << "______________________________\n\n";
cout << " Number of Questions   : " << quiz.NumberQUiz << "\n";
cout << " Questions Level       : " << getQuestionLevel(quiz.level) << "\n";
cout << " Operation Type        : " << getOperationType(quiz.type) << "\n";
cout << " Number of Righ Answer : " << rights << "\n";
cout << " Number of Wrong Answer : " << wrongs << "\n";
  cout << "______________________________\n\n";

  setColorScreen(quiz);

}
stQuiz startQuiz(short HowManyQuiz)
{
    stQuiz quiz;
    short RigthAnswers = 0, WrongAnswers = 0;
    quiz.level = QuestionLevel();
    quiz.type = OperationType();
    for(int QuestionRound = 1 ; QuestionRound <= HowManyQuiz ; QuestionRound++)
    {
       quiz.operation = operationChar( quiz.type);
        quiz.NumberQUiz = QuestionRound;
        checkLevel(quiz.level,quiz);

        printQuestino(QuestionRound,HowManyQuiz);
        PrintFormal(quiz.Number1,quiz.Number2, quiz.operation);
        int res;
        cin >> res;
        quiz.CorrectResult = RighResult(quiz);
        if(quiz.CorrectResult == res)
        {
            quiz.isCorrect = true;
            RigthAnswers++;
            setColorScreen(quiz);
            printResult(quiz);
        }
        else
        {
            quiz.isCorrect = false;
            WrongAnswers++;
            setColorScreen(quiz);
              printResult(quiz);
        }

    }

    // end of Questions
    if(checkPassed(RigthAnswers , WrongAnswers))quiz.isCorrect = true;
    else quiz.isCorrect = false;
    PrintFinalResult(RigthAnswers,WrongAnswers);
    PrintLastResult(quiz,RigthAnswers,WrongAnswers);
}

void Reset()
{
    system("color 0F");
    system("cls");
}

void startQuestion()
{
    char ch;
    do
    {
        Reset();
        stQuiz quizer = startQuiz(HowManyQuestion());
        cout << "Do you want play again [Y|N] ? ";
        cin >> ch;
    }
    while(ch == 'Y' || ch == 'y');
}
int main()
{
    srand((unsigned) time(NULL));
    startQuestion();
    return 0;
}
