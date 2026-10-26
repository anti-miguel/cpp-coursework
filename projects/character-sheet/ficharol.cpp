#include <iostream>
#include <string>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    const int numStats = 3;       // Fuerza, Destreza, Magia
    const int numOrigens = 6;    // Orígenes disponibles
    const int numProfesiones = 8; // Profesiones disponibles

    string statsNombres[numStats] = {"Fuerza", "Destreza", "Magia"};
    string origens[numOrigens] = {"Elfo", "Enano", "Hobbit", "Humano", "Orco", "Troll"};
    string profesiones[numProfesiones] = {"Arquero", "Bárbaro", "Curandero", "Druida", "Guerrero", "Mago", "Paladín", "Sacerdote"};

    // Modificadores por Origen
    int modOrigen[numOrigens][numStats] = {
        {-5, 15, 10}, // Elfo
        {25, 0, -5},  // Enano
        {-10, 25, 5}, // Hobbit
        {10, 5, 5},   // Humano
        {20, 5, -5},  // Orco
        {35, -15, 0}  // Troll
    };

    // Modificadores por Profesión
    int modProfesion[numProfesiones][numStats] = {
        {5, 20, -5},   // Arquero
        {30, 10, -20}, // Bárbaro
        {-5, 0, 25},   // Curandero
        {5, 5, 10},    // Druida
        {20, 5, -5},   // Guerrero
        {-10, 0, 30},  // Mago
        {15, 0, 5},    // Paladín
        {-5, 5, 20}    // Sacerdote
    };

    string nombre = "Sin Nombre";
    int stats[numStats] = {0};      // Tiradas iniciales
    int origen = -1;                // Índice del origen seleccionado
    int profesion = -1;             // Índice de la profesión seleccionada

    while (true) {
        cout << "\n-----------------------\n";
        cout << "MENU PRINCIPAL\n";
        cout << "1. Cambiar nombre\n";
        cout << "2. Cambiar origen\n";
        cout << "3. Cambiar profesión\n";
        cout << "4. Hacer tiradas aleatorias\n";
        cout << "5. Consultar tablas de modificadores\n";
        cout << "6. Salir\n";
        cout << "-----------------------\n";
        cout << "Selecciona una opción: ";
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            cout << "Introduce el nombre del personaje: ";
            cin.ignore();
            getline(cin, nombre);
        }
        else if (opcion == 2) {
            cout << "Selecciona un origen:\n";
            for (int i = 0; i < numOrigens; i++) {
                cout << i + 1 << ". " << origens[i] << "\n";
            }
            cin >> origen;
            if (origen < 1 || origen > numOrigens) {
                cout << "Origen no válido.\n";
                origen = -1;
            } else {
                origen--; // Ajustar índice
                cout << "Has seleccionado: " << origens[origen] << "\n";
            }
        }
        else if (opcion == 3) {
            cout << "Selecciona una profesión:\n";
            for (int i = 0; i < numProfesiones; i++) {
                cout << i + 1 << ". " << profesiones[i] << "\n";
            }
            cin >> profesion;
            if (profesion < 1 || profesion > numProfesiones) {
                cout << "Profesión no válida.\n";
                profesion = -1;
            } else {
                profesion--; // Ajustar índice
                cout << "Has seleccionado: " << profesiones[profesion] << "\n";
            }
        }
        else if (opcion == 4) {
            cout << "Tirando estadísticas...\n";
            for (int i = 0; i < numStats; i++) {
                stats[i] = 50 + rand() % 51; // Tiradas entre 50 y 100
            }
        }
        else if (opcion == 5) {
            cout << "\nTABLAS DE MODIFICADORES\n";

            cout << "\nPor Origen:\n";
            cout << "Origen\t\tFuerza\tDestreza\tMagia\n";
            for (int i = 0; i < numOrigens; i++) {
                cout << origens[i] << "\t" << modOrigen[i][0] << "\t" << modOrigen[i][1] << "\t\t" << modOrigen[i][2] << "\n";
            }

            cout << "\nPor Profesión:\n";
            cout << "Profesión\tFuerza\tDestreza\tMagia\n";
            for (int i = 0; i < numProfesiones; i++) {
                cout << profesiones[i] << "\t" << modProfesion[i][0] << "\t" << modProfesion[i][1] << "\t\t" << modProfesion[i][2] << "\n";
            }
        }
        else if (opcion == 6) {
            cout << "Saliendo del programa...\n";
            break;
        }
        else {
            cout << "Opción no válida. Inténtalo de nuevo.\n";
        }

        // Mostrar ficha del personaje
        cout << "\nFICHA RPG\n";
        cout << "Nombre: " << nombre << "\n";
        cout << "Origen: " << (origen >= 0 ? origens[origen] : "No seleccionado") << "\n";
        cout << "Profesión: " << (profesion >= 0 ? profesiones[profesion] : "No seleccionada") << "\n";
        cout << "Tirada\tMod. Origen\tMod. Profesión\tTotal\n";
        for (int i = 0; i < numStats; i++) {
            int total = stats[i] +
                        (origen >= 0 ? modOrigen[origen][i] : 0) +
                        (profesion >= 0 ? modProfesion[profesion][i] : 0);
            cout << stats[i] << "\t" 
                 << (origen >= 0 ? modOrigen[origen][i] : 0) << "\t\t" 
                 << (profesion >= 0 ? modProfesion[profesion][i] : 0) << "\t\t" 
                 << total << "\n";
        }
    }

    return 0;
}
