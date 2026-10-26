#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip> // Include iomanip for setw
using namespace std;

const int filas = 10, columnas = 10;
int probabilidad = 30;
const int barcos = 100;
int placedBarcos = 0;
char mapa[filas][columnas];
int respuesta = 0;

void clearConsole() {
    system("cls");
}

void renderMap() {
    // Print column numbers
    cout << "    ";
    for (int j = 0; j < columnas; j++) {
        cout << setw(2) << j + 1 << " ";
    }
    cout << endl;

    cout << "   " << string(columnas * 3 + 1, '-') << endl;

    for (int i = 0; i < filas; i++) {
        // Print row number
        cout << setw(2) << i + 1 << " | ";
        for (int j = 0; j < columnas; j++) {
            cout << mapa[i][j] << "  ";
        }
        cout << "|" << endl;
    }
    cout << "   " << string(columnas * 3 + 1, '-') << endl;
}

void initializeMap() {
    srand(time(0));
    placedBarcos = 0;

    // Initialize the map and place barcos
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (placedBarcos < barcos && rand() % 100 < probabilidad) {
                mapa[i][j] = '1';
                placedBarcos++;
            } else {
                mapa[i][j] = '0';
            }
        }
    }
}

bool movimiento(int x, int y) {
    if (x >= 0 && x < filas && y >= 0 && y < columnas) {
        if (mapa[x][y] == '1') {
            mapa[x][y] = 'X';
            return true;
        } else {
            mapa[x][y] = ' ';
            return false;
        }
    }
    return false;
}

int main() {
    initializeMap();
    renderMap();

    int x, y;
    while (true) {
        cout << "Enter coordinates to hit (row and column): ";
        cin >> x >> y;
        x--; // Adjust for 0-based index
        y--; // Adjust for 0-based index

        if (movimiento(x, y)) {
            cout << "Hit!" << endl;
        } else {
            cout << "Miss!" << endl;
        }

        renderMap();
    }

    return 0;
}