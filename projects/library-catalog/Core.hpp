#pragma once // Core.hpp
#include <vector>
#include <algorithm>
#include <queue>
#include <list>
#include "Item.hpp"
#include <string>
#include "User.hpp"
#include <sstream>
#include <chrono>
#include <map>
#include <iostream>
#include "TSVSerializer.hpp"

// Estructura para reservas con prioridad por rol
struct Reservation {
	int userId;
	int itemId;
	std::string requestDate;
	Role userRole;
	
	Reservation(int uid, int iid, const std::string& date, Role role) 
		: userId(uid), itemId(iid), requestDate(date), userRole(role) {}
	
	// Comparador para cola con prioridad: PDI > PAS > STUDENT
	// También prioriza por fecha (más antiguo = mayor prioridad)
	bool operator<(const Reservation& other) const {
		// Primero por rol: PDI tiene mayor prioridad
		if (userRole != other.userRole) {
			// PDI tiene mayor prioridad que todos
			if (userRole == Role::PDI) return false;
			if (other.userRole == Role::PDI) return true;
			// PAS tiene prioridad sobre STUDENT
			if (userRole == Role::PAS && other.userRole == Role::STUDENT) return false;
			if (userRole == Role::STUDENT && other.userRole == Role::PAS) return true;
		}
		// Si mismo rol, priorizar por fecha (más antiguo = mayor prioridad)
		return requestDate > other.requestDate;
	}
};


class Catalog {
	std::vector<Item*> items;
	int nextItemId;
public:
	inline Catalog() : items(), nextItemId(1) {}
	inline ~Catalog() { clear(); }

	Item* addItem(Item* item);
	bool removeItemById(int id);
	Item* findById(int id) const;
	std::vector<Item*> searchByAuthor(const std::string& author) const;
	std::vector<Item*> listAllSortedByTitle() const;

	inline size_t size() const { return items.size(); }

	inline void clear() {
		for (Item* p : items) {
			delete p;
		}
		items.clear();
		nextItemId = 1;
	}
	
	void updateNextItemId() {
		// Actualizar nextItemId basándose en los items existentes
		for (const Item* item : items) {
			if (item && item->getId() >= nextItemId) {
				nextItemId = item->getId() + 1;
			}
		}
	}
};

class Library {
	Catalog catalog;
	std::vector<User*> users;
	std::vector<Loan*> loans;
	// Cola con prioridad de reservas por item (C2 con prioridad por rol)
	std::map<int, std::priority_queue<Reservation>> reservations;
	// Lista enlazada para historial de préstamos ordenado cronológicamente
	std::list<Loan*> loanHistory;
	// Cola para procesar devoluciones pendientes
	std::queue<std::pair<int, std::string>> pendingReturns; // loanId, returnDate
	int nextUserId;
	int nextLoanId;
public:
	Library() : catalog(), users(), loans(), nextUserId(1), nextLoanId(1) {}
	~Library() {
		for (User* u : users) {
			delete u;
		}
		for (Loan* l : loans) {
			delete l;
		}
	}

	inline const std::vector<User*>& getUsers() const { return users; }
	inline const std::vector<Loan*>& getLoans() const { return loans; }
	inline std::vector<User*>& getUsersMutable() { return users; }
	inline std::vector<Loan*>& getLoansMutable() { return loans; }

	User* addUser(const std::string& name, Role role);
	

	bool removeUser(int userId);
	User* findUserById(int id) const;
	bool isItemAvailable(int itemId) const;
	Loan* loanItem(int userId, int itemId, const std::string& start, const std::string& due, std::string& errMsg);
	bool returnItem(int loanId, const std::string& returnDate, std::string& errMsg);
	std::vector<Loan*> loansByUser(int userId) const;
	std::vector<Loan*> activeLoans() const;
	void computeAllFines(const std::string& today);
	std::string reportByRole() const;
	
	// Métodos para gestionar reservas
	int getReservationCount(int itemId) const;
	std::vector<Reservation> getReservationsForItem(int itemId) const;
	
	// Métodos para historial y colas
	void addToHistory(Loan* loan);
	std::list<Loan*> getLoanHistory() const;
	void processPendingReturns();
	void addPendingReturn(int loanId, const std::string& returnDate);

	inline Catalog& getCatalog() { return catalog; }
	inline const Catalog& getCatalog() const { return catalog; }
	
	void clear() {
		// Limpiar préstamos
		for (Loan* l : loans) {
			delete l;
		}
		loans.clear();
		// Limpiar historial (no borrar préstamos, solo limpiar referencias)
		loanHistory.clear();
		// Limpiar cola de devoluciones pendientes
		while (!pendingReturns.empty()) {
			pendingReturns.pop();
		}
		// Limpiar reservas
		reservations.clear();
		// Limpiar usuarios
		for (User* u : users) {
			delete u;
		}
		users.clear();
		// Limpiar catálogo (items)
		catalog.clear();
		nextUserId = 1;
		nextLoanId = 1;
	}
	
	void updateIdCounters() {
		// Actualizar nextItemId del catálogo
		catalog.updateNextItemId();
		// Actualizar nextUserId basándose en los usuarios existentes
		for (const User* u : users) {
			if (u && u->getId() >= nextUserId) {
				nextUserId = u->getId() + 1;
			}
		}
		// Actualizar nextLoanId basándose en los préstamos existentes
		for (const Loan* l : loans) {
			if (l && l->getId() >= nextLoanId) {
				nextLoanId = l->getId() + 1;
			}
		}
	}
};

namespace utils {
	std::vector<std::string> split(const std::string& s, char delim);
	std::string join(const std::vector<std::string>& v, char delim);
	bool parseISODate(const std::string& s, std::tm& out);
	int daysBetween(const std::string& a, const std::string& b); // b - a (días entre fechas)
	std::string todayISO();
	std::string escapeTSV(const std::string& s);
	std::string unescapeTSV(const std::string& s);
}
class CLI {
	Library& lib;
public:
	explicit CLI(Library& l) : lib(l) {}
	void run() {
		std::string line;
		while (true) {
			std::cout << "> ";
			if (!std::getline(std::cin, line)) break;
			if (line.empty()) continue;
			// permitir salir
			if (line == "exit" || line == "quit") break;
			handleCommand(line);
		}
	}

private:
	void handleCommand(const std::string& line) {
		std::istringstream iss(line);
		std::string cmd;
		iss >> cmd;
		std::vector<std::string> args;
		std::string arg;
		while (iss >> arg) {
			args.push_back(arg);
		}

		if (cmd == "add_user") cmdAddUser(args);
		else if (cmd == "add_item") cmdAddItem(args);
		else if (cmd == "remove_item") cmdRemoveItem(args);
		else if (cmd == "edit_item") cmdEditItem(args);
		else if (cmd == "block_user") cmdBlockUser(args);
		else if (cmd == "unblock_user") cmdUnblockUser(args);
		else if (cmd == "loan") cmdLoan(args);
		else if (cmd == "return") cmdReturn(args);
		else if (cmd == "search") cmdSearch(args);
		else if (cmd == "list") cmdList(args);
		else if (cmd == "save") cmdSave(args);
		else if (cmd == "load") cmdLoad(args);
		else if (cmd == "report") cmdReport(args);
		else if (cmd == "help") printHelp();
		else std::cout << "Unknown command: " << cmd << std::endl;
	}

	void cmdAddUser(const std::vector<std::string>& args) {
		if (args.size() != 2) {
			std::cout << "Usage: add_user <name_no_spaces> <role>\nExample: add_user Usuario1 STUDENT\n";
			return;
		}
		std::string name = args[0];
		std::string roleStr = args[1];
		Role role;
		if (roleStr == "STUDENT") role = Role::STUDENT;
		else if (roleStr == "PDI") role = Role::PDI;
		else if (roleStr == "PAS") role = Role::PAS;
		else {
			std::cout << "Invalid role. Use STUDENT, PDI, or PAS.\n";
			return;
		}
		User* user = lib.addUser(name, role);
		if (user) std::cout << "Added user: " << user->info() << std::endl;
		else std::cout << "Failed to add user.\n";
	}

	// TYPE en {BOOK, JOURNAL, THESIS}. Por simplicidad algunos campos extra se dejan vacíos/por defecto.
	void cmdAddItem(const std::vector<std::string>& args) {
		if (args.size() < 3) {
			std::cout << "Usage: add_item <TYPE> <TITLE_no_spaces> <authors_csv> [year]\nExample: add_item BOOK ExampleBook Author1 2005\n";
			return;
		}
		std::string type = args[0];
		std::string title = args[1];
		std::string authorsCsv = args[2];
		int year = 0;
		if (args.size() >= 4) {
			try { year = std::stoi(args[3]); }
			catch (...) { year = 0; }
		}
		// separar autores por coma
		std::vector<std::string> authors;
		{
			std::istringstream ss(authorsCsv);
			std::string a;
			while (std::getline(ss, a, ',')) {
				if (!a.empty()) authors.push_back(a);
			}
		}

		Item* it = nullptr;
		if (type == "BOOK") {
			// Book tiene constructor Book(int id, title, authors, year, publisher, isbn)
			// no tenemos publisher/isbn aquí -> pasar cadenas vacías
			it = new Book(0, title, authors, year, "", "");
		}
		else if (type == "JOURNAL") {
			// asumir volume/issue = 0
			it = new Journal(0, title, authors, year, 0, 0);
		}
		else if (type == "THESIS") {
			// pasar director vacío y usar year como thesisYear si se proporciona
			// Validar thesisYear >= 1980 (B3)
			int tYear = year >= 1980 ? year : 1980;
			if (tYear < 1980) {
				std::cout << "Warning: thesisYear must be >= 1980. Using 1980.\n";
				tYear = 1980;
			}
			it = new Thesis(0, title, authors, year, "", tYear);
		}
		else {
			std::cout << "Unknown item type. Use BOOK, JOURNAL or THESIS.\n";
			return;
		}

		Item* added = lib.getCatalog().addItem(it);
		if (added) std::cout << "Added item: " << added->getTitle() << " (ID " << added->getId() << ")\n";
		else {
			std::cout << "Failed to add item (catalog rejected). Deleting temporary object.\n";
			delete it;
		}
	}

	void cmdLoan(const std::vector<std::string>& args) {
		if (args.size() != 4) {
			std::cout << "Usage: loan <user_id> <item_id> <start_date YYYY-MM-DD> <due_date YYYY-MM-DD>\n";
			return;
		}
		int userId = std::stoi(args[0]);
		int itemId = std::stoi(args[1]);
		std::string startDate = args[2];
		std::string dueDate = args[3];
		std::string errMsg;
		Loan* loan = lib.loanItem(userId, itemId, startDate, dueDate, errMsg);
		if (loan) std::cout << "Loan created: " << loan->info() << std::endl;
		else std::cout << "Error creating loan: " << errMsg << std::endl;
	}

	void cmdReturn(const std::vector<std::string>& args) {
		if (args.size() != 2) {
			std::cout << "Usage: return <loan_id> <return_date YYYY-MM-DD>\n";
			return;
		}
		int loanId = std::stoi(args[0]);
		std::string returnDate = args[1];
		std::string errMsg;
		if (lib.returnItem(loanId, returnDate, errMsg)) {
			std::cout << "Return processed successfully.\n";
		}
		else {
			std::cout << "Error returning item: " << errMsg << std::endl;
		}
	}

	// buscar autor <nombre>
	void cmdSearch(const std::vector<std::string>& args) {
		if (args.empty()) {
			std::cout << "Usage: search author <authorName>\n";
			return;
		}
		std::string criteria = args[0];
		if (criteria == "author") {
			if (args.size() < 2) {
				std::cout << "Usage: search author <authorName>\n";
				return;
			}
			std::string author = args[1];
			auto results = lib.getCatalog().searchByAuthor(author);
			if (results.empty()) {
				std::cout << "No items found for author '" << author << "'.\n";
				return;
			}
			for (Item* it : results) {
				std::cout << it->info() << "\n";
			}
		}
		else {
			std::cout << "Unsupported search criteria. Supported: author\n";
		}
	}

	// listar items | users | loans | history | reservations
	void cmdList(const std::vector<std::string>& args) {
		if (args.empty()) {
			std::cout << "Usage: list items|users|loans|history|reservations [item_id]\n";
			return;
		}
		std::string what = args[0];
		if (what == "items") {
			auto list = lib.getCatalog().listAllSortedByTitle();
			for (Item* it : list) std::cout << it->info() << "\n";
		}
		else if (what == "users") {
			const auto& users = lib.getUsers();
			for (const User* u : users) std::cout << u->info() << "\n";
		}
		else if (what == "loans") {
			const auto& loans = lib.getLoans();
			for (const Loan* L : loans) std::cout << L->info() << "\n";
		}
		else if (what == "history") {
			auto history = lib.getLoanHistory();
			std::cout << "Loan History (chronological order):\n";
			for (const Loan* L : history) std::cout << L->info() << "\n";
		}
		else if (what == "reservations") {
			if (args.size() < 2) {
				std::cout << "Usage: list reservations <item_id>\n";
				return;
			}
			int itemId = std::stoi(args[1]);
			auto resList = lib.getReservationsForItem(itemId);
			if (resList.empty()) {
				std::cout << "No reservations for item " << itemId << ".\n";
			} else {
				std::cout << "Reservations for item " << itemId << " (priority order):\n";
				for (const auto& res : resList) {
					std::string roleStr = (res.userRole == Role::STUDENT ? "STUDENT" : 
					                      (res.userRole == Role::PDI ? "PDI" : "PAS"));
					std::cout << "  User " << res.userId << " (" << roleStr << ") - Requested: " << res.requestDate << "\n";
				}
			}
		}
		else std::cout << "Unknown list target: " << what << ". Use items|users|loans|history|reservations\n";
	}

	// guardar [archivo]
	void cmdSave(const std::vector<std::string>& args) {
		std::string file = "biblioteca.tsv";
		if (!args.empty()) file = args[0];
		std::string err;
		bool ok = persistence::saveAll(file, lib);
		if (ok) std::cout << "Saved data to '" << file << "'\n";
		else std::cout << "Error saving data to '" << file << "': " << err << "\n";
	}

	// cargar [archivo]
	void cmdLoad(const std::vector<std::string>& args) {
		std::string file = "biblioteca.tsv";
		if (!args.empty()) file = args[0];
		std::string err;
		bool ok = persistence::loadAll(file, lib, err);
		if (ok) std::cout << "Loaded data from '" << file << "'\n";
		else std::cout << "Error loading data from '" << file << "': " << err << "\n";
	}

	// remove_item <item_id>
	void cmdRemoveItem(const std::vector<std::string>& args) {
		if (args.size() != 1) {
			std::cout << "Usage: remove_item <item_id>\n";
			return;
		}
		int itemId = std::stoi(args[0]);
		bool ok = lib.getCatalog().removeItemById(itemId);
		if (ok) std::cout << "Item " << itemId << " removed.\n";
		else std::cout << "Item " << itemId << " not found.\n";
	}

	// edit_item <item_id> <field> <value>
	void cmdEditItem(const std::vector<std::string>& args) {
		if (args.size() < 3) {
			std::cout << "Usage: edit_item <item_id> <field> <value>\n";
			std::cout << "Note: Edit functionality is limited. Consider removing and re-adding items.\n";
			return;
		}
		std::cout << "Edit item functionality not fully implemented. Use remove_item and add_item instead.\n";
	}

	// block_user <user_id>
	void cmdBlockUser(const std::vector<std::string>& args) {
		if (args.size() != 1) {
			std::cout << "Usage: block_user <user_id>\n";
			return;
		}
		int userId = std::stoi(args[0]);
		User* user = lib.findUserById(userId);
		if (!user) {
			std::cout << "User " << userId << " not found.\n";
			return;
		}
		user->setBlocked(true);
		std::cout << "User " << userId << " blocked.\n";
	}

	// unblock_user <user_id>
	void cmdUnblockUser(const std::vector<std::string>& args) {
		if (args.size() != 1) {
			std::cout << "Usage: unblock_user <user_id>\n";
			return;
		}
		int userId = std::stoi(args[0]);
		User* user = lib.findUserById(userId);
		if (!user) {
			std::cout << "User " << userId << " not found.\n";
			return;
		}
		user->setBlocked(false);
		std::cout << "User " << userId << " unblocked.\n";
	}

	// report
	void cmdReport(const std::vector<std::string>& args) {
		std::cout << lib.reportByRole() << std::endl;
	}

	void printHelp() const {
		std::cout <<
			"Commands:\n"
			"  add_user <name_no_spaces> <role>          - add a user (role: STUDENT|PDI|PAS)\n"
			"  add_item <TYPE> <TITLE> <authors_csv> [year] - add an item (TYPE: BOOK|JOURNAL|THESIS)\n"
			"  remove_item <item_id>                     - remove an item\n"
			"  edit_item <item_id> <field> <value>       - edit an item (limited)\n"
			"  block_user <user_id>                      - block a user\n"
			"  unblock_user <user_id>                    - unblock a user\n"
			"  loan <user_id> <item_id> <start> <due>    - create a loan (dates YYYY-MM-DD)\n"
			"  return <loan_id> <return_date>            - return an item\n"
			"  search author <name>                      - search items by author\n"
			"  list items|users|loans|history|reservations [item_id] - list entities\n"
			"  save [file]                                - save all data to TSV file (default biblioteca.tsv)\n"
			"  load [file]                                - load all data from TSV file (default biblioteca.tsv)\n"
			"  report                                     - show report by role (F2)\n"
			"  help                                      - show this help\n"
			"  exit|quit                                 - quit\n";
	}
};



