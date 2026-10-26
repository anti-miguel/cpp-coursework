#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

void movimiento(int tableroVisible[3][3], int respuesta);

void generarTablero(int tableroVisible[3][3]) {
    int numeros[9];
    for (int i = 0; i < 8; i++) {
        numeros[i] = i + 1;
    }
    numeros[8] = 0; // Blank space

    random_device rd;
    mt19937 generator(rd());
    shuffle(begin(numeros), end(numeros), generator);

    for (int i = 0; i < 9; i++) {
        tableroVisible[i / 3][i % 3] = numeros[i];
    }
}

void mostrarTablero(int tableroVisible[3][3]) {
    cout << "-------------" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tableroVisible[i][j] == 0) {
                cout << "    "; // Blank space
            } else {
                cout << "| " << tableroVisible[i][j] << " ";
            }
        }
        cout << "|" << endl;
        cout << "-------------" << endl;
    }
}

// Function to validate the player's input
bool esRespuestaValida(int respuesta) {
    return respuesta >= 1 && respuesta <= 9;
}

// Function to process the player's response
void procesarMovimiento(int tableroVisible[3][3], int respuesta) {
    if (!esRespuestaValida(respuesta)) {
        cout << "Numero invalido. Por favor selecciona un numero entre 1 y 9." << endl;
        return;
    }
    movimiento(tableroVisible, respuesta);
}

// Function to perform the movement
void movimiento(int tableroVisible[3][3], int tile) {
    int blankRow, blankCol, tileRow, tileCol;

    // Find the position of the blank space (0) and the selected tile
    blankRow = blankCol = tileRow = tileCol = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tableroVisible[i][j] == 0) {
                blankRow = i;
                blankCol = j;
            }
            if (tableroVisible[i][j] == tile) {
                tileRow = i;
                tileCol = j;
            }
        }
    }

    // Check if the tile is adjacent to the blank space
    if ((abs(blankRow - tileRow) == 1 && blankCol == tileCol) ||  // Vertical move
        (abs(blankCol - tileCol) == 1 && blankRow == tileRow)) { // Horizontal move
        // Swap the blank space (0) and the tile
        tableroVisible[blankRow][blankCol] = tile;
        tableroVisible[tileRow][tileCol] = 0;
    } else {
        cout << "Movimiento invalido. La casilla seleccionada no es adyacente al espacio en blanco." << endl;
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    int tableroVisible[3][3];

    // Generate and display the tablero
    generarTablero(tableroVisible);
    mostrarTablero(tableroVisible);

    // Gameplay loop
    while (true) {
        int respuesta;
        cout << "Selecciona la casilla hacia donde quieres desplazar el hueco (1-9): ";
        cin >> respuesta;

        procesarMovimiento(tableroVisible, respuesta);
        mostrarTablero(tableroVisible);
    }

    return 0;
}
