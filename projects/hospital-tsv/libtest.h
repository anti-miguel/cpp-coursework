#pragma once
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <utility>

namespace Hospitalnames {

    class Medicamento {
    private:
        int id;
        std::string nombre;
        std::string tipo;
        int cantidad;

    public:
        Medicamento() : id(0), nombre(""), tipo(""), cantidad(0) {}
        Medicamento(int id, const std::string& nombre, const std::string& tipo, int cantidad)
            : id(id), nombre(nombre), tipo(tipo), cantidad(cantidad) {
        }

        int getID() const { return id; }
        std::string getNombre() const { return nombre; }
        std::string getTipo() const { return tipo; }
        int getCantidad() const { return cantidad; }

        void setID(int id_) { id = id_; }
        void setNombre(const std::string& nombre_) { nombre = nombre_; }
        void setTipo(const std::string& tipo_) { tipo = tipo_; }
        void setCantidad(int cantidad_) { cantidad = cantidad_; }
    };

    class Enfermedad {
    private:
        int id;
        std::string nombre;
        int letalidad;
        int urgencia;

    public:
        Enfermedad() : id(0), nombre(""), letalidad(0), urgencia(0) {}
        Enfermedad(int id, const std::string& nombre, int letalidad, int urgencia)
            : id(id), nombre(nombre), letalidad(letalidad), urgencia(urgencia) {
        }

        int prioridad() const { return letalidad * urgencia; }

        int getID() const { return id; }
        std::string getNombre() const { return nombre; }
        int getLetalidad() const { return letalidad; }
        int getUrgencia() const { return urgencia; }

        void setID(int id_) { id = id_; }
        void setNombre(const std::string& nombre_) { nombre = nombre_; }
        void setLetalidad(int l) { letalidad = l; }
        void setUrgencia(int u) { urgencia = u; }
    };

    class Doctor {
    private:
        int id;
        std::string nombre;
        int dinero;
        std::list<Enfermedad>* pendientes;

        static int cobrarRec(std::list<Enfermedad>::const_iterator it, std::list<Enfermedad>::const_iterator end) {
            if (it == end) return 0;
            auto nextIt = it; ++nextIt;
            return it->prioridad() + cobrarRec(nextIt, end);
        }

    public:
        Doctor() : id(0), nombre(""), dinero(0), pendientes(new std::list<Enfermedad>()) {}
        Doctor(int id, const std::string& nombre, int dinero)
            : id(id), nombre(nombre), dinero(dinero), pendientes(new std::list<Enfermedad>()) {
        }
        Doctor(const Doctor& other) 
            : id(other.id), nombre(other.nombre), dinero(other.dinero), pendientes(new std::list<Enfermedad>(*other.pendientes)) {
        }
        Doctor& operator=(const Doctor& other) {
            if (this != &other) {
                id = other.id;
                nombre = other.nombre;
                dinero = other.dinero;
                *pendientes = *other.pendientes;
            }
            return *this;
        }
        ~Doctor() { delete pendientes; }

        int getID() const { return id; }
        std::string getNombre() const { return nombre; }
        int getDinero() const { return dinero; }
        const std::list<Enfermedad>& getPendientes() const { return *pendientes; }

        void setID(int id_) { id = id_; }
        void setNombre(const std::string& nombre_) { nombre = nombre_; }
        void setDinero(int d) { dinero = d; }

        void addPendiente(const Enfermedad& e) { pendientes->push_back(e); }
        void resetEnfermedadesSinPagar() { pendientes->clear(); }

        int cobrar() const { 
            return cobrarRec(pendientes->cbegin(), pendientes->cend()); 
        }
    };

    class Paciente {
    private:
        int id;
        std::string nombre;
        std::list<Enfermedad>* enfermedades;
        std::stack<std::pair<Enfermedad, Doctor>>* historial;

    public:
        Paciente() : id(0), nombre(""), enfermedades(new std::list<Enfermedad>()), historial(new std::stack<std::pair<Enfermedad, Doctor>>()) {}
        Paciente(int id, const std::string& nombre, const std::list<Enfermedad>& enf)
            : id(id), nombre(nombre), enfermedades(new std::list<Enfermedad>(enf)), historial(new std::stack<std::pair<Enfermedad, Doctor>>()) {
        }
        Paciente(const Paciente& other)
            : id(other.id), nombre(other.nombre), enfermedades(new std::list<Enfermedad>(*other.enfermedades)), historial(new std::stack<std::pair<Enfermedad, Doctor>>(*other.historial)) {
        }
        Paciente& operator=(const Paciente& other) {
            if (this != &other) {
                id = other.id;
                nombre = other.nombre;
                *enfermedades = *other.enfermedades;
                *historial = *other.historial;
            }
            return *this;
        }
        ~Paciente() { delete enfermedades; delete historial; }

        int getID() const { return id; }
        std::string getNombre() const { return nombre; }
        std::list<Enfermedad>& getEnfermedades() { return *enfermedades; }
        const std::list<Enfermedad>& getEnfermedadesConst() const { return *enfermedades; }
        std::stack<std::pair<Enfermedad, Doctor>>& getHistorial() { return *historial; }

        void setID(int id_) { id = id_; }
        void setNombre(const std::string& nombre_) { nombre = nombre_; }
        void setEnfermedades(const std::list<Enfermedad>& e) { *enfermedades = e; }

        int prioridadPaciente() const;

        Enfermedad tratarEnfermedad(Doctor& d);

        void darAlta(Doctor& d) {}

        bool operator<(const Paciente& other) const {
            return this->prioridadPaciente() < other.prioridadPaciente();
        }
    };

    class Hospital {
    private:
        std::queue<Doctor>* doctores;
        std::list<Medicamento>* almacen;
        std::priority_queue<Paciente>* urgencias;

        int pagarDoctoresRec(std::queue<Doctor>& q);

    public:
        Hospital() : doctores(new std::queue<Doctor>()), almacen(new std::list<Medicamento>()), urgencias(new std::priority_queue<Paciente>()) {}
        ~Hospital() { delete doctores; delete almacen; delete urgencias; }

        std::list<Medicamento>* getAlmacen() { return almacen; }
        const std::list<Medicamento>* getAlmacen() const { return almacen; }
        std::list<Medicamento>* getStock() { return almacen; }
        const std::priority_queue<Paciente>& getPacientesConst() const { return *urgencias; }
        std::priority_queue<Paciente> getPacientes() const { return *urgencias; }
        std::queue<Doctor>* getDoctores() { return doctores; }
        const std::queue<Doctor>* getDoctores() const { return doctores; }
        std::priority_queue<Paciente>* getUrgencias() { return urgencias; }
        const std::priority_queue<Paciente>* getUrgencias() const { return urgencias; }

        void insertMedicamento(const Medicamento& medicamento) { almacen->push_back(medicamento); }
        void removeMedicamento(int id) {
            for (auto it = almacen->begin(); it != almacen->end(); ++it) {
                if (it->getID() == id) { almacen->erase(it); break; }
            }
        }

        void insertDoctor(const Doctor& doctor) { doctores->push(doctor); }
        
        void insertPaciente(const Paciente& paciente) { urgencias->push(paciente); }
        void removePaciente() { if (!urgencias->empty()) urgencias->pop(); }

        std::list<Medicamento> reponerStock_k(int k) const;

        std::list<Medicamento> reponerStock_niveles(const std::list<Medicamento>& nivelesAdecuados) const;

        std::pair<Doctor, Paciente> treatPaciente();

        int pagarDoctores();
    };

}
