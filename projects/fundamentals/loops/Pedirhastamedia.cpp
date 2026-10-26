#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdlib>
using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    int numero=0;
    int numero2=0;
    int numeroediciones=0;
    cout << "Introduce números hasta que te aburras. Escribe el número 0 para terminar\n";
    cin >> numero;
    while (numero!=0) {
    numero2=numero+numero2;
    numeroediciones++;
    cin >> numero;
    }
    if (numero==0) {
    int media=numero2/numeroediciones;
    cout << "Media=" << media;
    }
}