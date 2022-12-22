#include <bits/stdc++.h>

#include "clsAuthor.h"
#include "clsBook.h"
#include "clsLibrary.h"

using namespace std;


int main()
{

    clsAuthor author1("Mhamad", "+96170123456", "mhamad@gmail.com");
    clsAuthor author2("Salem",  "+9664021833",  "salem@gmail.com");
    clsAuthor author3("Rola",   "+9631249392",  "rola@gmail.com");

    clsBook book1("Learn Java", "12-20-2019", 1, author1);
    clsBook book2("Learn HTML", "8-5-2018", 3, author1);
    clsBook book3("PHP for beginners", "10-2-2019", 1, author2);
    clsBook book4("C# for dummies", "12-20-2019", 1, author3);


    clsLibrary library;

    library.add_author(author1);
    library.add_author(author2);
    library.add_author(author3);

    library.add_book(book1);
    library.add_book(book2);
    library.add_book(book3);
    library.add_book(book4);


    library.print_author(1);
    library.print_author(2);
    library.print_author(3);

    library.print_book(1);
    library.print_book(2);
    library.print_book(3);
    library.print_book(4);

    library.print_author_books(1);
    library.print_author_books(2);
    library.print_author_books(3);


    library.remove_author(2);
    library.print_author(2);
       library.print_author_books(2);
    return 0;
}
