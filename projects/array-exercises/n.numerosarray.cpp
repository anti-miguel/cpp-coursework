#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
srand(time(0));
int numeros[100];
int respuesta = 0;

cout << "Introduce número de números aleatorios:"; 
cin >> respuesta;

for (int i=0; i<respuesta && i<100; i++) {
    numeros[i]= rand();
    cout << numeros[i] << " ";
}
}