#include <iostream>
#include <string>

using namespace std;

struct Par {
	int edad;
	string nombre;
};

// Funciones a desarrollar
// void EmparejarListas( ...
// void EscribirArray( ...

void EmparejarListas(int edades[], string nombres[], Par pares[], int longitud, int i) {
	if (i < longitud) {
		pares[i].edad = edades[i];
		pares[i].nombre = nombres[i];
		EmparejarListas(edades, nombres, pares, longitud, i + 1);
	}
}
void EscribirArray(Par pares[], int longitud, int i) {
	if (i < longitud) {
		cout << "Nombre: " << pares[i].nombre << ", Edad: " << pares[i].edad << endl;
		EscribirArray(pares, longitud, i + 1);
	}
}
int main() {
	const int LONGITUD = 5; // Puedes cambiar la dimensión aquí
	// 1. Array de int con las edades
	int edades[LONGITUD] = { 18, 23, 21, 22, 19 };
	// 2. Array de string con los nombres, del mismo tamaño
	string nombres[LONGITUD] = { "Persona1", "Persona2", "Persona3", "Persona4", "Persona5" };
	// 3. Array del tipo Par, con la misma longitud
	Par pares[LONGITUD];
	// 4. Función para emparejar las listas
	EmparejarListas(edades, nombres, pares, LONGITUD, 0);
	// 5. Comprobamos que el resultado es correcto
	cout << "Lista resultado: " << endl;
	EscribirArray(pares, LONGITUD, 0);
	return 0;
}