#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <cmath>
#ifdef _WIN32
#include <windows.h>
#endif
#include <conio.h> // Para entrada en tiempo real con _getch()
using namespace std;

// Tamaño del mapa
const int filas = 20;
const int columnas = 20;

// Máximo número de edificios en el mapa
const int maxEdificios = 10;

// Variables globales del personaje
string nombre = "Sin Nombre";
int fuerza = 0, destreza = 0, magia = 0;
int vidaMaxima = 100, vidaActual = 100, experiencia = 0;

// Variables globales de combate
bool enCombate = false;
int vidaEnemigo = 0;

// Tipos de casillas en el mapa
enum class Tile {
    ROAD,
    OUTPOST,
    VILLAGE,
    TERRAIN,
    EMPTY,
    SANCTUARY
};

// Mapa del mundo
array<array<Tile, columnas>, filas> mapa;

// Función para limpiar la consola
void limpiarConsola() {
    system("cls");
}

// Función para inicializar el mapa
void inicializarMapa(array<array<Tile, columnas>, filas>& mapa) {
    // Rellenar el mapa con terreno vacío
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            mapa[i][j] = Tile::EMPTY;
        }
    }

    // Colocar el santuario en el centro del mapa
    int centroX = filas / 2;
    int centroY = columnas / 2;
    mapa[centroX][centroY] = Tile::SANCTUARY;

    // Colocar edificios aleatorios
    int edificiosGenerados = 0;
    srand(time(0));
    while (edificiosGenerados < maxEdificios) {
        int x = rand() % filas;
        int y = rand() % columnas;
        if (mapa[x][y] == Tile::EMPTY) {
            mapa[x][y] = static_cast<Tile>(rand() % 3); // OUTPOST, VILLAGE, o ROAD
            ++edificiosGenerados;
        }
    }
}

// Función para mostrar el mapa
void mostrarMapa(const array<array<Tile, columnas>, filas>& mapa, int jugadorX, int jugadorY) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (i == jugadorX && j == jugadorY) {
                cout << "X "; // Representar al jugador
            } else if (mapa[i][j] == Tile::SANCTUARY) {
                cout << "S ";
            } else if (mapa[i][j] == Tile::ROAD) {
                cout << "# ";
            } else if (mapa[i][j] == Tile::OUTPOST) {
                cout << "O ";
            } else if (mapa[i][j] == Tile::VILLAGE) {
                cout << "V ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

// Función para conectar un edificio con el santuario
void crearCamino(int startX, int startY, int endX, int endY) {
    // Crear camino horizontal
    int x = startX;
    while (x != endX) {
        mapa[x][startY] = Tile::ROAD;
        x += (x < endX) ? 1 : -1;
    }

    // Crear camino vertical
    int y = startY;
    while (y != endY) {
        mapa[endX][y] = Tile::ROAD;
        y += (y < endY) ? 1 : -1;
    }
}

// Función para interactuar con edificios
void interactuarEdificio(Tile tipoEdificio, int jugadorX, int jugadorY) {
    if (tipoEdificio == Tile::OUTPOST) {
        cout << "Exploraste un puesto avanzado. ¡Encontraste suministros útiles!\n";
    } else if (tipoEdificio == Tile::VILLAGE) {
        cout << "Entraste a una aldea. Los habitantes compartieron recursos contigo.\n";
    } else if (tipoEdificio == Tile::SANCTUARY) {
        cout << "Estás en el Santuario. Tu salud ha sido restaurada.\n";
        vidaActual = vidaMaxima;
    }

    // Crear camino al santuario desde el edificio
    crearCamino(jugadorX, jugadorY, filas / 2, columnas / 2);
    system("pause");
}

// Función para mover al jugador
void moverJugador(int& jugadorX, int& jugadorY, char direccion) {
    int nuevoX = jugadorX, nuevoY = jugadorY;

    if (direccion == 'w') --nuevoX;
    else if (direccion == 's') ++nuevoX;
    else if (direccion == 'a') --nuevoY;
    else if (direccion == 'd') ++nuevoY;

    // Validar límites del mapa
    if (nuevoX < 0 || nuevoX >= filas || nuevoY < 0 || nuevoY >= columnas) {
        cout << "¡No puedes moverte fuera del mapa!\n";
        system("pause");
        return;
    }

    // Interactuar con la casilla actual
    Tile casilla = mapa[nuevoX][nuevoY];
    if (casilla == Tile::OUTPOST || casilla == Tile::VILLAGE || casilla == Tile::SANCTUARY) {
        interactuarEdificio(casilla, nuevoX, nuevoY);
    }

    // Actualizar posición del jugador
    jugadorX = nuevoX;
    jugadorY = nuevoY;
}

// Función para crear al personaje
void crearPersonaje() {
    cout << "CREACIÓN DE PERSONAJE\n";
    cout << "Introduce tu nombre: ";
    getline(cin, nombre);

    cout << "Distribuye 100 puntos entre Fuerza, Destreza y Magia.\n";
    int puntosRestantes = 100;
    while (puntosRestantes > 0) {
        cout << "Puntos restantes: " << puntosRestantes << "\n";
        cout << "Fuerza: ";
        int incremento;
        cin >> incremento;
        if (incremento <= puntosRestantes) {
            fuerza += incremento;
            puntosRestantes -= incremento;
        }

        cout << "Destreza: ";
        cin >> incremento;
        if (incremento <= puntosRestantes) {
            destreza += incremento;
            puntosRestantes -= incremento;
        }

        cout << "Magia: ";
        cin >> incremento;
        if (incremento <= puntosRestantes) {
            magia += incremento;
            puntosRestantes -= incremento;
        }
    }

    vidaMaxima += fuerza / 2;
    vidaActual = vidaMaxima;

    cout << "¡Personaje creado con éxito! Bienvenido, " << nombre << ".\n";
    system("pause");
}

// Función principal
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    // Crear al personaje
    crearPersonaje();

    // Inicializar el mapa
    inicializarMapa(mapa);

    // Posición inicial del jugador
    int jugadorX = filas / 2, jugadorY = columnas / 2;

    while (vidaActual > 0) {
        limpiarConsola();
        mostrarMapa(mapa, jugadorX, jugadorY);
        cout << "Nombre: " << nombre << " | Salud: " << vidaActual << "/" << vidaMaxima << " | Experiencia: " << experiencia << "\n";
        cout << "Controles: W/A/S/D para moverse, Q para salir\n";
        char comando = _getch();

        if (comando == 'q') {
            cout << "¡Gracias por jugar!\n";
            break;
        } else {
            moverJugador(jugadorX, jugadorY, comando);
        }
    }

    if (vidaActual <= 0) {
        cout << "¡Has muerto! Fin del juego.\n";
    }

    return 0;
}
