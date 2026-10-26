
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string nombre = "Persona1";
    int annoNacimiento = 1900;
    double altura = 1.5;
    double peso = 50.0;

    cout << "Hola " << nombre << "!\n\n\n\tBienvenido\n";
    cout << "Hoy es miercoles \n\n";

    nombre = "Persona2";
    cout << "Hola " << nombre << "!\n\n\n\tBienvenido\n";

    cout << "\n\n Como te llamas?";
    //cin >> nombre;
    getline(cin, nombre);
    cout << "Hola " << nombre << "!\n\n\n\tBienvenido\n"; 
}


