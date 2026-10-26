> Historical coursework document. This describes a broader design than the supplied `7.5.cpp` / `7.5.h` implementation; it is not a list of implemented features.

### Script para Presentación del Juego "Las Siete y Media"

## 1. Introducción (2 minutos)

Buenos días/tardes a todos. Hoy voy a presentarles mi implementación del juego de cartas español "Las Siete y Media".

**¿Qué es Las Siete y Media?**

- Es un juego tradicional español que utiliza la baraja española de 40 cartas
- El objetivo es conseguir una puntuación lo más cercana posible a 7.5 sin pasarse
- Las cartas numéricas (1-7) valen su valor nominal, mientras que las figuras (sota, caballo y rey) valen 0.5 puntos


**Características principales de mi implementación:**

- Juego de consola en C++ con soporte para múltiples jugadores
- Visualización de cartas con arte ASCII/Unicode
- Estrategia de la banca automatizada
- Interfaz de usuario interactiva


## 2. Estructura del Código (3 minutos)

El proyecto está organizado de forma modular, siguiendo principios de diseño orientado a objetos:

**Archivos principales:**

- `main.cpp`: Contiene la lógica principal del juego y el flujo de ejecución
- `carta.h/cpp`: Define la estructura `Carta` y funciones relacionadas
- `baraja.h/cpp`: Implementa la estructura `Baraja` para gestionar el mazo
- `jugador.h/cpp`: Define la estructura `Jugador` y sus comportamientos
- `utilidades.h/cpp`: Contiene funciones auxiliares para la interfaz y compatibilidad


**Diagrama de clases básico:**

- `Carta`: Almacena valor y palo, calcula valor de juego, obtiene nombre
- `Baraja`: Gestiona un vector de cartas, permite barajar y repartir
- `Jugador`: Mantiene nombre, mano de cartas, estado y puntuación
- `Utilidades`: Funciones para visualización y compatibilidad


## 3. Características Destacadas (4 minutos)

**Visualización de cartas:**

- Implementación dual: modo Unicode avanzado y modo ASCII básico
- El usuario puede elegir el modo que prefiera al inicio del juego
- Representación visual clara de las cartas y sus valores


```plaintext
Modo Unicode:
┌───────┐
│ A     │
│       │
│   ♥   │
│       │
│     A │
└───────┘
As de Copas

Modo ASCII básico:
+-------+
| A     |
|       |
|   C   |
|       |
|     A |
+-------+
As de Copas
```

**Estrategia de la banca:**

- La banca sigue reglas específicas para decidir si pide carta o se planta:

- Si tiene menos de 5 puntos, siempre pide carta
- Si tiene 7.5 puntos, nunca pide carta
- Si hay jugadores con más puntos, arriesga hasta 7 puntos
- Si no hay jugadores con más puntos, se planta con 5 o más





**Gestión de múltiples jugadores:**

- Soporte para 1-8 jugadores más la banca
- Nombres personalizables para cada jugador
- Sistema de turnos y determinación de ganadores


## 4. Desafíos Técnicos (3 minutos)

**Manejo de caracteres especiales:**

- Desafío: Mostrar correctamente caracteres españoles y símbolos de palos
- Solución: Configuración específica de la consola de Windows para UTF-8
- Implementación de detección de compatibilidad Unicode


```cpp
void configurarConsola() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::locale utf8_locale(".UTF-8");
    std::cout.imbue(utf8_locale);
    // ...
}
```

**Compatibilidad multiplataforma:**

- Uso de condicionales de preprocesador para código específico de plataforma
- Implementación de funciones genéricas para operaciones comunes


```cpp
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
```

**Gestión de entrada del usuario:**

- Implementación de una función `limpiarBuffer()` para evitar problemas con el buffer de entrada
- Solución a conflictos entre `windows.h` y `std::numeric_limits`


## 5. Demostración (3 minutos)

[En esta parte, haré una demostración en vivo del juego, mostrando:]

1. Inicio del juego y selección del modo de visualización
2. Configuración del número de jugadores y nombres
3. Desarrollo de una partida rápida
4. Determinación del ganador
5. Opción de jugar otra partida


## 6. Mejoras Futuras (2 minutos)

El código incluye comentarios "TODO" que indican posibles mejoras:

**Mejoras técnicas:**

- Implementar un sistema de apuestas
- Mejorar la compatibilidad multiplataforma
- Añadir soporte para diferentes tipos de barajas (francesa, etc.)


**Mejoras de jugabilidad:**

- Implementar modos de juego adicionales o reglas variantes
- Añadir un sistema de puntuación persistente entre partidas
- Mejorar la interfaz con colores y efectos visuales


**Mejoras de código:**

- Refactorizar para usar clases en lugar de estructuras
- Implementar pruebas unitarias
- Optimizar el rendimiento en ciertas operaciones


## 7. Conclusión y Lecciones Aprendidas (2 minutos)

**Principales lecciones:**

- La importancia de una arquitectura modular para facilitar el mantenimiento
- Los desafíos específicos de las aplicaciones de consola en diferentes plataformas
- El equilibrio entre la complejidad del código y la claridad
- La importancia de una documentación clara y completa


**Conclusión:**
Este proyecto demuestra cómo un diseño cuidadoso y una implementación incremental pueden resultar en un producto de software de calidad, incluso con las limitaciones inherentes a una aplicación de consola.

## 8. Preguntas (1-2 minutos)

¿Alguna pregunta sobre la implementación, las decisiones de diseño o cualquier aspecto del código?

---

[Notas para mí mismo durante la presentación:]

- Tener el código abierto en Visual Studio para mostrar partes específicas
- Preparar una terminal para la demostración en vivo
- Tener ejemplos de código listos para mostrar características específicas
- Estar preparado para explicar cualquier parte del código en detalle