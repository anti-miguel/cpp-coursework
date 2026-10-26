#pragma once
#include <string>
#include <vector>
#include "Item.hpp"
#include "User.hpp"
#include <fstream>

class Catalog;
class Library;

namespace persistence {
	bool saveItems(const std::string& path, const Catalog& c);
	bool loadItems(const std::string& path, Catalog& c, std::string& err);
	bool saveUsers(const std::string& path, const std::vector<User*>& users);
	bool loadUsers(const std::string& path, std::vector<User*>& users, std::string& err);
	bool saveLoans(const std::string& path, const std::vector<Loan*>& loans);
	bool loadLoans(const std::string& path, std::vector<Loan*>& loans, Catalog& c, std::vector<User*>& users, std::string& err);
	
	bool saveAll(const std::string& path, const Library& lib);
	bool loadAll(const std::string& path, Library& lib, std::string& err);
}