#pragma once
#include <vector>
#include <list>
#include <deque> // cola doblemente enlazada, permite acceso no FIFO con cuidado
#include <queue> // cola FIFO y priority_queue implementada con vector + algoritmos
#include <stack>
#include <string>
#include <iostream>
#include <memory>

namespace Hospitalnames {
	class Medicamento {
	private:
		int id;
		std::string nombre;
		std::string tipo;
		int cantidad;

	public:
		Medicamento();
		Medicamento(int _id, std::string _nombre, std::string _tipo, int _cantidad);
		Medicamento(const Medicamento& other);
		Medicamento& operator=(const Medicamento& other);

		bool operator==(const Medicamento& other) const;
		bool operator!=(const Medicamento& other) const;
		bool operator<(const Medicamento& other) const;

		int getId() const { return id; };
		void setId(int _id) { id = _id; };
		std::string getNombre() const { return nombre; };
		void setNombre(std::string _nombre) { nombre = _nombre; };
		std::string getTipo() const { return tipo; };
		void setTipo(std::string _tipo) { tipo = _tipo; };
		int getCantidad() const { return cantidad; };
		void setCantidad(int _cantidad) { cantidad = _cantidad; };

		Medicamento* copyCantidad(int k) const;
	};

	class Enfermedad {
	private:
		int id;
		std::string nombre;
		int letalidad;
		int urgencia;

	public:
		Enfermedad();
		Enfermedad(int _id, std::string _nombre, int _letalidad, int _urgencia);
		Enfermedad(const Enfermedad& other);
		Enfermedad& operator=(const Enfermedad& other);

		bool operator==(const Enfermedad& other) const;
		bool operator!=(const Enfermedad& other) const;
		bool operator<(const Enfermedad& other) const;

		int getId() const { return id; }
		std::string getNombre() const { return nombre; }
		int getLetalidad() const { return letalidad; }
		int getUrgencia() const { return urgencia; }

		int prioridad() const { return letalidad * urgencia; };
	};

	class Doctor {
	private:
		int id;
		std::string nombre;
		std::shared_ptr<int> dinero;
		std::list<Enfermedad>* pendientes;

	public:
		Doctor();
		~Doctor();
		Doctor(int _id, std::string _nombre, int _dinero);
		Doctor(int _id, std::string _nombre, int _dinero, std::list<Enfermedad>* _pendientes);
		Doctor(const Doctor& other);
		Doctor& operator=(const Doctor& other);

		bool operator==(const Doctor& other) const;
		bool operator!=(const Doctor& other) const;
		bool operator<(const Doctor& other) const;

		int getId() const { return id; }
		void setId(int _id) { id = _id; }
		std::string getNombre() const { return nombre; }
		void setNombre(std::string _nombre) { nombre = _nombre; }
		int getDinero() const { return dinero ? *dinero : 0; }
		void setDinero(int _dinero) { if (!dinero) dinero = std::make_shared<int>(_dinero); else *dinero = _dinero; }
		std::list<Enfermedad>* getPendientes() const { return pendientes; }
		void setPendientes(std::list<Enfermedad>* _pendientes) { pendientes = _pendientes; }

		int cobrar();
	};

	class Paciente {
	private:
		int id;
		std::string nombre;
		std::list<Enfermedad>* enfermedades;
		std::stack<std::pair<Enfermedad, Doctor>>* historial;

	public:
		Paciente();
		~Paciente();
		Paciente(int _id, std::string _nombre);
		Paciente(int _id, std::string _nombre, std::list<Enfermedad>* _enfermedades, std::stack<std::pair<Enfermedad, Doctor>>* _historial);
		Paciente(const Paciente& other);
		Paciente& operator=(const Paciente& other);

		int getId() const { return id; }
		void setId(int _id) { id = _id; }
		std::string getNombre() const { return nombre; }
		void setNombre(std::string _nombre) { nombre = _nombre; }
		std::list<Enfermedad>* getEnfermedades() const { return enfermedades; }
		void setEnfermedades(std::list<Enfermedad>* _enfermedades) { enfermedades = _enfermedades; }
		std::stack<std::pair<Enfermedad, Doctor>>* getHistorial() const { return historial; }
		void setHistorial(std::stack<std::pair<Enfermedad, Doctor>>* _historial) { historial = _historial; }

		void insertEnfermedad(Enfermedad* e) {
			if (e != nullptr) enfermedades->push_back(*e);
		}

		bool operator==(const Paciente& other) const;
		bool operator!=(const Paciente& other) const;
		bool operator<(const Paciente& other) const;

		std::list<Enfermedad>::iterator prioridadPaciente() const;
		Enfermedad tratarEnfermedad(Doctor* d);
		void darAlta(Doctor* d);
	};

	class Hospital {
	private:
		std::deque<Doctor>* doctores;
		std::list<Medicamento>* almacen;
		std::priority_queue<Paciente>* urgencias;

	public:
		Hospital();
		Hospital(std::deque<Doctor>* _doctores, std::list<Medicamento>* _almacen, std::priority_queue<Paciente>* _urgencias);

		std::deque<Doctor>* getDoctores() const { return doctores; };
		std::list<Medicamento>* getAlmacen() const { return almacen; };
		std::priority_queue<Paciente>* getUrgencias() const { return urgencias; };

		void setDoctores(std::deque<Doctor>* _doctores) { doctores = _doctores; };
		void setAlmacen(std::list<Medicamento>* _almacen) { almacen = _almacen; };
		void setUrgencias(std::priority_queue<Paciente>* _urgencias) { urgencias = _urgencias; };

		bool insertMedicamento(Medicamento* m) const;
		bool insertDoctor(Doctor* d) const;
		bool insertPaciente(Paciente* p) const;

		std::list<Medicamento>* reponerStock_k(int k);
		std::list<Medicamento>* reponerStock_niveles(std::list<Medicamento>* nivelesAdecuados);
		std::pair<Doctor, Paciente>* treatPaciente();
		int pagarDoctores();
	};

	std::ostream& operator<<(std::ostream& os, const Medicamento& m);
	std::ostream& operator<<(std::ostream& os, const Enfermedad& e);
	std::ostream& operator<<(std::ostream& os, const Doctor& d);
	std::ostream& operator<<(std::ostream& os, const Paciente& p);
	std::ostream& operator<<(std::ostream& os, const Hospital& h);
	std::ostream& operator<<(std::ostream& os, const std::pair<Doctor, Paciente>& p);
	std::ostream& operator<<(std::ostream& os, const std::pair<Enfermedad, Doctor>& p);
	std::ostream& operator<<(std::ostream& os, std::stack<std::pair<Enfermedad, Doctor>>& s);
	template<typename T>
	std::ostream& operator<<(std::ostream& os, std::list<T>& l) {
		os << "[";
		bool first = true;
		for (auto& item : l) {
			if (!first) os << ",";
			first = false;
			os << item;
		}
		os << "]";
		return os;
	}
	std::ostream& operator<<(std::ostream& os, std::priority_queue<Paciente>& pq);
}
