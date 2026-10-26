#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdlib>
using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    double balance = 0;
    int PIN = 0;
    double dinero = 0;
    string nombre;
    string respuesta;
    cout << "Introduce tu PIN: ";
    cin >> PIN;
    cin.ignore();
    while (PIN > 9999 || PIN < 1000)
    {
        cout << "PIN introducido no válido, Intenta otra vez";
        cin >> PIN;
        cin.ignore();


    }
    while (true) {
    cout << "Bienvenido a la plataforma de banco, ¿qué te gustaria hacer?\nDepositar\nSacar dinero\nEnviar dinero\nSalir\n";
    getline(cin, respuesta);
    if (respuesta == "Depositar")
    {
        cout << "Introduce el dinero en el cajero por favor.\n";
        cin >> dinero;
        cin.ignore();
        balance += dinero;
        cout << "Has introducido " << dinero << "€. Balance actual: " << balance << "€.\n";
    }
    else if (respuesta == "Sacar dinero")
    {
        cout << "Cuánto dinero quieres sacar de tu cuenta?\n";
        cin >> dinero;
        cin.ignore();
        if (dinero <= balance)
        {
            balance -= dinero;
            cout << "Sacando " << dinero << "€ del cajero... \n";
            cout << "Balance restante: " << balance << "€.\n";
        }
        else
        {
            cout << "Fondos insuficientes.\n";
        }
    }
    else if (respuesta == "Enviar dinero")
    {
        cout << "Introducir nombre de destinatario\n";
        getline(cin, nombre);
        cout << "Introducir cantidad: ";
        cin >> dinero;
        cin.ignore();
        if (dinero <= balance)
        {
            balance -= dinero;
            cout << "Enviando " << dinero << "€ a: " << nombre << "\n";
            cout << "Balance restante: " << balance << "€.\n";
        }
        else
        {
            cout << "Fondos insuficientes.\n";
        }
    }
    else if (respuesta == "Salir")
    {
        break;
    }
    else
    {
        cout << "Función introducida incorrecta, por favor, intenta otra vez:\n";
    }
    }
    return 0;
    }
