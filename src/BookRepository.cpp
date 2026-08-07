#include "BookRepository.h"

void BookRepository::addBook(const Book & book) {
	books_.push_back(book);
}

Book * BookRepository::findByIsbn(const std::string & isbn) {
	for (auto & book : books_) {
		if (book.getIsbn() == isbn) {
			return &book;
		}
	}
	return nullptr; // not found
}

const std::vector<Book> & BookRepository::getAllBooks() const {
	return books_;
}

size_t BookRepository::size() const {
	return books_.size();
}
