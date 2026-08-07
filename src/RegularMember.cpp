#include "RegularMember.h"

RegularMember::RegularMember(const std::string & name, const std::string & memberId)
	: Member(name, memberId) {
}

int RegularMember::getMaxBooksAllowed() const {
	return kMaxBooks;
}
