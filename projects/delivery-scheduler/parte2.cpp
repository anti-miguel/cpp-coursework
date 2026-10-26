#include "parte2.h"
#include <algorithm>

namespace Parte2 {

bool SistemaReparto::cmpSolicitudes(const Solicitud& a, const Solicitud& b) {
	if (a.prioridad != b.prioridad) return a.prioridad < b.prioridad;
	return a.orden > b.orden;
}

SistemaReparto::SistemaReparto()
	: cola_urgente(cmpSolicitudes), orden_solicitud(0) {}

int SistemaReparto::tiempoEntregaEstimado(const Pedido& p) const {
	// tiempo simple: preparacion + distancia*3
	return p.tiempo_preparacion + p.distancia_km * 3;
}

bool SistemaReparto::registrarPedido(int id, const std::string& cliente, int distancia_km, int prioridad, int tiempo_preparacion) {
	if (distancia_km < 0 || tiempo_preparacion < 0) return false;
	if (pedidos.find(id) != pedidos.end()) return false;
	pedidos[id] = Pedido{ id, cliente, distancia_km, prioridad, tiempo_preparacion };
	return true;
}

bool SistemaReparto::registrarRepartidor(int id, const std::string& nombre) {
	if (repartidores.find(id) != repartidores.end()) return false;
	repartidores[id] = Repartidor{ id, nombre, 0 };
	return true;
}

bool SistemaReparto::encolarPedido(int pedido_id) {
	if (pedidos.find(pedido_id) == pedidos.end()) return false;
	cola_preparacion.push_back(pedido_id);
	Solicitud s{ pedido_id, pedidos[pedido_id].prioridad, orden_solicitud++ };
	if (s.prioridad >= 7) {
		cola_urgente.push(s);
	}
	return true;
}

std::optional<Pedido> SistemaReparto::prepararSiguiente() {
	if (cola_preparacion.empty()) return std::nullopt;
	int id = cola_preparacion.front();
	cola_preparacion.pop_front();
	auto it = pedidos.find(id);
	if (it == pedidos.end()) return std::nullopt;
	return it->second;
}

std::optional<Ruta> SistemaReparto::asignarRuta(int repartidor_id, int max_pedidos) {
	auto itR = repartidores.find(repartidor_id);
	if (itR == repartidores.end()) return std::nullopt;
	if (max_pedidos <= 0) return std::nullopt;

	Ruta ruta{ repartidor_id, {}, 0 };
	int cuenta = 0;

	while (cuenta < max_pedidos && !cola_urgente.empty()) {
		Solicitud s = cola_urgente.top();
		cola_urgente.pop();
		auto itP = pedidos.find(s.pedido_id);
		if (itP != pedidos.end()) {
			ruta.pedidos_ids.push_back(s.pedido_id);
			ruta.minutos_estimados += tiempoEntregaEstimado(itP->second);
			cuenta++;
		}
	}

	if (cuenta == 0) return std::nullopt;
	itR->second.pedidos_entregados += cuenta;
	historial_rutas.push_back(ruta);
	return ruta;
}

std::vector<Pedido> SistemaReparto::topPedidosUrgentes(int k) const {
	std::vector<Pedido> v;
	v.reserve(pedidos.size());
	for (const auto& kv : pedidos) v.push_back(kv.second);
	std::sort(v.begin(), v.end(), [](const Pedido& a, const Pedido& b) {
		if (a.prioridad != b.prioridad) return a.prioridad > b.prioridad;
		return a.distancia_km < b.distancia_km;
	});
	if (k < 0) k = 0;
	if (static_cast<size_t>(k) < v.size()) v.resize(static_cast<size_t>(k));
	return v;
}

std::vector<std::string> SistemaReparto::trazasDemo() const {
	std::vector<std::string> out;
	out.push_back("Traza 1: registrar pedidos y repartidores, luego encolar pedidos." );
	out.push_back("Traza 2: preparar pedidos en orden de llegada (cola)." );
	out.push_back("Traza 3: asignar ruta priorizando urgentes (priority_queue)." );
	out.push_back("Traza 4: top de pedidos más urgentes y cercanos." );
	return out;
}

std::ostream& operator<<(std::ostream& os, const Pedido& p) {
	os << "Pedido(" << p.id << "," << p.cliente << ", dist=" << p.distancia_km
	   << ", prio=" << p.prioridad << ", prep=" << p.tiempo_preparacion << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Repartidor& r) {
	os << "Repartidor(" << r.id << "," << r.nombre << ", entregados=" << r.pedidos_entregados << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Ruta& ruta) {
	os << "Ruta(repartidor=" << ruta.repartidor_id << ", pedidos=" << ruta.pedidos_ids.size()
	   << ", minutos=" << ruta.minutos_estimados << ")";
	return os;
}

} // namespace Parte2
