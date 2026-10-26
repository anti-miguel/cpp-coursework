#include <iostream>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#endif
#include <conio.h> // Para entrada sin bloqueo con _getch()
#include <thread>  // Para temporizador de cooldown
#include <chrono>
using namespace std;

// Tamaño del mapa
const int filas = 20;
const int columnas = 20;

// Máximo número de edificios en el mapa
const int maxEdificios = 10;

// Variables globales del combate
bool enCombate = false;
int vidaEnemigo = 0;

// Función para limpiar la consola
void limpiarConsola() {
    system("cls");
}

// Función para inicializar el mapa oculto
void inicializarMapaOculto(char mapaOculto[filas][columnas]) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            mapaOculto[i][j] = '?'; // '?' indica celdas desconocidas
        }
    }
}

// Función para generar el mapa con un máximo de 10 edificios
void generarMapa(char mapa[filas][columnas], int& santuarioX, int& santuarioY) {
    const char terreno[] = {' ', 'C', 'H', 'M'}; // Solo 3 tipos de edificios
    int tamanoTerreno = sizeof(terreno) / sizeof(terreno[0]);

    srand(time(0)); // Semilla para la generación aleatoria

    // Limpiar el mapa
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            mapa[i][j] = ' ';
        }
    }

    // Colocar el santuario en el centro del mapa
    santuarioX = filas / 2;
    santuarioY = columnas / 2;
    mapa[santuarioX][santuarioY] = 'S';

    // Generar hasta 10 edificios aleatoriamente
    int edificiosGenerados = 0;
    while (edificiosGenerados < maxEdificios) {
        int x = rand() % filas;
        int y = rand() % columnas;

        // Evitar colocar edificios en el santuario o en celdas ya ocupadas
        if (mapa[x][y] == ' ') {
            mapa[x][y] = terreno[rand() % (tamanoTerreno - 1) + 1];
            edificiosGenerados++;
        }
    }
}

// Función para revelar un radio alrededor del jugador
void revelarRadio(char mapa[filas][columnas], char mapaOculto[filas][columnas], int jugadorX, int jugadorY, int radio) {
    for (int dx = -radio; dx <= radio; ++dx) {
        for (int dy = -radio; dy <= radio; ++dy) {
            int nuevoX = jugadorX + dx;
            int nuevoY = jugadorY + dy;

            // Revelar celdas solo dentro de los límites del mapa
            if (nuevoX >= 0 && nuevoX < filas && nuevoY >= 0 && nuevoY < columnas) {
                mapaOculto[nuevoX][nuevoY] = mapa[nuevoX][nuevoY];
            }
        }
    }
}

// Función para mostrar el mapa revelado hasta el momento
void mostrarMapa(char mapaOculto[filas][columnas], int jugadorX, int jugadorY) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (i == jugadorX && j == jugadorY) {
                cout << "X "; // Representar al jugador con 'X'
            } else {
                cout << mapaOculto[i][j] << ' ';
            }
        }
        cout << '\n';
    }
}

// Función de combate interactivo
void iniciarCombate(int& vidaJugador, int fuerzaJugador, int destrezaJugador) {
    enCombate = true;
    vidaEnemigo = 50 + rand() % 51; // Vida del enemigo entre 50 y 100

    cout << "¡Te encuentras en combate con un enemigo!\n";
    while (vidaEnemigo > 0 && vidaJugador > 0) {
        cout << "\n--- Registro del combate ---\n";
        cout << "Tu vida: " << vidaJugador << " | Vida del enemigo: " << vidaEnemigo << "\n";
        cout << "1. Atacar\n";
        cout << "2. Defender\n";
        cout << "3. Huir\n";
        cout << "Elige una acción: ";
        int accion;
        cin >> accion;

        if (accion == 1) { // Atacar
            int dano = fuerzaJugador + rand() % 10;
            cout << "¡Atacaste al enemigo e infligiste " << dano << " de daño!\n";
            vidaEnemigo -= dano;

            if (vidaEnemigo > 0) {
                int danoRecibido = 10 + rand() % 11; // Enemigo contraataca
                vidaJugador -= danoRecibido;
                cout << "El enemigo te golpeó e infligió " << danoRecibido << " de daño.\n";
            }
        } else if (accion == 2) { // Defender
            int danoRecibido = max(5, 10 + rand() % 11 - destrezaJugador / 2);
            vidaJugador -= danoRecibido;
            cout << "Defendiste parcialmente. El enemigo te infligió " << danoRecibido << " de daño.\n";
        } else if (accion == 3) { // Huir
            cout << "¡Huiste del combate!\n";
            enCombate = false;
            return;
        } else {
            cout << "Acción no válida.\n";
        }
    }

    if (vidaJugador <= 0) {
        cout << "¡Has muerto en combate!\n";
    } else if (vidaEnemigo <= 0) {
        cout << "¡Has derrotado al enemigo!\n";
    }
    enCombate = false;
}

// Función para crear al personaje
void crearPersonaje(string& nombre, int& fuerza, int& destreza, int& magia, int& vidaMaxima) {
    limpiarConsola();
    cout << "¡Bienvenido a la creación de personaje!\n";
    cout << "Introduce el nombre de tu personaje: ";
    cin.ignore();
    getline(cin, nombre);

    cout << "\nDistribuye 100 puntos entre Fuerza, Destreza y Magia.\n";
    int puntosRestantes = 100;

    while (puntosRestantes > 0) {
        cout << "Puntos restantes: " << puntosRestantes << "\n";
        cout << "Fuerza (" << fuerza << "): ";
        int incremento;
        cin >> incremento;

        if (incremento <= puntosRestantes) {
            fuerza += incremento;
            puntosRestantes -= incremento;
        } else {
            cout << "No tienes suficientes puntos.\n";
        }

        cout << "Destreza (" << destreza << "): ";
        cin >> incremento;

        if (incremento <= puntosRestantes) {
            destreza += incremento;
            puntosRestantes -= incremento;
        } else {
            cout << "No tienes suficientes puntos.\n";
        }

        cout << "Magia (" << magia << "): ";
        cin >> incremento;

        if (incremento <= puntosRestantes) {
            magia += incremento;
            puntosRestantes -= incremento;
        } else {
            cout << "No tienes suficientes puntos.\n";
        }
    }

    vidaMaxima = 100 + fuerza; // Vida inicial basada en fuerza
    cout << "¡Personaje creado con éxito!\n";
    cout << "Nombre: " << nombre << " | Fuerza: " << fuerza << " | Destreza: " << destreza << " | Magia: " << magia << " | Vida: " << vidaMaxima << "\n";
    system("pause");
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Soporte para caracteres UTF-8
#endif

    char mapa[filas][columnas];           // Mapa principal
    char mapaOculto[filas][columnas];     // Mapa oculto inicialmente
    string inventario[100];               // Inventario del jugador
    int inventarioTam = 0;                // Tamaño del inventario

    int santuarioX, santuarioY;           // Coordenadas del santuario
    generarMapa(mapa, santuarioX, santuarioY);
    inicializarMapaOculto(mapaOculto);

    // Crear personaje
    string nombre;
    int fuerza = 0, destreza = 0, magia = 0, vidaMaxima = 0;
    crearPersonaje(nombre, fuerza, destreza, magia, vidaMaxima);

    // Estadísticas del jugador
    int jugadorX = santuarioX, jugadorY = santuarioY;
    int vida = vidaMaxima, experiencia = 0;

    // Revelar la primera área alrededor del jugador
    revelarRadio(mapa, mapaOculto, jugadorX, jugadorY, 3);

    while (vida > 0) {
        limpiarConsola();
        mostrarMapa(mapaOculto, jugadorX, jugadorY);
        cout << "Nombre: " << nombre << " | Salud: " << vida << "/" << vidaMaxima << " | Experiencia: " << experiencia << "\n";
        cout << "Inventario: ";
        for (int i = 0; i < inventarioTam; ++i) {
            cout << inventario[i] << " ";
        }
        cout << "\n";

        cout << "Controles: Mover con W/A/S/D | Salir con Q: ";
        char comando = _getch();

        if (comando == 'q') {
            cout << "¡Hasta luego!\n";
            break;
        } else if (comando == 't' && enCombate) {
            iniciarCombate(vida, fuerza, destreza);
        } else if (!enCombate) {
            cout << "No puedes atacar fuera del combate.\n";
        }
    }

    if (vida <= 0) {
        cout << "¡Has muerto! Fin del juego.\n";
    }

    return 0;
}
