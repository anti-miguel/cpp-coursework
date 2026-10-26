#include "User.hpp"

std::string User::toTSV() const {
    std::ostringstream oss;
    std::string r = (role == Role::STUDENT ? "STUDENT" : (role == Role::PDI ? "PDI" : "PAS"));
    oss << id << '\t' << name << '\t' << r << '\t' << std::fixed << std::setprecision(2) << sanctionAmount;
    return oss.str();
}
User* User::fromTSV(const std::vector<std::string>& fields)
{
    if (fields.size() != 4) return nullptr;
    int id = std::stoi(fields[0]);
    std::string name = fields[1];
    Role role;
    if (fields[2] == "STUDENT") role = Role::STUDENT;
    else if (fields[2] == "PDI") role = Role::PDI;
    else if (fields[2] == "PAS") role = Role::PAS;
    else return nullptr;
    double sanction = std::stod(fields[3]);
    User* user = new User(id, name, role);
    user->addSanction(sanction);
    return user;
}

std::string User::info() const {
    std::ostringstream oss;
    oss << "User{id=" << id << ", name=\"" << name << "\", role=";
    if (role == Role::STUDENT) oss << "STUDENT";
    else if (role == Role::PDI) oss << "PDI";
    else oss << "PAS";
    oss << ", sanctions=" << std::fixed << std::setprecision(2) << sanctionAmount << "}";
    return oss.str();
}
