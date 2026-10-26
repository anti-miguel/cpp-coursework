#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#endif

#include "libtest.h"
#include "TSVLoader.hpp"

using namespace Hospitalnames;

void imprimirSeparador(const std::string& titulo) {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  " << titulo << "\n";
    std::cout << std::string(60, '=') << "\n";
}

void imprimirStock(const Hospital& hosp) {
    std::cout << "\nMedicamentos en stock:\n";
    if (auto almacenPtr = hosp.getAlmacen()) {
        if (almacenPtr->empty()) {
            std::cout << "  (almacen vacio)\n";
            return;
        }
        for (const auto& m : *almacenPtr) {
            std::cout << "  id=" << m.getID()
                << " | nombre=" << std::setw(15) << std::left << m.getNombre()
                << " | tipo=" << std::setw(15) << std::left << m.getTipo()
                << " | cantidad=" << m.getCantidad() << "\n";
        }
    }
    else {
        std::cout << "  (almacen nulo)\n";
    }
}

void imprimirDoctores(const Hospital& hosp) {
    std::cout << "\nDoctores (cola):\n";
    if (auto docsPtr = hosp.getDoctores()) {
        if (docsPtr->empty()) {
            std::cout << "  (no hay doctores en la cola)\n";
            return;
        }
        std::queue<Doctor> copia = *docsPtr;
        int idx = 0;
        while (!copia.empty()) {
            const Doctor& d = copia.front();
            std::cout << "  [" << ++idx << "] id=" << d.getID()
                << " | nombre=" << std::setw(20) << std::left << d.getNombre()
                << " | cobrar=" << d.cobrar() << " €\n";
            copia.pop();
        }
    }
    else {
        std::cout << "  (getter getDoctores() devuelve nullptr)\n";
    }
}

void imprimirPacientes(const Hospital& hosp) {
    std::cout << "\nPacientes en urgencias (por prioridad):\n";
    if (auto urgPtr = hosp.getUrgencias()) {
        if (urgPtr->empty()) {
            std::cout << "  (no hay pacientes en urgencias)\n";
            return;
        }
        auto copia = *urgPtr;
        int idx = 0;
        while (!copia.empty()) {
            const auto& p = copia.top();
            std::cout << "  [" << ++idx << "] id=" << p.getID()
                << " | nombre=" << std::setw(20) << std::left << p.getNombre()
                << " | prioridad=" << p.prioridadPaciente() << "\n";
            copia.pop();
        }
    }
    else {
        std::cout << "  (getter getUrgencias() devuelve nullptr)\n";
    }
}

void imprimirReposicion(const std::list<Medicamento>& reposicion) {
    if (reposicion.empty()) {
        std::cout << "  No se necesita reponer ningun medicamento.\n";
        return;
    }
    std::cout << "  Medicamentos a reponer:\n";
    for (const auto& m : reposicion) {
        if (m.getCantidad() > 0) {
            std::cout << "    id=" << m.getID()
                << " | nombre=" << std::setw(15) << std::left << m.getNombre()
                << " | cantidad necesaria=" << m.getCantidad() << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif
    std::string filename = "datos_mix.tsv";
    if (argc >= 2) filename = argv[1];

    Hospital hosp;
    std::string errorMsg;

    imprimirSeparador("CARGA DE DATOS DESDE TSV");
    // Cargar datos desde TSV
    if (!HospitalLoader::loadFromTSV(filename, hosp, errorMsg)) {
        std::cerr << "Error al cargar datos: " << errorMsg << "\n";
        return 1;
    }
    std::cout << "Carga completada desde " << filename << "\n";

    // Estado inicial
    imprimirSeparador("ESTADO INICIAL DEL HOSPITAL");
    imprimirStock(hosp);
    imprimirDoctores(hosp);
    imprimirPacientes(hosp);

    //FUNCION 1: reponerStock_k
    imprimirSeparador("FUNCION 1: reponerStock_k(k=100)");
    std::cout << "Calculando medicamentos necesarios para tener 100 unidades de cada uno:\n";
    auto reposicion_k = hosp.reponerStock_k(100);
    imprimirReposicion(reposicion_k);

    //FUNCION 2: reponerStock_niveles
    imprimirSeparador("FUNCION 2: reponerStock_niveles");
    std::cout << "Definiendo niveles adecuados de stock:\n";
    std::list<Medicamento> nivelesAdecuados;
    nivelesAdecuados.push_back(Medicamento(1, "Paracetamol", "Analgesico", 80));
    nivelesAdecuados.push_back(Medicamento(2, "Ibuprofeno", "Antiinflamatorio", 60));
    nivelesAdecuados.push_back(Medicamento(3, "Amoxicilina", "Antibiotico", 40));
    nivelesAdecuados.push_back(Medicamento(4, "Omeprazol", "Protector", 70));
    nivelesAdecuados.push_back(Medicamento(5, "Insulina", "Hormona", 30));
    
    for (const auto& nivel : nivelesAdecuados) {
        std::cout << "  id=" << nivel.getID() 
            << " | nombre=" << std::setw(15) << std::left << nivel.getNombre()
            << " | nivel objetivo=" << nivel.getCantidad() << "\n";
    }
    
    std::cout << "\nCalculando medicamentos necesarios para alcanzar estos niveles:\n";
    auto reposicion_niveles = hosp.reponerStock_niveles(nivelesAdecuados);
    imprimirReposicion(reposicion_niveles);

    //FUNCION 3: treatPaciente (múltiples tratamientos)
    imprimirSeparador("FUNCION 3: treatPaciente (MULTIPLES TRATAMIENTOS)");
    
    int tratamientosRealizados = 0;
    const int maxTratamientos = 5; // Limitar para no vaciar todo
    
    while (tratamientosRealizados < maxTratamientos) {
        auto res = hosp.treatPaciente();
        if (res.first.getNombre().empty() && res.second.getNombre().empty()) {
            std::cout << "No hay mas doctores o pacientes disponibles.\n";
            break;
        }
        tratamientosRealizados++;
        std::cout << "Tratamiento #" << tratamientosRealizados << ":\n";
        std::cout << "  Doctor: " << res.first.getNombre() 
            << " (id=" << res.first.getID() << ")\n";
        std::cout << "  Paciente: " << res.second.getNombre()
            << " (id=" << res.second.getID() << ")\n";
        std::cout << "  Prioridad del paciente ahora: " << res.second.prioridadPaciente() << "\n";
        
        // Mostrar estado después de cada tratamiento
        if (tratamientosRealizados < maxTratamientos) {
            std::cout << "\n  Estado actual:\n";
            std::cout << "    Pacientes restantes en urgencias: ";
            if (auto urgPtr = hosp.getUrgencias()) {
                std::cout << urgPtr->size() << "\n";
            } else {
                std::cout << "0\n";
            }
        }
    }

    // Estado después de tratamientos
    imprimirSeparador("ESTADO DESPUES DE TRATAMIENTOS");
    imprimirPacientes(hosp);
    imprimirDoctores(hosp);

    //FUNCION 4: pagarDoctores
    imprimirSeparador("FUNCION 4: pagarDoctores (RECURSIVA)");
    std::cout << "Calculando pagos a doctores basados en enfermedades tratadas:\n";
    int totalPagado = hosp.pagarDoctores();
    std::cout << "\nTotal pagado a todos los doctores: " << totalPagado << " €\n";
    
    // Mostrar estado de doctores después del pago
    std::cout << "\nEstado de doctores despues del pago:\n";
    imprimirDoctores(hosp);

    // Estado final
    imprimirSeparador("ESTADO FINAL DEL HOSPITAL");
    imprimirStock(hosp);
    imprimirDoctores(hosp);
    imprimirPacientes(hosp);
    
    return 0;
}
