#pragma once
#include <string>

class Book;
class Member;

class AbstractLibrary {
public:
	virtual ~AbstractLibrary() = default;

	// Pure virtual methods - no implementation, subclasses MUST define these
	virtual void addBook(Book * book) = 0;
	virtual bool borrowBook(const std::string & isbn, Member * member) = 0;
	virtual bool returnBook(const std::string & isbn, Member * member) = 0;
};
#pragma once
