#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
enum enOperationType {Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5};
enum enQuestionLevel {EasyLevel = 1, MedLevel = 2, HardLevel = 3,Mix = 4};
string GetOpTypeSymbol(enOperationType op)
{
    switch(op)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mul:
        return "*";
    case enOperationType::Div:
        return "/";
    default:
        return "+";
    }
}
void SetScreenColor(bool pass)
{
    if(pass)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F"); //turn screen to Red
        cout<<"\a";
    }
}
struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType operationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};
struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberQuestion = 0;
    enOperationType opType;
    enQuestionLevel QuestionLevel;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool isPass= false;
};
int RandomNumer(int from, int to)
{
    return rand() % (to - from ) + from;
}
enOperationType GetRandomOperationType()
{
    return (enOperationType)RandomNumer(1,4);
}
int SimpleCalculator(int num1, int num2, enOperationType op)
{
    switch(op)
    {
    case enOperationType::Add:
        return num1 + num2;
        break;
    case enOperationType::Sub:
        return num1 - num2;
        break;
    case enOperationType::Div:
        return num1 / num2;
        break;
    case enOperationType::Mul:
        return num1 * num2;
        break;

    default:
        return num1 + num2;
        break;
    }
}
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType opType)
{

    stQuestion question;

    if(QuestionLevel == enQuestionLevel::Mix)
        QuestionLevel = (enQuestionLevel)RandomNumer(1,3);

    if(opType == enOperationType::MixOp)
        opType = GetRandomOperationType();

    question.operationType = opType;
    question.QuestionLevel = QuestionLevel;

    switch(QuestionLevel)
    {
    case enQuestionLevel::EasyLevel:
        question.Number1 = RandomNumer(1,10);
        question.Number2 = RandomNumer(1,10);

        question.CorrectAnswer = SimpleCalculator(question.Number1,question.Number2,question.operationType);
        return question;
    case enQuestionLevel::MedLevel:
        question.Number1 = RandomNumer(10,50);
        question.Number2 = RandomNumer(1,50);

        question.CorrectAnswer = SimpleCalculator(question.Number1,question.Number2,question.operationType);
        return question;
    case enQuestionLevel::HardLevel:
        question.Number1 = RandomNumer(50,100);
        question.Number2 = RandomNumer(50,100);

        question.CorrectAnswer = SimpleCalculator(question.Number1,question.Number2,question.operationType);
        return question;
    }

}

void GenerateQuizQuestion(stQuizz &quiz)
{
    for(short Question = 0 ; Question < quiz.NumberQuestion ; Question++)
    {
        quiz.QuestionList[Question] = GenerateQuestion(quiz.QuestionLevel,quiz.opType);
    }
}
short HowManyQuestion()
{
    short NumberQuestions;
    do
    {
        cout << "Enter How many Question do you want ? ";
        cin >> NumberQuestions;
    }
    while(NumberQuestions < 1 || NumberQuestions > 10);
    return NumberQuestions;
}
enQuestionLevel ReadQuestionLeve()
{
    short QuestionLeve;
    do
    {
        cout << "Enter Question Level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ";
        cin >> QuestionLeve;

    }
    while(QuestionLeve < 0 || QuestionLeve > 4);
    return (enQuestionLevel)QuestionLeve;
}
enOperationType ReadOperationType()
{
    short opt;
    do
    {
        cout << "Enter Operation Type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix ? ";
        cin >> opt;

    }
    while(opt < 0 || opt > 5);
    return (enOperationType)opt;
}
void printTheQuestion(stQuizz quizz, short QuestionNumber)
{
    cout << "\n";

    cout << "Question["<<QuestionNumber+1 << "/" << quizz.NumberQuestion << "] \n\n";
    cout << quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(quizz.QuestionList[QuestionNumber].operationType) << endl;
    cout << "\n_______________________\n";

}
int ReadPlayerAnswer()
{
    int ans = 0;
    cin >> ans;
    return ans;
}
void CorrectTheQuestionAnswer(stQuizz& quiz, short QuestionNumber)
{
    if(quiz.QuestionList[QuestionNumber].PlayerAnswer != quiz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        quiz.QuestionList[QuestionNumber].AnswerResult = false;
        quiz.NumberOfWrongAnswers++;

        cout << "Wrong answer :(\n";
        cout << "The right answer is: ";
        cout << quiz.QuestionList[QuestionNumber].CorrectAnswer << "\n";
    }
    else
    {
        quiz.QuestionList[QuestionNumber].AnswerResult = true;
        quiz.NumberOfRightAnswers++;

        cout << "Right answer :)\n";
    }
         SetScreenColor(quiz.QuestionList[QuestionNumber].AnswerResult);
}
void AskAndCorrectQuestionListAnswer(stQuizz &quiz)
{
    for(short QuestionNumber = 0 ; QuestionNumber < quiz.NumberQuestion ; QuestionNumber++)
    {
        printTheQuestion(quiz,QuestionNumber);

        quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();

        CorrectTheQuestionAnswer(quiz,QuestionNumber);

    }
    quiz.isPass = quiz.NumberOfRightAnswers >= quiz.NumberOfWrongAnswers;
    SetScreenColor(quiz.isPass);
}
string GetQuestionLevel(enQuestionLevel level)
{
    string levels[4] = {"Easy","Medium","Hard","mix"};
    return levels[level- 1];
}
string GetOperationType(enOperationType type)
{
    string levels[5] = {"Add","Subtract","Multiplication","Division","Mix"};
    return levels[type- 1];
}
string getFinalResult(bool isPass)
{
    if(isPass) return "PASSED";
    else return "FALID";
}
void PrintQuizzResult(stQuizz quiz)
{
    cout << "\n";
    cout << "_____________________________\n";
    cout << "Final result is : " << getFinalResult(quiz.isPass) << "\n";
    cout << "_____________________________\n";

    cout << "Number of Question      : " << quiz.NumberQuestion << "\n";
    cout << "Question Level          : " << GetQuestionLevel(quiz.QuestionLevel) << "\n";
    cout << "opType                  : " << GetOpTypeSymbol(quiz.opType) << "\n";
    cout << "Number of Right Qusetion: " << quiz.NumberOfRightAnswers << "\n";
    cout << "Number of Wrong Qusetion: " << quiz.NumberOfWrongAnswers << "\n";
}
void playMathGame()
{
    stQuizz Quiz;
    Quiz.NumberQuestion = HowManyQuestion();
    Quiz.QuestionLevel = ReadQuestionLeve();
    Quiz.opType = ReadOperationType();

    GenerateQuizQuestion(Quiz);

    AskAndCorrectQuestionListAnswer(Quiz);

    PrintQuizzResult(Quiz);

}
void ResetScreen()
{
    system("color 0F");
    system("cls");
}
void startGame()
{
    char playAgin = 'Y';
    do
    {
        ResetScreen();
        playMathGame();
        cout << "Do you want to play again Y|N: ";
        cin >> playAgin;

    }
    while(playAgin == 'Y' || playAgin == 'y');
}
int main()
{
    srand((unsigned) time(NULL));
    startGame();
    return 0;
}
