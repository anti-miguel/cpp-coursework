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
    cout << "Introduce un número: ";
    cin >> numero;
    if (numero%2==0 && numero !=2){
    cout << "El número no es primo\n";
    numero=numero/2;
}
if (numero % 3 == 0 && numero !=3){
    cout << "El número no es primo\n";
    numero=numero/3;
}
if (numero%5==0 && numero !=5){
    cout << "El número no es primo\n";
    numero=numero/5;
}
if (numero%7==0 && numero!=7){
    cout << "El número no es primo\n";
    numero=numero/7;
}
else {
    cout << "\nEl número es primo";
}
}