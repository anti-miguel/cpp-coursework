#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip> // Include iomanip for setw
using namespace std;

int main() {
    srand(time(0));
    int filas = rand() % 101;
    int columnas = rand() % 101;
    int num = 0;
    int respuesta = 0;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            num = rand() % 101;
            cout <<  num << " | "; // Use setw to format the output
        }
        cout << endl; // Print each row on a new line
    }
    cin >> respuesta;
    return 0;
}