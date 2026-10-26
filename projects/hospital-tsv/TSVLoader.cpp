#include "TSVLoader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>
#include <vector>
#include <unordered_map>

namespace HospitalLoader {

    std::string trim(const std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) return "";
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }

    std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> out;
        std::string token;
        std::istringstream ss(s);
        while (std::getline(ss, token, delim)) {
            out.push_back(trim(token));
        }
        return out;
    }

    std::string toUpper(const std::string& s) {
        std::string r = s;
        std::transform(r.begin(), r.end(), r.begin(), [](unsigned char c) { 
            return std::toupper(c); 
        });
        return r;
    }

    bool parseMedicamento(const std::vector<std::string>& cols, int lineno, Hospitalnames::Hospital& hosp, std::string& errorMsg) {
        // MED, id, nombre, tipo, cantidad
        if (cols.size() < 5) {
            errorMsg = "Línea " + std::to_string(lineno) + ": formato MED inválido (se requieren 5 campos)";
            return false;
        }
        try {
            int id = std::stoi(cols[1]);
            std::string nombre = cols[2];
            std::string tipo = cols[3];
            int cantidad = std::stoi(cols[4]);
            hosp.insertMedicamento(Hospitalnames::Medicamento(id, nombre, tipo, cantidad));
            return true;
        }
        catch (const std::exception& ex) {
            errorMsg = "Línea " + std::to_string(lineno) + ": error parseando MED -> " + std::string(ex.what());
            return false;
        }
    }

    bool parseEnfermedad(const std::vector<std::string>& cols, int lineno, std::unordered_map<int, Hospitalnames::Enfermedad>& enferMap, std::string& errorMsg) {
        // ENF, id, nombre, letalidad, urgencia
        if (cols.size() < 5) {
            errorMsg = "Línea " + std::to_string(lineno) + ": formato ENF inválido (se requieren 5 campos)";
            return false;
        }
        try {
            int id = std::stoi(cols[1]);
            std::string nombre = cols[2];
            int letalidad = std::stoi(cols[3]);
            int urgencia = std::stoi(cols[4]);
            enferMap.emplace(id, Hospitalnames::Enfermedad(id, nombre, letalidad, urgencia));
            return true;
        }
        catch (const std::exception& ex) {
            errorMsg = "Línea " + std::to_string(lineno) + ": error parseando ENF -> " + std::string(ex.what());
            return false;
        }
    }

    bool parseDoctor(const std::vector<std::string>& cols, int lineno, Hospitalnames::Hospital& hosp, std::string& errorMsg) {
        // DOC, id, nombre, dinero
        if (cols.size() < 4) {
            errorMsg = "Línea " + std::to_string(lineno) + ": formato DOC inválido (se requieren 4 campos)";
            return false;
        }
        try {
            int id = std::stoi(cols[1]);
            std::string nombre = cols[2];
            int dinero = std::stoi(cols[3]);
            hosp.insertDoctor(Hospitalnames::Doctor(id, nombre, dinero));
            return true;
        }
        catch (const std::exception& ex) {
            errorMsg = "Línea " + std::to_string(lineno) + ": error parseando DOC -> " + std::string(ex.what());
            return false;
        }
    }

    bool parsePaciente(const std::vector<std::string>& cols, int lineno, std::vector<PendingPatient>& pendientes, std::string& errorMsg) {
        // PAC, id, nombre, enf1;enf2;...
        if (cols.size() < 4) {
            errorMsg = "Línea " + std::to_string(lineno) + ": formato PAC inválido (se requieren 4 campos)";
            return false;
        }
        try {
            PendingPatient pp;
            pp.id = std::stoi(cols[1]);
            pp.nombre = cols[2];
            pp.listaEnfs = cols[3];
            pendientes.push_back(std::move(pp));
            return true;
        }
        catch (const std::exception& ex) {
            errorMsg = "Línea " + std::to_string(lineno) + ": error parseando PAC -> " + std::string(ex.what());
            return false;
        }
    }

    void processPendingPatients(const std::vector<PendingPatient>& pendientes, 
                                const std::unordered_map<int, Hospitalnames::Enfermedad>& enferMap,
                                Hospitalnames::Hospital& hosp) {
        for (const auto& pp : pendientes) {
            std::list<Hospitalnames::Enfermedad> enfList;
            auto ids = split(pp.listaEnfs, ';');
            for (const auto& idstr : ids) {
                if (idstr.empty()) continue;
                try {
                    int eid = std::stoi(idstr);
                    auto it = enferMap.find(eid);
                    if (it != enferMap.end()) {
                        enfList.push_back(it->second);
                    }
                    else {
                        std::cerr << "Aviso: paciente " << pp.id << " refiere enfermedad id=" << eid << " no definida\n";
                    }
                }
                catch (...) {
                    std::cerr << "Aviso: id de enfermedad inválido en paciente " << pp.id << ": '" << idstr << "'\n";
                }
            }
            // Crear paciente con la lista de enfermedades
            Hospitalnames::Paciente p(pp.id, pp.nombre, enfList);
            hosp.insertPaciente(p);
        }
    }

    bool loadFromTSV(const std::string& filename, Hospitalnames::Hospital& hosp, std::string& errorMsg) {
        std::ifstream f(filename);
        if (!f.is_open()) {
            errorMsg = "No se pudo abrir el archivo: " + filename;
            return false;
        }

        std::unordered_map<int, Hospitalnames::Enfermedad> enferMap;
        std::vector<PendingPatient> pendientesPacientes;

        std::string line;
        int lineno = 0;
        bool hasErrors = false;

        while (std::getline(f, line)) {
            ++lineno;
            line = trim(line);
            if (line.empty()) continue;
            if (line[0] == '#') continue; // Comentarios

            auto cols = split(line, '\t');
            if (cols.empty()) continue;

            std::string tipo = toUpper(cols[0]);
            std::string lineError;

            if (tipo == "MED" || tipo == "MEDICAMENTO" || tipo == "M") {
                if (!parseMedicamento(cols, lineno, hosp, lineError)) {
                    std::cerr << lineError << "\n";
                    hasErrors = true;
                }
            }
            else if (tipo == "ENF" || tipo == "ENFERMEDAD" || tipo == "E") {
                if (!parseEnfermedad(cols, lineno, enferMap, lineError)) {
                    std::cerr << lineError << "\n";
                    hasErrors = true;
                }
            }
            else if (tipo == "DOC" || tipo == "DOCTOR" || tipo == "D") {
                if (!parseDoctor(cols, lineno, hosp, lineError)) {
                    std::cerr << lineError << "\n";
                    hasErrors = true;
                }
            }
            else if (tipo == "PAC" || tipo == "PACIENTE" || tipo == "P") {
                if (!parsePaciente(cols, lineno, pendientesPacientes, lineError)) {
                    std::cerr << lineError << "\n";
                    hasErrors = true;
                }
            }
            else {
                std::cerr << "Línea " << lineno << ": tipo desconocido '" << cols[0] << "'\n";
                hasErrors = true;
            }
        }

        // Procesar pacientes pendientes después de cargar todas las enfermedades
        processPendingPatients(pendientesPacientes, enferMap, hosp);

        if (hasErrors) {
            errorMsg = "Se encontraron errores durante la carga. Revisa los mensajes anteriores.";
            return false;
        }

        return true;
    }

}

