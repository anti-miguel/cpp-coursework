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

    // Solicitar PIN
    cout << "Introduce tu PIN: ";
    cin >> PIN;
    cin.ignore();  // Ignorar salto de línea sobrante

    // Validar PIN
    while (PIN > 9999 || PIN < 1000)
    {
        cout << "PIN introducido no válido. Intenta otra vez: ";
        cin >> PIN;
        cin.ignore();  // Limpiar buffer
    }

    // Ciclo para repetir opciones
    while (true) {
        cout << "Bienvenido a la plataforma de banco, ¿qué te gustaría hacer?\n";
        cout << "Opciones: Depositar, Sacar dinero, Enviar dinero, Salir\n";
        getline(cin, respuesta);  // Leer la respuesta completa

        // Opción Depositar
        if (respuesta == "Depositar") {
            cout << "Introduce el dinero en el cajero por favor: ";
            cin >> dinero;
            cin.ignore();  // Limpiar buffer
            balance += dinero;  // Actualizar balance
            cout << "Has introducido " << dinero << "€. Balance actual: " << balance << "€.\n";
        }
        // Opción Sacar dinero
        else if (respuesta == "Sacar dinero") {
            cout << "¿Cuánto dinero quieres sacar de tu cuenta?\n";
            cin >> dinero;
            cin.ignore();  // Limpiar buffer
            if (dinero <= balance) {
                balance -= dinero;
                cout << "Sacando " << dinero << "€ del cajero...\n";
                cout << "Balance restante: " << balance << "€.\n";
            } else {
                cout << "Fondos insuficientes.\n";
            }
        }
        // Opción Enviar dinero
        else if (respuesta == "Enviar dinero") {
            cout << "Introducir nombre de destinatario: ";
            getline(cin, nombre);  // Leer nombre completo
            cout << "Introducir cantidad: ";
            cin >> dinero;
            cin.ignore();  // Limpiar buffer
            if (dinero <= balance) {
                balance -= dinero;
                cout << "Enviando " << dinero << "€ a: " << nombre << "\n";
                cout << "Balance restante: " << balance << "€.\n";
            } else {
                cout << "Fondos insuficientes.\n";
            }
        }
        // Opción Salir
        else if (respuesta == "Salir") {
            cout << "Gracias por usar la plataforma. ¡Adiós!\n";
            break;  // Salir del ciclo en lugar de usar exit(0)
        }
        // Entrada inválida
        else {
            cout << "Función introducida incorrecta, por favor, intenta otra vez.\n";
        }
    }

    return 0;
}
