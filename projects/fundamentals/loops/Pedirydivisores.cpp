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

cout << "Introduce un número:\n";
cin >> numero;
while (numero%2==0){
    cout << "El número es divisible entre 2\n";
    numero=numero/2;
}
while (numero % 3 == 0){
    cout << "El número es divisible entre 3\n";
    numero=numero/3;
}
while (numero%5==0){
    cout << "El número es divisible entre 5\n";
    numero=numero/5;
}
while (numero%7==0){
    cout << "El número es divisible entre 7\n";
    numero=numero/7;
}
while (numero%11==0){
    cout << "El número es divisible entre 11\n";
    numero=numero/11;
}
while (numero%17==0){
    cout << "El número es divisible entre 17\n";
    numero=numero/17;
}

}