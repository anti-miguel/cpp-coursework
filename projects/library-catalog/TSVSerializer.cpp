#include "TSVSerializer.hpp"
#include "Item.hpp"
#include "User.hpp"
#include "Core.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

// Helper para buscar user por id en vector
static User* findUserById(const std::vector<User*>& users, int id) {
    for (User* u : users) if (u && u->getId() == id) return u;
    return nullptr;
}

bool persistence::saveUsers(const std::string& path, const std::vector<User*>& users) {
    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        return false;
    }
    for (const auto& user : users) {
        ofs << user->toTSV() << "\n";
    }
    return true;
}

bool persistence::loadUsers(const std::string& path, std::vector<User*>& users, std::string& err) { 
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        err = "Could not open file: " + path;
        return false;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        std::vector<std::string> fields = utils::split(line, '\t');
        User* user = User::fromTSV(fields);
        if (user == nullptr) {
            err = "Malformed user entry: " + line; return false;
        }
        users.push_back(user);
    }
    return true;
}

bool persistence::saveItems(const std::string& path, const Catalog& c) {
    std::ofstream ofs(path);
    if (!ofs.is_open()) return false;

    // Usamos lista ordenada por título para guardar
    auto items = c.listAllSortedByTitle();
    for (const auto& item : items) {
        if (!item) continue;
        ofs << item->toTSV() << '\n';
        if (!ofs.good()) return false;
    }
    return true;
}

// este método crea Items y los añade al Catalog usando Catalog::addItem(Item*).
// Se asume el formato descrito arriba. Si falla una línea => devuelve false + err.
bool persistence::loadItems(const std::string& path, Catalog& c, std::string& err) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        err = "Could not open file: " + path;
        return false;
    }

    std::string line;
    int lineNo = 0;
    while (std::getline(ifs, line)) {
        ++lineNo;
        if (line.empty()) continue;

        auto fields = utils::split(line, '\t');
        if (fields.size() < 7) {
            err = "Malformed item (too few fields) at line " + std::to_string(lineNo);
            return false;
        }

        std::string type = fields[0];
        int id = 0;
        try { id = std::stoi(fields[1]); }
        catch (...) { id = 0; }
        std::string title = fields[2];
        std::vector<std::string> authors;
        {
            std::istringstream ss(fields[3]);
            std::string a;
            while (std::getline(ss, a, ';')) if (!a.empty()) authors.push_back(a);
        }
        int year = 0;
        try { year = std::stoi(fields[4]); }
        catch (...) { year = 0; }

        Item* it = nullptr;
        if (type == "BOOK") {
            std::string publisher = fields[5];
            std::string isbn = fields[6];
            // Constructor Book: Book(int id, title, authors, year, publisher, isbn)
            it = new Book(id, title, authors, year, publisher, isbn);
        }
        else if (type == "JOURNAL") {
            int volume = 0, issue = 0;
            try { volume = std::stoi(fields[5]); }
            catch (...) { volume = 0; }
            try { issue = std::stoi(fields[6]); }
            catch (...) { issue = 0; }
            it = new Journal(id, title, authors, year, volume, issue);
        }
        else if (type == "THESIS") {
            std::string director = fields[5];
            int thesisYear = 0;
            try { thesisYear = std::stoi(fields[6]); }
            catch (...) { thesisYear = year; }
            it = new Thesis(id, title, authors, year, director, thesisYear);
        }
        else {
            err = "Unknown item type '" + type + "' at line " + std::to_string(lineNo);
            return false;
        }

        // Añadir al catálogo; si addItem falla (nullptr), liberar y devolver error.
        Item* added = c.addItem(it);
        if (!added) {
            delete it;
            err = "Catalog rejected item at line " + std::to_string(lineNo);
            return false;
        }
    }

    return true;
}

bool persistence::saveLoans(const std::string& path, const std::vector<Loan*>& loans) {
    std::ofstream ofs(path);
    if (!ofs.is_open()) return false;

    for (const Loan* loan : loans) {
        if (!loan) continue;
        // LOANID\tUSERID\tITEMID\tSTART\tDUE\tRETURN(opcional)\tFINE
        std::ostringstream oss;
        oss << loan->getId() << '\t'
            << (loan->getUser() ? loan->getUser()->getId() : -1) << '\t'
            << (loan->getItem() ? loan->getItem()->getId() : -1) << '\t'
            << loan->info(); 
        std::string start = "";
        if constexpr (true) {
            ofs << loan->toTSV() << '\n';
        }
        else {}

        if (!ofs.good()) return false;
    }
    return true;
}

bool persistence::loadLoans(const std::string& path, std::vector<Loan*>& loans, Catalog& c, std::vector<User*>& users, std::string& err) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        err = "Could not open file: " + path;
        return false;
    }

    std::string line;
    int lineNo = 0;
    while (std::getline(ifs, line)) {
        ++lineNo;
        if (line.empty()) continue;
        auto f = utils::split(line, '\t');
        if (f.size() < 6) {
            err = "Malformed loan at line " + std::to_string(lineNo);
            return false;
        }
        int loanId = 0;
        int userId = 0;
        int itemId = 0;
        try { loanId = std::stoi(f[0]); }
        catch (...) { loanId = 0; }
        try { userId = std::stoi(f[1]); }
        catch (...) { userId = 0; }
        try { itemId = std::stoi(f[2]); }
        catch (...) { itemId = 0; }
        std::string start = f[3];
        std::string due = f[4];
        std::string ret = "";
        double fine = 0.0;
        if (f.size() >= 6) ret = f[5];
        if (f.size() >= 7) {
            try { fine = std::stod(f[6]); }
            catch (...) { fine = 0.0; }
        }

        User* u = findUserById(users, userId);
        if (!u) {
            err = "Unknown user id " + std::to_string(userId) + " for loan at line " + std::to_string(lineNo);
            return false;
        }
        Item* it = c.findById(itemId);
        if (!it) {
            err = "Unknown item id " + std::to_string(itemId) + " for loan at line " + std::to_string(lineNo);
            return false;
        }

        // Crear préstamo
        Loan* loan = new Loan(loanId, u, it, start, due);
        if (!ret.empty() && ret != "-" && ret != "NULL") {
            loan->setReturnDate(ret);
        }
        loan->setComputedFine(fine);
        loans.push_back(loan);
    }
    return true;
}

bool persistence::saveAll(const std::string& path, const Library& lib) {
    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        return false;
    }
    
    // Guardar sección de items
    ofs << "[ITEMS]\n";
    auto items = lib.getCatalog().listAllSortedByTitle();
    for (const auto& item : items) {
        if (!item) continue;
        ofs << item->toTSV() << '\n';
        if (!ofs.good()) return false;
    }
    
    // Guardar sección de usuarios
    ofs << "[USERS]\n";
    const auto& users = lib.getUsers();
    for (const auto& user : users) {
        if (!user) continue;
        ofs << user->toTSV() << '\n';
        if (!ofs.good()) return false;
    }
    
    // Guardar sección de préstamos
    ofs << "[LOANS]\n";
    const auto& loans = lib.getLoans();
    for (const Loan* loan : loans) {
        if (!loan) continue;
        ofs << loan->toTSV() << '\n';
        if (!ofs.good()) return false;
    }
    
    return true;
}

bool persistence::loadAll(const std::string& path, Library& lib, std::string& err) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        err = "Could not open file: " + path;
        return false;
    }
    
    lib.clear();
    
    enum class Section { NONE, ITEMS, USERS, LOANS };
    Section currentSection = Section::NONE;
    
    std::string line;
    int lineNo = 0;
    
    while (std::getline(ifs, line)) {
        ++lineNo;
        
        // Eliminar espacios en blanco
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n' || line.back() == ' ' || line.back() == '\t')) {
            line.pop_back();
        }
        while (!line.empty() && (line.front() == ' ' || line.front() == '\t')) {
            line.erase(0, 1);
        }
        
        if (line.empty()) continue;
        
        // Verificar enums
        if (line == "[ITEMS]") {
            currentSection = Section::ITEMS;
            continue;
        }
        else if (line == "[USERS]") {
            currentSection = Section::USERS;
            continue;
        }
        else if (line == "[LOANS]") {
            currentSection = Section::LOANS;
            continue;
        }
        
        // Procesar datos según enum actual
        if (currentSection == Section::ITEMS) {
            auto fields = utils::split(line, '\t');
            if (fields.size() < 7) {
                err = "Malformed item (too few fields) at line " + std::to_string(lineNo);
                return false;
            }
            
            std::string type = fields[0];
            int id = 0;
            try { id = std::stoi(fields[1]); }
            catch (...) { id = 0; }
            std::string title = fields[2];
            std::vector<std::string> authors = utils::split(fields[3], ',');
            int year = 0;
            try { year = std::stoi(fields[4]); }
            catch (...) { year = 0; }
            
            Item* it = nullptr;
            if (type == "BOOK") {
                std::string publisher = fields[5];
                std::string isbn = fields[6];
                it = new Book(id, title, authors, year, publisher, isbn);
            }
            else if (type == "JOURNAL") {
                int volume = 0, issue = 0;
                try { volume = std::stoi(fields[5]); }
                catch (...) { volume = 0; }
                try { issue = std::stoi(fields[6]); }
                catch (...) { issue = 0; }
                it = new Journal(id, title, authors, year, volume, issue);
            }
            else if (type == "THESIS") {
                std::string director = fields[5];
                int thesisYear = 0;
                try { thesisYear = std::stoi(fields[6]); }
                catch (...) { thesisYear = year; }
                // Validar thesisYear >= 1980 (B3)
                if (thesisYear < 1980) {
                    err = "Thesis year must be >= 1980 at line " + std::to_string(lineNo);
                    return false;
                }
                it = new Thesis(id, title, authors, year, director, thesisYear);
            }
            else {
                err = "Unknown item type '" + type + "' at line " + std::to_string(lineNo);
                return false;
            }
            
            Item* added = lib.getCatalog().addItem(it);
            if (!added) {
                delete it;
                err = "Catalog rejected item at line " + std::to_string(lineNo);
                return false;
            }
        }
        else if (currentSection == Section::USERS) {
            auto fields = utils::split(line, '\t');
            User* user = User::fromTSV(fields);
            if (user == nullptr) {
                err = "Malformed user entry at line " + std::to_string(lineNo);
                return false;
            }
            lib.getUsersMutable().push_back(user);
        }
        else if (currentSection == Section::LOANS) {
            auto f = utils::split(line, '\t');
            if (f.size() < 6) {
                err = "Malformed loan at line " + std::to_string(lineNo);
                return false;
            }
            int loanId = 0;
            int userId = 0;
            int itemId = 0;
            try { loanId = std::stoi(f[0]); }
            catch (...) { loanId = 0; }
            try { userId = std::stoi(f[1]); }
            catch (...) { userId = 0; }
            try { itemId = std::stoi(f[2]); }
            catch (...) { itemId = 0; }
            std::string start = f[3];
            std::string due = f[4];
            std::string ret = "";
            double fine = 0.0;
            if (f.size() >= 6) ret = f[5];
            if (f.size() >= 7) {
                try { fine = std::stod(f[6]); }
                catch (...) { fine = 0.0; }
            }
            
            User* u = findUserById(lib.getUsers(), userId);
            if (!u) {
                err = "Unknown user id " + std::to_string(userId) + " for loan at line " + std::to_string(lineNo);
                return false;
            }
            Item* it = lib.getCatalog().findById(itemId);
            if (!it) {
                err = "Unknown item id " + std::to_string(itemId) + " for loan at line " + std::to_string(lineNo);
                return false;
            }
            
            Loan* loan = new Loan(loanId, u, it, start, due);
            if (!ret.empty() && ret != "-" && ret != "NULL") {
                loan->setReturnDate(ret);
            }
            loan->setComputedFine(fine);
            lib.getLoansMutable().push_back(loan);
        }
        else {
            err = "Data found before section marker at line " + std::to_string(lineNo);
            return false;
        }
    }
    
    // Actualizar contadores de ID después de cargar para asegurar que nuevos items obtengan IDs correctos
    lib.updateIdCounters();
    
    return true;
}
