# TPII-Estructuras-Autoreferenciadas.

__EJERCICIO 35:__

<p align ="justify">
Hacer un programa que tome los datos de contacto de una persona (Nombre, Apellido, edad, teléfono, mail) y los cargue, en forma directa, en una pila de memoria dinámica. Imprimir en pantalla y cargar en un archivo llamado "contactos.dat", de organización secuencial, los registros ingresados por el usuario si la persona tiene una edad mayor a 21 años.
</p>

__EJERCICIO 38:__

<p align ="justify">
Hacer una cola con los valores muestreados de un cuarto de ciclo de una señal sinusoidal, en 8 bits, para luego recorrerla y recomponer la señal completa. Las muestras deberán ir de 127 a -127 utilizando el bit más significativo en 1 para los valores negativos y en 0 para los valores positivos. Imprimir en pantalla los valores.
</p>

__EJERCICIO 36:__

<p align ="justify">
Hacer un programa que lea al archivo "contactos.dat" creado en el __Ejercicio 35__ y crear una lista, en memoria dinámica, ordenada alfabéticamente. Una vez creada la lista guardarla en un archivo de organización directa llamado "contactos_ordenados.dat" imprimiendola en pantalla.
  </p>

El código del ejercicio 36 NO está terminado.

__EJERCICIO 39:__

<p align ="justify">
Hacer un programa que tome los datos de medición de potencia, cargados por el usuario, de un sistema de medición a distancia.

Los datos que cargará el usuario tienen la siguiente estructura:

```c
char desc[60];
unsigned char potencia;
unsigned int estado;

```
Donde estado es la multiplicación del valor ASCII de la primer letra de la descripción por la potencia. Los datos cargados se deberán guardar en una lista ordenada, de mayor a menor, del valor de potencia. Una vez finalizada la carga guardar los datos en un archivo de organización directa llamado "potencia.dat" imprimiendo en pantalla los datos.
</p>

__EJERCICIO 40:__

<p align ="justify">
Utilizando el archivo “potencia.dat” creado en el Ejercicio 39, realizar una función que pase como parámetro, entre otros datos, la clave del registro (id).</p>
<p align ="justify">
La función ubicará el registro correspondiente al id pasado como parámetro, y utilizando punteros imprimirá la primera palabra del campo "desc" en forma inversa, además cambiará el estado del bit 3 para luego actualizar el archivo. Además, se agregará a una pila la potencia cuando los bits 0 y 2, del campo estado, estén encendidos, en caso contrario se agregará el registro al archivo “salida.dat” de organización secuencial.
</p>

__EJERCICIO 37__:

   Existe un archivo llamado "datos.dat", de tipo binario, cuya organización es secuencial. Los datos están organizados según la siguiente estructura:   

   ```c
   struct d{                                                                                            
   long clave; //Clave o Id del registro

   char d[30]; // Descripcion                                                                                          
   unsigned char tipo; //Tipo de datos como entero sin signo                                                                                                                                            
   char b; //'A':Alta 'B':Baja                                                                                                                                                                          
   }
   ```
<p align ="justify">
   Se Pide:
   Realizar una función que pase como parámetro la clave, entre otros parámetros, y apile dos valores, la Clave y su posición física respecto
   al archivo (registro 1, 2, etc), si es que el campo tipo tiene el bit 4 con valor 1. En caso de no encontrarlo mostrar por pantalla "Registro no encontrado".
   La función debe devolver el puntero de pila.
   Realizar el main con varias llamadas a dicha función y proceder a mostrar las descripciones del archivo, mediante la pila como acceso directo. _NO USAR VARIABLES GLOBALES__
</p>

El código del ejercicio 37 NO está terminado.
