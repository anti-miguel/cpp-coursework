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
int numero = 0;
cout << "Números impares del 1 al 100";
while(numero<100) {
    numero=numero+1;
    if (numero%2!=0) {
    cout << numero;
    }
}
}