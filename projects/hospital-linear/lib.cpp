#include "lib.h"
#include <cmath>
#include <algorithm>
#include <climits>

namespace Hospitalnames {
	Medicamento::Medicamento() : id(0), nombre(""), tipo(""), cantidad(0) {}

	Medicamento::Medicamento(int _id, std::string _nombre, std::string _tipo, int _cantidad)
		: id(_id), nombre(_nombre), tipo(_tipo), cantidad(_cantidad) {}

	Medicamento::Medicamento(const Medicamento& other)
		: id(other.id), nombre(other.nombre), tipo(other.tipo), cantidad(other.cantidad) {}

	Medicamento& Medicamento::operator=(const Medicamento& other) {
		if (this != &other) {
			id = other.id;
			nombre = other.nombre;
			tipo = other.tipo;
			cantidad = other.cantidad;
		}
		return *this;
	}

	bool Medicamento::operator==(const Medicamento& other) const {
		return id == other.id && nombre == other.nombre && tipo == other.tipo;
	}

	bool Medicamento::operator!=(const Medicamento& other) const {
		return !(*this == other);
	}

	bool Medicamento::operator<(const Medicamento& other) const {
		return (nombre + tipo) < (other.nombre + other.tipo);
	}

	Medicamento* Medicamento::copyCantidad(int k) const {
		return new Medicamento(id, nombre, tipo, k);
	}

	Enfermedad::Enfermedad() : id(0), nombre(""), letalidad(0), urgencia(0) {}

	Enfermedad::Enfermedad(int _id, std::string _nombre, int _letalidad, int _urgencia)
		: id(_id), nombre(_nombre), letalidad(_letalidad), urgencia(_urgencia) {}

	Enfermedad::Enfermedad(const Enfermedad& other)
		: id(other.id), nombre(other.nombre), letalidad(other.letalidad), urgencia(other.urgencia) {}

	Enfermedad& Enfermedad::operator=(const Enfermedad& other) {
		if (this != &other) {
			id = other.id;
			nombre = other.nombre;
			letalidad = other.letalidad;
			urgencia = other.urgencia;
		}
		return *this;
	}

	bool Enfermedad::operator==(const Enfermedad& other) const {
		return id == other.id && nombre == other.nombre && letalidad == other.letalidad && urgencia == other.urgencia;
	}

	bool Enfermedad::operator!=(const Enfermedad& other) const {
		return !(*this == other);
	}

	bool Enfermedad::operator<(const Enfermedad& other) const {
		// Mayor prioridad debe salir primero en estructuras ordenadas.
		return prioridad() > other.prioridad();
	}

Doctor::Doctor() : id(0), nombre(""), dinero(std::make_shared<int>(0)), pendientes(new std::list<Enfermedad>()) {}

	Doctor::~Doctor() { delete pendientes; }

Doctor::Doctor(int _id, std::string _nombre, int _dinero)
	: id(_id), nombre(_nombre), dinero(std::make_shared<int>(_dinero)), pendientes(new std::list<Enfermedad>()) {}

Doctor::Doctor(int _id, std::string _nombre, int _dinero, std::list<Enfermedad>* _pendientes)
	: id(_id), nombre(_nombre), dinero(std::make_shared<int>(_dinero)),
	  pendientes(_pendientes ? _pendientes : new std::list<Enfermedad>()) {}

Doctor::Doctor(const Doctor& other)
	: id(other.id), nombre(other.nombre), dinero(other.dinero),
	  pendientes(other.pendientes ? new std::list<Enfermedad>(*other.pendientes) : new std::list<Enfermedad>()) {}

	Doctor& Doctor::operator=(const Doctor& other) {
		if (this != &other) {
			id = other.id;
			nombre = other.nombre;
		dinero = other.dinero;
			if (pendientes != nullptr) delete pendientes;
			pendientes = other.pendientes ? new std::list<Enfermedad>(*other.pendientes) : new std::list<Enfermedad>();
		}
		return *this;
	}

	bool Doctor::operator==(const Doctor& other) const {
		return id == other.id && nombre == other.nombre;
	}

	bool Doctor::operator!=(const Doctor& other) const {
		return !(*this == other);
	}

	bool Doctor::operator<(const Doctor& other) const {
		return id < other.id;
	}

	int Doctor::cobrar() {
		// Recursivo: suma prioridades y vacía la lista de pendientes
		if (pendientes == nullptr || pendientes->empty()) return 0;
		Enfermedad e = pendientes->front();
		pendientes->pop_front();
		int subtotal = cobrar();
	int amount = e.prioridad();
	setDinero(getDinero() + amount);
	return amount + subtotal;
}

	Paciente::Paciente() : id(static_cast<int>(INFINITY)), nombre(""),
		enfermedades(new std::list<Enfermedad>()), historial(new std::stack<std::pair<Enfermedad, Doctor>>()) {}

	Paciente::~Paciente() { delete enfermedades; delete historial; }

	Paciente::Paciente(int _id, std::string _nombre)
		: id(_id), nombre(_nombre), enfermedades(new std::list<Enfermedad>()), historial(new std::stack<std::pair<Enfermedad, Doctor>>()) {}

	Paciente::Paciente(int _id, std::string _nombre, std::list<Enfermedad>* _enfermedades, std::stack<std::pair<Enfermedad, Doctor>>* _historial)
		: id(_id), nombre(_nombre),
		  enfermedades(_enfermedades ? _enfermedades : new std::list<Enfermedad>()),
		  historial(_historial ? _historial : new std::stack<std::pair<Enfermedad, Doctor>>()) {}

	Paciente::Paciente(const Paciente& other)
		: id(other.id), nombre(other.nombre),
		  enfermedades(other.enfermedades ? new std::list<Enfermedad>(*other.enfermedades) : new std::list<Enfermedad>()),
		  historial(other.historial ? new std::stack<std::pair<Enfermedad, Doctor>>(*other.historial) : new std::stack<std::pair<Enfermedad, Doctor>>()) {}

	Paciente& Paciente::operator=(const Paciente& other) {
		if (this != &other) {
			id = other.id;
			nombre = other.nombre;
			if (enfermedades != nullptr) delete enfermedades;
			if (historial != nullptr) delete historial;
			enfermedades = other.enfermedades ? new std::list<Enfermedad>(*other.enfermedades) : new std::list<Enfermedad>();
			historial = other.historial ? new std::stack<std::pair<Enfermedad, Doctor>>(*other.historial) : new std::stack<std::pair<Enfermedad, Doctor>>();
		}
		return *this;
	}

	bool Paciente::operator==(const Paciente& other) const {
		return id == other.id && nombre == other.nombre;
	}

	bool Paciente::operator!=(const Paciente& other) const {
		return !(*this == other);
	}

	std::list<Enfermedad>::iterator Paciente::prioridadPaciente() const {
		static std::list<Enfermedad> empty;
		if (enfermedades == nullptr || enfermedades->empty()) return empty.end();
		auto list_ptr = const_cast<std::list<Enfermedad>*>(enfermedades);
		auto it = list_ptr->begin();
		auto best = it;
		for (; it != list_ptr->end(); ++it) {
			if (best->prioridad() < it->prioridad()) best = it;
		}
		return best;
	}

	bool Paciente::operator<(const Paciente& other) const {
	auto max_priority = [](const std::list<Enfermedad>* l) -> int {
		if (l == nullptr || l->empty()) return INT_MAX;
		int best = l->begin()->prioridad();
		for (const auto& e : *l) {
			best = std::max(best, e.prioridad());
			}
			return best;
		};
	// Invertimos para que mayor prioridad sea "menor" en la cola.
	return max_priority(enfermedades) > max_priority(other.enfermedades);
}

	Enfermedad Paciente::tratarEnfermedad(Doctor* d) {
		if (enfermedades == nullptr || enfermedades->empty()) return Enfermedad();
		auto it = prioridadPaciente();
		Enfermedad e = *it;
		enfermedades->erase(it);
		if (d != nullptr) {
			historial->push(std::make_pair(e, *d));
			d->getPendientes()->push_back(e);
		}
		return e;
	}

	void Paciente::darAlta(Doctor* d) { (void)d; }

	Hospital::Hospital() : doctores(new std::deque<Doctor>()), almacen(new std::list<Medicamento>()), urgencias(new std::priority_queue<Paciente>()) {}

	Hospital::Hospital(std::deque<Doctor>* _doctores, std::list<Medicamento>* _almacen, std::priority_queue<Paciente>* _urgencias)
		: doctores(_doctores ? _doctores : new std::deque<Doctor>()),
		  almacen(_almacen ? _almacen : new std::list<Medicamento>()),
		  urgencias(_urgencias ? _urgencias : new std::priority_queue<Paciente>()) {}

	bool Hospital::insertMedicamento(Medicamento* m) const {
		if (m == nullptr) return false;
		almacen->push_back(*m);
		return true;
	}

	bool Hospital::insertDoctor(Doctor* d) const {
		if (d == nullptr) return false;
		doctores->push_back(*d);
		return true;
	}

	bool Hospital::insertPaciente(Paciente* p) const {
		if (p == nullptr) return false;
		urgencias->push(*p);
		return true;
	}

	std::list<Medicamento>* Hospital::reponerStock_k(int k) {
		// Calcula lo que falta para llegar a k unidades
		auto* faltantes = new std::list<Medicamento>();
		if (almacen == nullptr || almacen->empty()) return faltantes;
		for (const auto& m : *almacen) {
			int diff = k - m.getCantidad();
			if (diff > 0) {
				Medicamento* tmp = m.copyCantidad(diff);
				faltantes->push_back(*tmp);
				delete tmp;
			}
		}
		return faltantes;
	}

	std::list<Medicamento>* Hospital::reponerStock_niveles(std::list<Medicamento>* nivelesAdecuados) {
		// Calcula lo que falta para llegar a los niveles adecuados
		auto* faltantes = new std::list<Medicamento>();
		if (almacen == nullptr || almacen->empty()) return faltantes;
		if (nivelesAdecuados == nullptr || nivelesAdecuados->empty()) return faltantes;
		for (const auto& nivel : *nivelesAdecuados) {
			for (const auto& stock : *almacen) {
				if (stock == nivel) {
					int diff = nivel.getCantidad() - stock.getCantidad();
					if (diff > 0) {
						Medicamento* tmp = nivel.copyCantidad(diff);
						faltantes->push_back(*tmp);
						delete tmp;
					}
					break;
				}
			}
		}
		return faltantes;
	}

std::pair<Doctor, Paciente>* Hospital::treatPaciente() {
	// Atiende al paciente con mayor prioridad usando el primer doctor
	if (doctores == nullptr || doctores->empty()) return nullptr;
	if (urgencias == nullptr || urgencias->empty()) return nullptr;

	Doctor doctor = doctores->front();
	doctores->pop_front();

		Paciente paciente = urgencias->top();
		urgencias->pop();

	paciente.tratarEnfermedad(&doctor);

	// Se reinsertan los pacientes para futuras llamadas, aunque no tengan enfermedades.
	urgencias->push(paciente);
	return new std::pair<Doctor, Paciente>(doctor, paciente);
}

	int Hospital::pagarDoctores() {
		// Recursivo: paga a todos los doctores
		if (doctores == nullptr || doctores->empty()) return 0;
		auto pagar_rec = [&](auto&& self, size_t idx) -> int {
			if (idx >= doctores->size()) return 0;
			int paid = (*doctores)[idx].cobrar();
			return paid + self(self, idx + 1);
		};
		return pagar_rec(pagar_rec, 0);
	}

	std::ostream& operator<<(std::ostream& os, const Medicamento& m) {
		os << "Medicamento(" << m.getId() << "," << m.getNombre() << "," << m.getTipo() << "," << m.getCantidad() << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Enfermedad& e) {
		os << "Enfermedad(" << e.getId() << "," << e.getNombre() << "," << e.getLetalidad() << "," << e.getUrgencia() << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Doctor& d) {
		os << "Doctor(" << d.getId() << "," << d.getNombre() << "," << d.getDinero() << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Paciente& p) {
		os << "Paciente(" << p.getId() << "," << p.getNombre() << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Hospital& h) {
		os << "Hospital(doctores=" << h.getDoctores()->size() << ", almacen=" << h.getAlmacen()->size() << ", urgencias=" << h.getUrgencias()->size() << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const std::pair<Doctor, Paciente>& p) {
		os << "(" << p.first << "," << p.second << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const std::pair<Enfermedad, Doctor>& p) {
		os << "(" << p.first << "," << p.second << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, std::stack<std::pair<Enfermedad, Doctor>>& s) {
		os << "[";
		bool first = true;
		while (!s.empty()) {
			if (!first) os << ",";
			first = false;
			os << s.top();
			s.pop();
		}
		os << "]";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, std::priority_queue<Paciente>& pq) {
		os << "[";
		bool first = true;
		auto copy = pq;
		while (!copy.empty()) {
			if (!first) os << ",";
			first = false;
			os << copy.top();
			copy.pop();
		}
		os << "]";
		return os;
	}
}
