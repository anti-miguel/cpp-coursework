#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    ifstream archivo("numeros.txt");
    string linea;
    int suma = 0;
    while (getline(archivo, linea)) {
        // Remove leading and trailing spaces
        linea.erase(linea.begin(), find_if(linea.begin(), linea.end(), [](unsigned char ch) { return !isspace(ch); }));
        linea.erase(find_if(linea.rbegin(), linea.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), linea.end());

        // Skip empty lines
        if (!linea.empty()) {
            stringstream ss(linea);
            string numero;
            while (ss >> numero) {
                suma += stoi(numero);
            }
        }
    }
    cout << "La suma de los números es: " << suma << endl;
    archivo.close();
    return 0;
} 