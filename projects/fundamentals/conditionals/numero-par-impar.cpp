#include <iostream>
#include <string>
using namespace std;

int main (){
    int numero_user = 0;
    cout << "Introduce un número\n";
    cin >> numero_user;
    if (numero_user % 2 == 0) {
        cout << "El número es par";
    }
    else {
        cout << "El número es impar";
    }
}
