#include "ofApp.h"
#include "PremiumMember.h"
#include "RegularMember.h"

void ofApp::setup() {
	ofBackground(20);
	ofSetWindowTitle("Library Management System");
	statusMessage = ""; // no status yet
}

void ofApp::update() { }

void ofApp::draw() {
	ofSetColor(255);
	ofDrawBitmapString("Library Management System", 20, 20);
	ofDrawBitmapString(kInstructions, 20, 40);

	if (!statusMessage.empty()) {
		ofSetColor(150, 200, 255);
		ofDrawBitmapString(statusMessage, 20, 58);
	}

	if (mode != InputMode::NONE) {
		ofSetColor(255, 220, 100);
		ofDrawBitmapString(prompt + inputBuffer + "_", 20, 76);
	}

	float afterBooks = drawBookList(20, 100);
	drawMemberList(20, afterBooks + 20); // starts below books, same x now
}

float ofApp::drawBookList(float x, float y) {
	ofSetColor(200);
	ofDrawBitmapString("Books:", x, y);
	float lineY = y + 20;
	for (const auto & book : library.getAllBooks()) {
		std::string borrower = findBorrowerName(book.getIsbn());
		std::string line = book.getTitle() + " by " + book.getAuthor() + " [" + book.getIsbn() + "]";
		if (borrower.empty()) {
			ofSetColor(120, 220, 120);
			ofDrawBitmapString(line + " - available", x, lineY);
		} else {
			ofSetColor(220, 100, 100);
			ofDrawBitmapString(line + " - borrowed by " + borrower, x, lineY);
		}
		lineY += 16;
	}
	return lineY; // report where the list ended
}

void ofApp::drawMemberList(float x, float y) {
	ofSetColor(200);
	ofDrawBitmapString("Members:", x, y);
	float lineY = y + 20;
	for (const auto & m : members) {
		bool isPremium = dynamic_cast<PremiumMember *>(m.get()) != nullptr;
		std::string type = isPremium ? "Premium" : "Regular";
		std::string line = m->getName() + " [" + m->getMemberId() + "] (" + type + ") - "
			+ ofToString(m->getBorrowedBooks().size()) + "/" + ofToString(m->getMaxBooksAllowed());
		ofSetColor(255);
		ofDrawBitmapString(line, x, lineY);
		lineY += 16;
	}
}

std::string ofApp::findBorrowerName(const std::string & isbn) {
	for (const auto & m : members) {
		for (const auto * b : m->getBorrowedBooks()) {
			if (b->getIsbn() == isbn) return m->getName();
		}
	}
	return "";
}

void ofApp::startMode(InputMode newMode, const std::string & newPrompt) {
	mode = newMode;
	prompt = newPrompt;
	inputBuffer.clear();
}

void ofApp::keyPressed(int key) {
	if (mode == InputMode::NONE) {
		if (key == 'a' || key == 'A')
			startMode(InputMode::ADD_BOOK_TITLE, "Book title: ");
		else if (key == 'm' || key == 'M')
			startMode(InputMode::ADD_MEMBER_NAME, "Member name: ");
		else if (key == 'b' || key == 'B')
			startMode(InputMode::BORROW_ISBN, "Borrow - ISBN: ");
		else if (key == 'r' || key == 'R')
			startMode(InputMode::RETURN_ISBN, "Return - ISBN: ");
		return;
	}

	if (mode == InputMode::ADD_MEMBER_TYPE) {
		if (key == 'r' || key == 'R') {
			members.push_back(std::make_unique<RegularMember>(tempMemberName, "M" + ofToString(members.size() + 1)));
			library.registerMember(members.back().get());
			statusMessage = "Added Regular member: " + tempMemberName;
			mode = InputMode::NONE;
		} else if (key == 'p' || key == 'P') {
			members.push_back(std::make_unique<PremiumMember>(tempMemberName, "M" + ofToString(members.size() + 1)));
			library.registerMember(members.back().get());
			statusMessage = "Added Premium member: " + tempMemberName;
			mode = InputMode::NONE;
		}
		return;
	}

	if (key == OF_KEY_RETURN)
		handleEnter();
	else if (key == OF_KEY_BACKSPACE) {
		if (!inputBuffer.empty()) inputBuffer.pop_back();
	} else if (key >= 32 && key <= 126)
		inputBuffer += static_cast<char>(key);
}

void ofApp::handleEnter() {
	switch (mode) {
	case InputMode::ADD_BOOK_TITLE:
		tempTitle = inputBuffer;
		startMode(InputMode::ADD_BOOK_AUTHOR, "Book author: ");
		break;
	case InputMode::ADD_BOOK_AUTHOR:
		tempAuthor = inputBuffer;
		startMode(InputMode::ADD_BOOK_ISBN, "Book ISBN: ");
		break;
	case InputMode::ADD_BOOK_ISBN: {
		Book newBook(tempTitle, tempAuthor, inputBuffer);
		library.addBook(&newBook);
		statusMessage = "Added book: " + tempTitle;
		mode = InputMode::NONE;
		break;
	}
	case InputMode::ADD_MEMBER_NAME:
		tempMemberName = inputBuffer;
		prompt = "Type (R=Regular, P=Premium): ";
		inputBuffer.clear();
		mode = InputMode::ADD_MEMBER_TYPE;
		break;
	case InputMode::BORROW_ISBN:
		tempIsbn = inputBuffer;
		startMode(InputMode::BORROW_MEMBER_ID, "Borrow - Member ID: ");
		break;
	case InputMode::BORROW_MEMBER_ID: {
		Member * target = nullptr;
		for (auto & m : members)
			if (m->getMemberId() == inputBuffer) target = m.get();
		if (target && library.borrowBook(tempIsbn, target))
			statusMessage = target->getName() + " borrowed " + tempIsbn;
		else
			statusMessage = "Borrow failed - check ISBN, member ID, or limit";
		mode = InputMode::NONE;
		break;
	}
	case InputMode::RETURN_ISBN:
		tempIsbn = inputBuffer;
		startMode(InputMode::RETURN_MEMBER_ID, "Return - Member ID: ");
		break;
	case InputMode::RETURN_MEMBER_ID: {
		Member * target = nullptr;
		for (auto & m : members)
			if (m->getMemberId() == inputBuffer) target = m.get();
		if (target && library.returnBook(tempIsbn, target))
			statusMessage = target->getName() + " returned " + tempIsbn;
		else
			statusMessage = "Return failed - check ISBN, member ID, or ownership";
		mode = InputMode::NONE;
		break;
	}
	default:
		break;
	}
}
