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
    int numero_user = 0;
    cout << "Introduce un número\n";
    cin >> numero_user;
    if (numero_user % 2 == 0) {
        cout << "El número es par\n";
    }
    else {
        cout << "El número es impar\n";
    }
    int numero_1 = 0;
    cout << "Introduce un número 1\n";
    cin >> numero_1;
    int numero_2 = 0;
    cout << "Introduce un número 2\n";
    cin >> numero_2;
    int numero_3 = 0;
    cout << "Introduce un número 3\n";
    cin >> numero_3;

    if (numero_1 < numero_2 && numero_3 > numero_2) {
        cout << "El número central es: " << numero_2;
    }
    else if (numero_2<numero_1 && numero_2>numero_3)
        cout << "El número central es: " << numero_3;
    else {
        cout << "El número central es: " << numero_1;
    }

int numero_4 = 0;
    cout << "\nIntroduce otro número";
    cin >> numero_4;

    if (numero_4 % 2 == 0  ) {
    cout << "El número es divisible entre 2\n";
    }
    if (numero_4 % 3 == 0) {
        cout << "El número es divisible entre 3\n";
    }
    if (numero_4 % 5 == 0) {
        cout << "El número es divisible entre 5\n";
    }
    if (numero_4 % 7 == 0) {
        cout << "El número es divisible entre 7\n";
    }
    if (numero_4 % 11 == 0) {
        cout << "El número es divisible entre 11\n";
    }
    else {
        cout << "El número no es divisible entre 2, 3, 5, 7 ni 11\n";
    }

    double nota1=0,nota2=0,nota3=0,nota4=0,nota5=0,nota6=0;
    int numeroaprobados = 0;
    int aprobado = 5;
    cout << "Introduce una nota 1: ";
    cin >> nota1;
    cout << "\nIntroduce una nota 2: ";
    cin >> nota2;
    cout << "\nIntroduce una nota 3: ";
    cin >> nota3;
    cout << "\nIntroduce una nota 4: ";
    cin >> nota4;
    cout << "\nIntroduce una nota 5: ";
    cin >> nota5;
    cout << "\nIntroduce una nota 6: ";
    cin >> nota6;

    if (nota1>5) {
        numeroaprobados += 1;
    }
    if (nota2>5) {
        numeroaprobados += 1;
    }
    if (nota3>5) {
        numeroaprobados += 1;
    }
    if (nota4>5) {
        numeroaprobados += 1;
    }
    if (nota5>5) {
        numeroaprobados += 1;
    }
    if (nota1>6) {
        numeroaprobados += 1;
    }
    int numerosuspensos = 6 - numeroaprobados;
    cout << "Han habido " << numeroaprobados << "aprobados y " << numerosuspensos << " suspensos.\n";

int año = 0;
cout << "Introduce un año\n";
cin >> año;

if (año % 4 ==0) {
    if (año % 100 == 0) {
        if (año % 400==0) {
            cout << "El año " << año << " es bisiesto ";
        }
    }
    cout << "El año " << año << " es bisiesto";
}
else {
    cout << "El año " << año << " no es bisiesto";
}
}