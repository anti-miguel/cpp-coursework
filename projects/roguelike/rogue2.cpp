#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h> // Para entrada en tiempo real con _getch()
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// Tamaño del mapa
const int filas = 20;
const int columnas = 20;

// Máximo número de edificios en el mapa
const int maxEdificios = 10;

// Probabilidad de encontrar enemigos
const int probabilidadEnemigo = 30;

// Variables globales del personaje
string nombre = "Sin Nombre";
int fuerza = 0, destreza = 0, magia = 0;
int vidaMaxima = 100, vidaActual = 100, experiencia = 0;
int carneCocinada = 5; // Carne cocinada inicial
int medicinas = 2;     // Medicinas iniciales

// Tipos de casillas en el mapa
enum class Tile {
    OUTPOST,
    VILLAGE,
    EMPTY,
    ROAD,
    SANCTUARY,
    INN,
    ENEMY_HIDDEN // Enemigo oculto, no visible en el mapa
};

// Mapa del mundo
array<array<Tile, columnas>, filas> mapa;
array<array<char, columnas>, filas> mapaOculto; // Representación del mapa oculto ('?' inicialmente)

// Función para limpiar la consola
void limpiarConsola() {
    system("cls");
}

// Función para inicializar el mapa y el mapa oculto
void inicializarMapa(array<array<Tile, columnas>, filas>& mapa, array<array<char, columnas>, filas>& mapaOculto) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            mapa[i][j] = Tile::EMPTY;
            mapaOculto[i][j] = '?';
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
            mapa[x][y] = static_cast<Tile>(rand() % 2); // OUTPOST o VILLAGE
            ++edificiosGenerados;
        }
    }
}

// Función para revelar un radio alrededor del jugador
void revelarRadio(const array<array<Tile, columnas>, filas>& mapa, array<array<char, columnas>, filas>& mapaOculto, int jugadorX, int jugadorY, int radio) {
    for (int dx = -radio; dx <= radio; ++dx) {
        for (int dy = -radio; dy <= radio; ++dy) {
            int nuevoX = jugadorX + dx;
            int nuevoY = jugadorY + dy;

            if (nuevoX >= 0 && nuevoX < filas && nuevoY >= 0 && nuevoY < columnas) {
                if (sqrt(dx * dx + dy * dy) <= radio) {
                    switch (mapa[nuevoX][nuevoY]) {
                        case Tile::SANCTUARY:
                            mapaOculto[nuevoX][nuevoY] = 'S';
                            break;
                        case Tile::ROAD:
                            mapaOculto[nuevoX][nuevoY] = '#';
                            break;
                        case Tile::OUTPOST:
                            mapaOculto[nuevoX][nuevoY] = 'O';
                            break;
                        case Tile::VILLAGE:
                            mapaOculto[nuevoX][nuevoY] = 'V';
                            break;
                        case Tile::INN:
                            mapaOculto[nuevoX][nuevoY] = 'P';
                            break;
                        case Tile::EMPTY:
                            mapaOculto[nuevoX][nuevoY] = '.';
                            break;
                        default:
                            mapaOculto[nuevoX][nuevoY] = '?';
                            break;
                    }
                }
            }
        }
    }
}

// Función para mostrar el mapa revelado
void mostrarMapa(const array<array<char, columnas>, filas>& mapaOculto, int jugadorX, int jugadorY) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (i == jugadorX && j == jugadorY) {
                cout << "X "; // Representar al jugador
            } else {
                cout << mapaOculto[i][j] << ' ';
            }
        }
        cout << endl;
    }
}

void crearCamino(int startX, int startY, int endX, int endY) {
    // Draw horizontal road segment
    int x = startX;
    while (x != endX) {
        mapa[x][startY] = Tile::ROAD;
        x += (x < endX) ? 1 : -1;
    }

    // Draw vertical road segment
    int y = startY;
    while (y != endY) {
        mapa[endX][y] = Tile::ROAD;
        y += (y < endY) ? 1 : -1;
    }
}


// Función para consumir carne cocinada automáticamente al moverse
bool gameOver = false; // Global game-over flag

void consumirCarne(int& jugadorX, int& jugadorY) {
    if (carneCocinada > 0) {
        carneCocinada--;
        cout << "Has consumido carne cocinada. Restante: " << carneCocinada << "\n";
    } else {
        cout << "Te quedaste sin carne cocinada y colapsaste de hambre.\n";
        cout << "Has sido devuelto al Santuario para recuperarte...\n";

        // Reset player position to the sanctuary
        jugadorX = filas / 2;
        jugadorY = columnas / 2;

        // Restore a small amount of meat to continue
        carneCocinada = 3;
        vidaActual = vidaMaxima / 2; // Restore half health as a penalty
        system("pause");
    }
}



// Función para curar al jugador con medicinas
void usarMedicina() {
    if (medicinas > 0) {
        medicinas--;
        vidaActual = min(vidaMaxima, vidaActual + 50); // Curar 50 puntos de salud
        cout << "Usaste una medicina. Salud restaurada: " << vidaActual << "/" << vidaMaxima << ". Medicinas restantes: " << medicinas << "\n";
    } else {
        cout << "No tienes medicinas.\n";
    }
}

// Función para interactuar con edificios
void interactuarEdificio(Tile& tipoEdificio, int jugadorX, int jugadorY) {
    if (tipoEdificio == Tile::SANCTUARY) {
        cout << "Estás en el Santuario. Recibiste carne cocinada y medicinas.\n";
        carneCocinada += 3;
        medicinas += 1;
    } else if (tipoEdificio == Tile::OUTPOST || tipoEdificio == Tile::VILLAGE) {
        cout << "Exploraste un edificio. Ahora se convirtió en una posada.\n";
        tipoEdificio = Tile::INN;

        // Draw a road back to the sanctuary
        crearCamino(jugadorX, jugadorY, filas / 2, columnas / 2);
    } else if (tipoEdificio == Tile::INN) {
        cout << "Estás en una posada. Descansaste y recibiste carne cocinada.\n";
        carneCocinada += 1;
    }
    system("pause");
}


// Función para manejar encuentros aleatorios al pisar casillas vacías
void manejarEncuentro(Tile& tile) {
    if (tile == Tile::EMPTY && rand() % 100 < probabilidadEnemigo) {
        cout << "¡Un enemigo apareció de repente!\n";
        tile = Tile::ENEMY_HIDDEN;
    }

    if (tile == Tile::ENEMY_HIDDEN) {
        cout << "Entras en combate.\n";
        system("pause");
        tile = Tile::EMPTY; // Casilla vacía tras el combate
    }
}

// Función para mover al jugador
void moverJugador(int& jugadorX, int& jugadorY, char direccion, array<array<Tile, columnas>, filas>& mapa, array<array<char, columnas>, filas>& mapaOculto) {
    int nuevoX = jugadorX, nuevoY = jugadorY;

    if (direccion == 'w') --nuevoX;
    else if (direccion == 's') ++nuevoX;
    else if (direccion == 'a') --nuevoY;
    else if (direccion == 'd') ++nuevoY;

    if (nuevoX < 0 || nuevoX >= filas || nuevoY < 0 || nuevoY >= columnas) {
        cout << "¡No puedes moverte fuera del mapa!\n";
        system("pause");
        return;
    }

    consumirCarne(jugadorX, jugadorY); // Updated to reset position if needed
    manejarEncuentro(mapa[nuevoX][nuevoY]);

    Tile& casilla = mapa[nuevoX][nuevoY];
    if (casilla == Tile::SANCTUARY || casilla == Tile::OUTPOST || casilla == Tile::VILLAGE || casilla == Tile::INN) {
        interactuarEdificio(casilla, nuevoX, nuevoY);
    }

    revelarRadio(mapa, mapaOculto, nuevoX, nuevoY, 2);
    jugadorX = nuevoX;
    jugadorY = nuevoY;
}


// Función principal
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    inicializarMapa(mapa, mapaOculto);

    int jugadorX = filas / 2, jugadorY = columnas / 2;
    revelarRadio(mapa, mapaOculto, jugadorX, jugadorY, 2);

    while (vidaActual > 0) {
        limpiarConsola();
        mostrarMapa(mapaOculto, jugadorX, jugadorY);
        cout << "Nombre: " << nombre << " | Salud: " << vidaActual << "/" << vidaMaxima 
             << " | Carne: " << carneCocinada << " | Medicinas: " << medicinas << "\n";
        cout << "Controles: W/A/S/D para moverse, M para usar medicina, Q para salir\n";

        char comando = _getch();
        if (comando == 'q') {
            cout << "¡Gracias por jugar!\n";
            break;
        } else if (comando == 'm') {
            usarMedicina();
        } else {
            moverJugador(jugadorX, jugadorY, comando, mapa, mapaOculto);
        }
    }

    cout << "¡Fin del juego!\n";
    return 0;
}
