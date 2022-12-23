
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include<fstream>
#include <cstdlib>
#include <vector>

/**********************************************************************************/
// my solution
/**********************************************************************************/
using namespace std;
const string UserFileName = "users.txt";
const string QuestionFileName = "questions.txt";
void start_system();
struct User
{
    int id = -1;
    string userName = "";
    string password = "";
    string name = "";
    string email = "";
    bool allowAnonymous = false;

};
// global user to login
User loginUser;
struct Question
{
    int id = 0;
    string threadQuestion = "";
    int from =0;
    int to =0;
    bool isAnoy = false;
    string question = "";
    string answer = "";
    bool mark = false;

    Question()
    {
        id++;
    }
};
Question quesForMaking;
vector<string>Split(string str, string delimeter = ",")
{
    vector<string> result;
    string sWord = "";
    int pos = 0;

    while ((pos = str.find(delimeter)) != string::npos)
    {
        sWord = str.substr(0, pos);
        if (sWord != "")
            result.push_back(sWord);

        str.erase(0, pos + delimeter.length());
    }
    if (str != "")
        result.push_back(str);

    return result;
}
User ConverLineToRecordUser(string line, string delimeter = ",")
{
    vector<string> res = Split(line, delimeter);
    User user;

    if (!res.empty())
    {
        user.id = stoi(res[0]);
        user.userName = res[1];
        user.password = res[2];
        user.name = res[3];
        user.email = res[4];
        user.allowAnonymous = stoi(res[5]);
    }
    return user;
}
Question ConverLineToRecordQuestion(string line, string delimeter = ",")
{
    vector<string> res = Split(line, delimeter);
    Question ques;

    if (!res.empty() && res.size() == 7)
    {
        ques.id = stoi(res[0]);
        ques.threadQuestion = res[1];
        ques.from = stoi(res[2]);
        ques.to = stoi(res[3]);
        ques.isAnoy = stoi(res[4]);
        ques.question = res[5];
        ques.answer = res[6];
    }
    else if(!res.empty() && res.size() == 6)
    {
        ques.id = stoi(res[0]);
        ques.threadQuestion = res[1];
        ques.from = stoi(res[2]);
        ques.to = stoi(res[3]);
        ques.isAnoy = stoi(res[4]);
        ques.question = res[5];
        ques.answer = "";
    }
    return ques;
}
string ConverRecordToLineQuestion(Question ques, string delimeter = ",")
{
    string res = "";
    if(ques.id != 0)
    {


        res+=to_string(ques.id) + delimeter;
        res+=ques.threadQuestion + delimeter;
        res+= to_string(ques.from) + delimeter;
        res+= to_string(ques.to) + delimeter;
        res+= to_string(ques.isAnoy)+ delimeter;
        res+=ques.question+ delimeter;
        res+=ques.answer;
    }
    return res;
}

string ConverRecordToLineUser(User users, string delimeter = ",")
{
    string res = "";
    if(users.id != 0)
    {


        res+=to_string(users.id) + delimeter;
        res+=users.userName + delimeter;
        res+= users.password + delimeter;
        res+= users.name + delimeter;
        res+= users.email+ delimeter;
        res+=to_string(users.allowAnonymous);
    }
    return res;
}
vector<User> LoadUserFromFileToVector(string file)
{
    vector <User> vClients;
    fstream myFile;

    myFile.open(file, ios::in); // read mode
    if (myFile.is_open())
    {
        string line;
        User client;
        while (getline(myFile, line))
        {
            client = ConverLineToRecordUser(line,",");
            vClients.push_back(client);
        }
        myFile.close();
    }
    return vClients;
}
vector<Question> LoadQuestionFromFileToVector(string file)
{
    vector <Question> vClients;
    fstream myFile;

    myFile.open(file, ios::in); // read mode
    if (myFile.is_open())
    {
        string line;
        Question ques;
        while (getline(myFile, line))
        {
            ques = ConverLineToRecordQuestion(line,",");
            vClients.push_back(ques);
        }
        myFile.close();
    }
    return vClients;
}
bool UserFindByUserNameAndPassword(vector<User>& users, string userName, string password,User &user)
{
    for (auto& u : users)
    {
        if (u.userName == userName && u.password == password)
        {
            user = u;
            return true;
        }
    }
    return false;
}
bool isUserNameExist(vector<User>& users, string userName, string password,User &user)
{
    for (auto& u : users)
    {
        if (u.userName == userName )
        {
            user = u;
            return true;
        }
    }
    return false;
}
bool UserFindByID(vector<User>& users, int id,User &user)
{
    for (auto& u : users)
    {
        if (u.id == id)
        {
            user = u;
            return true;
        }
    }
    return false;
}
bool QuestionFindByID(vector<Question>& questions,int id,Question &ques)
{
    for (auto& q : questions)
    {
        if (q.id == id)
        {
            ques = q;
            return true;
        }
    }
    return false;
}
int menuDetali()
{
    int num = -1;
    cout << "Menu: \n";
    cout << "\t 1: Print Question To Me\n";
    cout << "\t 2: Print Question From Me\n";
    cout << "\t 3: Answer Questions\n";
    cout << "\t 4: Delete Question\n";
    cout << "\t 5: ASk Question\n";
    cout << "\t 6: List System Users\n";
    cout << "\t 7: Feed\n";
    cout << "\t 8: Logout\n";
    while (num == -1)
    {

        cout << "\nEnter number in range 1 - 8: ";
        cin >> num;
        if (!(1 <= num && num <= 8))
        {

            cout << "\nError,Invalid number please try again...\n";
            num = -1;
        }
    }
    return num;
}

int mainMenu()
{
    int num = -1;
    cout << "Menu: \n";
    cout << "\t 1: Login\n";
    cout << "\t 2: Sign UP\n\n";

    while (num == -1)
    {

        cout << "\nEnter number in range 1 - 2: ";
        cin >> num;
        if (!(1 <= num && num <= 2))
        {

            cout << "\nInvalid number please try again...\n";
            num = -1;
        }
    }
    return num;
}
enum eMenuDetali
{
    printQuestionTo = 1, printQuestionFrom = 2,
    answerQuestion = 3, deleteQuestion = 4,
    askQuestion = 5, listSystem = 6,
    feed = 7, logout = 8
};
string trimRight(string str)
{
    int size = str.size() - 1;
    for (int i = size; i >= 0; i--)
    {
        if (str[i] != ' ')
            return str.substr(0, i+1);

    }
    return "";
}
void showQuestionToMe(Question question,bool is= true)
{
    string parent;
    if(is)
        parent = question.threadQuestion == "-1" ? "":"\tThread:";

    if(!question.isAnoy)
        cout <<parent<< " Question id(" << question.id  << ") From user id(" << question.from << ") ";
    else
    {
        cout <<parent<< " Question id(" << question.id << ")\t";
    }

    cout << "\tQuestion: " <<  question.question << "\n";
    if(trimRight(question.answer) != "")
        cout << parent <<"\t\t\t Answer: " <<  question.answer  << "\n\n";
    else
        cout << endl;

}
void printQuestionToMe()
{
    vector<Question> questions = LoadQuestionFromFileToVector(QuestionFileName);
    for(auto& a : questions)
    {
        if(a.to == loginUser.id)
        {
            showQuestionToMe(a);
        }
    }
}

void showQuestionFromMe(Question question)
{
    string anoynmous = question.isAnoy == 0 ? "!AQ " : "";

    cout <<" Question id(" << question.id  <<")" << anoynmous << "To user id(" << question.to << ") ";
    cout << "\tQuestion: " <<  question.question << "\n";
    if(trimRight(question.answer) != "")
        cout  <<"\t\t Answer: " <<  question.answer  << "\n\n";
    else
        cout << "\t\tNot Answerd Yet" << endl;

}
void printQuestionFromMe()
{
    vector<Question> questions = LoadQuestionFromFileToVector(QuestionFileName);
    for(auto& a : questions)
    {
        if(a.from == loginUser.id)
        {
            showQuestionFromMe(a);
        }
    }
}
void saveDataToFile(vector<Question>& ques, string fileName)
{
    fstream myFile;
    //vector<string> res =
    myFile.open(fileName, ios::out); // write mode
    if (myFile.is_open())
    {
        string line;
        for (auto& q : ques)
        {
            if (q.mark == false)
            {
                line = ConverRecordToLineQuestion(q);
                myFile << line << endl;
            }
        }
        myFile.close();
    }
}

void saveUserDataToFile(vector<User>& users, string fileName)
{
    fstream myFile;
    //vector<string> res =
    myFile.open(fileName, ios::out); // write mode
    if (myFile.is_open())
    {
        string line;
        for (auto& u : users)
        {
                line = ConverRecordToLineUser(u);
                myFile << line << endl;

        }
        myFile.close();
    }
}
void updateQuestion()
{
    vector<Question> questions = LoadQuestionFromFileToVector(QuestionFileName);

    Question ques;
    int QuestionId;
    cout << "\nEnter Question id or -1 to cancel: ";
    cin >> QuestionId;

    if(QuestionId == -1)
    {
        cout << "Canceld\n";
        return;
    }

    if(QuestionFindByID(questions,QuestionId,ques))
    {
        showQuestionToMe(ques,false);

        if(ques.answer != "")
            cout << "Warning: Already answerd. Answer will be updated\n";
        string newAnswer;
        getline(cin >> ws,newAnswer);



        for (auto& q : questions)
        {
            if(q.id == QuestionId)
            {
                q.answer = newAnswer;
                break;
            }
        }

        saveDataToFile(questions,QuestionFileName);
    }
    else
    {
        cout << "\tthis id not found!\n";
    }

}
void removeQuestion()
{
    vector<Question> questions = LoadQuestionFromFileToVector(QuestionFileName);

    Question ques;
    int QuestionId;
    cout << "\nEnter Question id or -1 to cancel: ";
    cin >> QuestionId;

    if(QuestionFindByID(questions,QuestionId,ques))
    {
        for (auto& q : questions)
        {
            if(q.id == QuestionId)
            {
                q.mark = true;
                if(q.threadQuestion =="-1")
                {
                    for (auto& in : questions)
                    {
                        if(in.threadQuestion == to_string(q.id))
                            in.mark = true;
                    }

                }
                else
                    break;
            }
        }
        saveDataToFile(questions,QuestionFileName);
    }
    else
    {
        cout << "\tthis id not found!\n";
    }
}
void listSystemUsers()
{
    vector<User> users = LoadUserFromFileToVector(UserFileName);
    for(auto &u : users)
    {
        cout << "ID: " << u.id << "\t Name: " <<u.name << endl;
    }
}
int nextQuestionID()
{
    vector<Question> questions = LoadQuestionFromFileToVector(QuestionFileName);
    int MAX = -1;

    for(auto & t : questions)
    {
        if(t.id > MAX)
            MAX = t.id;
    }
    return ++MAX;
}
int nextUserID()
{
    vector<User> users = LoadUserFromFileToVector(UserFileName);
    int MAX = -1;

    for(auto & t : users)
    {
        if(t.id > MAX)
            MAX = t.id;
    }
    return ++MAX;
}
Question makeNewQuestion(string thread,int f, int t,string q)
{

    quesForMaking.id = nextQuestionID();
    quesForMaking.threadQuestion = thread;
    quesForMaking.from = f;
    quesForMaking.to = t;
    quesForMaking.question = q;
    quesForMaking.answer = "";
    return quesForMaking;
}
void askNewQuestion()
{
    vector<User> users = LoadUserFromFileToVector(UserFileName);
    vector<Question> questions = LoadQuestionFromFileToVector(QuestionFileName);

    User user;
    Question ques;
    int id;
    cout << "Enter User ID or -1 to cancel: ";
    cin >> id;
    if(id != -1)
    {

        if(UserFindByID(users,id,user))
        {
            if(!user.allowAnonymous)
                cout << "Note: Anonymous questions are not allowed for this users\n";
            int number;
            cout << "For Thread Question: Enter Question id or -1 for new question: ";
            cin >> number;
            string text;
            cout << "Enter Question Text: ";
            getline(cin >> ws,text);
            if(number == -1)
                ques = makeNewQuestion("-1",loginUser.id,id,text);
            else
                ques = makeNewQuestion(to_string(number),loginUser.id,id,text);

            questions.push_back(ques);
            saveDataToFile(questions,QuestionFileName);


        }

    }
}
void listUsersFeed()
{
    vector<Question> questions = LoadQuestionFromFileToVector(QuestionFileName);

    for(auto &q : questions)
    {
        if(q.from == loginUser.id)
            showQuestionFromMe(q);
        else if(q.to == loginUser.id)
            showQuestionToMe(q);
    }
}
void goBackToDetail()
{
    cout << "Please press any key to return back to menu...\n";
    system("pause>0");
    system("cls");

}

void performMenuDetali(eMenuDetali menu)
{

    switch(menu)
    {
    case eMenuDetali::printQuestionTo:
    {
        printQuestionToMe();
        goBackToDetail();
        break;
    }
    case eMenuDetali::printQuestionFrom:
    {
        printQuestionFromMe();
        goBackToDetail();
        break;
    }
    case eMenuDetali::answerQuestion:
    {
        updateQuestion();
        goBackToDetail();
        break;
    }
    case eMenuDetali::deleteQuestion:
    {
        removeQuestion();
        goBackToDetail();
        break;
    }
    case eMenuDetali::askQuestion:
    {
        askNewQuestion();
        goBackToDetail();
        break;
    }
    case eMenuDetali::listSystem:
    {
        listSystemUsers();
        goBackToDetail();
        break;
    }
    case eMenuDetali::feed:
    {
        listUsersFeed();
        goBackToDetail();
        break;
    }
    case eMenuDetali::logout:
    {
        start_system();
        User user;
        loginUser =user;
        break;
    }

    }
}
void login()
{
    string userName, password;
    vector<User> users = LoadUserFromFileToVector(UserFileName);

    cout << "Enter User Name & Password: ";
    cin >> userName >> password;


    if (UserFindByUserNameAndPassword(users, userName, password,loginUser))
    {
        int num = menuDetali();
        while((eMenuDetali)num != eMenuDetali::logout)
        {
            performMenuDetali((eMenuDetali)num);
            num = menuDetali();
        }
        start_system();
    }
    else
    {
        cout << "Invalid userName or password\n";
    }

}
void signUp()
{
    vector<User> users = LoadUserFromFileToVector(UserFileName);

    loginUser.id = nextUserID();
    cout << "\nEnter User Name: ";
    cin >> loginUser.userName;

    cout << "Enter Password: ";
    cin >> loginUser.password;

    cout << "Enter Name: ";
    cin >> loginUser.name;

    cout << "Enter Email: ";
    cin >> loginUser.email;

    cout << "Allow Anonymous question?: (0 or 1) ";
    cin >> loginUser.allowAnonymous;
    if (isUserNameExist(users, loginUser.userName, loginUser.password,loginUser))
    {
        cout << "This user already exists\n";
        return ;
    }

    // add it to file
    users.push_back(loginUser);
    saveUserDataToFile(users,UserFileName);
}
void start_system()
{
    int choice = mainMenu();

    if (choice == 1)
    {
        login();
    }
    else if (choice == 2)
    {
        signUp();
    }
}

int main()
{
    start_system();

    system("pause>0");
}

