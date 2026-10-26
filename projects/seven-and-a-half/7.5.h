#ifndef SIETE_Y_MEDIA_H
#define SIETE_Y_MEDIA_H

#include <iostream>
#include <string>

struct carta {
    std::string palo;
    std::string valor;
    bool volteada;
    int puntos;
};

struct baraja {
    carta cartas[40];
    const int numCartas = 40;
};

struct jugador {
    std::string nombre;
    int puntos;
    bool esBanca;
};

void inicializarBaraja(baraja& b);
void barajar(baraja& b);
void repartirCarta(baraja& b, int& cartaActual, jugador& j);
std::ostream& operator<<(std::ostream& os, const carta& c);
void turnoJugador(baraja& b, int& cartaActual, jugador& j);
void turnoBanca(baraja& b, int& cartaActual, jugador& banca);

#endif // SIETE_Y_MEDIA_H