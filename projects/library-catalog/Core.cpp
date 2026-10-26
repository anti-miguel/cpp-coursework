#include "Core.hpp"
#include <iomanip>

Item* Catalog::addItem(Item* item) {
    // Si el item ya tiene un ID (de carga), preservarlo y actualizar nextItemId
    if (item->getId() > 0) {
        if (item->getId() >= nextItemId) {
            nextItemId = item->getId() + 1;
        }
    } else {
        // Asignar nuevo ID si el item no tiene uno
        item->setId(nextItemId++);
    }
    items.push_back(item);
    return item;
}
bool Catalog::removeItemById(int id) {
    auto it = std::find_if(items.begin(), items.end(), [id](Item* item) { return item->getId() == id; });
    if (it != items.end()) {
        delete *it;
        items.erase(it);
        return true;
    }
    return false;
}

Item* Catalog::findById(int id) const {
    auto it = std::find_if(items.begin(), items.end(), [id](Item* item) { return item->getId() == id; });
    if (it != items.end()) {
        return *it;
    }
    return nullptr;
}
std::vector<Item*> Catalog::searchByAuthor(const std::string& author) const {
    std::vector<Item*> results;
    for (Item* item : items) {
        auto authors = item->getAuthors();
        if (std::find(authors.begin(), authors.end(), author) != authors.end()) {
            results.push_back(item);
        }
    }
    return results;
}
std::vector<Item*> Catalog::listAllSortedByTitle() const {
    std::vector<Item*> sortedItems = items;
    std::sort(sortedItems.begin(), sortedItems.end(), [](Item* a, Item* b) {
        return a->getTitle() < b->getTitle();
    });
    return sortedItems;
}

User* Library::addUser(const std::string& name, Role role) {
    User* user = new User(nextUserId++, name, role);
    users.push_back(user);
    return user;
}
bool Library::removeUser(int userId) {
    auto it = std::find_if(users.begin(), users.end(), [userId](User* user) { return user->getId() == userId; });
    if (it != users.end()) {
        delete *it;
        users.erase(it);
        return true;
    }
    return false;
}
User* Library::findUserById(int id) const {
    auto it = std::find_if(users.begin(), users.end(), [id](User* user) { return user->getId() == id; });
    if (it != users.end()) {
        return *it;
    }
    return nullptr;
}
// Verificar si un item está disponible (no tiene préstamos activos)
bool Library::isItemAvailable(int itemId) const {
    for (const Loan* loan : loans) {
        if (loan->getItem()->getId() == itemId && loan->isActive()) {
            return false;
        }
    }
    return true;
}

Loan* Library::loanItem(int userId, int itemId, const std::string& start, const std::string& due, std::string& errMsg) {
    User* user = findUserById(userId);
    if (!user) {
        errMsg = "User not found.";
        return nullptr;
    }
    if (user->isBlocked()) {
        errMsg = "User is blocked.";
        return nullptr;
    }
    // Verificar límite de préstamos activos por rol (C1: Estudiante=3, PDI=6, PAS=5)
    if (user->getActiveLoansCount() >= user->maxAllowedLoans()) {
        errMsg = "User has reached maximum allowed loans for their role.";
        return nullptr;
    }
    Item* item = catalog.findById(itemId);
    if (!item) {
        errMsg = "Item not found.";
        return nullptr;
    }
    
    // Si el item no está disponible, agregar a cola de reservas con prioridad por rol (C2)
    if (!isItemAvailable(itemId)) {
        reservations[itemId].push(Reservation(userId, itemId, start, user->getRole()));
        errMsg = "Item is currently on loan. Added to reservation queue (priority by role).";
        return nullptr;
    }
    
    Loan* loan = new Loan(nextLoanId++, user, item, start, due);
    loans.push_back(loan);
    addToHistory(loan); // Agregar a historial ordenado
    user->incActiveLoans();
    return loan;
}
bool Library::returnItem(int loanId, const std::string& returnDate, std::string& errMsg) {
    auto it = std::find_if(loans.begin(), loans.end(), [loanId](Loan* loan) { return loan->getId() == loanId; });
    if (it == loans.end()) {
        errMsg = "Loan not found.";
        return false;
    }
    Loan* loan = *it;
    if (!loan->isActive()) {
        errMsg = "Loan is already returned.";
        return false;
    }
    int itemId = loan->getItem()->getId();
    loan->setReturnDate(returnDate);
    loan->getUser()->decActiveLoans();
    
    // Procesar cola de reservas con prioridad (C2): asignar a usuario con mayor prioridad
    while (!reservations[itemId].empty()) {
        Reservation res = reservations[itemId].top();
        reservations[itemId].pop();
        // Intentar crear préstamo automáticamente para el siguiente en cola
        std::string today = utils::todayISO();
        std::string dueDate = utils::todayISO(); // Calcular fecha de vencimiento según rol
        // Por simplicidad, usar 14 días por defecto
        int daysToAdd = 14;
        std::tm tm = {};
        if (utils::parseISODate(today, tm)) {
            tm.tm_mday += daysToAdd;
            std::mktime(&tm);
            char buffer[11];
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
            dueDate = buffer;
        }
        std::string autoErr;
        Loan* autoLoan = loanItem(res.userId, res.itemId, today, dueDate, autoErr);
        if (autoLoan) {
            // Préstamo automático creado para usuario con mayor prioridad
            break; // Solo procesar el primero que pueda obtener el préstamo
        }
        // Si falla (usuario bloqueado, límite alcanzado, etc.), continuar con siguiente
    }
    
    // Procesar cualquier devolución pendiente en cola
    processPendingReturns();
    
    return true;
}
std::vector<Loan*> Library::loansByUser(int userId) const {
    std::vector<Loan*> userLoans;
    for (Loan* loan : loans) {
        if (loan->getUser()->getId() == userId) {
            userLoans.push_back(loan);
        }
    }
    return userLoans;
}
std::vector<Loan*> Library::activeLoans() const {
    std::vector<Loan*> active;
    for (Loan* loan : loans) {
        if (loan->isActive()) {
            active.push_back(loan);
        }
    }
    return active;
}
void Library::computeAllFines(const std::string& today) {
    for (Loan* loan : loans) {
        if (loan->isActive()) {
            double fine = loan->calculateFine(today);
            loan->setComputedFine(fine);
            loan->getUser()->addSanction(fine);
        }
    }
}
std::string Library::reportByRole() const {
    std::ostringstream oss;
    std::map<Role, int> roleCounts;
    std::map<Role, int> activeLoansByRole;
    std::map<Role, int> overdueLoansByRole;
    std::map<Role, double> sanctionsByRole;
    
    // Contar usuarios por rol
    for (const User* user : users) {
        roleCounts[user->getRole()]++;
        sanctionsByRole[user->getRole()] += user->getSanction();
    }
    
    // Contar préstamos activos y retrasados por rol
    std::string today = utils::todayISO();
    for (const Loan* loan : loans) {
        if (loan->isActive()) {
            Role role = loan->getUser()->getRole();
            activeLoansByRole[role]++;
            // Calcular días de retraso
            int days = utils::daysBetween(loan->getDueDate(), today);
            if (days > 0) {
                overdueLoansByRole[role]++;
            }
        }
    }
    
    oss << "=== Reporte por Rol (F2) ===\n";
    for (const auto& [role, count] : roleCounts) {
        std::string roleStr = (role == Role::STUDENT ? "STUDENT" : (role == Role::PDI ? "PDI" : "PAS"));
        oss << "\n" << roleStr << ":\n";
        oss << "  Usuarios: " << count << "\n";
        oss << "  Préstamos activos: " << activeLoansByRole[role] << "\n";
        oss << "  Préstamos con retraso: " << overdueLoansByRole[role] << "\n";
        oss << "  Sanciones acumuladas: " << std::fixed << std::setprecision(2) << sanctionsByRole[role] << " €\n";
    }
    return oss.str();
}

// Agregar préstamo al historial ordenado cronológicamente
void Library::addToHistory(Loan* loan) {
    // Insertar en orden cronológico (por fecha de inicio)
    auto it = loanHistory.begin();
    while (it != loanHistory.end() && (*it)->getStartDate() < loan->getStartDate()) {
        ++it;
    }
    loanHistory.insert(it, loan);
}

// Obtener historial de préstamos
std::list<Loan*> Library::getLoanHistory() const {
    return loanHistory;
}

// Obtener cantidad de reservas para un item
int Library::getReservationCount(int itemId) const {
    auto it = reservations.find(itemId);
    if (it == reservations.end()) return 0;
    // priority_queue no tiene size() directo, necesitamos copiar para contar
    std::priority_queue<Reservation> temp = it->second;
    int count = 0;
    while (!temp.empty()) {
        count++;
        temp.pop();
    }
    return count;
}

// Obtener todas las reservas para un item (para consulta)
std::vector<Reservation> Library::getReservationsForItem(int itemId) const {
    std::vector<Reservation> result;
    auto it = reservations.find(itemId);
    if (it == reservations.end()) return result;
    
    // Copiar la cola para poder iterar
    std::priority_queue<Reservation> temp = it->second;
    while (!temp.empty()) {
        result.push_back(temp.top());
        temp.pop();
    }
    return result;
}

// Agregar devolución pendiente a la cola
void Library::addPendingReturn(int loanId, const std::string& returnDate) {
    pendingReturns.push(std::make_pair(loanId, returnDate));
}

// Procesar cola de devoluciones pendientes
void Library::processPendingReturns() {
    while (!pendingReturns.empty()) {
        auto pending = pendingReturns.front();
        pendingReturns.pop();
        std::string errMsg;
        returnItem(pending.first, pending.second, errMsg);
        // Si falla, se pierde (se podría reintentar o loguear)
    }
}

bool utils::parseISODate(const std::string& s, std::tm& out) {
    std::istringstream iss(s);
    iss >> std::get_time(&out, "%Y-%m-%d");
    return !iss.fail();
}
int utils::daysBetween(const std::string& a, const std::string& b) {
    std::tm tmA = {}, tmB = {};
    if (!parseISODate(a, tmA) || !parseISODate(b, tmB)) {
        return 0;
    }
    std::time_t timeA = std::mktime(&tmA);
    std::time_t timeB = std::mktime(&tmB);
    const int secondsPerDay = 60 * 60 * 24;
    return static_cast<int>(std::difftime(timeB, timeA) / secondsPerDay);
}
std::string utils::todayISO() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
    return std::string(buffer);
}
std::string utils::escapeTSV(const std::string& s) {
    std::string escaped;
    for (char c : s) {
        if (c == '\t') {
            escaped += "\\t";
        }
        else if (c == '\n') {
            escaped += "\\n";
        }
        else if (c == '\\') {
            escaped += "\\\\";
        }
        else {
            escaped.push_back(c);
        }
    }
    return escaped;
}
std::string utils::unescapeTSV(const std::string& s) {
    std::string unescaped;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\\' && i + 1 < s.size()) {
            char next = s[i + 1];
            if (next == 't') {
                unescaped.push_back('\t');
                ++i;
            }
            else if (next == 'n') {
                unescaped.push_back('\n');
                ++i;
            }
            else if (next == '\\') {
                unescaped.push_back('\\');
                ++i;
            }
            else {
                unescaped.push_back(s[i]);
            }
        }
        else {
            unescaped.push_back(s[i]);
        }
    }
    return unescaped;
}

std::vector<std::string> utils::split(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::string cur;
    for (char c : s) {
        if (c == delim) {
            out.push_back(cur);
            cur.clear();
        }
        else {
            cur.push_back(c);
        }
    }
    out.push_back(cur);
    return out;
}
std::string utils::join(const std::vector<std::string>& v, char delim) {
    std::string out;
    for (size_t i = 0; i < v.size(); ++i) {
        out += v[i];
        if (i + 1 < v.size()) out.push_back(delim);
    }
    return out;
}

