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
    int numeros[20]= {rand()%11};
    int numeronumeros=0;
    int numeros2[100]={rand()};

    for (int i=0; i<20; i++) {
        numeros[i]=rand()%11;
        cout << numeros[i] << ", ";
    }
    

cout << "Introducir número de números aleatorios: ";
cin >> numeronumeros;
for (int i=0; i<numeronumeros; i++) { 
    numeros2[i]=rand()%100;
    cout << numeros2[i]<<", ";
}

}