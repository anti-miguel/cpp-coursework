#pragma once
#include <string>
#include <unordered_map>
#include <deque>
#include <queue>
#include <vector>
#include <optional>
#include <ostream>

namespace Parte2 {

struct Pedido {
	int id;
	std::string cliente;
	int distancia_km;
	int prioridad; // mayor = más urgente
	int tiempo_preparacion; // minutos
};

struct Repartidor {
	int id;
	std::string nombre;
	int pedidos_entregados;
};

struct Ruta {
	int repartidor_id;
	std::vector<int> pedidos_ids;
	int minutos_estimados;
};

struct Solicitud {
	int pedido_id;
	int prioridad;
	int orden;
};

class SistemaReparto {
private:
	std::unordered_map<int, Pedido> pedidos;
	std::unordered_map<int, Repartidor> repartidores;
	std::deque<int> cola_preparacion; // pedidos en orden de llegada
	std::priority_queue<Solicitud, std::vector<Solicitud>, bool(*)(const Solicitud&, const Solicitud&)> cola_urgente;
	std::vector<Ruta> historial_rutas;
	int orden_solicitud;

	static bool cmpSolicitudes(const Solicitud& a, const Solicitud& b);
	int tiempoEntregaEstimado(const Pedido& p) const;

public:
	SistemaReparto();

	bool registrarPedido(int id, const std::string& cliente, int distancia_km, int prioridad, int tiempo_preparacion);
	bool registrarRepartidor(int id, const std::string& nombre);

	bool encolarPedido(int pedido_id);
	std::optional<Pedido> prepararSiguiente();
	std::optional<Ruta> asignarRuta(int repartidor_id, int max_pedidos);

	std::vector<Pedido> topPedidosUrgentes(int k) const;
	std::vector<std::string> trazasDemo() const;

	const std::unordered_map<int, Pedido>& getPedidos() const { return pedidos; }
	const std::unordered_map<int, Repartidor>& getRepartidores() const { return repartidores; }
	const std::vector<Ruta>& getHistorialRutas() const { return historial_rutas; }
};

std::ostream& operator<<(std::ostream& os, const Pedido& p);
std::ostream& operator<<(std::ostream& os, const Repartidor& r);
std::ostream& operator<<(std::ostream& os, const Ruta& ruta);

} // namespace Parte2
