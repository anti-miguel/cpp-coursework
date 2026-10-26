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
    int numero = 0;
    int numerouser = 0;
    cout << "Introduce un número ";
    cin >> numerouser;
    while (numero<numerouser) {
        numero++;
        cout << numero << "+";
    }
}
