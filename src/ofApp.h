#pragma once
#include "Member.h"
#include "MyLibrary.h"
#include "ofMain.h"
#include <memory>
#include <string>
#include <vector>

enum class InputMode {
	NONE,
	ADD_BOOK_TITLE,
	ADD_BOOK_AUTHOR,
	ADD_BOOK_ISBN,
	ADD_MEMBER_NAME,
	ADD_MEMBER_TYPE,
	BORROW_ISBN,
	BORROW_MEMBER_ID,
	RETURN_ISBN,
	RETURN_MEMBER_ID
};

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key) { }
	void mouseMoved(int x, int y) { }
	void mouseDragged(int x, int y, int button) { }
	void mousePressed(int x, int y, int button) { }
	void mouseReleased(int x, int y, int button) { }
	void windowResized(int w, int h) { }

private:
	void startMode(InputMode newMode, const std::string & newPrompt);
	void handleEnter();
	float drawBookList(float x, float y);
	void drawMemberList(float x, float y);
	std::string findBorrowerName(const std::string & isbn);

	MyLibrary library;
	std::vector<std::unique_ptr<Member>> members; // ofApp owns members; MyLibrary only associates via pointers

	InputMode mode = InputMode::NONE;
	std::string inputBuffer;
	std::string prompt;
	std::string statusMessage;

	const std::string kInstructions = "A: add book | M: add member | B: borrow | R: return";

	std::string tempTitle, tempAuthor, tempMemberName, tempIsbn;
};
