#include<bits/stdc++.h>
using namespace std;

/////////////////////////////// Helper Methods ///////////////////////////////
vector<string> ReadFileLines(string path)
{
    vector<string> lines;

    fstream file_handler(path.c_str());

    if (file_handler.fail())
    {
        cout << "\n\nERROR: Can't open the file\n\n";
        return lines;
    }
    string line;

    while (getline(file_handler, line))
    {
        if (line.size() == 0)
            continue;
        lines.push_back(line);
    }

    file_handler.close();
    return lines;
}

void WriteFileLines(string path, vector<string> lines, bool append = true)
{
    auto status = ios::in | ios::out | ios::app;

    if (!append)
        status = ios::in | ios::out | ios::trunc;	// overwrite

    fstream file_handler(path.c_str(), status);

    if (file_handler.fail())
    {
        cout << "\n\nERROR: Can't open the file\n\n";
        return;
    }
    for (auto line : lines)
        file_handler << line << "\n";

    file_handler.close();
}

vector<string> SplitString(string s, string delimiter = ",")
{
    vector<string> strs;

    int pos = 0;
    string substr;
    while ((pos = (int) s.find(delimiter)) != -1)
    {
        substr = s.substr(0, pos);
        strs.push_back(substr);
        s.erase(0, pos + delimiter.length());
    }
    strs.push_back(s);
    return strs;
}

int ToInt(string str)
{
    istringstream iss(str);
    int num;
    iss >> num;

    return num;
}

int ReadInt(int low, int high)
{
    cout << "\nEnter number in range " << low << " - " << high << ": ";
    int value;

    cin >> value;

    if (low <= value && value <= high)
        return value;

    cout << "ERROR: invalid number...Try again\n";
    return ReadInt(low, high);
}

int ShowReadMenu(vector<string> choices)
{
    cout << "\nMenu:\n";
    for (int ch = 0; ch < (int) choices.size(); ++ch)
    {
        cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
    }
    return ReadInt(1, choices.size());
}
//////////////////////////////////////////////////////////////

class Question
{
private:
    int question_id;
    // To support thread. Each question look to a parent question
    // -1 No parent (first question in the thread)
    int parent_question_id;
    int from_user_id;
    int to_user_id;
    int is_anonymous_questions;	// 0 or 1
    string question_text;
    string answer_text;			// empty = not answered
public:
    Question():question_id(-1),parent_question_id(-1),from_user_id(-1),to_user_id(-1),is_anonymous_questions(1)
    { }

    Question(string line)
    {
        vector<string> substrs = SplitString(line);
        assert(substrs.size() == 7);

        question_id = ToInt(substrs[0]);
        parent_question_id = ToInt(substrs[1]);
        from_user_id = ToInt(substrs[2]);
        to_user_id = ToInt(substrs[3]);
        is_anonymous_questions = ToInt(substrs[4]);
        question_text = substrs[5];
        answer_text = substrs[6];
    }

    void setquestionId(int id)
    {
        this->question_id = id;
    }
    int getquestionId()const
    {
        return this->question_id;
    }
    void setParentId(int id)
    {
        this->parent_question_id = id;
    }
    int getParentId()const
    {
        return this->parent_question_id;
    }
    void setFromUserId(int id)
    {
        this->from_user_id = id;
    }
    int getFromUserId()const
    {
        return this->from_user_id;
    }
    void setToUserId(int id)
    {
        this->to_user_id = id;
    }
    int getToUserId()const
    {
        return this->to_user_id;
    }
    void setQuestionText(string text)
    {
        this->question_text = text;
    }
    string getQuestionText()const
    {
        return this->question_text;
    }
    void setQuestionAnswer(string text)
    {
        this->answer_text = text;
    }
    string getQuestionAnswer()const
    {
        return this->answer_text;
    }
    void set_is_anonymous_questions(int any)
    {
        this->is_anonymous_questions=any;
    }
    int get_is_anonymous_questions()const
    {
        this->is_anonymous_questions;
    }
    string ToString() const
    {
        ostringstream oss;
        oss << question_id << "," << parent_question_id << "," << from_user_id << "," << to_user_id << "," << is_anonymous_questions << "," << question_text << "," << answer_text;

        return oss.str();
    }
    void PrintToQuestion() const
    {
        string prefix = "";

        if (parent_question_id != -1)
            prefix = "\tThread: ";

        cout << prefix << "Question Id (" << question_id << ")";
        if (!is_anonymous_questions)
            cout << " from user id(" << from_user_id << ")";
        cout << "\t Question: " << question_text << "\n";

        if (answer_text != "")
            cout << prefix << "\tAnswer: " << answer_text << "\n";
        cout << "\n";
    }

    void PrintFromQuestion()const
    {
        cout << "Question Id (" << question_id << ")";
        if (!is_anonymous_questions)
            cout << " !AQ";

        cout << " to user id(" << to_user_id << ")";
        cout << "\t Question: " << question_text;

        if (answer_text != "")
            cout << "\tAnswer: " << answer_text << "\n";
        else
            cout << "\tNOT Answered YET\n";
    }

    void PrintFeedQuestion() const
    {
        if (parent_question_id != -1)
            cout << "Thread Parent Question ID (" << parent_question_id << ") ";

        cout << "Question Id (" << question_id << ")";
        if (!is_anonymous_questions)
            cout << " from user id(" << from_user_id << ")";

        cout << " To user id(" << to_user_id << ")";

        cout << "\t Question: " << question_text << "\n";
        if (answer_text != "")
            cout << "\tAnswer: " << answer_text <<"\n";
    }
};

class User
{
private:
    int user_id;		// internal system ID
    string user_name;
    string password;
    string name;
    string email;
    int allow_anonymous_questions;	// 0 or 1

    vector<int> questions_id_from_me;
    // From question id to list of questions IDS on this question (thread questions) - For this user
    map<int, vector<int>> questionid_questionidsThead_to_map;
public:
    User():user_id(-1),allow_anonymous_questions(-1)
    {
    }

    User(string line)
    {
        vector<string> substrs = SplitString(line);
        assert(substrs.size() == 6);

        user_id = ToInt(substrs[0]);
        user_name = substrs[1];
        password = substrs[2];
        name = substrs[3];
        email = substrs[4];
        allow_anonymous_questions = ToInt(substrs[5]);
    }
    void addQuestionIDUserid(int id)
    {
        questions_id_from_me.push_back(id);
    }
    void addquestionid_questionidsThead_to_map(int first, int id)
    {
        questionid_questionidsThead_to_map[first].push_back(id);
    }
    int getSizeOfquestionid_questionidsThead_to_map()
    {
        return questionid_questionidsThead_to_map.size();
    }
    int getSizequestions_id_from_me()
    {
        return questions_id_from_me.size();
    }
    void setUserId(int id)
    {
        this->user_id = id;
    }
    int getUserId()const
    {
        return this->user_id;
    }
    void setUserName(string name)
    {
        this->name = name;
    }
    string getUserName()const
    {
        return this->user_name;
    }
    void setPassword(string pass)
    {
        this->password = pass;
    }
    string getPassword()const
    {
        return this->password;
    }
    void setName(string name)
    {
        this->name = name;
    }
    string getName()const
    {
        return this->name;
    }
    void setEmail(string email)
    {
        this->email = email;
    }
    string getEmail()const
    {
        return this->email;
    }
    void setallow_anonymous_questions(int any)
    {
        this->allow_anonymous_questions = any;
    }
    int getallow_anonymous_questions()
    {
        return this->allow_anonymous_questions;
    }
    vector<int>& get_questions_id_from_me()
    {
        return this->questions_id_from_me;
    }
    map<int, vector<int>>& get_questionid_questionidsThead_to_map()
    {
        return this->questionid_questionidsThead_to_map;
    }
    string ToString()const
    {
        ostringstream oss;
        oss << user_id << "," << user_name << "," << password << "," << name << "," << email << "," << allow_anonymous_questions;

        return oss.str();
    }
    void Print()const
    {
        cout << "User " << user_id << ", " << user_name << " " << password << ", " << name << ", " << email << "\n";
    }
};

class QuestionsManager
{
private:
    // From question id to list of questions IDS on this question (thread questions) - All users
    map<int, vector<int>> questionid_questionidsThead_to_map;

    // Map the question id to question object. Let's keep one place ONLY with the object
    // When you study pointers, easier handling
    map<int, Question> questionid_questionobject_map;

    int last_id;
public:
    QuestionsManager():last_id(0)
    {
    }

    void LoadDatabase()
    {
        last_id = 0;
        questionid_questionidsThead_to_map.clear();
        questionid_questionobject_map.clear();

        vector<string> lines = ReadFileLines("questions.txt");
        for (auto &line : lines)
        {
            Question question(line);
            last_id = max(last_id, question.getquestionId());

            questionid_questionobject_map[question.getquestionId()] = question;

            if (question.getParentId() == -1)
                questionid_questionidsThead_to_map[question.getquestionId()].push_back(question.getquestionId());
            else
                questionid_questionidsThead_to_map[question.getParentId()].push_back(question.getquestionId());
        }
    }

    void FillUserQuestions(User &user)
    {
        user.get_questions_id_from_me().clear();
        user.get_questionid_questionidsThead_to_map().clear();

        for (const auto &pair : questionid_questionidsThead_to_map)  	// pair<int, vector<Question>>
        {
            for (const auto &question_id : pair.second)  		//  vector<Question>
            {

                // Get the question from the map. & means same in memory, DON'T COPY
                const Question &question = questionid_questionobject_map[question_id];

                if (question.getFromUserId() == user.getUserId())
                    user.addQuestionIDUserid(question.getquestionId());

                if (question.getToUserId() == user.getUserId())
                {
                    if (question.getParentId() == -1)
                        user.addquestionid_questionidsThead_to_map(question.getquestionId(),question.getquestionId());
                    else
                        user.addquestionid_questionidsThead_to_map(question.getParentId(),question.getquestionId());
                }
            }
        }
    }

    void PrintUserToQuestions(User &user)
    {
        cout << "\n";

        if (user.getSizeOfquestionid_questionidsThead_to_map() == 0)
            cout << "No Questions";

        for (auto &pair : user.get_questionid_questionidsThead_to_map())  		// pair<int, vector<Question>>
        {
            for (auto &question_id : pair.second)  		//  vector<Question>
            {

                // Get the question from the map. & means same in memory, DON'T COPY
                Question &question = questionid_questionobject_map[question_id];
                question.PrintToQuestion();
            }
        }
        cout << "\n";
    }

    void PrintUserFromQuestions( User &user)
    {
        cout << "\n";
        if (user.getSizequestions_id_from_me() == 0)
            cout << "No Questions";

        for (const auto &question_id : user.get_questions_id_from_me())  		//  vector<Question>
        {

            // Get the question from the map. & means same in memory, DON'T COPY
            Question &question = questionid_questionobject_map[question_id];
            question.PrintFromQuestion();
        }
        cout << "\n";
    }

    // Used in Answering a question for YOU.
    // It can be any of your questions (thread or not)
    int ReadQuestionIdAny(User &user)
    {
        int question_id;
        cout << "Enter Question id or -1 to cancel: ";
        cin >> question_id;

        if (question_id == -1)
            return -1;

        if (!questionid_questionobject_map.count(question_id))
        {
            cout << "\nERROR: No question with such ID. Try again\n\n";
            return ReadQuestionIdAny(user);
        }
        Question &question = questionid_questionobject_map[question_id];

        if (question.getToUserId() != user.getUserId())
        {
            cout << "\nERROR: Invalid question ID. Try again\n\n";
            return ReadQuestionIdAny(user);
        }
        return question_id;
    }

    // Used to ask a question on a specific thread for whatever user
    int ReadQuestionIdThread(const User &user)const
    {
        int question_id;
        cout << "For thread question: Enter Question id or -1 for new question: ";
        cin >> question_id;

        if (question_id == -1)
            return -1;

        if (!questionid_questionidsThead_to_map.count(question_id))
        {
            cout << "No thread question with such ID. Try again\n";
            return ReadQuestionIdThread(user);
        }
        return question_id;
    }

    void AnswerQuestion( User &user)
    {
        int question_id = ReadQuestionIdAny(user);

        if (question_id == -1)
            return;

        Question &question = questionid_questionobject_map[question_id];

        question.PrintToQuestion();

        if (question.getQuestionAnswer() != "")
            cout << "\nWarning: Already answered. Answer will be updated\n";

        cout << "Enter answer: ";	// if user entered comma, system fails :)
        string ans;
        getline(cin, ans);	// read last enter
        getline(cin, ans);
        question.setQuestionAnswer(ans);
    }

    void DeleteQuestion(User &user)
    {
        int question_id = ReadQuestionIdAny(user);

        if (question_id == -1)
            return;

        vector<int> ids_to_remove;	// to remove from questionid_questionobject_map

        // Let's see if thread or not. If thread, remove all of it
        if (questionid_questionidsThead_to_map.count(question_id))   // thread
        {
            ids_to_remove = questionid_questionidsThead_to_map[question_id];
            questionid_questionidsThead_to_map.erase(question_id);
        }
        else
        {
            ids_to_remove.push_back(question_id);

            // let's find in which thread to remove. Consistency is important when have multi-view
            for (auto &pair : questionid_questionidsThead_to_map)
            {
                vector<int> &vec = pair.second;
                for (int pos = 0; pos < (int) vec.size(); ++pos)
                {
                    if (question_id == vec[pos])
                    {
                        vec.erase(vec.begin() + pos);
                        break;
                    }
                }
            }

        }

        for (auto id : ids_to_remove)
        {
            questionid_questionobject_map.erase(id);
        }
    }

    void AskQuestion(User &user, pair<int, int> to_user_pair)
    {
        Question question;

        if (!to_user_pair.second)
        {
            cout << "Note: Anonymous questions are not allowed for this user\n";
            question.set_is_anonymous_questions(0);
        }
        else
        {
            cout << "Is anonymous questions?: (0 or 1): ";
            int num;
            cin >> num;
            question.set_is_anonymous_questions(num);
        }

        question.setParentId(ReadQuestionIdThread(user));

        cout << "Enter question text: ";	// if user entered comma, system fails :)
        string ans;
        getline(cin, ans);
        getline(cin, ans);
        question.setQuestionText(ans);

        question.setFromUserId(user.getUserId());
        question.setToUserId(to_user_pair.first);

        // What happens in 2 parallel sessions who asked question?
        // They are given same id. This is wrong handling :)
        question.setquestionId(++last_id);

        questionid_questionobject_map[question.getquestionId()] = question;

        if (question.getParentId() == -1)
            questionid_questionidsThead_to_map[question.getquestionId()].push_back(question.getquestionId());
        else
            questionid_questionidsThead_to_map[question.getParentId()].push_back(question.getquestionId());
    }

    void ListFeed()
    {
        for (auto &pair : questionid_questionobject_map)
        {
            Question &question = pair.second;

            if (question.getQuestionAnswer() == "")
                continue;

            question.PrintFeedQuestion();
        }
    }

    void UpdateDatabase()
    {
        vector<string> lines;

        for (auto &pair : questionid_questionobject_map)
            lines.push_back(pair.second.ToString());

        WriteFileLines("questions.txt", lines, false);
    }
};

class UsersManager
{
private:
    map<string, User> userame_userobject_map;
    User current_user;
    int last_id;
public:
    UsersManager():last_id(0) {	}
    void set_userame_userobject_map(string userName,User& user)
    {
        //userame_userobject_map[userName].
    }
    map<string, User>& get_userame_userobject_map()
    {
        return userame_userobject_map;
    }
    void setUser(User& user)
    {
        this->current_user = user;
    }
    User& getUser()
    {
        return this->current_user;
    }
    void setLastID(int id)
    {
        this->last_id = id;
    }
    int getLastLast()const
    {
        return this->last_id;
    }

    void LoadDatabase()
    {
        last_id = 0;
        userame_userobject_map.clear();

        vector<string> lines = ReadFileLines("users.txt");
        for (auto &line : lines)
        {
            User user(line);
            userame_userobject_map[user.getUserName()] = user;
            last_id = max(last_id, user.getUserId());
        }
    }

    void AccessSystem()
    {
        int choice = ShowReadMenu( { "Login", "Sign Up" });
        if (choice == 1)
            DoLogin();
        else
            DoSignUp();
    }

    void DoLogin()
    {
        LoadDatabase();	// in case user added from other parallel run

        while (true)
        {
            cout << "Enter user name & password: ";
            string userName,Password;
            cin >> userName >> Password;

            current_user.setUserName(userName);
            current_user.setPassword(Password);

            if (!userame_userobject_map.count(current_user.getUserName()))
            {
                cout << "\nInvalid user name or password. Try again\n\n";
                continue;
            }
            User user_exist = userame_userobject_map[current_user.getUserName()];

            if (current_user.getPassword() != user_exist.getPassword())
            {
                cout << "\nInvalid user name or password. Try again\n\n";
                continue;
            }
            current_user = user_exist;
            break;
        }
    }

    void DoSignUp()
    {
        while (true)
        {
            cout << "Enter user name. (No spaces): ";
            string userName;
            cin >> userName;
            current_user.setUserName(userName);

            if (userame_userobject_map.count(current_user.getUserName()))
                cout << "Already used. Try again\n";
            else
                break;
        }
        string pass,name,email;
        int allow;
        cout << "Enter password: ";
        cin >> pass;
        current_user.setPassword(pass);

        cout << "Enter name: ";
        cin >>name;
        current_user.setName(name);

        cout << "Enter email: ";
        cin >> email;
        current_user.setEmail(email);

        cout << "Allow anonymous questions? (0 or 1): ";
        cin >> allow;
        current_user.setallow_anonymous_questions(allow);

        // What happens in 2 parallel sessions if they signed up?
        // They are given same id. This is wrong handling :)
        current_user.setUserId(++last_id);
        userame_userobject_map[current_user.getUserName()] = current_user;

        UpdateDatabase(current_user);
    }

    void ListUsersNamesIds()
    {
        for (auto &pair : userame_userobject_map)
            cout << "ID: " << pair.second.getUserId() << "\t\tName: " << pair.second.getName() << "\n";
    }

    pair<int, int> ReadUserId()
    {
        int user_id;
        cout << "Enter User id or -1 to cancel: ";
        cin >> user_id;

        if (user_id == -1)
            return make_pair(-1, -1);

        for (auto &pair : userame_userobject_map)
        {
            if (pair.second.getUserId() == user_id)
                return make_pair(user_id, pair.second.getallow_anonymous_questions());
        }

        cout << "Invalid User ID. Try again\n";
        return ReadUserId();
    }

    void UpdateDatabase(User &user)
    {
        string line = user.ToString();
        vector<string> lines(1, line);
        WriteFileLines("users.txt", lines);
    }
};

class AskMeSystem
{
    UsersManager users_manager;
    QuestionsManager questions_manager;
public:

    void LoadDatabase(bool fill_user_questions = false)
    {
        users_manager.LoadDatabase();
        questions_manager.LoadDatabase();

        if (fill_user_questions)	// first time, waiting for login
            questions_manager.FillUserQuestions(users_manager.getUser());
    }

    void run()
    {
        LoadDatabase();
        users_manager.AccessSystem();
        questions_manager.FillUserQuestions(users_manager.getUser());

        vector<string> menu;
        menu.push_back("Print Questions To Me");
        menu.push_back("Print Questions From Me");
        menu.push_back("Answer Question");
        menu.push_back("Delete Question");
        menu.push_back("Ask Question");
        menu.push_back("List System Users");
        menu.push_back("Feed");
        menu.push_back("Logout");

        while (true)
        {
            int choice = ShowReadMenu(menu);
            LoadDatabase(true);

            if (choice == 1)
                questions_manager.PrintUserToQuestions(users_manager.getUser());
            else if (choice == 2)
                questions_manager.PrintUserFromQuestions(users_manager.getUser());
            else if (choice == 3)
            {
                questions_manager.AnswerQuestion(users_manager.getUser());
                questions_manager.UpdateDatabase();
            }
            else if (choice == 4)
            {
                questions_manager.DeleteQuestion(users_manager.getUser());
                // Let's build again (just easier, but slow)
                questions_manager.FillUserQuestions(users_manager.getUser());
                questions_manager.UpdateDatabase();
            }
            else if (choice == 5)
            {
                pair<int, int> to_user_pair = users_manager.ReadUserId();
                if (to_user_pair.first != -1)
                {
                    questions_manager.AskQuestion(users_manager.getUser(), to_user_pair);
                    questions_manager.UpdateDatabase();
                }
            }
            else if (choice == 6)
                users_manager.ListUsersNamesIds();
            else if (choice == 7)
                questions_manager.ListFeed();
            else
                break;
        }
        run();	// Restart again
    }
};

int main ()
{
    AskMeSystem service;
    service.run();
    return 0;
}
