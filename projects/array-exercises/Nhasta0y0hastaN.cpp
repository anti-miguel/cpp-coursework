#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
srand(time(0));
int numeros[100];
int count = 0;
for (int i = 0; i < 100; i++) {
    numeros[i]= rand() % 101;
    cout << numeros[i] << " ";
    count++;
    if (numeros[i] == 0) {
        break;
    }
}

cout << "Números introducidos al revés tras encontrar el 0: ";
for (int i = count - 1; i >= 0; i--) {
    cout << numeros[i] << " ";
}
return 0;
}