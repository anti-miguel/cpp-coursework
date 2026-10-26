#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// Tamaño del mapa
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;

// Representación del mapa
enum Tile {
    EMPTY,     // Espacio vacío
    WALL,      // Obstáculo
    TREASURE,  // Tesoro
    TRAP,      // Trampa
    EXIT,      // Salida
    ENEMY      // Enemigo
};

// Ficha del jugador
struct Player {
    string name;
    int vida = 100;
    int mana = 50;
    int dinero = 0;
    int fuerza = 15;
    int destreza = 10;
    int magia = 10;
    int x = 0; // Coordenadas en el mapa
    int y = 0;
};

// Ficha del enemigo
struct Enemy {
    int vida = 50;
    int ataque = 10;
};

// Inicializar enemigos en el mapa
vector<Enemy> initializeEnemies(vector<vector<Tile>> &map) {
    vector<Enemy> enemies;
    srand(time(0));
    for (int i = 0; i < 5; i++) { // 5 enemigos generados aleatoriamente
        int x, y;
        do {
            x = rand() % MAP_WIDTH;
            y = rand() % MAP_HEIGHT;
        } while (map[y][x] != EMPTY || (x == 0 && y == 0));
        map[y][x] = ENEMY;
        enemies.push_back({50 + rand() % 21, 10 + rand() % 6}); // Vida: 50-70, Ataque: 10-15
    }
    return enemies;
}

// Inicializar el mapa
void initializeMap(vector<vector<Tile>> &map) {
    srand(time(0));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int random = rand() % 100;
            if (random < 70) map[i][j] = EMPTY;         // 70% espacios vacíos
            else if (random < 80) map[i][j] = WALL;     // 10% paredes
            else if (random < 85) map[i][j] = TREASURE; // 5% tesoros
            else if (random < 95) map[i][j] = TRAP;     // 10% trampas
            else map[i][j] = EXIT;                     // 2% salida
        }
    }
    map[0][0] = EMPTY; // Asegurar inicio vacío
}

// Mostrar el mapa
void displayMap(const vector<vector<Tile>> &map, const Player &player) {
    cout << "\nMapa de la mazmorra:\n";
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == player.y && j == player.x) {
                cout << "P "; // Posición del jugador
            } else {
                switch (map[i][j]) {
                    case EMPTY: cout << ". "; break;
                    case WALL: cout << "# "; break;
                    case TREASURE: cout << "$ "; break;
                    case TRAP: cout << "^ "; break;
                    case EXIT: cout << "E "; break;
                    case ENEMY: cout << "X "; break;
                }
            }
        }
        cout << endl;
    }
}

// Combate con enemigo
void combat(Player &player, Enemy &enemy) {
    cout << "¡Te enfrentas a un enemigo!\n";
    while (player.vida > 0 && enemy.vida > 0) {
        cout << "Jugador ataca: -" << player.fuerza << " vida al enemigo.\n";
        enemy.vida -= player.fuerza;

        if (enemy.vida > 0) {
            cout << "Enemigo contraataca: -" << enemy.ataque << " vida al jugador.\n";
            player.vida -= enemy.ataque;
        }
    }

    if (player.vida > 0) {
        cout << "¡Has derrotado al enemigo! Ganas 20 monedas.\n";
        player.dinero += 20;
    } else {
        cout << "¡Has sido derrotado por el enemigo! Fin del juego.\n";
    }
}

// Manejar eventos en la casilla
void handleTileEvent(Player &player, Tile tile, vector<Enemy> &enemies, int enemyIndex) {
    switch (tile) {
        case TREASURE:
            cout << "¡Encontraste un tesoro! Ganas 50 monedas.\n";
            player.dinero += 50;
            break;
        case TRAP:
            cout << "¡Caíste en una trampa! Pierdes 20 puntos de vida.\n";
            player.vida -= 20;
            break;
        case EXIT:
            cout << "¡Has alcanzado la salida! ¡Victoria!\n";
            player.vida = 0; // Marcar fin del juego
            break;
        case ENEMY:
            combat(player, enemies[enemyIndex]);
            break;
        default:
            cout << "Nada interesante aquí.\n";
            break;
    }
}

// Movimiento del jugador
void movePlayer(Player &player, vector<vector<Tile>> &map, vector<Enemy> &enemies) {
    char command;
    cout << "Moverse (WASD): ";
    cin >> command;

    int newX = player.x, newY = player.y;
    switch (toupper(command)) {
        case 'W': newY--; break;
        case 'A': newX--; break;
        case 'S': newY++; break;
        case 'D': newX++; break;
        default: cout << "Comando no válido.\n"; return;
    }

    // Verificar límites y obstáculos
    if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT || map[newY][newX] == WALL) {
        cout << "¡Movimiento inválido!\n";
        return;
    }

    // Buscar enemigo en la casilla
    int enemyIndex = -1;
    if (map[newY][newX] == ENEMY) {
        for (size_t i = 0; i < enemies.size(); i++) {
            if (enemies[i].vida > 0 && newX == player.x && newY == player.y) {
                enemyIndex = i;
                break;
            }
        }
    }

    // Actualizar posición del jugador
    player.x = newX;
    player.y = newY;

    // Manejar el evento de la casilla
    handleTileEvent(player, map[newY][newX], enemies, enemyIndex);
    if (map[newY][newX] != ENEMY || (enemyIndex != -1 && enemies[enemyIndex].vida <= 0)) {
        map[newY][newX] = EMPTY; // Limpiar casilla después del evento
    }
}

// Mostrar estado del jugador
void displayPlayer(const Player &player) {
    cout << "\nFicha del jugador:\n";
    cout << "Nombre: " << player.name << "\n";
    cout << "Vida: " << player.vida << "\n";
    cout << "Maná: " << player.mana << "\n";
    cout << "Dinero: " << player.dinero << "\n";
    cout << "Fuerza: " << player.fuerza << "\n";
    cout << "Destreza: " << player.destreza << "\n";
    cout << "Magia: " << player.magia << "\n";
}

int main() {
    // Inicializar jugador y mapa
    Player player;
    cout << "Introduce el nombre de tu personaje: ";
    cin >> player.name;

    vector<vector<Tile>> map(MAP_HEIGHT, vector<Tile>(MAP_WIDTH));
    initializeMap(map);

    vector<Enemy> enemies = initializeEnemies(map);

    // Bucle principal del juego
    while (player.vida > 0) {
        displayMap(map, player);
        displayPlayer(player);
        movePlayer(player, map, enemies);
    }

    cout << "Fin del juego. Gracias por jugar.\n";
    return 0;
}
