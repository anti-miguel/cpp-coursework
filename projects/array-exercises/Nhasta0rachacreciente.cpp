#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
srand(time(0));
int numeros[100];
int cuenta = 0;
for (int i = 0; i < 100; i++) {
    numeros[i]= rand() % 101;
    cout << numeros[i] << " ";
    cuenta++;
    if (numeros[i] == 0) {
        break;
    }
}

int rachaMax=0;
int racha=1;

for (int i = 1; i < cuenta; i++) {
    if (numeros[i] == numeros[i-1]) {
        racha++;
    }
    else {
        if (racha > rachaMax) {
            rachaMax = racha;
        }
    }
}
if (racha>rachaMax) {
       rachaMax = racha; 
    }
    cout << "La racha más larga de números iguales es: " << rachaMax << endl;

return 0;
}