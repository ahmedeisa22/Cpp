#include "clsBook.h"

int clsBook::_idIncrementer = 1;

clsBook::clsBook()
{
    this->_id = _idIncrementer++;
    this->_version = 0;
}

clsBook::clsBook(string title,string publish, int version, clsAuthor& auth):
    _title(title),_publishing_date(publish),_version(version),_author(auth)
{
    this->_id = _idIncrementer++;
}

int clsBook::getID()
{
    return this->_id;
}
void clsBook::setTile(string title)
{
    this->_title = title;
}
string clsBook::getTitle()
{
    return this->_title;
}
void clsBook::setPublishDate(string date)
{
    this->_publishing_date = date;
}
string clsBook::getPublishDate()
{
    return this->_publishing_date;
}

void clsBook::setVersion(int version)
{
    this->_version = version;
}
int clsBook::getVersion()
{
   return this->_version;
}
void clsBook::setBookAuthor(clsAuthor& author)
{
    this->_author = author;
}
clsAuthor clsBook::getBookAuthor()
{
    return this->_author;
}
