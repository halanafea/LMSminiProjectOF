#include "PremiumMember.h"

PremiumMember::PremiumMember(const std::string & name, const std::string & memberId)
	: Member(name, memberId) {
}

int PremiumMember::getMaxBooksAllowed() const {
	return kMaxBooks;
}
