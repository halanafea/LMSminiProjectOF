#pragma once
#include "Member.h"

class RegularMember : public Member {
public:
	RegularMember(const std::string & name, const std::string & memberId);

	int getMaxBooksAllowed() const override;

private:
	static constexpr int kMaxBooks = 3;
};

