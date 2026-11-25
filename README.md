# Caravana del Desierto

Trabajo práctico grupal en C. Es un juego de consola por turnos en el que tenés que llegar a la salida de un tablero de 30 casillas antes de quedarte sin vidas. El dado determina cuántas casillas te movés y, cuando hay espacio, podés elegir avanzar (`F`) o retroceder (`B`). Los bandidos te persiguen y las casillas pueden darte premios, vidas extra, protección en un oasis o hacerte perder un turno por una tormenta.

El menú permite jugar con un nombre de usuario local y consultar el ranking por dificultad. El tablero se representa con una lista circular doblemente enlazada, los movimientos se gestionan con colas y los usuarios se indexan con un árbol binario de búsqueda.

## Compilar y ejecutar en Windows

El juego usa comandos de Windows (`cls`, `pause` y `timeout`) para controlar la consola. Podés compilarlo con GCC (MinGW) desde Code::Blocks o desde PowerShell.

### Con Code::Blocks

1. Abrí `TpCaravanaDelDesierto/TpCaravanaDelDesierto.cbp` en Code::Blocks con el compilador **GNU GCC Compiler** configurado.
2. Seleccioná el objetivo **Debug** y usá **Build**. El ejecutable queda en `TpCaravanaDelDesierto/bin/Debug/TpCaravanaDelDesierto.exe`.
3. Desde la raíz del repositorio, ejecutá en PowerShell:

   ```powershell
   Set-Location TpCaravanaDelDesierto
   .\bin\Debug\TpCaravanaDelDesierto.exe
   ```

### Con GCC desde PowerShell

Con `gcc` en el `PATH`, ejecutá estos comandos desde la raíz del repositorio:

```powershell
Set-Location TpCaravanaDelDesierto
New-Item -ItemType Directory -Force bin/Debug | Out-Null
gcc -std=c11 -Wall -g main.c bandido.c config.c juego.c partidas.c tablero.c usuarios.c `
    TDAs/ColaDinamica.c TDAs/ListaCircularDoblementeEnlazada.c TDAs/PilaDinamica.c `
    TDAs/arbol.c TDAs/listaSimplementeEnlazada.c TDAs/vector.c `
    -o bin/Debug/TpCaravanaDelDesierto.exe
```

Cuando termine la compilación, ejecutá `.\bin\Debug\TpCaravanaDelDesierto.exe` desde esa misma carpeta. En el menú, elegí `1` para empezar una partida, `2` para ver el ranking o `3` para salir.

## Archivos de datos

El juego lee y escribe con rutas relativas a la **carpeta de trabajo**. Ejecutalo desde `TpCaravanaDelDesierto/`, con permisos de escritura, para que todas las ejecuciones compartan los mismos datos. Si lo abrís desde otra carpeta, va a buscar y generar los archivos ahí.

Un clon limpio puede arrancar sin archivos de datos previos. El programa los maneja así:

| Archivo | Uso |
| --- | --- |
| `configF.txt`, `configI.txt`, `configD.txt`, `configE.txt` | Se crean o sobrescriben en cada arranque con los valores definidos en `config.c`. El juego lee el archivo de la dificultad elegida al iniciar una partida. |
| `caravana.txt` | Se crea o sobrescribe al empezar cada partida. Guarda una vista del tablero inicial y la posición de los bandidos. |
| `usuarios.dat` | Se crea al registrar el primer usuario. Guarda los nombres de usuario y sus contadores de partidas. |
| `idx_usuarios.idx` | Se escribe al registrar un usuario y se lee al arrancar. Si falta pero existe `usuarios.dat`, el juego reconstruye el índice en memoria. |
| `partidas.dat` | Se crea al guardar el resultado de la primera partida. Alimenta el ranking, que arranca vacío. |
