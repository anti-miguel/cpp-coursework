#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;

// Dimensiones del mapa
const int filas = 20, columnas = 20;
int respuesta = 0;

enum class Tile {
    HYPHEN,
    DOT,
    EX,
    BAR,
    EMPTY
};

Tile mapa[filas][columnas];


void mostrarMapa() {
    srand(time(0));

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int randomTile = rand() % 5; // Generate a random number between 0 and 4
            switch (randomTile) {
                case 0: mapa[i][j] = Tile::HYPHEN; break;
                case 1: mapa[i][j] = Tile::DOT; break;
                case 2: mapa[i][j] = Tile::EX; break;
                case 3: mapa[i][j] = Tile::BAR; break;
                case 4: mapa[i][j] = Tile::EMPTY; break;
            }

            // Print the tile
            switch (mapa[i][j]) {
                case Tile::HYPHEN:
                    cout << "~"; break;
                case Tile::DOT:
                    cout << "."; break;
                case Tile::EX:
                    cout << "X"; break;
                case Tile::BAR:
                    cout << "|"; break;
                case Tile::EMPTY:
                    cout << " "; break;
            }
        }
        cout << endl;
    }
}

int main() {
    mostrarMapa();
    cin >> respuesta;
}
            
