## Integrantes
- José Luis Villalobos Jiménez
- Elías Emanuel Paz Raymondi


## Modo de ejecución
Tener CMake instalado para la compilación del proyecto.
Ejecutar en la terminal
```shell
cmake -B build
```
para crear la carpeta de build, y luego 
```
cmake --build build
```
para compilar el ejecutable.

Finalmente, para ejecutar el programa simplemente se usa
```shell
./build/Tarea3
```
En caso de abrir el proyecto en CLion, simplemente darle al botón de Play luego de crear la carpeta de `build/`.

## Como usar el programa
Por defecto en main ya hay comandos usados, pero en la consola de comandos están disponibles los siguientes comandos:
| Comando   | Argumentos | Resultado                                                          |
|-----------|------------|--------------------------------------------------------------------|
| heal      | n          | Aumenta en n la vida de la entidad                                 |
| move      | x y        | Establece la posición de la entidad a (x,y)                        |
| lvlsum    | n          | Aumenta en n el nivel                                              |
| energsum  | n          | Aumenta en n la energía. Tiene un límite de uso de 5 veces         |
| status    | Ninguno    | Muestra todos los datos de la entidad                              |
| resource  | nombre     | Agrega el nombre del recurso al conjunto de recursos de la entidad |
| statchng  | nombre     | Modifica el estado de la entidad a nombre                          |
| papear    | Ninguno    | Reduce en 99999 la vida de la entidad                              |
| posx/posy | n          | Cambian individualmente las coordenadas x o y.                     |

También se pueden usar las siguientes macros:
| Macro           | Secuencia                  | Resultado                                                        |
|-----------------|----------------------------|------------------------------------------------------------------|
| fullheal        | lvlsum,heal,posx,posy      | Sube de nivel, cura y la entidad escapa al hogar (x=y=0).        |
| buff_and_status | energsum,statchng,resource | Mejoras de energía, estado y otorga una poción.                  |
| bumbumpatapir   | heal, noexiste,papear      | Macro para testeo, falla en el segundo comando porque no existe. |

Además, estan los comandos especiales `history`, para ver el registro de comandos y `exit` o `quit` para terminar la ejecución del programa.