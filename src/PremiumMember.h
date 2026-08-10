#pragma once
#include "Member.h"

class PremiumMember : public Member {
public:
	PremiumMember(const std::string & name, const std::string & memberId);

	int getMaxBooksAllowed() const override;

private:
	static constexpr int kMaxBooks = 5;
};

