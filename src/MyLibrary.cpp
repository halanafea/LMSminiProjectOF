#include "MyLibrary.h"
#include "Member.h"
#include <algorithm>

void MyLibrary::addBook(Book * book) {
	if (book) {
		bookRepository_.addBook(*book); // copies book data into the repository
	}
}

bool MyLibrary::borrowBook(const std::string & isbn, Member * member) {
	if (!member) {
		return false;
	}

	Book * book = bookRepository_.findByIsbn(isbn);
	if (!book || book->isBorrowed()) {
		return false; // doesn't exist, or already out
	}

	if (!member->borrowBook(book)) {
		return false; // member is at their borrow limit
	}

	book->setBorrowed(true);
	return true;
}

bool MyLibrary::returnBook(const std::string & isbn, Member * member) {
	if (!member) {
		return false;
	}

	Book * book = bookRepository_.findByIsbn(isbn);
	if (!book || !book->isBorrowed()) {
		return false; // doesn't exist, or isn't currently out at all
	}

	const auto & memberBooks = member->getBorrowedBooks();
	bool memberHasThisBook = std::find(memberBooks.begin(), memberBooks.end(), book) != memberBooks.end();
	if (!memberHasThisBook) {
		return false; // this member never borrowed this book - reject the return
	}

	member->returnBook(book);
	book->setBorrowed(false);
	return true;
}

void MyLibrary::registerMember(Member * member) {
	members_.push_back(member);
}

size_t MyLibrary::getBookCount() const {
	return bookRepository_.size();
}

// MyLibrary.cpp - add
const std::vector<Book> & MyLibrary::getAllBooks() const {
	return bookRepository_.getAllBooks();
}
