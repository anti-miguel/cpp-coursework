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
    double coste = 0;
    double pagado = 0;
    int cincuenta = 50;
    int veinte = 20;
    int diez = 10;
    int cinco = 5;
    int dos = 2;
    int uno= 1;
    double cambio = pagado-coste;
cout << "Indicar coste de la compra: ";
cin >> coste;
cout << "Introducir " << coste << " Euro\n";
cin >> pagado;
if (pagado>coste) {
    cout << "Tu cambio es de " << cambio << " Euro. \n Que tengas un buen día";
}
else if (pagado == coste) {
    cout << "Gracias por tu compra";
}
else if (pagado>=100) {
    cout << "La máquina no tiene suficiente cambio, introducir una cantidad inferior.";
}
else {
double falta = coste-pagado;
cout << "Dinero insuficiente, faltan " << falta << " Euro.";
}


}
