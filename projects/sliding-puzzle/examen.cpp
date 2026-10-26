#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <algorithm>
#include <random>
#include <array>

using namespace std;

char tablero[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '0'}};
int respuesta = 0;

// Function to count inversions in the puzzle
int countInversions(int numeros[]) {
    int inversions = 0;
    for (int i = 0; i < 8; i++) {  // Skip the blank (0)
        for (int j = i + 1; j < 9; j++) {
            if (numeros[i] > numeros[j] && numeros[j] != 0) {
                inversions++;
            }
        }
    }
    return inversions;
}

// Generate a solvable 3x3 puzzle
void generarTablero(int tableroVisible[3][3]) {
    int numeros[9];
    for (int i = 0; i < 8; i++) {
        numeros[i] = i + 1;
    }
    numeros[8] = 0;  // Blank space

    random_device rd;
    mt19937 generator(rd());

    do {
        shuffle(begin(numeros), end(numeros), generator);  // Shuffle the array
    } while (countInversions(numeros) % 2 != 0);  // Ensure the puzzle is solvable

    for (int i = 0; i < 9; i++) {
        tableroVisible[i / 3][i % 3] = numeros[i];
    }
}

void mostrarTablero(int tableroVisible[3][3]) {
    cout << "-------------" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tableroVisible[i][j] == 0) {
                cout << "|   ";
            } else {
                cout << "| " << tableroVisible[i][j] << " ";
            }
        }
        cout << "|" << endl;
        cout << "-------------" << endl;
    }
}

void movimiento(int tableroVisible[3][3], int casilla) {
    int huecoFila, huecoCol, casillaFila, casillaCol;
    huecoFila = huecoCol = casillaFila = casillaCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tableroVisible[i][j] == 0) {
                huecoFila = i;
                huecoCol = j;
            }
            if (tableroVisible[i][j] == casilla) {
                casillaFila = i;
                casillaCol = j;
            }
        }
    }

    if ((abs(huecoFila - casillaFila) == 1 && huecoCol == casillaCol) ||
        (abs(huecoCol - casillaCol) == 1 && huecoFila == casillaFila)) {
        tableroVisible[huecoFila][huecoCol] = casilla;
        tableroVisible[casillaFila][casillaCol] = 0;
    } else {
        cout << "Movimiento invalido. La casilla seleccionada no es adyacente al espacio en blanco." << endl;
    }
}

bool esRespuestaValida(int respuesta) {
    return respuesta >= 1 && respuesta <= 9;
}

void procesarMovimiento(int tableroVisible[3][3], int respuesta) {
    if (!esRespuestaValida(respuesta)) {
        cout << "Numero invalido. Por favor selecciona un numero entre 1 y 9." << endl;
        return;
    }
    movimiento(tableroVisible, respuesta);
}

bool checkWin(int tableroVisible[3][3]) {
    int cuenta = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tableroVisible[i][j] != cuenta && (i != 2 || j != 2)) {
                return false;  // Not in order
            }
            cuenta++;
        }
    }

    return tableroVisible[2][2] == 0;  // Ensure the last cell is blank
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    int tableroVisible[3][3];
    generarTablero(tableroVisible);
    mostrarTablero(tableroVisible);

    while (true) {
        cout << "Selecciona la casilla hacia donde quieres desplazar el hueco (1-8):\n";
        cin >> respuesta;
        procesarMovimiento(tableroVisible, respuesta);
        mostrarTablero(tableroVisible);
        if (checkWin(tableroVisible)) {
            cout << "Enhorabuena!" << endl;
            break;  // Exit the game loop
        }
    }

    return 0;
}
