#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
enum enQuestionsLevel {EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4};
enum enOperationType {Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp= 5};
struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enQuestionsLevel QuestionLevel;
    enOperationType OperationType;
    int CorrectAsnwers = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};
struct stQuizz
{
    stQuestion QuestionsList[100];
    int NumberOfQuestions = 0;
    int WrongAnswers = 0;
    int RightAnswers = 0;
    enQuestionsLevel QuestionLevel;
    enOperationType OperationType;
    bool isPass = false;

};
int RandomNumber(int From, int To)
{
    return rand()%(To - From) + From;
}
int ReadHowManyQuestion()
{
    short q;
    do
    {
        cout << "Enter How many Question ? ";
        cin >> q;
    }
    while(q < 0 || q > 10);
    return q;
}
enQuestionsLevel ReadQuestionLevel()
{
    short q;
    do
    {
        cout << "\nEnter Question Level [1]:Easy, [2]:Meduim, [3]:Hard, [4]:Mix : ";
        cin >> q;
    }
    while(q < 0 || q > 4);
    return (enQuestionsLevel)q;
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
enQuestionsLevel getOperationTypeRandom()
{
    return (enQuestionsLevel)RandomNumber(1,4);
}
int SimpleCalculator(int Number1, int Number2, enOperationType opType)
{
    switch(opType)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Div:
        return Number1 / Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    default:
        return Number1 + Number2;

    }
}
stQuestion GenerateQuestion(enOperationType operationType, enQuestionsLevel questionLeve)
{
    stQuestion question;

    if(operationType == enOperationType::MixOp)
        operationType = (enOperationType)getOperationTypeRandom();
    if(questionLeve == enQuestionsLevel::Mix)
        questionLeve = (enQuestionsLevel)RandomNumber(1,3);

    question.QuestionLevel = questionLeve;
    question.OperationType = operationType;

    switch(questionLeve)
    {
    case enQuestionsLevel::EasyLevel:
        question.Number1 = RandomNumber(1,10);
        question.Number2 = RandomNumber(1,10);

        question.CorrectAsnwers = SimpleCalculator(question.Number1,question.Number2,question.OperationType);
        return question;

    case enQuestionsLevel::MedLevel:
        question.Number1 = RandomNumber(10,50);
        question.Number2 = RandomNumber(10,50);

        question.CorrectAsnwers = SimpleCalculator(question.Number1,question.Number2,question.OperationType);
        return question;

    case enQuestionsLevel::HardLevel:
        question.Number1 = RandomNumber(50,100);
        question.Number2 = RandomNumber(50,100);

        question.CorrectAsnwers = SimpleCalculator(question.Number1,question.Number2,question.OperationType);
        return question;


    }

}
void GenerateQuizzQuestions(stQuizz &quiz)
{
    for(int question = 0 ; question < quiz.NumberOfQuestions ; question++)
    {
        quiz.QuestionsList[question] = GenerateQuestion(quiz.OperationType,quiz.QuestionLevel);
    }
}
string GetOpTypeSymbol(enOperationType opt)
{
    switch(opt)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Div:
        return "/";
    case enOperationType::Mult:
        return "*";
    case enOperationType::Sub:
        return "-";

    }
}
void PrintTheQuestion(stQuizz &Quizz,int QuestionNumber)
{
    cout     <<     "\n";
    cout     <<     "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
    cout     <<     Quizz.QuestionsList[QuestionNumber].Number1 << endl;
    cout     <<     Quizz.QuestionsList[QuestionNumber].Number2 << " ";
    cout     <<     GetOpTypeSymbol(Quizz.QuestionsList[QuestionNumber].OperationType);
    cout     <<     "\n_________" << endl;
}
int ReadPlayerAnser()
{
    int ans;
    cin >> ans;
    return ans;
}
void SetColor(bool isPass)
{
    if(isPass)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F"); //turn screen to Red
        cout     <<     "\a";
    }
}
void CorrectTheQuestionAnswer(stQuizz &quiz, int QuestionNumber)
{

    if(quiz.QuestionsList[QuestionNumber].PlayerAnswer !=quiz.QuestionsList[QuestionNumber].CorrectAsnwers )
    {
        quiz.QuestionsList[QuestionNumber].AnswerResult = false;
        quiz.RightAnswers++;

        cout     <<     "Worng Answer :-( \n";
        cout     <<     "The right answer is: ";
        cout     <<quiz.QuestionsList[QuestionNumber].CorrectAsnwers;
        cout     <<     "\n";

    }
    else
    {
        quiz.QuestionsList[QuestionNumber].AnswerResult = true;
        quiz.WrongAnswers++;
        cout<<"Right Answer :-) \n";
    }
    cout << endl;
    quiz.isPass = quiz.RightAnswers >= quiz.WrongAnswers;

}
void AskAndCorrectQuestionListAnswers(stQuizz &quiz)
{
    for(int question = 0 ; question < quiz.NumberOfQuestions ; question++)
    {
        PrintTheQuestion(quiz,question);
        quiz.QuestionsList[question].PlayerAnswer = ReadPlayerAnser();

        CorrectTheQuestionAnswer(quiz, question);
        SetColor(quiz.QuestionsList[question].AnswerResult);
    }
}
string GetFinalResultsText(bool isPass)
{
    if(isPass)return "Passed";
    return "Falid";
}
string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix"};
    return arrQuestionLevelText[QuestionLevel - 1];
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout     <<     "\n";
    cout     <<     "______________________________\n\n";
    cout << " Final Resutls is " <<  GetFinalResultsText(Quizz.isPass);
    cout     <<     "\n______________________________\n\n";
    cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
    cout     <<     "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout     <<     "OpType             : " << GetOpTypeSymbol(Quizz.OperationType) << endl;
    cout     <<     "Number of Right Answers: " << Quizz.RightAnswers << endl;
    cout     <<     "Number of Wrong Answers: " << Quizz.WrongAnswers << endl;
    cout     <<     "______________________________\n";
}

void PlayMathGame()
{
    stQuizz quiz;

    quiz.NumberOfQuestions = ReadHowManyQuestion();
    quiz.QuestionLevel = ReadQuestionLevel();
    quiz.OperationType = OperationType();

    GenerateQuizzQuestions(quiz);

    AskAndCorrectQuestionListAnswers(quiz);

    PrintQuizzResults(quiz);
    SetColor(quiz.isPass);

}
void ResetQuestion()
{
    system("color 0F");
    system("cls");
}
void startGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetQuestion();
        PlayMathGame();

        cout << "\nDo you want to play again[Y||N]: ";
        cin >> PlayAgain;
    }
    while(PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
    srand((unsigned) time(NULL));
    startGame();
    return 0;
}
