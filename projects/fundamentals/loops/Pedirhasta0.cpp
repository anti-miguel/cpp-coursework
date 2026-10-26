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
    int negativos=0;
    int positivos=0;
    cout << "Introduce números hasta que te aburras. Escribe el número 0 para terminar\n";
    cin >> numero;
    while (numero>0){
    positivos++;
    cin >> numero;
    }
    while (numero<0) {
    negativos++;
    cin >> numero;
    }
    if (numero=0) 
        cout << "Números positivos: " << positivos << "\nNumeros negativos: " << negativos;
    
}