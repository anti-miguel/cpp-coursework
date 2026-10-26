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
    int Nota1 = 0;
    int Nota2 = 0;
    int Nota3 = 0;

    cout << "Qué nota has sacado en el primer trimestre?";
    cin >> Nota1;

    if (Nota1 < 0 || Nota1 > 10)
        cout << "La nota introducida no es válida.";


    else {

    if (Nota1 < 5) {
        cout << "\tEstás suspenso.";
    }
    else if (5 <= Nota1 && Nota1 <= 6.8) {
        cout << "Has sacado un Aprobado";
    }
        if (6.9 <= Nota1 && Nota1 < 8.9) {
            cout << "Has sacado un Notable";
        }
        else {
            cout << "Has sacado un Sobresaliente";
        }
}
    cout << "\nQué nota has sacado en el segundo trimestre?";
    cin >> Nota2;

    if (Nota2 < 0 || Nota2 > 10)
        cout << "La nota introducida no es válida.";


    else {

        if (Nota2 < 5) {
            cout << "\tEstás suspenso.";
        }
        else if (5 <= Nota2 && Nota2 <= 6.8) {
            cout << "Has sacado un Aprobado";
        }
        if (6.9 <= Nota2 && Nota2 < 8.9) {
            cout << "Has sacado un Notable";
        }
        else {
            cout << "Has sacado un Sobresaliente";
        }
    }
    cout << "\nQué nota has sacado en el tercer trimestre?";
    cin >> Nota3;

    if (Nota3 < 0 || Nota3 > 10)
        cout << "La nota introducida no es válida.";


    else {

        if (Nota3 < 5) {
            cout << "\tEstás suspenso.";
        }
        else if (5 <= Nota3 && Nota3 <= 6.8) {
            cout << "Has sacado un Aprobado";
        }
        if (6.9 <= Nota3 && Nota3 < 8.9) {
            cout << "Has sacado un Notable";
        }
        else {
            cout << "Has sacado un Sobresaliente";
        }
    }

    int Media = (Nota1 + Nota2 + Nota3) / 3;

    cout << "\n Tu media de exámenes es de " << Media;
   

}

