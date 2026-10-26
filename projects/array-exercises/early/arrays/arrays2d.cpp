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
    int notas[35] = { };
    int modProf[6][3]={-20,5,20};
    int tamannoNotas = sizeof(notas);
    int tamannoArray= tamannoNotas /sizeof(int);
    int numColumnas = sizeof(modProf)/sizeof(int);
    for (int i=0; i<tamannoArray; i++) {
        notas[i] = rand() %11;
        cout << notas[i] << endl;

    }
}