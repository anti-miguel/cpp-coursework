#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
srand(time(0));
int numeros[20];
for (int i = 0; i < 20; i++) {
    numeros[i]= rand() % 11;
    cout << numeros[i] << " ";
}
return 0;
}