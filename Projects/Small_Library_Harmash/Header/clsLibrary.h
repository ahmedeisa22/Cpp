#ifndef CLSLIBRARY_H
#define CLSLIBRARY_H

#include "clsAuthor.h"
#include "clsBook.h"
#include <vector>

class clsLibrary
{
private:
    vector<clsAuthor> _authors;
    vector<clsBook> _books;
public:

    void add_author(const clsAuthor&);
    void remove_author(int);
    void print_author(int);
    void print_author_books(int);
    void add_book(const clsBook&);
    void remove_book();
    void print_book(int);
};

#endif // CLSLIBRARY_H
