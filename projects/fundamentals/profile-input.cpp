#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std; 

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    cout << "Hola\n\n Por favor, dime tu nombre y apellidos:\n\n\n";
    string nombre = "";
    getline(cin, nombre);

    int annoNacimiento = 1900;
    cout << "\n\n\nIntroduce tu año de nacimiento:";
    cin >> annoNacimiento;

    double altura = 150;
    double peso = 50;
    cout << "Hola " << nombre << ",\n\n\n Cuánto mides?\n";
    cin >> altura;

    cout << "\n\n\n Y cuánto pesas?\n";
    cin >> peso;

    double IMC = peso / (altura * altura);
    cout << "\n\n Tu IMC es " << IMC;
    cout << "\n\n\nNombre: " << nombre;

    int Edad = 2024 - annoNacimiento;
    cout << "\nEdad: " << Edad;
    cout << "\nAltura: " << altura;
    cout << "\nPeso: " << peso;
    cout << "\nIMC: " << IMC;

    if (Edad < 18) {
        cout << "\tLo siento, eres menor de edad, no puedes seguir con el programa";
        cout << "\tTe faltan " << 18 - Edad << " años para poder acceder";
    }

    else if (Edad >= 90) {
        cout << "\nLo siento, los mayores de 90 no pueden votar";
          
    }
        
    else
        { //mayores de edad
        cout << "\n\n A continuación el programa de votación.";
        cout << "\nBienvenido";

    }




    cout << "\n\n\nAdiós";
    
}


