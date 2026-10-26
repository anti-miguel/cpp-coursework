#include "7.5.h"
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#endif
#include <vector>

void inicializarBaraja(baraja& b) {
    std::string palos[4] = { "Copas", "Oros", "Espadas", "Bastos" };
    std::string valores[10] = { "As", "Dos", "Tres", "Cuatro", "Cinco", "Seis", "Siete", "Sota", "Caballo", "Rey" };
    int cartaActual = 0;

    for (int i = 0; i < 40; i++) {
        b.cartas[i].palo = palos[i / 10];
        b.cartas[i].valor = valores[i % 10];
        b.cartas[i].volteada = false;
        b.cartas[i].puntos = (i % 10) + 1;
    }
}

void barajar(baraja& b) {
    for (int i = 0; i < b.numCartas; i++) {
        int j = rand() % b.numCartas;
        carta temp = b.cartas[i];
        b.cartas[i] = b.cartas[j];
        b.cartas[j] = temp;
    }
}

void repartirCarta(baraja& b, int& cartaActual, jugador& j) {
    if (cartaActual < b.numCartas) {
        b.cartas[cartaActual].volteada = true;
        j.puntos += b.cartas[cartaActual].puntos;
        cartaActual++;
    }
}

std::ostream& operator<<(std::ostream& os, const carta& c) {
    os << c.valor << " de " << c.palo;
    return os;
}

void turnoJugador(baraja& b, int& cartaActual, jugador& j) {
    char opcion;
    do {
        repartirCarta(b, cartaActual, j);
        std::cout << j.nombre << " ha recibido: " << b.cartas[cartaActual - 1] << " (Puntos: " << j.puntos << ")\n";
        if (j.puntos >= 7.5) break;
        std::cout << "¿Deseas otra carta? (s/n): ";
        std::cin >> opcion;
    } while (opcion == 's');
}

void turnoBanca(baraja& b, int& cartaActual, jugador& banca) {
    while (banca.puntos < 5.5) {
        repartirCarta(b, cartaActual, banca);
        std::cout << "Banca ha recibido: " << b.cartas[cartaActual - 1] << " (Puntos: " << banca.puntos << ")\n";
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    srand(time(0));
    baraja b;
    inicializarBaraja(b);
    barajar(b);

    // juego de las siete y media
    std::cout << "Juego de las siete y media\n";
    std::cout << "-------------------------\n";
    std::cout << "Barajando cartas...\n";
    std::cout << "-------------------------\n";
    int cartaActual = 0;

    // Crear jugadores
    std::vector<jugador> jugadores;
    int numJugadores;
    std::cout << "Ingrese el número de jugadores: ";
    std::cin >> numJugadores;

    for (int i = 0; i < numJugadores; i++) {
        jugador j;
        j.nombre = "Jugador " + std::to_string(i + 1);
        j.puntos = 0;
        j.esBanca = false;
        jugadores.push_back(j);
    }

    jugador banca = { "Banca", 0, true };

    // Turnos de los jugadores
    for (auto& j : jugadores) {
        turnoJugador(b, cartaActual, j);
    }

    // Turno de la banca
    turnoBanca(b, cartaActual, banca);

    // Determinar el ganador
    for (const auto& j : jugadores) {
        if ((j.puntos > 7.5 && banca.puntos > 7.5) || (j.puntos == banca.puntos)) {
            std::cout << j.nombre << " y la banca empatan\n";
        }
        else if ((j.puntos > 7.5) || (banca.puntos <= 7.5 && banca.puntos > j.puntos)) {
            std::cout << "Gana la banca contra " << j.nombre << "\n";
        }
        else {
            std::cout << "Gana " << j.nombre << " contra la banca\n";
        }
    }

    return 0;
}