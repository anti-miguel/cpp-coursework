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
while (numero>0) {
    numero++;
    if (numero%2!=0 && numero >=0) {
        cout << numero << " ";
    }
}
}