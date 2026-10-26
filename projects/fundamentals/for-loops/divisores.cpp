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
    cout << "Sus divisores son ";
    for (int i = 1; i<=numero; i++) {
        if (numero % i == 0) {
            cout << i << " ";
        }
    }
}