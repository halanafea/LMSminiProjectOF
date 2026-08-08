
#include "Book.h"
#include "ofApp.h"
#include "RegularMember.h"
#include "PremiumMember.h"
#include "BookRepository.h"
#include "MyLibrary.h"
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

	/* BookRepository repo;
	repo.addBook(Book("1984", "George Orwell", "978-0451524935"));
	repo.addBook(Book("Brave New World", "Aldous Huxley", "978-0060850524"));

	std::cout << "Repository has " << repo.size() << " books" << std::endl;

	Book * found = repo.findByIsbn("978-0451524935");
	if (found) {
		std::cout << "Found: " << found->getTitle() << std::endl;
	}

	Book * notFound = repo.findByIsbn("000-0000000000");
	std::cout << "Search for missing ISBN returned: " << (notFound == nullptr ? "nullptr (correct)" : "unexpected result") << std::endl;*/

	/* MyLibrary myLibrary;

	Book b1("1984", "George Orwell", "978-0451524935");
	Book b2("Brave New World", "Aldous Huxley", "978-0060850524");
	myLibrary.addBook(&b1);
	myLibrary.addBook(&b2);
	std::cout << "Library has " << myLibrary.getBookCount() << " books" << std::endl;

	RegularMember alice("Alice", "M001");
	myLibrary.registerMember(&alice);

	std::cout << "Alice borrows 1984: " << myLibrary.borrowBook("978-0451524935", &alice) << std::endl;
	std::cout << "Alice borrows 1984 again (should fail, already out): "
			  << myLibrary.borrowBook("978-0451524935", &alice) << std::endl;

	std::cout << "Alice returns 1984: " << myLibrary.returnBook("978-0451524935", &alice) << std::endl;
	std::cout << "Alice borrows 1984 again (should succeed now): "
			  << myLibrary.borrowBook("978-0451524935", &alice) << std::endl;

	// Test through the abstract interface - true polymorphism
	AbstractLibrary * libInterface = &myLibrary;
	Book b3("Fahrenheit 451", "Ray Bradbury", "978-1451673319");
	libInterface->addBook(&b3);
	std::cout << "Library now has " << myLibrary.getBookCount() << " books (added via AbstractLibrary*)" << std::endl;*/


		std::cout << "=== Library Management System Demo ===\n"
				  << std::endl;

		// --- Composition: MyLibrary owns its BookRepository internally ---
		MyLibrary library;

		// --- Add books (Encapsulation: Book's fields only reachable via getters/setters) ---
		Book b1("1984", "George Orwell", "978-0451524935");
		Book b2("Brave New World", "Aldous Huxley", "978-0060850524");
		Book b3("Fahrenheit 451", "Ray Bradbury", "978-1451673319");
		Book b4("Animal Farm", "George Orwell", "978-0451526342");
		Book b5("Brave New World Revisited", "Aldous Huxley", "978-0060748953");

		library.addBook(&b1);
		library.addBook(&b2);
		library.addBook(&b3);
		library.addBook(&b4);
		library.addBook(&b5);
		std::cout << "Library stocked with " << library.getBookCount() << " books.\n"
				  << std::endl;

		// --- Inheritance: RegularMember and PremiumMember both extend Member ---
		RegularMember alice("Alice", "M001"); // limit: 3
		PremiumMember bob("Bob", "M002"); // limit: 5

		library.registerMember(&alice);
		library.registerMember(&bob);

		// --- Association: members borrow through the library, which links both sides ---
		std::cout << "-- Alice (Regular, limit 3) borrows books --" << std::endl;
		std::cout << "Borrow 1984: " << (library.borrowBook("978-0451524935", &alice) ? "OK" : "FAILED") << std::endl;
		std::cout << "Borrow Brave New World: " << (library.borrowBook("978-0060850524", &alice) ? "OK" : "FAILED") << std::endl;
		std::cout << "Borrow Fahrenheit 451: " << (library.borrowBook("978-1451673319", &alice) ? "OK" : "FAILED") << std::endl;
		std::cout << "Borrow Animal Farm (should FAIL - at limit of 3): "
				  << (library.borrowBook("978-0451526342", &alice) ? "OK" : "FAILED") << std::endl;
		std::cout << "Alice currently holds " << alice.getBorrowedBooks().size() << " book(s).\n"
				  << std::endl;

		std::cout << "-- Bob (Premium, limit 5) borrows books --" << std::endl;
		std::cout << "Borrow Animal Farm: " << (library.borrowBook("978-0451526342", &bob) ? "OK" : "FAILED") << std::endl;
		std::cout << "Borrow Brave New World Revisited: " << (library.borrowBook("978-0060748953", &bob) ? "OK" : "FAILED") << std::endl;
		std::cout << "Borrow 1984 (should FAIL - already borrowed by Alice): "
				  << (library.borrowBook("978-0451524935", &bob) ? "OK" : "FAILED") << std::endl;
		std::cout << "Bob currently holds " << bob.getBorrowedBooks().size() << " book(s).\n"
				  << std::endl;

		// --- Returning a book frees it up for someone else ---
		std::cout << "-- Alice returns 1984 --" << std::endl;
		std::cout << "Return 1984: " << (library.returnBook("978-0451524935", &alice) ? "OK" : "FAILED") << std::endl;
		std::cout << "Now Bob borrows 1984: " << (library.borrowBook("978-0451524935", &bob) ? "OK" : "FAILED") << std::endl;
		std::cout << "Bob currently holds " << bob.getBorrowedBooks().size() << " book(s).\n"
				  << std::endl;

		// --- Abstraction: same operations work through the AbstractLibrary interface ---
		std::cout << "-- Using MyLibrary through an AbstractLibrary* pointer --" << std::endl;
		AbstractLibrary * libraryInterface = &library;
		Book b6("The Great Gatsby", "F. Scott Fitzgerald", "978-0743273565");
		libraryInterface->addBook(&b6);
		std::cout << "Book added via AbstractLibrary*. Library now has "
				  << library.getBookCount() << " books." << std::endl;
		std::cout << "Borrow via AbstractLibrary*: "
				  << (libraryInterface->borrowBook("978-0743273565", &alice) ? "OK" : "FAILED") << std::endl;

		std::cout << "\n-- Edge case tests --" << std::endl;
		std::cout << "Borrow nonexistent ISBN: "
				  << (library.borrowBook("000-0000000000", &alice) ? "OK" : "FAILED (correct)") << std::endl;
		std::cout << "Bob tries to return Alice's book (should FAIL): "
				  << (library.returnBook("978-0743273565", &bob) ? "OK" : "FAILED (correct)") << std::endl;

		std::cout << "\n=== Demo complete ===" << std::endl;
	

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
