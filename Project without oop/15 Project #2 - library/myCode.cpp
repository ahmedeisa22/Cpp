#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

struct User
{
    int id;
    string name;
    vector<int> borrowedBooks;
    void ReadUserInfo()
    {
        cout << "Enter user name & national id: ";
        cin >> name >> id;
    }

    bool is_id_find(int id)
    {
        for(int i = 0 ; i < borrowedBooks.size() ; i++)
            if(borrowedBooks[i] == id) return true;
        return false;
    }
    void delete_book_by_id(int id){
     for(int i = 0 ; i < borrowedBooks.size() ; i++)
            if(borrowedBooks[i] == id) borrowedBooks.erase(borrowedBooks.begin()+i);
    }
    void printUser()
    {
        cout << "User " << name << " id " << id << "  ";
        cout << "Borrowed books id: ";
        for(int i = 0 ; i < borrowedBooks.size() ; i++)
            cout << borrowedBooks[i] << " ";
        cout << endl;
    }
};
struct Book
{
    int id;
    string name;
    int total_quantity;
    int total_borrow;
    Book()
    {
        total_quantity = total_borrow = 0;
    }
    void ReadBookInfo()
    {
        cout << "Enter Book INFO: id & name & total quantity: ";
        cin >> id >> name >> total_quantity;
    }

    void printBookInfo()
    {
        cout << "id = " << id << "  name =  " << name << " total_quantity =  "
             << total_quantity << " total_borrowed = " << total_borrow << endl;
    }
};
bool sort_books_by_id(Book &b1,Book &b2)
{
    return b1.id < b2.id;
}
bool sort_books_by_name(Book &b1,Book &b2)
{
    return b1.name < b2.name;
}

struct Library_System
{
    Book books[100];
    User users[100];
    int counterBooks;
    int counterUsers;
    Library_System()
    {
        counterBooks = counterUsers = 0;
    }

    void print_Menu()
    {
        cout << "Library Menu: \n";
        cout << "1) add_book\n";
        cout << "2) search_books_by_prefix\n";
        cout << "3) print_who_borrowed_book_by_name\n";
        cout << "4) print_Library_by_id\n";
        cout << "5) print_Library_by_name\n";
        cout << "6) add users\n";
        cout << "7) user_borrow_book\n";
        cout << "8) user_return_book\n";
        cout << "9) print_usres\n";
        cout << "10) Exit\n";
    }
    int menu()
    {
        int ch = -1;
        while(ch == -1)
        {
            cout << "\nEnter your menu choice [1 - 10]: ";
            cin >> ch;
            if(!(ch >= 1 && ch <= 10))
            {
                cout << "Invalid input please enter number in [1 - 10]\n";
                ch = -1;
            }
        }
        return ch;
    }
    void printUsers()
    {
        cout << endl;
        for(int i = 0 ; i < counterUsers ; i++)
            users[i].printUser();
    }
    void printBooks()
    {
        cout << endl;
        for(int i = 0 ; i < counterBooks ; i++)
            books[i].printBookInfo();
    }
    void print_library_by_id()
    {
        sort(books,books+counterBooks,sort_books_by_id);
        printBooks();
    }
    void print_library_by_name()
    {
        sort(books,books+counterBooks,sort_books_by_name);
        printBooks();
    }
    int get_indx_User_by_name(string name)
    {
        for(int i = 0 ; i < counterUsers ; i++)
        {
            if(users[i].name == name)
                return i;
        }
        return -1;
    }
    int get_indx_Book_by_name(string name)
    {
        for(int i = 0 ; i < counterBooks ; i++)
        {
            if(books[i].name == name)
                return i;
        }
        return -1;
    }
    void user_borrow_book()
    {
        string userName, bookName;
        cout << "Enter user name & book name: ";
        cin >> userName >> bookName;

        int indxUser = get_indx_User_by_name(userName);
        int indxBook = get_indx_Book_by_name(bookName);

        if(indxUser == -1 || indxBook == -1)
        {
            cout << "Sorry this is invalid user or books\n";
            return;
        }

        if( books[indxBook].total_borrow <  books[indxBook].total_quantity)
        {
            books[indxBook].total_borrow++;
        }
        else
        {
            cout << "Sorry we cann't borrow this book\n";
            return;
        }

        // add id books to user
        users[indxUser].borrowedBooks.push_back(books[indxBook].id);
    }
    bool is_prefix(string name,string pre)
    {
        for(int i = 0 ; i < pre.size() ; i++)
        {
            if(name[i] != pre[i]) return false;
        }
        return true;
    }
    void search_books_by_prefix()
    {
        string prefix;
        cout << "Enter book name prefix: ";
        cin >> prefix;
        bool flag = false;
        for(int i = 0 ; i < counterBooks ; i++)
        {
            if(is_prefix(books[i].name,prefix))
            {
                flag = true;
                cout << books[i].name << "\n";
            }
        }

        if(!flag)
        {
            cout << "No books with such prefix\n";
        }
    }
    void print_who_borrowed_book_by_name()
    {
        string bookName;
        cout << "\n Enter book Name: ";
        cin >> bookName;
        int indxBook = get_indx_Book_by_name(bookName);
        if(indxBook == -1)
        {
            cout << "Invalid book name\n";
            return;
        }

        int BookId = books[indxBook].id;

        for(int i = 0 ; i < counterUsers ; i++)
        {
            if(users[i].is_id_find(BookId))
            {
                cout << users[i].name << "\n";
            }
        }
    }
    void user_return_book()
    {
        string userName,bookName;
        cout << "\n Enter userName & book Name: ";
        cin >> userName >> bookName;

        int indxUser = get_indx_User_by_name(userName);
        int indxBook = get_indx_Book_by_name(bookName);

        if(indxUser == -1 || indxBook == -1)
        {
            cout << "Sorry this is invalid user or books\n";
            return;
        }

        int BookId = books[indxBook].id;
        books[indxBook].total_borrow--;

        users[indxUser].delete_book_by_id(BookId);
    }
    void run_system()
    {
        // show menu only one
        print_Menu();
        while(true)
        {
            int ch = menu();

            if(ch == 1)
                books[counterBooks++].ReadBookInfo();
            else if(ch == 2)
                search_books_by_prefix();
            else if(ch == 3)
                print_who_borrowed_book_by_name();
            else if(ch == 4)
                print_library_by_id();
            else if(ch == 5)
                print_library_by_name();
            else if(ch == 6)
                users[counterUsers++].ReadUserInfo();
            else if(ch == 7)
                user_borrow_book();
            else if(ch == 8)
                user_return_book();
            else if(ch == 9)
                printUsers();
            else
                break;
        }
    }
};
int main()
{
    Library_System lib;
    lib.run_system();
    return 0;
}

/*

1   100 math4 3
1   101 math2 5
1   102 math1 4
1   103 math3 2
1   201 prog1 5
1   201 prog2 3

4
5

6 mostafa     30301
6 ali		  50501
6 noha        70701
6 ashraf      90901

7 mostafa math1
7 mostafa math2
7 mostafa math3
7 ali math1
7 ali math2
7 noha math1
7 noha math3
7 noha prog2

4
9

2 ma
2 pro
2 machine

3 math1
3 math2
3 machine

4
9
8 mostafa math1
4
9



10



 */
