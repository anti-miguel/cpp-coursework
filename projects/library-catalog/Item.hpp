#pragma once
#include <string>
#include <vector>
#include <optional>
#include "User.hpp"

class Item {
protected:
	int id;
	std::string title;
	std::vector<std::string> authors;
	int year;
	std::string category;
public:
	Item() : id(0), title(""), authors({}), year(0), category("") {}

	Item(int id_, const std::string& title_, const std::vector<std::string>& authors_, int year_, const std::string& cat = "") 
		: id(id_), title(title_), authors(authors_), year(year_), category(cat)
	{
	}

	virtual ~Item() {}
	int getId() const { return id; }
	std::string getTitle() const { return title; }
	std::vector<std::string> getAuthors() const { return authors; }
	int getYear() const { return year; }

	void setId(int newId) { id = newId; }

	virtual std::string info() const = 0;
	virtual std::string toTSV() const = 0;
};

class Book : public Item {
	std::string publisher;
	std::string isbn;
public:
	Book() : Item(0, "", {}, 0) {}
	
	Book(int id_, const std::string& title_, const std::vector<std::string>& authors_, int year_, const std::string& publisher_, const std::string& isbn_)
		: Item(id_, title_, authors_, year_), publisher(publisher_), isbn(isbn_) 
	{
	}

	~Book() override {}
	std::string info() const override;
	std::string toTSV() const override;
	static Book* fromTSV(const std::vector<std::string>& fields );
};

class Journal : public Item {
	int volume;
	int issue;
public:
	Journal(int id_, const std::string& title_, const std::vector<std::string>& authors_, int year_, int volume_, int issue_)
		: Item(id_, title_, authors_, year_), volume(volume_), issue(issue_) 
	{
	}
	~Journal() override {}
	std::string info() const override;
	std::string toTSV() const override;
	static Journal* fromTSV(const std::vector<std::string>& fields);
};

class Loan {
	int id;
	User* user; 
	Item* item; 
	std::string startDate;
	std::string dueDate;
	std::optional<std::string> returnDate;
	double computedFine;
public:
	Loan(int id_, User* u, Item* it, const std::string& start, const std::string& due)
		: id(id_), user(u), item(it), startDate(start), dueDate(due), computedFine(0.0) 
	{
	}
	~Loan() {}
	int getId() const { return id; }
	User* getUser() const { return user; }
	Item* getItem() const { return item; }
	std::string getStartDate() const { return startDate; }
	std::string getDueDate() const { return dueDate; }
	double getComputedFine() const { return computedFine; }
	void setComputedFine(double fine) { computedFine = fine; }

	bool isActive() const { return !returnDate.has_value(); }
	int daysOverdue(const std::string& today) const; // implementación necesaria
	double calculateFine(const std::string& today) const; 
	void setReturnDate(const std::string& rdate) { returnDate = rdate; }
	std::string toTSV() const;
	static Loan* fromTSV(const std::vector<std::string>& fields, User* (*userResolver)(int), Item* (*itemResolver)(int));
	std::string info() const;


};

class Thesis : public Item {
	std::string director;
	int thesisYear;
public:
	Thesis(int id_, const std::string& title_, const std::vector<std::string>& authors_, int year_, const std::string& director_, int thesisYear_)
		: Item(id_, title_, authors_, year_), director(director_), thesisYear(thesisYear_) 
	{
	}
	~Thesis() override {}
	std::string info() const override;
	std::string toTSV() const override;
	static Thesis* fromTSV(const std::vector<std::string>& fields);
};







