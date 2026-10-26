> Historical coursework document. This describes a broader design than the supplied `7.5.cpp` / `7.5.h` implementation; it is not a list of implemented features.

### Documento de Diseño y Desarrollo: Juego "Las Siete y Media"

## 1. Introducción

Este documento describe las decisiones de diseño y desarrollo tomadas durante la implementación del juego de cartas español "Las Siete y Media" en C++. El juego ha sido desarrollado como una aplicación de consola, permitiendo a múltiples jugadores competir contra la banca siguiendo las reglas tradicionales del juego.

### 1.1 Descripción del Juego

"Las Siete y Media" es un juego de cartas tradicional español que utiliza la baraja española de 40 cartas. El objetivo es conseguir una puntuación lo más cercana posible a 7.5 sin pasarse. Las cartas numéricas (del 1 al 7) valen su valor nominal, mientras que las figuras (sota, caballo y rey) valen 0.5 puntos cada una.

## 2. Arquitectura y Estructura del Código

### 2.1 Organización del Proyecto

El proyecto se ha estructurado siguiendo un enfoque modular, separando las diferentes responsabilidades en archivos distintos:

- **main.cpp**: Contiene la lógica principal del juego y el flujo de ejecución.
- **carta.h/cpp**: Define la estructura `Carta` y las funciones relacionadas con las cartas.
- **baraja.h/cpp**: Implementa la estructura `Baraja` para gestionar el mazo de cartas.
- **jugador.h/cpp**: Define la estructura `Jugador` y sus comportamientos.
- **utilidades.h/cpp**: Contiene funciones auxiliares para la interfaz y compatibilidad.


Esta organización modular facilita el mantenimiento del código y permite una clara separación de responsabilidades.

### 2.2 Diagrama de Clases

El diseño se basa en las siguientes estructuras principales:

```plaintext
Carta
  - valor: int
  - palo: Palo (enum)
  + getValorJuego(): float
  + getNombre(): string

Baraja
  - cartas: vector<Carta>
  + Baraja()
  + barajar(): void
  + repartirCarta(): Carta
  + estaVacia(): bool

Jugador
  - nombre: string
  - mano: vector<Carta>
  - esBanca: bool
  - haPerdido: bool
  + Jugador(nombre, esBanca)
  + recibirCarta(carta): void
  + calcularPuntuacion(): float
  + sePasoDe7ymedia(): bool
  + mostrarCartas(): void
  + mostrarCartasASCII(): void
```

## 3. Decisiones de Diseño Importantes

### 3.1 Uso de Estructuras vs. Clases

**Decisión**: Se utilizaron estructuras (`struct`) en lugar de clases (`class`) para representar las entidades del juego.

**Justificación**:

- Las entidades del juego (Carta, Baraja, Jugador) son principalmente contenedores de datos con comportamientos simples.
- El uso de estructuras con miembros públicos simplifica el acceso a los datos y refleja mejor la naturaleza del problema.
- No se requiere un alto nivel de encapsulamiento para este juego, ya que las interacciones entre componentes son directas y transparentes.


**Implicaciones**:

- Mayor simplicidad en el código y acceso directo a los miembros.
- Menor protección de los datos internos, lo que podría ser un inconveniente en un proyecto más grande o con múltiples desarrolladores.


### 3.2 Representación de las Cartas

**Decisión**: Se implementó una representación visual de las cartas utilizando caracteres ASCII/Unicode.

**Justificación**:

- Mejora significativamente la experiencia del usuario al proporcionar una representación visual de las cartas.
- Permite distinguir fácilmente entre diferentes cartas y palos.
- Se implementaron dos versiones (ASCII básico y Unicode) para garantizar la compatibilidad con diferentes terminales.


**Implicaciones**:

- Mayor complejidad en el código de visualización.
- Necesidad de detectar la compatibilidad de la consola con caracteres Unicode.
- Mejora sustancial en la usabilidad y atractivo visual del juego.


### 3.3 Estrategia de la Banca

**Decisión**: Se implementó una estrategia específica para la banca que determina cuándo debe pedir carta o plantarse.

**Justificación**:

- Simula el comportamiento tradicional de la banca en el juego real.
- Proporciona un desafío equilibrado para los jugadores.
- La estrategia se basa en reglas claras que consideran tanto la puntuación de la banca como la de los jugadores.


**Reglas implementadas**:

- Si tiene menos de 5 puntos, siempre pide carta.
- Si tiene 7.5 puntos, nunca pide carta.
- Si hay jugadores con más puntos, arriesga hasta 7 puntos.
- Si no hay jugadores con más puntos, se planta con 5 o más.


**Implicaciones**:

- Comportamiento predecible pero estratégico de la banca.
- Balance adecuado entre dificultad y posibilidades de ganar para los jugadores.


### 3.4 Gestión de Múltiples Jugadores

**Decisión**: Se implementó soporte para un número variable de jugadores (entre 1 y 8) más la banca.

**Justificación**:

- Permite mayor flexibilidad y adaptabilidad del juego a diferentes contextos.
- Posibilita tanto partidas individuales como grupales.
- El límite de 8 jugadores es razonable para mantener la jugabilidad y evitar partidas excesivamente largas.


**Implicaciones**:

- Mayor complejidad en la gestión de turnos y determinación del ganador.
- Necesidad de implementar un sistema para personalizar los nombres de los jugadores.
- Mejora en la reusabilidad del juego para diferentes escenarios.


## 4. Consideraciones Técnicas

### 4.1 Manejo de Caracteres Especiales y Unicode

**Desafío**: Mostrar correctamente caracteres especiales del español y símbolos de los palos de la baraja en la consola de Windows.

**Solución implementada**:

- Configuración de la consola para utilizar la página de códigos UTF-8 (CP_UTF8).
- Detección de la compatibilidad de la consola con caracteres Unicode.
- Implementación de versiones alternativas (ASCII básico) para consolas con limitaciones.


**Código relevante**:

```cpp
void configurarConsola() {
    // Configurar la consola para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Configurar la salida de `std::cout` en UTF-8
    std::locale utf8_locale(".UTF-8");
    std::cout.imbue(utf8_locale);

    // Habilitar el procesamiento de secuencias ANSI
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hConsole, &mode);
    SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
```

**Implicaciones**:

- Mayor compatibilidad con diferentes configuraciones de consola.
- Mejor experiencia visual para los usuarios.
- Complejidad adicional en el código para manejar diferentes escenarios.


### 4.2 Compatibilidad Multiplataforma

**Desafío**: Desarrollar un juego que pueda funcionar en diferentes sistemas operativos.

**Solución parcial**:

- Uso de condicionales de preprocesador (#ifdef _WIN32) para código específico de Windows.
- Implementación de funciones multiplataforma para operaciones comunes (limpiar pantalla).
- Detección del entorno para adaptar la visualización.


**Limitaciones actuales**:

- Algunas funcionalidades (configuración de la consola) están implementadas específicamente para Windows.
- Se requeriría trabajo adicional para garantizar una experiencia óptima en sistemas Unix/Linux.


**Implicaciones**:

- Compatibilidad parcial con diferentes plataformas.
- Necesidad de mejoras futuras para una verdadera compatibilidad multiplataforma.


### 4.3 Gestión de Entrada del Usuario

**Desafío**: Manejar correctamente la entrada del usuario, especialmente con nombres que pueden contener espacios.

**Solución implementada**:

- Uso de `std::getline` para leer nombres completos con espacios.
- Implementación de una función `limpiarBuffer()` para evitar problemas con el buffer de entrada.
- Validación de entradas para prevenir comportamientos inesperados.


**Problema específico resuelto**:

- Conflicto entre `windows.h` y `std::numeric_limits<std::streamsize>::max()`.
- Solución: Usar un valor fijo grande (10000) en lugar de `std::numeric_limits`.


**Implicaciones**:

- Mayor robustez en la gestión de entradas del usuario.
- Solución pragmática para evitar conflictos entre bibliotecas.


## 5. Evolución del Código Durante el Desarrollo

### 5.1 Mejoras Incrementales

El desarrollo del juego siguió un enfoque incremental, con las siguientes etapas principales:

1. **Implementación básica**: Estructuras fundamentales y lógica del juego.
2. **Mejora visual**: Adición de representación ASCII de las cartas.
3. **Soporte para caracteres especiales**: Resolución de problemas con caracteres españoles y símbolos.
4. **Ampliación a múltiples jugadores**: Soporte para varios jugadores con nombres personalizados.
5. **Refinamiento de la interfaz**: Mejoras en la visualización y experiencia de usuario.
6. **Documentación y comentarios**: Adición de documentación detallada y comentarios explicativos.


### 5.2 Desafíos Encontrados y Soluciones

#### Desafío 1: Visualización de Cartas

- **Problema**: Representación visual clara y atractiva de las cartas en la consola.
- **Evolución**: De una simple representación textual a un diseño ASCII/Unicode completo.
- **Solución final**: Implementación de dos versiones (básica y avanzada) según la compatibilidad de la consola.


#### Desafío 2: Compatibilidad con Caracteres Especiales

- **Problema**: Mostrar correctamente caracteres españoles (ñ, tildes) y símbolos de palos.
- **Evolución**: Múltiples intentos con diferentes configuraciones de consola.
- **Solución final**: Configuración específica de la consola de Windows y detección de compatibilidad.


#### Desafío 3: Gestión de Múltiples Jugadores

- **Problema**: Implementar un sistema flexible para diferentes números de jugadores.
- **Evolución**: De un juego para un solo jugador a soporte para hasta 8 jugadores.
- **Solución final**: Vector dinámico de jugadores y lógica adaptativa para determinar ganadores.


## 6. Mejoras Potenciales y Trabajo Futuro

### 6.1 Mejoras Técnicas

#### Sistema de Apuestas

- **Descripción**: Implementar un sistema de apuestas que permita a los jugadores apostar fichas.
- **Beneficios**: Mayor profundidad estratégica y similitud con el juego real.
- **Implementación sugerida**: Añadir un campo `fichas` a la estructura `Jugador` y funciones para gestionar apuestas.


#### Verdadera Compatibilidad Multiplataforma

- **Descripción**: Mejorar la compatibilidad con sistemas Unix/Linux.
- **Beneficios**: Mayor accesibilidad para usuarios de diferentes plataformas.
- **Implementación sugerida**: Refactorizar el código específico de Windows y usar bibliotecas multiplataforma como ncurses.


#### Interfaz Gráfica

- **Descripción**: Evolucionar de una interfaz de consola a una interfaz gráfica.
- **Beneficios**: Experiencia visual mejorada y mayor atractivo para usuarios modernos.
- **Implementación sugerida**: Utilizar una biblioteca como SFML o SDL para crear una interfaz gráfica.


### 6.2 Mejoras de Jugabilidad

#### Modos de Juego Adicionales

- **Descripción**: Implementar variantes del juego o reglas opcionales.
- **Beneficios**: Mayor variedad y rejugabilidad.
- **Implementación sugerida**: Añadir un sistema de configuración para activar/desactivar reglas específicas.


#### Sistema de Puntuación Persistente

- **Descripción**: Mantener un registro de puntuaciones entre partidas.
- **Beneficios**: Añade un elemento competitivo a largo plazo.
- **Implementación sugerida**: Implementar un sistema de guardado/carga de puntuaciones en archivos.


#### Inteligencia Artificial Mejorada

- **Descripción**: Desarrollar estrategias más sofisticadas para la banca.
- **Beneficios**: Mayor desafío y comportamiento más realista.
- **Implementación sugerida**: Implementar algoritmos de toma de decisiones basados en probabilidades y estado del juego.


## 7. Conclusiones

### 7.1 Logros del Proyecto

El desarrollo del juego "Las Siete y Media" ha resultado en una implementación funcional y atractiva que:

- Implementa correctamente las reglas del juego tradicional.
- Proporciona una interfaz visual clara y atractiva en la consola.
- Soporta múltiples jugadores con nombres personalizados.
- Maneja correctamente caracteres especiales y símbolos.
- Está estructurado de forma modular y bien documentado.


### 7.2 Lecciones Aprendidas

Durante el desarrollo se han adquirido valiosas lecciones sobre:

- La importancia de una arquitectura modular para facilitar el mantenimiento.
- Los desafíos específicos de las aplicaciones de consola en diferentes plataformas.
- La necesidad de equilibrar la complejidad del código con la claridad y mantenibilidad.
- La importancia de una documentación clara y completa para facilitar futuras mejoras.


### 7.3 Reflexión Final

El proyecto demuestra cómo un diseño cuidadoso y una implementación incremental pueden resultar en un producto de software de calidad, incluso con las limitaciones inherentes a una aplicación de consola. Las decisiones de diseño tomadas han priorizado la claridad, la usabilidad y la extensibilidad, sentando una base sólida para futuras mejoras y expansiones.

---

## Apéndice: Estructura de Archivos del Proyecto

```plaintext
siete-y-media/
├── main.cpp          # Programa principal y lógica del juego
├── carta.h           # Definición de la estructura Carta
├── carta.cpp         # Implementación de funciones relacionadas con cartas
├── baraja.h          # Definición de la estructura Baraja
├── baraja.cpp        # Implementación de métodos de la baraja
├── jugador.h         # Definición de la estructura Jugador
├── jugador.cpp       # Implementación de métodos del jugador
├── utilidades.h      # Declaración de funciones auxiliares
└── utilidades.cpp    # Implementación de funciones auxiliares
```