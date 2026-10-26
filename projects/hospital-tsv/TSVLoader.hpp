#pragma once
#include "libtest.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace HospitalLoader {

    // Estructura temporal para pacientes pendientes de procesar
    struct PendingPatient {
        int id;
        std::string nombre;
        std::string listaEnfs; // "1;2;3"
    };

    // Función principal para cargar datos desde TSV
    bool loadFromTSV(const std::string& filename, Hospitalnames::Hospital& hosp, std::string& errorMsg);

    // Funciones auxiliares para parsear cada tipo de entidad
    bool parseMedicamento(const std::vector<std::string>& cols, int lineno, Hospitalnames::Hospital& hosp, std::string& errorMsg);
    bool parseEnfermedad(const std::vector<std::string>& cols, int lineno, std::unordered_map<int, Hospitalnames::Enfermedad>& enferMap, std::string& errorMsg);
    bool parseDoctor(const std::vector<std::string>& cols, int lineno, Hospitalnames::Hospital& hosp, std::string& errorMsg);
    bool parsePaciente(const std::vector<std::string>& cols, int lineno, std::vector<PendingPatient>& pendientes, std::string& errorMsg);
    
    // Procesar pacientes pendientes después de cargar todas las enfermedades
    void processPendingPatients(const std::vector<PendingPatient>& pendientes, 
                                const std::unordered_map<int, Hospitalnames::Enfermedad>& enferMap,
                                Hospitalnames::Hospital& hosp);

    // Utilidades
    std::string trim(const std::string& s);
    std::vector<std::string> split(const std::string& s, char delim);
    std::string toUpper(const std::string& s);

}

