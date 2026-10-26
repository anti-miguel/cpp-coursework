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
    double numero1 = 0;
    double numero2 = 0;
    int Respuesta = 0;
    cout << "Introduce un número: ";
    cin >> numero1;
    cout << "Introduce un número 2: ";
    cin >> numero2;
    cout << "Qué quieres calcular?\n Indicar mayor o menor: \"1\" \n La distancia entre ambos: \"2\" \n La media entre los números: \"3\"\n";
    cin >> Respuesta;
    if (Respuesta == 1) {
        if (numero1 < numero2) {
            cout << numero2 << " es el número mayor";
        }
        else {
            cout << numero1 << " es el número mayor";
        }
    }
    else if (Respuesta == 2) {
        if (numero1 < numero2) {
            double distancia = numero2 - numero1;
            cout << "La distancia es de " << distancia;
        }
        else {
            double distancia = numero1 - numero2;
            cout << "La distancia es de " << distancia;
        }
    }
    else {
        double Media = (numero1 + numero2) / 2;
        cout << "La media es " << Media;
    }
}


