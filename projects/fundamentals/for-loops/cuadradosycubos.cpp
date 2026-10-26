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
    int numero=10;
    for (int i=0; i<=numero; i++) {
    int cuadrado=i*i;int cubo=i*i*i;
    cout << "------------------------------";
    cout << i << " | " << cuadrado << " | " << cubo << " | ";
    cout << "------------------------------";
    }


}