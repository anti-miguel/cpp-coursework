#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


enum class Role { STUDENT, PDI, PAS };

class User {
	int id;
	std::string name;
	Role role;
	double sanctionAmount;
	int activeLoansCount;
	bool blocked;
public:
	User(int id_, const std::string& name_, Role role_) :
		id(id_), name(name_), role(role_), sanctionAmount(0.0), activeLoansCount(0), blocked(false) 
	{
	}
	~User() {}

	int getId() const { return id; }
	std::string getName() const { return name; }
	Role getRole() const { return role; }
	double getSanction() const { return sanctionAmount; }
	void addSanction(double euros) { sanctionAmount += euros; }
	void clearSanction() { sanctionAmount = 0.0; }

	void setBlocked(bool b) { blocked = b; }
	bool isBlocked() const { return blocked; }

	inline int maxAllowedLoans() const {
		switch (role) {
		case Role::STUDENT: return 3;
		case Role::PDI:     return 6;
		case Role::PAS:     return 5;
		default:            return 3;
		}
	}

	inline void incActiveLoans() { ++activeLoansCount; }
	inline void decActiveLoans() { if (activeLoansCount > 0) --activeLoansCount; }
	inline int getActiveLoansCount() const { return activeLoansCount; }

	std::string toTSV() const; 
	static User* fromTSV(const std::vector<std::string>& fields);
	std::string info() const;
};

