#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int IA = 0;
int jugador = 0;
int modo = 0;
int p1 = 0;
char tablero[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };

void mostrarTablero() {
    cout << "-------------" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "| " << tablero[i][j] << " ";
        }
        cout << "|" << endl;
        cout << "-------------" << endl;
    }
}

bool checkWin(char player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((tablero[i][0] == player && tablero[i][1] == player && tablero[i][2] == player) ||
            (tablero[0][i] == player && tablero[1][i] == player && tablero[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((tablero[0][0] == player && tablero[1][1] == player && tablero[2][2] == player) ||
        (tablero[0][2] == player && tablero[1][1] == player && tablero[2][0] == player)) {
        return true;
    }
    return false;
}

bool movimiento(int jugador, int posicion) {
    int fila = (posicion - 1) / 3;
    int col = (posicion - 1) % 3;
    if (posicion >= 1 && posicion <= 9 && tablero[fila][col] == ' ') {
        tablero[fila][col] = (jugador == 1) ? 'X' : 'O';
        return true;
    }
    return false;
}

bool checkAndBlock(char a, char b, char c, int& fila, int& col, int pos) {
    if (a == 'X' && b == 'X' && c == ' ') {
        fila = pos;
        col = 2;
        return true;
    }
    if (a == 'X' && c == 'X' && b == ' ') {
        fila = pos;
        col = 1;
        return true;
    }
    if (b == 'X' && c == 'X' && a == ' ') {
        fila = pos;
        col = 0;
        return true;
    }
    return false;
}

bool blockPlayer() {
    int fila = -1, col = -1;
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (checkAndBlock(tablero[i][0], tablero[i][1], tablero[i][2], fila, col, i)) {
            tablero[i][col] = 'O';
            return true;
        }
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (checkAndBlock(tablero[0][i], tablero[1][i], tablero[2][i], fila, col, i)) {
            tablero[fila][i] = 'O';
            return true;
        }
    }
    // Check diagonals
    if (checkAndBlock(tablero[0][0], tablero[1][1], tablero[2][2], fila, col, 0)) {
        tablero[fila][col] = 'O';
        return true;
    }
    if (checkAndBlock(tablero[0][2], tablero[1][1], tablero[2][0], fila, col, 0)) {
        tablero[fila][col] = 'O';
        return true;
    }
    return false;
}

bool turnoBot() {
    // First, try to block the player
    if (blockPlayer()) {
        return true;
    }

    // If no blocking move is found, make a random move
    srand(time(0));
    do {
        IA = rand() % 9 + 1;
        int fila = (IA - 1) / 3;
        int col = (IA - 1) % 3;
        if (tablero[fila][col] == ' ') {
            tablero[fila][col] = 'O';
            return true;
        }
    } while (true);
}

bool checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void pvp() {
    int currentPlayer = 1;
    while (true) {
        mostrarTablero();
        int posicion;
        cout << "Jugador " << currentPlayer << ", ingrese una posición (1-9): ";
        cin >> posicion;
        if (movimiento(currentPlayer, posicion)) {
            if (checkWin((currentPlayer == 1) ? 'X' : 'O')) {
                mostrarTablero();
                cout << "Jugador " << currentPlayer << " gana!" << endl;
                break;
            }
            if (checkDraw()) {
                mostrarTablero();
                cout << "Es un empate!" << endl;
                break;
            }
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        } else {
            cout << "Movimiento inválido, intente de nuevo." << endl;
        }
    }
}

void pve() {
    while (true) {
        mostrarTablero();
        int posicion;
        cout << "Jugador 1, ingrese una posición (1-9): ";
        cin >> posicion;
        if (movimiento(1, posicion)) {
            if (checkWin('X')) {
                mostrarTablero();
                cout << "Jugador 1 gana!" << endl;
                break;
            }
            if (checkDraw()) {
                mostrarTablero();
                cout << "Es un empate!" << endl;
                break;
            }
            // Bot's turn
            if (turnoBot()) {
                if (checkWin('O')) {
                    mostrarTablero();
                    cout << "El bot gana!" << endl;
                    break;
                }
                if (checkDraw()) {
                    mostrarTablero();
                    cout << "Es un empate!" << endl;
                    break;
                }
            }
        } else {
            cout << "Movimiento inválido, intente de nuevo." << endl;
        }
    }
}

int main() {
    cout << "Escoger modo: \n1: PVP\n2: PVE\n3: PVE con IA\n";
    cin >> modo;

    if (modo == 1) {
        pvp();
    } else if (modo == 2) {
        pve();
    } else {
        cout << "Opción inválida, ingrese un valor entre 1 y 3: ";
    }

    return 0;
}