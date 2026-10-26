#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <string>

using namespace std;






// Dimensiones del mapa
const int filas = 20, columnas = 20;

// Límites globales
const int maxEdificios = 10; // Estructuras máximas
const int probabilidadEnemigo = 30; // Probabilidad de que aparezca un enemigo por cada casilla que se recorre
int CasillasRecorridas = 0;
const int COOLDOWN_ENCUENTRO = 5;  // Numero de movimientos de cooldown
vector<pair<int, int>> PosadasVisitadas;  // Coordenadas de Posadas visitadas
bool DescansoEnSantuario = false;  // Revisar si el jugador ha pasado por el santuario


// Estadísticas del jugador
string nombre = "Sin Nombre";
int fuerza = 0, destreza = 0, magia = 0;
int vidaMaxima = 100, vidaActual = 100, experiencia = 0;
int carneCocinada = 5, medicinas = 2;

// Constantes y estructuras de creación de personaje
const int numStats = 3;
const int numOrigens = 6;
const int numProfesiones = 8;

// Función para limpiar consola
void limpiarConsola() { system("cls"); }

void esperarSegundos(float segundos) {
    Sleep(segundos * 1000);
}

void animarTexto(string texto) {
    for(char c : texto) {
        cout << c << flush;
        Sleep(30);
    }
    cout << endl;
}

struct CharacterCreation {
    string statsNombres[numStats] = {"Fuerza", "Destreza", "Magia"};
    string origens[numOrigens] = {"Elfo", "Enano", "Hobbit", "Humano", "Orco", "Troll"};
    string profesiones[numProfesiones] = {"Arquero", "Bárbaro", "Curandero", "Druida", 
                                        "Guerrero", "Mago", "Paladín", "Sacerdote"};

    // Modificadores por Origen
    int modOrigen[numOrigens][numStats] = {
        {-5, 15, 10},  // Elfo
        {25, 0, -5},   // Enano
        {-10, 25, 5},  // Hobbit
        {10, 5, 5},    // Humano
        {20, 5, -5},   // Orco
        {35, -15, 0}   // Troll
    };

    // Modificadores por Profesión
    int modProfesion[numProfesiones][numStats] = {
        {5, 20, -5},   // Arquero
        {30, 10, -20}, // Bárbaro
        {-5, 0, 25},   // Curandero
        {5, 5, 10},    // Druida
        {20, 5, -5},   // Guerrero
        {-10, 0, 30},  // Mago
        {15, 0, 5},    // Paladín
        {-5, 5, 20}    // Sacerdote
    };
};

// Funciones de creación de personaje
void mostrarModificadores(CharacterCreation& cc) {
    cout << "\nTABLAS DE MODIFICADORES\n";
    
    cout << "\nPor Origen:\n";
    cout << "Origen\t\tFuerza\tDestreza\tMagia\n";
    for (int i = 0; i < numOrigens; i++) {
        cout << cc.origens[i] << "\t" << cc.modOrigen[i][0] << "\t" 
             << cc.modOrigen[i][1] << "\t\t" << cc.modOrigen[i][2] << "\n";
    }

    cout << "\nPor Profesión:\n";
    cout << "Profesión\tFuerza\tDestreza\tMagia\n";
    for (int i = 0; i < numProfesiones; i++) {
        cout << cc.profesiones[i] << "\t" << cc.modProfesion[i][0] << "\t" 
             << cc.modProfesion[i][1] << "\t\t" << cc.modProfesion[i][2] << "\n";
    }
}

void mostrarFichaPersonaje(CharacterCreation& cc, string nombre, int origen, int profesion, int stats[]) {
    cout << "\nFICHA RPG\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Origen: " << (origen >= 0 ? cc.origens[origen] : "No seleccionado") << "\n";
    cout << "Profesión: " << (profesion >= 0 ? cc.profesiones[profesion] : "No seleccionada") << "\n";
    cout << "\nEstadísticas:\n";
    cout << "Atributo\tBase\tMod. Origen\tMod. Profesión\tTotal\n";
    
    for (int i = 0; i < numStats; i++) {
        int modOrig = (origen >= 0 ? cc.modOrigen[origen][i] : 0);
        int modProf = (profesion >= 0 ? cc.modProfesion[profesion][i] : 0);
        int total = stats[i] + modOrig + modProf;
        
        cout << cc.statsNombres[i] << "\t\t" << stats[i] << "\t" 
             << modOrig << "\t\t" << modProf << "\t\t" << total << "\n";
    }
}

bool crearPersonaje() {
    CharacterCreation cc;
    int stats[numStats] = {0};
    int origen = -1;
    int profesion = -1;
    
    limpiarConsola();
    animarTexto("=== Creación de Personaje ===\n");
    animarTexto("Bienvenido al mundo post-apocalíptico...\n");
    esperarSegundos(1);

    // Obtener nombre de personaje
    cout << "\nIntroduce el nombre de tu personaje: ";
    cin.ignore();
    getline(cin, nombre);

    while (true) {
        limpiarConsola();
        cout << "\n=== Menú de Creación ===\n";
        cout << "1. Ver tablas de modificadores\n";
        cout << "2. Seleccionar origen\n";
        cout << "3. Seleccionar profesión\n";
        cout << "4. Tirar estadísticas\n";
        cout << "5. Ver ficha actual\n";
        cout << "6. Confirmar personaje\n";
        cout << "Selecciona una opción: ";
        
        int opcion;
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarModificadores(cc);
                break;
                
            case 2: {
                cout << "\nSelecciona tu origen:\n";
                for (int i = 0; i < numOrigens; i++) {
                    cout << i + 1 << ". " << cc.origens[i] << "\n";
                }
                cin >> origen;
                if (origen >= 1 && origen <= numOrigens) {
                    origen--;
                    animarTexto("Has elegido ser un " + cc.origens[origen]);
                } else {
                    cout << "Origen no válido.\n";
                    origen = -1;
                }
                break;
            }
                
            case 3: {
                cout << "\nSelecciona tu profesión:\n";
                for (int i = 0; i < numProfesiones; i++) {
                    cout << i + 1 << ". " << cc.profesiones[i] << "\n";
                }
                cin >> profesion;
                if (profesion >= 1 && profesion <= numProfesiones) {
                    profesion--;
                    animarTexto("Has elegido ser un " + cc.profesiones[profesion]);
                } else {
                    cout << "Profesión no válida.\n";
                    profesion = -1;
                }
                break;
            }
                
            case 4: {
                cout << "\nTirando estadísticas base...\n";
                for (int i = 0; i < numStats; i++) {
                    stats[i] = 50 + rand() % 51; // 50-100
                    cout << cc.statsNombres[i] << ": " << stats[i] << endl;
                }
                break;
            }
                
            case 5:
                mostrarFichaPersonaje(cc, nombre, origen, profesion, stats);
                break;
                
            case 6:
                if (origen >= 0 && profesion >= 0 && stats[0] > 0) {
                    // Aplicar estadísticas finales a las variables
                    for (int i = 0; i < numStats; i++) {
                        int total = stats[i] + 
                                  cc.modOrigen[origen][i] + 
                                  cc.modProfesion[profesion][i];
                        
                        switch(i) {
                            case 0: fuerza = total; break;
                            case 1: destreza = total; break;
                            case 2: magia = total; break;
                        }
                    }
                    
                    // Establecer estadísticas derivadas iniciales
                    vidaMaxima = 100 + (destreza * 2);
                    vidaActual = vidaMaxima;
                    
                    animarTexto("\n¡Personaje creado con éxito!");
                    esperarSegundos(1);
                    return true;
                } else {
                    cout << "\nDebes completar todas las opciones antes de confirmar.\n";
                }
                break;
        }
        
        system("pause");
    }
    
    return false;
}

// Spawn de personaje
int spawnX = filas / 2, spawnY = columnas / 2;

// Tipos de casillas
enum class Tile {
    OUTPOST,
    VILLAGE,
    EMPTY,
    ROAD,
    SANCTUARY,
    INN,
};

// Mapas
array<array<Tile, columnas>, filas> mapa; //Mapa real 20x20
array<array<char, columnas>, filas> mapaOculto; //Mapa oculto 20x20


// Inicializar mapa y ocultar casillas
void inicializarMapa() {
    srand(time(0)); //Semilla aleatoria
    //Inicializar todas las casillas como vacías y ocultas
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            mapa[i][j] = Tile::EMPTY,/*Vacío*/ mapaOculto[i][j] = '?'; //Oculto

    mapa[spawnX][spawnY] = Tile::SANCTUARY; //Santuario en el centro del mapa. Lugar de spawn
    //Colocar edificios aleatoriamente
    int edificiosGenerados = 0;
    while (edificiosGenerados < maxEdificios) {
        int x = rand() % filas, y = rand() % columnas;
        if (mapa[x][y] == Tile::EMPTY) {
            mapa[x][y] = (rand() % 2) ? Tile::OUTPOST : Tile::VILLAGE;
            edificiosGenerados++;
        }
    }
}

// Revelar casillas cerca del jugador
void revelarRadio(int jugadorX, int jugadorY, int radio) {
    for (int dx = -radio; dx <= radio; ++dx) { //Revelar casillas en un radio circular alrededor del jugador
        for (int dy = -radio; dy <= radio; ++dy) {
            int nx = jugadorX + dx, ny = jugadorY + dy;
            if (nx >= 0 && nx < filas && ny >= 0 && ny < columnas) { //Revisar si está dentro de los límites del mapa
                if (sqrt(dx * dx + dy * dy) <= radio) { //Teorema de pitágoras para radio de visibilidad
                    switch (mapa[nx][ny]) { //Convertir tipo de casilla a Letra visible
                        case Tile::SANCTUARY: mapaOculto[nx][ny] = 'S'; break;
                        case Tile::ROAD:      mapaOculto[nx][ny] = '#'; break;
                        case Tile::OUTPOST:   mapaOculto[nx][ny] = 'O'; break;
                        case Tile::VILLAGE:   mapaOculto[nx][ny] = 'V'; break;
                        case Tile::INN:       mapaOculto[nx][ny] = 'P'; break;
                        case Tile::EMPTY:     mapaOculto[nx][ny] = '.'; break;
                        default:              mapaOculto[nx][ny] = '?';
                    }
                }
            }
        }
    }
}

// Mostrar mapa
void mostrarMapa(int jugadorX, int jugadorY) {
    //Escribir cada casilla del mapa
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (i == jugadorX && j == jugadorY) cout << "X "; //Jugador
            else cout << mapaOculto[i][j] << ' '; //Casilla
        }
        cout << endl; //Nueva línea para cada fila
    }
}

// Crear un camino hacia el Santuario
void crearCamino(int startX, int startY, int endX, int endY) {
    int x = startX;
    while (x != endX) {
        if (mapa[x][startY] == Tile::EMPTY) mapa[x][startY] = Tile::ROAD;
        x += (x < endX) ? 1 : -1;
    }

    int y = startY;
    while (y != endY) {
        if (mapa[endX][y] == Tile::EMPTY) mapa[endX][y] = Tile::ROAD;
        y += (y < endY) ? 1 : -1;
    }
}

// Estructura de nivel y estadísticas de personaje
struct PlayerStats {
    int nivel = 1;
    int experienciaNecesaria = 100; // XP base necesaria para subir de nivel
    
    void calcularExperienciaNecesaria() {
        // La experiencia incrementa por cada nivel 
        experienciaNecesaria = nivel * 100;
    }
};

PlayerStats statsJugador;

void mostrarEstadisticas() {
    animarTexto("\n=== Estadísticas del Personaje ===");
    cout <<"Nivel: " + to_string(statsJugador.nivel);
    cout <<"Experiencia: " + to_string(experiencia) + "/" + to_string(statsJugador.experienciaNecesaria);
    
    // Mostrar estadísticas con barras visuales
    auto mostrarBarra = [](string nombre, int valor) {
        string barra = nombre + ": " + to_string(valor) + " [";
        for(int i = 0; i < valor/2; i++) barra += "█";
        for(int i = valor/2; i < 50; i++) barra += "-";
        barra += "]";
        cout << barra;
    };
    
    mostrarBarra("Fuerza   ", fuerza);
    mostrarBarra("Destreza ", destreza);
    mostrarBarra("Magia    ", magia);
    animarTexto("\nVida: " + to_string(vidaActual) + "/" + to_string(vidaMaxima));
}

// Menú de subir de nivel
void menuMejorarEstadistica() {
    while(true) {
        limpiarConsola();
        mostrarEstadisticas();
        
        animarTexto("\n=== Menú de Mejora ===");
        cout << "1. Aumentar Fuerza   (+3 daño físico)";
        cout << "2. Aumentar Destreza (+2 evasión, +10 vida máxima)";
        cout << "3. Aumentar Magia    (+2 poder mágico, +5 vida máxima)";
        cout << "4. Volver al Santuario";
        
        char opcion = _getch();
        
        if(experiencia >= statsJugador.experienciaNecesaria) {
            switch(opcion) {
                case '1':
                    fuerza += 3;
                    experiencia -= statsJugador.experienciaNecesaria;
                    break;
                case '2':
                    destreza += 2;
                    vidaMaxima += 10;
                    experiencia -= statsJugador.experienciaNecesaria;
                    break;
                case '3':
                    magia += 2;
                    vidaMaxima += 5;
                    experiencia -= statsJugador.experienciaNecesaria;
                    break;
                case '4':
                    return;
                default:
                    continue;
            }
            
            statsJugador.nivel++;
            statsJugador.calcularExperienciaNecesaria();
            vidaActual = vidaMaxima; // Curarse a tope cuando se sube de nivel
            
            animarTexto("\n¡Nivel Aumentado! Ahora eres nivel " + to_string(statsJugador.nivel));
            system("pause");
        } else if(opcion == '4') {
            return;
        } else {
            animarTexto("\nNo tienes suficiente experiencia para subir de nivel.");
            animarTexto("Necesitas " + to_string(statsJugador.experienciaNecesaria - experiencia) + " puntos más.");
            system("pause");
        }
    }
}


// Funcion de descansar en el Santuario
void descansarEnSantuario(int& jugadorX, int& jugadorY) {
    while(true) {
        limpiarConsola();
        cout << "=== Santuario ===\n";
        cout << "Un lugar de reposo y reflexión...\n\n";
        mostrarEstadisticas();
       
        cout << "\n¿Qué deseas hacer?\n";
        cout << "1. Descansar (recuperar vida)\n";
        cout << "2. Meditar (subir de nivel)\n";
        cout << "3. Cocinar carne (convierte 2 carnes en 1 medicina)\n";
        cout << "4. Salir del Santuario\n";
       
        char opcion = _getch();
       
        switch(opcion) {
            case '1': {
                animarTexto("Te sientas junto al fuego y descansas...");
                vidaActual = vidaMaxima;
                esperarSegundos(1);
                animarTexto("¡Vida completamente restaurada!");
                // Establecer santuario como visitado
                DescansoEnSantuario = true;
                system("pause");
                break;
            }
            case '2': {
                menuMejorarEstadistica();
                break;
            }
            case '3': {
                if(carneCocinada >= 2) {
                    carneCocinada -= 2;
                    medicinas++;
                    animarTexto("Has cocinado la carne y creado una medicina.");
                } else {
                    animarTexto("No tienes suficiente carne para cocinar.");
                }
                system("pause");
                break;
            }
            case '4':
                return;
        }
    }
}

// Structs y enums de combate
struct Enemy {
    string name;
    int health;
    int maxHealth;
    int damage;
    int defense;
    
    Enemy(string n, int h, int d, int def) : 
        name(n), health(h), maxHealth(h), damage(d), defense(def) {}
};

vector<Enemy> enemyTypes = {
    Enemy("Infected Survivor", 80, 10, 5),
    Enemy("Military Zombie", 100, 15, 8),
    Enemy("Feral Beast", 50, 20, 3),
    Enemy("Rogue Soldier", 150, 12, 10)
};

// Funciones de apoyo en combate
void mostrarBarraVida(int actual, int maxima, string nombre) {
    cout << nombre << " HP: [";
    int barras = (actual * 20) / maxima;
    for(int i = 0; i < 20; i++) {
        if(i < barras) cout << "█";
        else cout << "-";
    }
    cout << "] " << actual << "/" << maxima << endl;
}


// Función principal de combate
bool combate(int& vidaActual, int vidaMaxima, int& medicinas, int& carneCocinada, Tile ubicacion) {
    limpiarConsola();
    
    // Seleccionar enemigo según localización de jugador
    Enemy enemigo = enemyTypes[rand() % enemyTypes.size()];
    if(ubicacion == Tile::OUTPOST) {
        enemigo.health *= 1.5;
        enemigo.damage *= 1.2;
    }
    
    animarTexto("¡Un " + enemigo.name + " aparece frente a ti!");
    esperarSegundos(1);
    
    bool turnoJugador = true;
    
    while(vidaActual > 0 && enemigo.health > 0) {
        limpiarConsola();
        
        // Mostrar barras de vida
        mostrarBarraVida(vidaActual, vidaMaxima, "Jugador");
        mostrarBarraVida(enemigo.health, enemigo.maxHealth, enemigo.name);
        cout << "\nMedicinas: " << medicinas << " | Carne: " << carneCocinada << endl;
        
        if(turnoJugador) {
            cout << "\nTu turno! ¿Qué deseas hacer?\n";
            cout << "1. Atacar\n";
            cout << "2. Usar medicina (+" << vidaMaxima/2 << " HP)\n";
            cout << "3. Comer carne (+" << vidaMaxima/4 << " HP)\n";
            cout << "4. Intentar huir\n";
            
            char opcion = _getch();
            
            switch(opcion) {
                case '1': {
                    int damage = fuerza + (rand() % 10) - enemigo.defense;
                    damage = max(1, damage); // Mínimo 1 de daño
                    enemigo.health -= damage;
                    animarTexto("¡Atacaste al " + enemigo.name + " causando " + to_string(damage) + " de daño!");
                    break;
                }
                case '2': {
                    if(medicinas > 0) {
                        int curacion = vidaMaxima/2;
                        vidaActual = min(vidaMaxima, vidaActual + curacion);
                        medicinas--;
                        animarTexto("¡Te has curado " + to_string(curacion) + " puntos de vida!");
                    } else {
                        animarTexto("¡No tienes medicinas!");
                        continue;
                    }
                    break;
                }
                case '3': {
                    if(carneCocinada > 0) {
                        int curacion = vidaMaxima/4;
                        vidaActual = min(vidaMaxima, vidaActual + curacion);
                        carneCocinada--;
                        animarTexto("¡Has comido carne y recuperado " + to_string(curacion) + " puntos de vida!");
                    } else {
                        animarTexto("¡No tienes carne!");
                        continue;
                    }
                    break;
                }
                case '4': {
                    if(rand() % 100 < 30) { // 30% probabilidad de escape
                        animarTexto("¡Lograste escapar!");
                        return true;
                    } else {
                        animarTexto("¡No lograste escapar!");
                    }
                    break;
                }
                default:
                    continue;
            }
        } else {
            // Turno enemigo
            esperarSegundos(1);
            int damage = max(1, enemigo.damage - (destreza / 2));
            vidaActual -= damage;
            animarTexto("¡" + enemigo.name + " te ha atacado causando " + to_string(damage) + " de daño!");
        }
        
        esperarSegundos(1);
        turnoJugador = !turnoJugador;
    }
    
    if(vidaActual <= 0) {
        animarTexto("Has sido derrotado...");
        return false;
    } else {
        int expGanada = enemigo.maxHealth / 2;
        experiencia += expGanada;
        int carneGanada = 1 + (rand() % 2);
        carneCocinada += carneGanada;
        
        animarTexto("¡Victoria! Has derrotado al " + enemigo.name);
        animarTexto("Ganaste " + to_string(expGanada) + " puntos de experiencia");
        animarTexto("Encontraste " + to_string(carneGanada) + " unidades de carne");
        esperarSegundos(2);
        return true;
    }
}


// Consumir carne a cada paso, reiniciar posicion si el jugador se queda sin
void consumirCarne(int& jugadorX, int& jugadorY) {
    if (carneCocinada > 0) {
        carneCocinada--;
    } else {
        animarTexto("Te quedaste sin carne y colapsaste de hambre. Volviste al Santuario.");
        vidaActual -= 10;
        jugadorX = spawnX; // Reiniciar posicion
        jugadorY = spawnY;
        carneCocinada = 3; // Restaurar un poco de carne
        if (vidaActual <= 0) {
            animarTexto("Tu salud se agotó...");
            system("pause");
            exit(0);
        }
        system("pause");
    }
}


// Función de encuentros de enemigos
void manejarEncuentro(Tile edificio) {
    // Solo permitir encuentros si se ha recorrido la cantidad de casillas limite
    if (CasillasRecorridas < COOLDOWN_ENCUENTRO) {
        return;
    }

    int chance = rand() % 100;
    int dificultad = probabilidadEnemigo;
   
    if (edificio == Tile::OUTPOST) dificultad = 70;
    else if (edificio == Tile::VILLAGE) dificultad = 50;
    else if (edificio == Tile::EMPTY) dificultad = 20;
   
    if (chance < dificultad) {
        if(!combate(vidaActual, vidaMaxima, medicinas, carneCocinada, edificio)) {
            cout << "\nGame Over\n";
            system("pause");
            exit(0);
        }
        // Reiniciar casillas de cooldown
        CasillasRecorridas = 0;
        // Limpiar buffer
        while (_kbhit()) _getch();
    }
}
void interactuarPosada(Tile& edificio, int jugadorX, int jugadorY) {
    // Posada Visitada si o no
    bool PosadaVisitada = false;
    for(const auto& inn : PosadasVisitadas) {
        if(inn.first == jugadorX && inn.second == jugadorY) {
            PosadaVisitada = true;
            break;
        }
    }

    // Si posada visitada y no se ha pasado por el santuario:
    if(PosadaVisitada && !DescansoEnSantuario) {
        limpiarConsola();
        animarTexto("Ya has visitado esta posada...");
        esperarSegundos(1);
        animarTexto("Debes visitar un santuario antes de poder descansar aquí de nuevo.");
        system("pause");
        return;
    }

    // Interaccion de posada normal
    limpiarConsola();
    animarTexto("Has llegado a una posada restaurada...");
    esperarSegundos(1);
   
    animarTexto("El posadero te ofrece comida y un lugar para descansar.");
    esperarSegundos(1);
   
    carneCocinada += 10;
    animarTexto("Has recibido 10 unidades de carne cocinada.");
   
    // Curar al jugador un poco
    int curacion = vidaMaxima / 4;
    vidaActual = min(vidaMaxima, vidaActual + curacion);
    animarTexto("El descanso te ha recuperado algo de salud.");
   
    // Añadir posada a la lista de posadas visitadas si no lo está
    if(!PosadaVisitada) {
        PosadasVisitadas.push_back({jugadorX, jugadorY});
    }
    
    // Establecer santuario como NO visitado
    DescansoEnSantuario = false;
    
    system("pause");
}
// Explorar edificios
void interactuarEdificio(Tile& edificio, int jugadorX, int jugadorY) {
    limpiarConsola();
    if (edificio == Tile::OUTPOST) {
        cout << "Escuchas disparos lejanos y ves un campamento militar.\n";
    } else if (edificio == Tile::VILLAGE) {
        cout << "Una ciudad en ruinas se alza entre los escombros. Es un sitio desolado.\n";
    }
    else if (edificio == Tile::INN) {
        cout << "Un lugar cálido. Recuperas tus fuerzas.\n";
        carneCocinada +=10;
        system("pause");
    }

    cout << "¿Deseas explorar el edificio? (Y/N): ";
    char respuesta;
    cin >> respuesta;

    if (toupper(respuesta) == 'Y') {
        manejarEncuentro(edificio);
        cout << "Encontraste suministros en el edificio.\n";    
        carneCocinada += 3;
        edificio = Tile::INN;

        // Crear camino al santuario
        crearCamino(jugadorX, jugadorY, spawnX, spawnY);
        system("pause");
    } else {
        cout << "Decidiste ignorar el edificio.\n";
        system("pause");
    }
}

// Función de movimiento de jugador
void moverJugador(int& x, int& y, char direccion) {
    int nx = x, ny = y;
   
    // Procesar movimiento segun tecla minuscula 
    switch(tolower(direccion)) {
        case 'w': nx--; break;
        case 's': nx++; break;
        case 'a': ny--; break;
        case 'd': ny++; break;
        default: return; // No valida
    }
   
    // Validate movement bounds
    if (nx >= 0 && nx < filas && ny >= 0 && ny < columnas) {
        Tile& casilla = mapa[nx][ny];
       
        // Process tile interaction
        switch(casilla) {
            case Tile::SANCTUARY:
                descansarEnSantuario(nx, ny);
                while (_kbhit()) _getch(); // Limpiar buffer tras interaccion
                break;
               
            case Tile::ROAD:
                revelarRadio(nx, ny, 2);
                x = nx;
                y = ny;
                CasillasRecorridas++;  // Subir el contador tras desplazarse
                return;
               
            case Tile::OUTPOST:
            case Tile::VILLAGE:
                consumirCarne(x, y);
                interactuarEdificio(casilla, nx, ny);
                while (_kbhit()) _getch(); // Limpiar buffer tras interaccion
                break;
               
            case Tile::EMPTY:
                consumirCarne(x, y);
                manejarEncuentro(casilla);
                break;
               
            case Tile::INN:
                consumirCarne(x, y);
                interactuarPosada(casilla, nx, ny);
                while (_kbhit()) _getch(); // Limpiar buffer tras interaccion
                break;
        }
       
        revelarRadio(nx, ny, 2);
        x = nx;
        y = ny;
        CasillasRecorridas++;  // Subir el contador tras desplazarse
    } else {
        cout << "¡No puedes moverte fuera del mapa!\n";
        Sleep(500); // Pausa corta
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    srand(time(0));
   
    if (!crearPersonaje()) {
        cout << "Error en la creación del personaje.\n";
        return 1;
    }
   
    inicializarMapa();
    statsJugador.calcularExperienciaNecesaria();
   
    int jugadorX = spawnX, jugadorY = spawnY;
    revelarRadio(jugadorX, jugadorY, 2);

    while (vidaActual > 0) {
        limpiarConsola();
        mostrarMapa(jugadorX, jugadorY);
        cout << "Nombre: " << nombre << " | Nivel: " << statsJugador.nivel << endl;
        cout << "Salud: " << vidaActual << "/" << vidaMaxima
             << " | Carne: " << carneCocinada << " | Medicinas: " << medicinas << "\n";
        cout << "Experiencia: " << experiencia << "/" << statsJugador.experienciaNecesaria << endl;
        cout << "Controles: W/A/S/D para moverte, Q para salir\n";
        
        // Registrar input y limpiar buffer
        char comando = _getch();
        if (comando == 'q' || comando == 'Q') break;
        
        // Procesar movimientos
        moverJugador(jugadorX, jugadorY, comando);
    }
    
    cout << "Fin del juego. Gracias por jugar.\n";
    return 0;
}