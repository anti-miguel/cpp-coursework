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
            cout << setw(4) << num << " | "; // Use setw to format the output
        }
        cout << endl; // Print each row on a new line

        // Print horizontal line after each row
        for (int k = 0; k < columnas; k++) {
            cout << "------"; // Adjust the number of dashes to match the column width
        }
        cout << endl;
    }

    cin >> respuesta;
    return 0;
}