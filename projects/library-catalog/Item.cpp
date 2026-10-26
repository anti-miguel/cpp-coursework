#include "Item.hpp"
#include "Core.hpp"

int Loan::daysOverdue(const std::string& today) const {
	if (!isActive()) return 0; // Si ya fue devuelto, no hay retraso
	int days = utils::daysBetween(dueDate, today);
	return days > 0 ? days : 0;
}
double Loan::calculateFine(const std::string& today) const {
	// Política A1: 0.10€/día, tope 15€
	int days = daysOverdue(today);
	if (days <= 0) return 0.0;
	double fine = days * 0.10;
	return fine > 15.0 ? 15.0 : fine; // Tope de 15€
}




std::string Book::info() const {
	std::ostringstream oss;
	oss << "Book{id=" << id << ", title=\"" << title << "\", authors=[";
	for (size_t i = 0; i < authors.size(); ++i) {
		oss << "\"" << authors[i] << "\"";
		if (i + 1 < authors.size()) oss << ", ";
	}
	oss << "], year=" << year << ", publisher=\"" << publisher << "\", isbn=\"" << isbn << "\"}";
	return oss.str();
}
std::string Book::toTSV() const {
	std::ostringstream oss;
	oss << "BOOK" << '\t' << id << '\t' << title << '\t' << utils::join(authors, ',') << '\t' << year << '\t' << publisher << '\t' << isbn;
	return oss.str();
}
Book* Book::fromTSV(const std::vector<std::string>& fields)
{
	if (fields.size() != 7) return nullptr;
	int id = std::stoi(fields[1]);
	std::string title = fields[2];
	std::vector<std::string> authors = utils::split(fields[3], ',');
	int year = std::stoi(fields[4]);
	std::string publisher = fields[5];
	std::string isbn = fields[6];
	return new Book(id, title, authors, year, publisher, isbn);
}
std::string Journal::info() const {
	std::ostringstream oss;
	oss << "Journal{id=" << id << ", title=\"" << title << "\", authors=[";
	for (size_t i = 0; i < authors.size(); ++i) {
		oss << "\"" << authors[i] << "\"";
		if (i + 1 < authors.size()) oss << ", ";
	}
	oss << "], year=" << year << ", volume=" << volume << ", issue=" << issue << "}";
	return oss.str();
}
std::string Journal::toTSV() const {
	std::ostringstream oss;
	oss << "JOURNAL" << '\t' << id << '\t' << title << '\t' << utils::join(authors, ',') << '\t' << year << '\t' << volume << '\t' << issue;
	return oss.str();
}
Journal* Journal::fromTSV(const std::vector<std::string>& fields)
{
	if (fields.size() != 7) return nullptr;
	int id = std::stoi(fields[1]);
	std::string title = fields[2];
	std::vector<std::string> authors = utils::split(fields[3], ',');
	int year = std::stoi(fields[4]);
	int volume = std::stoi(fields[5]);
	int issue = std::stoi(fields[6]);
	return new Journal(id, title, authors, year, volume, issue);
}
std::string Loan::info() const {
	std::ostringstream oss;
	oss << "Loan{id=" << id << ", userId=" << (user ? user->getId() : -1)
		<< ", itemId=" << (item ? item->getId() : -1)
		<< ", start=" << startDate << ", due=" << dueDate;
	if (returnDate.has_value()) oss << ", return=" << returnDate.value();
	oss << ", fine=" << computedFine << "}";
	return oss.str();
}
std::string Loan::toTSV() const {
	std::ostringstream oss;
	oss << id << '\t' << (user ? user->getId() : -1) << '\t' << (item ? item->getId() : -1)
		<< '\t' << startDate << '\t' << dueDate << '\t';
	if (returnDate.has_value()) oss << returnDate.value();
	else oss << "NULL";
	oss << '\t' << std::fixed << std::setprecision(2) << computedFine;
	return oss.str();
}
Loan* Loan::fromTSV(const std::vector<std::string>& fields, User* (*userResolver)(int), Item* (*itemResolver)(int))
{
	if (fields.size() != 7) return nullptr;
	int id = std::stoi(fields[0]);
	int userId = std::stoi(fields[1]);
	int itemId = std::stoi(fields[2]);
	std::string start = fields[3];
	std::string due = fields[4];
	User* user = userResolver(userId);
	Item* item = itemResolver(itemId);
	if (!user || !item) return nullptr;
	Loan* loan = new Loan(id, user, item, start, due);
	if (fields[5] != "NULL") {
		loan->setReturnDate(fields[5]);
	}
	loan->setComputedFine(std::stod(fields[6]));
	return loan;
}
std::string Thesis::info() const {
	std::ostringstream oss;
	oss << "Thesis{id=" << id << ", title=\"" << title << "\", authors=[";
	for (size_t i = 0; i < authors.size(); ++i) {
		oss << "\"" << authors[i] << "\"";
		if (i + 1 < authors.size()) oss << ", ";
	}
	oss << "], year=" << year << ", director=\"" << director << "\", thesisYear=" << thesisYear << "}";
	return oss.str();
}
std::string Thesis::toTSV() const {
	std::ostringstream oss;
	oss << "THESIS" << '\t' << id << '\t' << title << '\t' << utils::join(authors, ',') << '\t' << year << '\t' << director << '\t' << thesisYear;
	return oss.str();
}
Thesis* Thesis::fromTSV(const std::vector<std::string>& fields)
{
	if (fields.size() != 7) return nullptr;
	int id = std::stoi(fields[1]);
	std::string title = fields[2];
	std::vector<std::string> authors = utils::split(fields[3], ',');
	int year = std::stoi(fields[4]);
	std::string director = fields[5];
	int thesisYear = std::stoi(fields[6]);
	return new Thesis(id, title, authors, year, director, thesisYear);
}

