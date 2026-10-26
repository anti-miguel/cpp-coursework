#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

class Character {
private:
    string name;
    string origin;
    string profession;
    int stats[3];  // Fuerza, Destreza, Magia
    int health;
    int experience;
    int money;
    int food;

public:
    Character() {
        name = "Sin Nombre";
        origin = "No seleccionado";
        profession = "No seleccionada";
        stats[0] = stats[1] = stats[2] = 50;
        health = 100;
        experience = 0;
        money = 10;
        food = 50;
    }

    void createCharacter() {
        // Similar to previous character creation logic
    }

    void displayStatus() {
        cout << "\n--- STATUS DEL PERSONAJE ---\n";
        cout << "Nombre: " << name << endl;
        cout << "Origen: " << origin << endl;
        cout << "Profesión: " << profession << endl;
        cout << "Salud: " << health << endl;
        cout << "Experiencia: " << experience << endl;
        cout << "Dinero: " << money << endl;
        cout << "Comida: " << food << endl;
    }
};

class Dungeon {
private:
    static const int MAP_SIZE = 10;
    char map[MAP_SIZE][MAP_SIZE];
    int playerX, playerY;

public:
    Dungeon() {
        initializeMap();
    }

    void initializeMap() {
        // Inicializar el mapa con diferentes tipos de casillas
        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++) {
                map[i][j] = '.';  // Casilla vacía
            }
        }
        // Añadir elementos especiales
        map[0][0] = 'E';  // Entrada
        map[MAP_SIZE-1][MAP_SIZE-1] = 'S';  // Salida
    }

    void displayMap() {
        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++) {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool movePlayer(char direction) {
        int newX = playerX, newY = playerY;

        switch (direction) {
            case 'N': newY--; break;
            case 'S': newY++; break;
            case 'E': newX++; break;
            case 'W': newX--; break;
        }

        // Validar límites y movimiento
        if (newX >= 0 && newX < MAP_SIZE && newY >= 0 && newY < MAP_SIZE) {
            playerX = newX;
            playerY = newY;
            return true;
        }
        return false;
    }
};

class Game {
private:
    Character player;
    Dungeon dungeon;
    bool gameOver;

public:
    Game() : gameOver(false) {}

    void start() {
        cout << "Bienvenido al juego de mazmorras\n";
        player.createCharacter();
        gameLoop();
    }

    void gameLoop() {
        while (!gameOver) {
            system("cls");
            player.displayStatus();
            dungeon.displayMap();
            processCommand();
        }
    }

    void processCommand() {
        string command;
        cout << "\nIngrese un comando (N/S/E/W para moverse, Q para salir): ";
        cin >> command;

        if (command == "Q" || command == "q") {
            gameOver = true;
        } else if (command == "N" || command == "S" || command == "E" || command == "W") {
            dungeon.movePlayer(command[0]);
            // Lógica de encuentros aleatorios
        }
    }
};

int main() {
    srand(time(NULL));
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    Game game;
    game.start();

    return 0;
}