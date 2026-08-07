
#include "Book.h"
#include "ofApp.h"
#include "RegularMember.h"
#include "PremiumMember.h"
#include "BookRepository.h"
//--------------------------------------------------------------
void ofApp::setup(){
	//Book b("1984", "George Orwell", "978-0451524935");
	//std::cout << b.getTitle() << " by " << b.getAuthor() << std::endl;
	/* Book b1("1984", "George Orwell", "978-0451524935");
	Book b2("Brave New World", "Aldous Huxley", "978-0060850524");
	Book b3("Fahrenheit 451", "Ray Bradbury", "978-1451673319");
	Book b4("Animal Farm", "George Orwell", "978-0451526342");

	RegularMember reg("Alice", "M001");
	std::cout << "Alice borrows b1: " << reg.borrowBook(&b1) << std::endl;
	std::cout << "Alice borrows b2: " << reg.borrowBook(&b2) << std::endl;
	std::cout << "Alice borrows b3: " << reg.borrowBook(&b3) << std::endl;
	std::cout << "Alice borrows b4 (should fail, limit 3): " << reg.borrowBook(&b4) << std::endl;

	PremiumMember prem("Bob", "M002");
	std::cout << "Bob borrows b4: " << prem.borrowBook(&b4) << std::endl;*/

	BookRepository repo;
	repo.addBook(Book("1984", "George Orwell", "978-0451524935"));
	repo.addBook(Book("Brave New World", "Aldous Huxley", "978-0060850524"));

	std::cout << "Repository has " << repo.size() << " books" << std::endl;

	Book * found = repo.findByIsbn("978-0451524935");
	if (found) {
		std::cout << "Found: " << found->getTitle() << std::endl;
	}

	Book * notFound = repo.findByIsbn("000-0000000000");
	std::cout << "Search for missing ISBN returned: " << (notFound == nullptr ? "nullptr (correct)" : "unexpected result") << std::endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
