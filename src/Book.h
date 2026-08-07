#pragma once
#include <string>

class Book {
public:
	Book(const std::string & title, const std::string & author, const std::string & isbn);

	// Getters
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getIsbn() const;
	bool isBorrowed() const;

	// Setters
	void setTitle(const std::string & title);
	void setAuthor(const std::string & author);
	void setIsbn(const std::string & isbn);
	void setBorrowed(bool borrowed);

private:
	std::string title_;
	std::string author_;
	std::string isbn_;
	bool borrowed_ = false;
};
