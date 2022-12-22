#include "clsLibrary.h"
#include <iostream>

//Author Section
void clsLibrary::add_author(clsAuthor &autohr)
{
    _authors.push_back(autohr);
}
void clsLibrary::remove_author(int id)
{
    bool is_found = false;
    for(auto it = _authors.begin() ; it != _authors.end() ; it++)
    {
        if((*it).getID() == id)
        {
            _authors.erase(it);
            is_found = true;
        }
    }

    if(!is_found)
    {
        cout << "Author with id " << id << " Not found!\n";
        return;
    }
}
void clsLibrary::print_author(int id)
{
    bool is_found = false;
    for(auto &auth: _authors)
    {
        if(auth.getID() == id)
        {
            std::cout << "Author with id " << auth.getID()<< " info" << "\n";
            std::cout << "Name   : " << auth.getName() << "\n";
            std::cout << "Phone  : " << auth.getPhone() << "\n";
            std::cout << "Email  : " << auth.getEmail() << "\n";
            std::cout << "----------------------------------------------------\n";
            is_found = true;
        }
    }
    if(!is_found)
    {
        std::cout << "Author with id " << id << " Not found!\n";
        return;
    }
}
void clsLibrary::print_author_books(int idAuthor)
{
    bool is_found = false;
    std::cout << "Book of Author ";
    for(auto &auth: _authors)
    {
        if(auth.getID() == idAuthor)
        {
            std::cout << auth.getName() << ":\n";
            is_found = true;
        }
    }

    if(!is_found)
    {
        std::cout << "with id " << idAuthor << " Not found!\n";
        return;
    }

    for(auto &b: _books)
    {
        if(b.getBookAuthor().getID() == idAuthor)
        {
        std::cout <<"- " <<b.getTitle() << "\n";
        }
    }
      std::cout << "----------------------------------------------------\n";
}


// Book Section
void clsLibrary::add_book(clsBook& book)
{
    _books.push_back(book);
}

void clsLibrary::print_book(int id)
{
    for(auto &b: _books)
    {
        if(b.getID() == id)
        {
            std::cout << "Book with id " << b.getID()  << " info"<< "\n";
            std::cout << "Title            : " << b.getTitle() << "\n";
            std::cout << "Version          : " << b.getVersion() << "\n";
            std::cout << "Publishing date  : " << b.getPublishDate() << "\n";
            std::cout << "Author In " << b.getBookAuthor().getName() << "\n";
            std::cout << "----------------------------------------------------\n";
        }
    }

}
