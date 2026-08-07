#include "Member.h"
#include "Book.h"
#include <algorithm>

Member::Member(const std::string & name, const std::string & memberId)
	: name_(name)
	, memberId_(memberId) {
}

std::string Member::getName() const {
	return name_;
}

std::string Member::getMemberId() const {
	return memberId_;
}

const std::vector<Book *> & Member::getBorrowedBooks() const {
	return borrowedBooks_;
}

bool Member::borrowBook(Book * book) {
	if (static_cast<int>(borrowedBooks_.size()) >= getMaxBooksAllowed()) {
		return false; // at limit, can't borrow more
	}
	borrowedBooks_.push_back(book);
	return true;
}

void Member::returnBook(Book * book) {
	auto it = std::find(borrowedBooks_.begin(), borrowedBooks_.end(), book);
	if (it != borrowedBooks_.end()) {
		borrowedBooks_.erase(it);
	}
}
