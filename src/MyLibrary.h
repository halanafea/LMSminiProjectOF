#pragma once
#include "AbstractLibrary.h"
#include "BookRepository.h"
#include <string>
#include <vector>

class Member;

class MyLibrary : public AbstractLibrary {
public:
	// AbstractLibrary interface implementation
	void addBook(Book * book) override;
	bool borrowBook(const std::string & isbn, Member * member) override;
	bool returnBook(const std::string & isbn, Member * member) override;

	// Association - library knows about members, doesn't own them
	void registerMember(Member * member);

	size_t getBookCount() const;

	const std::vector<Book> & getAllBooks() const;

private:
	BookRepository bookRepository_; // Composition - owns book storage
	std::vector<Member *> members_; // Association - non-owning references
};
#pragma once
