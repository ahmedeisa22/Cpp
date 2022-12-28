#pragma warning(disable: 4996)
#include<bits/stdc++.h>
using namespace std;

class Admin
{
private:
    string _UserName;
    string _Password;
    string _Name;
    string _Email;
public:
    Admin() = default;
    //Admin(const Admin& admin) = delete;
    //void operator=(const Admin& admin) = delete;


    Admin(string userName,string password,string name,string email)
        :_UserName(userName),_Password(password),_Name(name),_Email(email)
    {}

    void viewProfile()
    {
        cout << "\nName  : " <<getName() << "\n";
        cout << "Email   : " << getEmail() << "\n";
        cout << "UserName: " << _UserName << "\n";
    }
    // setters & getters
    void setUserName(const string userName)
    {
        this->_UserName = userName;
    }
    const string getUserName()const
    {
        return this->_UserName;
    }
    void setPassword(const string password)
    {
        this->_Password = password;
    }
    const string getPassword()const
    {
        return this->_Password;
    }
    void setName(const string name)
    {
        this->_Name = name;
    }
    const string getName()const
    {
        return this->_Name;
    }
    void setEmail(const string email)
    {
        this->_Email = email;
    }
    const string getEmail()const
    {
        return this->_Email;
    }
};

class Customer
{
private:
    string _UserName;
    string _Password;
    string _Name;
    string _Email;
    map<int,string> _seasions;
    static int countSeasion;
public:
    Customer() = default;
    Customer(string userName,string password,string name,string email)
        :_UserName(userName),_Password(password),_Name(name),_Email(email)
    {}
    //Customer(const Customer& customer) = delete;
    void operator=(const Customer& customer) = delete;

    void ReadCustomer()
    {
        cout << "Enter UserName (no spaces): ";

        cin >> _UserName;

        cout << "Enter Password (no spaces): ";
        cin >> _Password;

        cout << "Enter Name (no spaces): ";
        cin >> _Name;

        cout << "Enter Email (no spaces): ";
        cin >> _Email;
    }
    void viewProfile()
    {
        cout << "\nName  : " <<getName() << "\n";
        cout << "Email   : " << getEmail() << "\n";
        cout << "UserName: " << _UserName << "\n";
    }
    void setSeasion(int id,string name,int currentPage,int pages)
    {

        time_t t = time(0);
        char* dt = ctime(&t);
        string res = "";
        res+= to_string(id)+ ": " + name + ": "+to_string(currentPage)+"/"+to_string(pages) + " - " + dt;

        _seasions[id]=res;
    }
    void printSeasion()
    {
        for(auto& se : _seasions)
            cout << se.second << "\n";
    }
    // setters & getters
    void setUserName(const string userName)
    {
        this->_UserName = userName;
    }
    const string getUserName()const
    {
        this->_UserName;
    }
    void setPassword(const string password)
    {
        this->_Password = password;
    }
    const string getPassword()const
    {
        return this->_Password;
    }
    void setName(const string name)
    {
        this->_Name = name;
    }
    const string getName()const
    {
        return this->_Name;
    }
    void setEmail(const string email)
    {
        this->_Email = email;
    }
    const string getEmail()const
    {
        return this->_Email;
    }
    map<int,string>& getSeasions()
    {
        return this->_seasions;
    }
};

class Book
{
private:
    int _id;
    int _pages;
    int _CurrentPage;
    string _name;
    map<int,string> _content;

    static int increament;

public:
    Book():_pages(5),_CurrentPage(1)
    {
    }

    Book(int pages, string name):
        _pages(pages),_name(name),_CurrentPage(1)
    {
        _id = ++increament;
    }
    void AddBook()
    {
        _id= ++increament;
        cout << "BookName: ";
        cin >> _name;

        cout << "How Many Page: ";
        cin >> _pages;

        cout << "Enter Content:\n";
        for(int i = 1 ; i <= _pages ; i++)
        {
            cout << "Enter Page Number #"<< i << " Content: ";
            cin >> _content[i];
        }

    }
    void fillContent()
    {
        char ch[] = {' ','A','B','C','D','E','F','H','J','K'};
        string em = " ";
        _name = em+_name;
        for(int i =1; i <= _pages ; i++)
        {

            string cont;
            cont += ch[i];
            cont+= _name;
            _content[i]= cont;
        }
    }
    void viewBook()
    {
        cout << "\nCurrent Page  : " <<_CurrentPage << "/"<< _pages<<"\n";
        cout <<  _content[_CurrentPage] << "\n";

    }
    void NextPage()
    {
        if( _CurrentPage < _pages)
        {

            this->_CurrentPage++;
            return;
        }
        cout << "Wrong Page\n";

        return;
    }
    void PrevPage()
    {
        if(_CurrentPage >1 )
        {

            this->_CurrentPage--;
            return;
        }
        cout << "Wrong Page\n";

        return;
    }

    // setters & getters
    int getid()const
    {
        return this->_id;
    }
    void setPages(int pages)
    {
        this->_pages = pages;
    }
    int getPages()const
    {
        return this->_pages;
    }
    void setCurrentPage(int curr)
    {
        this->_CurrentPage = curr;
    }
    int getCurrentPage()const
    {
        return this->_CurrentPage;
    }
    void setName(const string& Name)
    {
        this->_name = Name;
    }
    const string& getName()const
    {
        return this->_name;
    }

    const  map<int,string>&  getContent()const
    {
        return this->_content;
    }
};
int Book::increament = 0;
int Customer::countSeasion = 0;
class OnlineReader_system
{
    vector<Customer> customers;
    vector<Book> books;
    Customer currentCustomer;
    Book currentbook;
    Admin admin;
public:
    OnlineReader_system()
    {
        loadBooks();
        admin= Admin("eissa","222","ahmed Adel Eissa","eisa88667@gmail.com");
    }
    void loadBooks()
    {

        Book b1(5,"C++");
        b1.fillContent();
        books.push_back(b1);

        Book b2(5,"Algorithms");
        b2.fillContent();
        books.push_back(b2);

        Book b3(5,"Data Structure");
        b3.fillContent();
        books.push_back(b3);


    }


    int ReadInt(int from, int to)
    {
        cout << "\nEnter Number in Range " << from << " - " << to << "\n";
        int num;
        cin >> num;

        if(num >= from && num <= to)
            return num;
        cout << "ERROR: invalid number...Try again\n";
        ReadInt(from,to);
    }
    int ShowReadMenu(vector<string> menu)
    {
        cout << "\nMenu:\n";
        for(int i = 0 ; i < (int)menu.size() ; i++)
            cout <<  i+1 <<": " << menu[i] <<"\n";

        return ReadInt(1,menu.size());
    }
    // view
    void AccessSystem()
    {
        while(true)
        {
            int choice = ShowReadMenu({"Login","SignUp"});

            if(choice == 1)
            {
                Login();
            }
            else
            {
                SignUp();
            }
        }
    }
    void Login()
    {
        while(true)
        {
            string userName,Pass;
            cout << "Enter UserName: ";
            cin >> userName;

            if(userName != admin.getUserName())
            {
                cout << "\nInvalid userName or Password please try again!\n";
                continue;
            }
            cout << "Enter Password: ";
            cin >> Pass;
            if(Pass != admin.getPassword())
            {
                cout << "\nInvalid userName or Password please try again!\n";
                continue;
            }
            break;
        }
        viewAdmin();
    }
    void viewAdmin()
    {
        while(true)
        {
            cout << "\n\nHello " << admin.getName() << " | Admin View\n";
            int choice = ShowReadMenu({"View Profile",
                                       "Add Book",
                                       "LogOut"
                                      });

            if(choice == 1)
                admin.viewProfile();
            else if(choice == 2)
            {
                currentbook.AddBook();
                books.push_back(currentbook);
            }
            else
                break;

        }

    }
    void SignUp()
    {
        currentCustomer.ReadCustomer();
        // add it to system
        customers.push_back(currentCustomer);
        viewUser();
    }

    void viewUser()
    {
        while(true)
        {
            cout << "\n\nHello " << currentCustomer.getName() << " | User View\n";
            int choice = ShowReadMenu({"View Profile",
                                       "List & Select From My Reading History",
                                       "List & Select From Available books"
                                      });

            if(choice == 1)
                currentCustomer.viewProfile();
            else if(choice == 2)
            {
                currentCustomer.printSeasion();
                SelectMyReadingHistory();
            }
            else if(choice == 3)
                SelectAvailableBook();
            else
                break;

        }
    }

    Book& searchBookById(int id)
    {
        for(auto& book : books)
        {
            if(book.getid() == id)
                return book;
        }
    }
    void SelectAvailableBook()
    {

        cout << "\nOur current Book collection\n";
        for(auto& book : books)
            cout << book.getid() << " " << book.getName() << "\n";

        cout << "\nWhich book to read? ";
        int choice = ReadInt(1,books.size());

        currentbook = searchBookById(choice);
        currentbook.viewBook();
        bookOperation();
    }

    void bookOperation()
    {
        while(true)
        {

            int choice2 = ShowReadMenu({"Next Page","Previous Page","Stop Reading"});

            if(choice2 == 1)
            {
                currentbook.NextPage();
                currentbook.viewBook();
            }
            else if(choice2 == 2)
            {
                currentbook.PrevPage();
                currentbook.viewBook();
            }
            else
            {
                currentCustomer.setSeasion(currentbook.getid(),currentbook.getName(),currentbook.getCurrentPage(),currentbook.getPages());

                for(auto it = 0 ; it < books.size() ; it++)
                {
                    if(currentbook.getid() == books[it].getid())
                    {
                        books.erase(books.begin()+it);
                    }
                }
                books.push_back(currentbook);

                break;
            }

        }
    }

    void SelectMyReadingHistory()
    {
        cout << "\nWhich seasion to open: \n";
        int choice = ReadInt(1,currentCustomer.getSeasions().size());
        //cout << "Number (id)"<<currentCustomer.getSeasions() << endl;
        currentbook= searchBookById(choice);
        currentbook.viewBook();
        bookOperation();
    }

};

int main ()
{
    OnlineReader_system sys;
    sys.AccessSystem();

    return 0;
}
