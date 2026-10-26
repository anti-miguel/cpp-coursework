#include "parte2.h"
#include <iostream>

using namespace Parte2;

int main() {
	SistemaReparto s;
	
	s.registrarRepartidor(1, "Repartidor1");
	s.registrarRepartidor(2, "Repartidor2");

	s.registrarPedido(100, "Cliente1", 3, 5, 10);
	s.registrarPedido(101, "Persona1", 8, 9, 15);
	s.registrarPedido(102, "Cliente3", 2, 7, 8);

	s.encolarPedido(100);
	s.encolarPedido(101);
	s.encolarPedido(102);

	auto p1 = s.prepararSiguiente();
	if (p1) std::cout << "Preparado: " << *p1 << "\n";
	auto p2 = s.prepararSiguiente();
	if (p2) std::cout << "Preparado: " << *p2 << "\n";

	auto ruta = s.asignarRuta(1, 2);
	if (ruta) std::cout << "Ruta asignada: " << *ruta << "\n";

	auto top = s.topPedidosUrgentes(2);
	for (const auto& p : top) std::cout << p << "\n";

	return 0;
}
