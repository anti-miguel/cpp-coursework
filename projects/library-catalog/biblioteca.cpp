#include <iostream>
#include "Core.hpp"


int main() {
	Library lib;
	CLI cli(lib);
	std::cout << "Biblioteca - CLI\nEscriba 'help' para ver comandos." << std::endl;
	cli.run();
	return 0;
}