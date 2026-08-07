#pragma once
#include <string>
#include <vector>

class Book; // forward declaration - avoids needing full Book.h here

class Member {
public:
	Member(const std::string & name, const std::string & memberId);
	virtual ~Member() = default;

	// Getters
	std::string getName() const;
	std::string getMemberId() const;
	const std::vector<Book *> & getBorrowedBooks() const;

	// Pure virtual: forces every subclass to define its own limit
	virtual int getMaxBooksAllowed() const = 0;

	// Shared borrowing logic (uses getMaxBooksAllowed() polymorphically)
	virtual bool borrowBook(Book * book);
	virtual void returnBook(Book * book);

protected:
	std::string name_;
	std::string memberId_;
	std::vector<Book *> borrowedBooks_; // association - Member doesn't own these Books
};

