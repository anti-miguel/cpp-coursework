#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    srand(0);
    int adivinanza = rand() % 11;
    int respuesta = 0;
    cout << "Adivina el número del 1 al 10\n";
    cin >> respuesta;
    if (respuesta >= 1 && respuesta <= 10) {
        if (respuesta == adivinanza) {
            cout << "Has adivinado el número\n";
        }
        else {
            cout << "Número incorrecto, te quedan 2 intentos\n";
            cin >> respuesta;
            if (respuesta == adivinanza) {
                cout << "Has adivinado el número\n";
            }
            else {
                cout << "Número incorrecto, te queda 1 intento\n";
                cin >> respuesta;
                if (respuesta == adivinanza) {
                    cout << "Has adivinado el número\n";
                }
                else {
                    cout << "Número incorrecto, no te quedan más intentos, el número era " << adivinanza;
                }
            }
        }
    }
    else {
        cout << "Número introducido incorrecto";
    }
}
