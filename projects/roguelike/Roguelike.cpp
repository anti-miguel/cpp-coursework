#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#endif
#include <thread>
#include <chrono>
using namespace std;

// Estructura para representar un arma
struct Arma {
    string nombre;
    int daño;
    float cooldown; // Tiempo de espera entre ataques en segundos
};

// Estructura para representar un enemigo
struct Enemigo {
    string nombre;
    int vida;
    float velocidadAtaque; // Ataques por segundo
    int daño;
};

// Estructura para representar un objeto
struct Objeto {
    string nombre;
    string tipo; // "curacion" o "arma"
    int efecto;  // Puntos de curación o daño base
};

// Sistema de inventario
class Inventario {
private:
    vector<Objeto> objetos;

public:
    void agregarObjeto(const Objeto& objeto) {
        objetos.push_back(objeto);
        cout << "Objeto añadido al inventario: " << objeto.nombre << endl;
    }

    void mostrarInventario() const {
        if (objetos.empty()) {
            cout << "El inventario está vacío.\n";
            return;
        }
        cout << "\n--- Inventario ---\n";
        for (size_t i = 0; i < objetos.size(); ++i) {
            cout << i + 1 << ". " << objetos[i].nombre << " (" << objetos[i].tipo << ")\n";
        }
        cout << "------------------\n";
    }

    Objeto usarObjeto(int indice) {
        if (indice < 1 || indice > objetos.size()) {
            cout << "Índice inválido.\n";
            return {"", "", 0};
        }
        Objeto objeto = objetos[indice - 1];
        objetos.erase(objetos.begin() + indice - 1);
        return objeto;
    }
};

// Función para generar enemigos
Enemigo generarEnemigoAleatorio() {
    const vector<string> nombres = {"Goblin", "Orco", "Troll", "Esqueleto"};
    int vida = rand() % 50 + 50;        // Vida entre 50 y 100
    float velocidadAtaque = 1.0f + (rand() % 10) / 10.0f; // Entre 1 y 2 ataques por segundo
    int daño = rand() % 20 + 10;       // Daño entre 10 y 30

    return {nombres[rand() % nombres.size()], vida, velocidadAtaque, daño};
}

// Combate entre jugador y enemigo
void combateJugadorEnemigo(int& vidaJugador, float velocidadAtaqueJugador, Arma armaJugador, Enemigo enemigo) {
    cout << "¡Te has encontrado con un " << enemigo.nombre << "!\n";
    cout << "Vida del enemigo: " << enemigo.vida << "\n";

    float cooldownJugador = 1.0f / velocidadAtaqueJugador;
    float cooldownEnemigo = 1.0f / enemigo.velocidadAtaque;

    auto tiempoInicioJugador = chrono::steady_clock::now();
    auto tiempoInicioEnemigo = chrono::steady_clock::now();

    while (vidaJugador > 0 && enemigo.vida > 0) {
        auto tiempoActual = chrono::steady_clock::now();
        float tiempoJugador = chrono::duration<float>(tiempoActual - tiempoInicioJugador).count();
        float tiempoEnemigo = chrono::duration<float>(tiempoActual - tiempoInicioEnemigo).count();

        // Ataque del jugador
        if (tiempoJugador >= cooldownJugador) {
            enemigo.vida -= armaJugador.daño;
            cout << "¡Golpeaste al " << enemigo.nombre << " con " << armaJugador.nombre << "! Daño: " << armaJugador.daño << ". Vida restante: " << enemigo.vida << "\n";
            tiempoInicioJugador = chrono::steady_clock::now();
        }

        // Ataque del enemigo
        if (tiempoEnemigo >= cooldownEnemigo) {
            vidaJugador -= enemigo.daño;
            cout << enemigo.nombre << " te atacó. Daño: " << enemigo.daño << ". Tu vida restante: " << vidaJugador << "\n";
            tiempoInicioEnemigo = chrono::steady_clock::now();
        }

        this_thread::sleep_for(chrono::milliseconds(100)); // Reducir el consumo de CPU
    }

    if (vidaJugador > 0) {
        cout << "¡Has derrotado al " << enemigo.nombre << "!\n";
    } else {
        cout << "Fuiste derrotado por el " << enemigo.nombre << ".\n";
    }
}

// Generar el mapa
void generarMapa(vector<vector<char>>& mapa, int filas, int columnas, int& santuarioX, int& santuarioY) {
    const char terreno[] = {' ', 'C', 'H', 'M', 'E', 'O'};
    int tamanoTerreno = sizeof(terreno) / sizeof(terreno[0]);

    srand(time(0));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            mapa[i][j] = terreno[rand() % tamanoTerreno];
        }
    }

    // Colocar santuario en una posición fija
    santuarioX = rand() % filas;
    santuarioY = rand() % columnas;
    mapa[santuarioX][santuarioY] = 'S';

    // Colocar al jugador en la posición inicial
    mapa[0][0] = 'X';
}

// Mostrar el mapa
void mostrarMapa(const vector<vector<char>>& mapa) {
    for (const auto& fila : mapa) {
        for (const auto& celda : fila) {
            cout << celda << ' ';
        }
        cout << '\n';
    }
}

// Manejar interacciones del mapa
void interactuarMapa(char celda, int& vidaJugador, int& experiencia, Inventario& inventario, float velocidadAtaqueJugador, Arma& armaJugador) {
    if (celda == 'C') {
        cout << "Exploraste una ciudad abandonada y encontraste un objeto.\n";
        inventario.agregarObjeto({"Poción Grande", "curacion", 50});
    } else if (celda == 'H') {
        cout << "Entraste a una casa y recuperaste 10 puntos de vida.\n";
        vidaJugador += 10;
    } else if (celda == 'M') {
        cout << "Encontraste un campamento militar. ¡Prepárate para luchar!\n";
        Enemigo enemigo = generarEnemigoAleatorio();
        combateJugadorEnemigo(vidaJugador, velocidadAtaqueJugador, armaJugador, enemigo);
    } else if (celda == 'E') {
        cout << "Un enemigo apareció en tu camino. ¡Es hora de combatir!\n";
        Enemigo enemigo = generarEnemigoAleatorio();
        combateJugadorEnemigo(vidaJugador, velocidadAtaqueJugador, armaJugador, enemigo);
    } else if (celda == 'O') {
        cout << "Recogiste un objeto misterioso.\n";
        inventario.agregarObjeto({"Espada Rápida", "arma", 25});
    }
}

// Mover al jugador en el mapa
void moverJugador(vector<vector<char>>& mapa, int& jugadorX, int& jugadorY, char direccion, int santuarioX, int santuarioY, int& vidaJugador, int& experiencia, Inventario& inventario, float velocidadAtaqueJugador, Arma& armaJugador) {
    int nuevoX = jugadorX, nuevoY = jugadorY;

    if (direccion == 'w') --nuevoX;
    else if (direccion == 's') ++nuevoX;
    else if (direccion == 'a') --nuevoY;
    else if (direccion == 'd') ++nuevoY;

    if (nuevoX < 0 || nuevoX >= mapa.size() || nuevoY < 0 || nuevoY >= mapa[0].size()) {
        cout << "¡Movimiento inválido! Estás fuera de los límites del mapa.\n";
        return;
    }

    if (nuevoX == santuarioX && nuevoY == santuarioY) {
        cout << "Llegaste al Santuario. Aquí puedes descansar y recuperar toda tu vida.\n";
        vidaJugador = 100;
        return;
    }

    interactuarMapa(mapa[nuevoX][nuevoY], vidaJugador, experiencia, inventario, velocidadAtaqueJugador, armaJugador);

    mapa[jugadorX][jugadorY] = ' '; // Limpia la posición anterior
    jugadorX = nuevoX;
    jugadorY = nuevoY;
    mapa[jugadorX][jugadorY] = 'X'; // Actualiza la posición del jugador
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    srand(time(0));

    const int filas = 10, columnas = 10;
    vector<vector<char>> mapa(filas, vector<char>(columnas));
    int santuarioX, santuarioY;

    generarMapa(mapa, filas, columnas, santuarioX, santuarioY);

    string nombreJugador = "Aventurero";
    int vidaJugador = 100, experiencia = 0, jugadorX = 0, jugadorY = 0;
    float velocidadAtaqueJugador = 1.5f; // Ataques por segundo
    Arma armaJugador = {"Espada Básica", 15, 1.0f / 1.5f};
    Inventario inventario;

    while (true) {
        cout << "\n--- Mapa ---\n";
        mostrarMapa(mapa);
        cout << "Tu posición: (" << jugadorX << ", " << jugadorY << ")\n";
        cout << "Muévete con W/A/S/D (o Q para salir): ";
        char movimiento;
        cin >> movimiento;

        if (movimiento == 'q') {
            cout << "¡Hasta la próxima!\n";
            break;
        }

        moverJugador(mapa, jugadorX, jugadorY, movimiento, santuarioX, santuarioY, vidaJugador, experiencia, inventario, velocidadAtaqueJugador, armaJugador);
        if (vidaJugador <= 0) {
            cout << "Has muerto. Fin del juego.\n";
            break;
        }
    }

    return 0;
}
