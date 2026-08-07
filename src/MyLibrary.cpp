#include "MyLibrary.h"
#include "Member.h"

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
	if (!book) {
		return false;
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
