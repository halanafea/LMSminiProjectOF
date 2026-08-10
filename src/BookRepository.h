#pragma once
#include "Book.h"
#include <string>
#include <vector>

class BookRepository {
public:
	void addBook(const Book & book);
	Book * findByIsbn(const std::string & isbn);
	const std::vector<Book> & getAllBooks() const;
	size_t size() const;

private:
	std::vector<Book> books_;
};

