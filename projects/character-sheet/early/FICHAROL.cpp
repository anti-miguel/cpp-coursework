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
    string nombre = "";
    int fuerza = 50 + rand() % 50 + 1;
    int destreza = 51 + rand() % 50;
    int magia = 51 + rand() % 50;
    int clase = 0;
    int profesion = 0;
    int fuerzamodclass = 0;
    int fuerzamodprof = 0;
    int dexmodclass = 0;
    int dexmodprof = 0;
    int magiamodclass = 0;
    int magiamodprof = 0;
    int ftotal=0;
    int dtotal=0;
    int mtotal=0;
    int respuesta=0;

    string nombreClase = "";
    string nombreProfesion = "";

    while(true) {
        
        cout << "\nQué quieres hacer?\n1: Cambiar nombre \n2: Escoger clase \n3: Escoger profesión\n4: Tirar estadísticas\n5: Ver ficha\n6: Salir\n";
        cin >> respuesta;
        
        if (respuesta==1) {
            cout << "Cuál es tu nombre?\n";
            cin >> nombre;
        }

        else if (respuesta==2) {
            cout << "\n\nEscoge tu clase: \n 1: Elfo \n 2: Enano \n 3: Orco\n";
            cin >> clase;
            switch (clase)
            {
                case 1:
                {
                    cout << "\nHas escogido Elfo\n\n";
                    nombreClase = "Elfo";
                    fuerzamodclass = +0;
                    dexmodclass = +10;
                    magiamodclass = +15;

                    break;
                }
                case 2:
                {
                    cout << "Has escogido Enano\n\n";
                    nombreClase = "Enano";
                    fuerzamodclass = +10;
                    dexmodclass = +5;
                    magiamodclass = -10;
                    break;
                }
                case 3:
                {
                    cout << "Has escogido Orco\n\n";
                    nombreClase = "Orco";
                    fuerzamodclass = +15;
                    dexmodclass = +0;
                    magiamodclass = -15;
                    break;
                }
                default:
                {
                    cout << "Clase introducida no válida.\n\n";
                    break;
                }
            }
            
        }
        else if (respuesta==3) {
            cout << "Escoge tu profesión\n 1: Guerrero \n 2: Mago \n 3: Arquero\n\n";
            cin >> profesion;
            switch (profesion)
            {
                case 1:
                {
                    cout << "Has escogido Guerrero\n\n";
                    nombreProfesion = "Guerrero";
                    fuerzamodprof = +20;
                    dexmodprof = +10;
                    magiamodprof = -20;
                    break;
                }
                case 2:
                {
                    profesion = 2;
                    cout << "Has escogido Mago\n\n";
                    nombreProfesion = "Mago";
                    fuerzamodprof = -10;
                    dexmodprof = -5;
                    magiamodprof = +20;

                    break;
                }
                case 3:
                {
                    profesion = 3;
                    cout << "Has escogido Arquero\n\n";
                    nombreProfesion = "Arquero";
                    fuerzamodprof = -10;
                    dexmodprof = +15;
                    magiamodprof = -10;
                    break;
                }
                default:
                {
                    cout << "Profesión introducida no válida.\n\n";
                    break;
                }
            }
        
        }
        else if (respuesta==4) {
            fuerza = 50 + rand() % 50 + 1;
            destreza = 51 + rand() % 50;
            magia = 51 + rand() % 50;
            cout << "Roll de estadísticas:\nFuerza=" << fuerza << " Destreza=" << destreza << " Magia=" << magia << "\n\n";

        }
        else if (respuesta==5) {

            ftotal=fuerza+fuerzamodclass+fuerzamodprof;
            dtotal=destreza+dexmodclass+dexmodprof;
            mtotal=magia+magiamodclass+magiamodprof;
        
        
            cout << "Tu ficha es:\nNombre: " << nombre << "\nClase: " << nombreClase << "\nProfesión: " << nombreProfesion << 
            "\nFuerza: " << fuerza << "+" << fuerzamodprof+fuerzamodclass<< "=" << ftotal << 
            "\nDestreza: " << destreza << "+" << dexmodprof+dexmodclass<<   "=" << dtotal <<
            "\nMagia: " << magia << "+" << magiamodprof+magiamodclass << "=" << mtotal << "\n\n";
        
        }

        else if(respuesta==6) {
            break;
        }
        else {
            cout << "Opción no válida. Inténtalo de nuevo.\n";
        }
    }
        return 0;
    }