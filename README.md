<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Alumno: Ivan Emanuel Fabregat - 112287 - ifabregat@fi.uba.ar

# **Comandos**

- Para compilar:

```bash
gcc -o tp_hash tp_hash.c src/hash.c src/split.c src/csv.c 
```

- Para ejecutar:

```bash
./tp_hash ejemplos/pokedex.csv
```

- Para ejecutar con valgrind:
```bash
valgrind ./tp_hash ejemplos/pokedex.csv
```

<br>

---
#  Funcionamiento

## Estructuras

* **nodo_t**: contiene un `char *` para la clave, un `void *` para el valor y un `struct nodo *` para almacenar la direccion del proximo nodo.
    
* **hash_t**: contiene un `nodo_t **` para el arreglo de punteros a nodos, un `size_t` para la cantidad de elementos del arreglo, un `size_t` para la capacidad del arreglo y `inf (*hash_func)(char *, size_t)` para la funcion de hash.

<div align="center">
<img height="200px" width="700px" src="https://i.ibb.co/1q4Yd9r/estructuras.jpg">
</div>

## Funciones

* **hash_func**: recibe un `char *` con la clave y un `size_t` con la capacidad de la tabla. Mi funcion de hash, va a sumar cada caracter de la clave en su valor ASCII y al final le aplicara la funcion `%` con respecto a la capacidad de tabla. Esto se debe para que el numero que devuelva (indice del arreglo) este dentro del rango de **0** y de **capacidad - 1**.

* **hash_crear**: recibe un `size_t` con la capacidad inicial que el usuario desea para el arreglo, esta debe ser como minimo `3`. Asigna memoria para una estructura `hash_t` e inicializa todo en `0` o `NULL`. Despues asigno memoria para los elementos del arreglo de `nodo_t *` y inicializo los elementos en `NULL`. Asigno la capacidad de `hash` y asigno la funcion mencionada anteriormente. Si no hubo problemas con las asginaciones de memoria, devuelve el puntero a la estructura`hash_t` creado, caso contrario `NULL`.

* **hash_cantidad**: recibe un `hash_t *` con la tabla. Si es `NULL` devuelve `0`, caso contrario el campo `cantidad`.

* **hash_dimensionar**: recibe un `hash_t *` con la tabla y un `size_t` con la nueva capacidad del arreglo (**capacidad * 2**). Se encarga de crear de manera dinamica un nuevo arreglo de `nodo_t *`. Va a recorrer el arreglo viejo y se encargara de aplicar de nuevo la funcion de `hash_func` a cada elemento para poder ser ubicado en el nuevo arreglo. Una vez terminado el copiado de datos, paso a liberar la memoira usada del primer arreglo. Y finalmente reubico el puntero al arreglo nuevo y modifico el campo capacidad.

* **hash_insertar**: recibe un `hash_t *` con la tabla, un `char *` con la clave, un `void *` con el dato y un `void **` para guardar el valor anterior si la clave ya fue ingresada anteriormente (o sea se intento cambiar el valor a esa clave). Lo primero que va a hacer esta funcion va a ser calcular el **factor de carga** con los campos `cantidad / capacidad`  si este resultado da **mayor o igual** a `0.75` va a recurrir a la funcion de `hash_dimensionar`. Una vez hecho esta validacion, la funcion de `hash_func` calculara el indice del arreglo a donde ira el nodo.  Una vez en ese indice se encargara de recorrer los nodos enlazados para comprobar que el par con esa `clave` no haya sido ingresado, si se ingreso se guarda el valor en el `void **` y se actualiza el valor y se devuelve `True`. Si paso esa parte significa que no encontro el nodo. Por ende hay dos opciones, que en ese indice haya `NULL` o que en los nodos enlazados no este esa clave. Por eso asigna memoria para un nuevo `nodo` y para su `clave`. Es importante destacar que en caso en ese indice ya haya unos nodos enlazados, el nuevo nodo sera ingresado en la **primer posicion**. Si todo esto salio bien devuelve `True`, caso contrario `False`.

* **hash_buscar**: recibe un `hash_t *` con la tabla y un `char *` con la clave. Va a llamar a la funcion de hash `hash_func` con la clave pasada para ver en que indice del arreglo esta. Recorrera los nodos enlazados para corroborar si se encuentra o no. Si lo encuentra devuelve el `valor` a esa `clave` pasada por parametro, caso contrario develve `NULL`.

* **hash_contiene**: recibe un `hash_t *` con la tabla y un `char *` con la clave. Devolvera si el valor de retorno de `hash_buscar` es distinto a `NULL`. Ya que se la funcion de buscar verifica si la tabla contiene esa `clave` si esta devuelve `NULL` significa que no encontro nada con esa `clave` por ende la tabla no lo contiene (devuelve `False`), caso contrario contiene un par con esa clave y devolveria algo distinto a `NULL` (devuelve `True`).

* **hash_quitar**: recibe un `hash_t *` con la tabla y un `char *` con la clave. Con la funcion de `hash_func` busca el indice dentro del arreglo donde estaria ese elemento. Recorre los nodos enlazados comparando las claves hasta encontrar ese elemento guardandose el puntero del nodo anterior para poder eliminar. Si el nodo anterior es `NULL` es el primero si no lo es ajusta el puntero del campo `siguiente`. Si lo encuentra se guarda el `valor` para ser retornado, decrementa la `cantidad` y libera memoria, caso contrario devuelve `NULL`.

* **hash_iterar**: recibe un `hash_t *` con la tabla, un `(f*)(char *, void *, void *)` con el puntero a la funcion la cual recibira un `char *` con la clave, un `void *` con el valor y un `void *` con un contexto si el usuario lo desea utilizar y por ultimo un `void *` que se usara como contexto. Se encarga de recorrer cada elemento del arreglo y los nodos enlazados si tiene y aplicara la funcion `f` a cada elemento hasta que esta devuelva `False`. La funcion devolvera la cantidad de veces que fue aplicada la funcion `f`.

* **hash_destruir**: recibe un `hash_t *` con la tabla. Llama a `hash_destruir_todo` pero con la funcion el puntero a la funcion como `NULL`.

* **hash_destruir_todo**: recibe un `hash_t *` con la tabla y `(*destructor)(void *)` con el puntero a la funcion que se aplicara a cada elemento. Va a recorrer el arreglo y cada nodo de los nodos enlazados si este tiene y les aplicara la funcion `destructor` a cada uno guardando la posicion del `nodo_siguiente`. Luego de liberar la memoria de los nodos, libera la del arreglo y siguiente la tabla.

<br>

---

<br>

# Diccionario

## ¿Que es?

Un diccionario es una estructura de datos que almacena pares de `clave-valor` permitiendo agilizar los tiempos a la hora de realizar una busqueda ya que asocia los elementos con una clave que no se puede repetir (siendo esta **unica**). Si se ingresa una clave que ya fue ingresada se debe actualizar el valor para esa clave (*segun esta implementacion*). Existen dos tipos de Hash:


### Hash cerrado (direccionamiento abierto)

Este tipo de hash tiene la peculiaridad que los valores asociados a ese par `clave-valor` es ingresado el `valor` directamente en la posicion de la tabla. Viendo la foto, siendo `Ivan`la clave se le aplica la funcion de hash devolviendo `3` que es el indice de la tabla en donde se insertara. En este tipo de hash si ocurren colisiones (que una *una / varias* claves al aplicarle la funcion de hash devuelvan el mismo numero) se suele solucionar con alguno de estos metodos `Probing lineal o probing cuadratico o hash doble`.

<div align="center">
<img height="200px" width="700px" src="https://i.ibb.co/6HqdjNm/hash-Cerrado.jpg">
</div>

### Hash abierto (direccionamiento cerrado)

Este tipo de hash a diferencia del anterior la tabla contendra punteros a un nodos que contendra el par `clave-valor`. Viendo la foto primero se ingresa el par de clave `abc` al aplicarla la funcion de hash devuelve `0` siendo el indice del arreglo en donde ira la informacion. Despues se inserto el par de clave `fgh` que al aplicarle la funcion de hash vuelve a devolver `0` lo cual vuelve al indice `0`. Por como lo implemente el nuevo elemento siempre ira en la primer posicion de los nodos enlazados (ya que en su interior cada nodo tiene *clave*, *valor* y un **puntero al siguiente nodo**). En este tipo de hash la manera de resolver las colisiones es a traves del metodo `encademiento`.

<div align="center">
<img height="200px" width="700px" src="https://i.ibb.co/1zQb3FB/mi-Func-Hash.jpg">
</div>


## Implementaciones:

Algunas formas de implementar esta estructura son:

1. **Lista simplemente enlazada**: esta implementacion utilizara una estructura como la de **Lista Simplemente Enlazada** donde cada nodo tendra los campos que se ven en la imagen. El orden que tendra esta lista sera a medida que sean ingresados. El primer par `clave-valor` que sea ingresado sera el inicio de la lista y se ira agrandando a media que sean ingresados mas pares.

<div align="center">
<img height="200px" width="500px" src="https://i.ibb.co/TrZPNgs/lista.jpg">
</div>

2. **Arbol Binario de Busqueda**: esta implementacion utilizara una estructura como la del **Arbol Binario de Busqueda** donde cada nodo tendra los campos que se ven en la imagen. El orden que tendra este arbol sera por las claves. El primer par `clave-valor` que se ingrese sera la `raiz` y los siguientes elementos ingresados que tengan una clave *menor* iran a la izquierda y los que tengan *mayor* iran a la derecha.

<div align="center">
<img height="200px" width="500px" src="https://i.ibb.co/t8FJ3nH/abb.jpg">
</div>

3. **Tabla de Hash**: esta implementacion utilizara una funcion de hash, permitiendo mapear cada `clave` ingresada a un indice de un arreglo. La funcion de hash convierte cada clave en un indice unico, pero puede pasar que no, si esto ocurre se llama `colision`. Lo mejor seria que la distribucion de indices sea variada y no se repita (para que no haya colisiones). A continuacion en la foto se ve como la clave `Ivan` se le aplica la `funcion hash` y da `3`. El par `Ivan - Alumno` el valor `Alumno` ira al indice `3` de la tabla. Y asi con las siguientes clves.

<div align="center">
<img height="200px" width="700px" src="https://i.ibb.co/wdc2BcC/tabla-Hash.jpg">
</div>

<br>

# Relacionado a la palabra ***<u>Hash</u>***

## Funcion de Hash

Es una funcion la cual recibe es este caso una clave **string** y a traves de un algoritmo cualquiera genera un numero unico para esa clave. Este numero se lo llama **codigo hash** y va a ser utilizado como indice para la posicion de la tabla donde ira la informacion vinculada a esa clave.

Analicemos mi funcion de hash:
    * Tiene un contador llamado `hash` el cual se inicializa en 0.
    * Recorre la `clave` caracter por caracter hasta el final.
    * Convierte cada caracter a su valor ASCII y lo suma a `hash`.
    * Reduce el rango del indice a devolver entre `0` y `capacidad - 1` usando el operador **%**. Garantizando que este dentro de los limites.

Ahora para mi funcion veamos los siguientes casos con estas claves:

1. `abc`: la suma en **ASCII** es de `97 + 98 + 99` que da `294` y eso le aplicamos `% 3` y nos da 0.
2. `fgh`: la suma en **ASCII** es de `102 + 103 + 104` que da `309` y eso le aplicamos `% 3` y nos da 0.

Distintas claves nos da el mismo `codigo hash` a este problema se lo llama `colision`. Esto seria un problema si ingresamos muchas claves y justo todas al ser **hasheadas** devuelvan 0. Y esto seria un problema porque estariamos perdiendo la optimizacion que conseguimos al hacer un diccionario de este tipo. Porque tendriamos que acceder al arreglo a la posicion que nos de la funcion de hash, lo cual no es problema. Y despues recorrer los nodos enlazados y ahi perdimos toda la optimizacion. Para volver a ganar cierta optimizacion calcule el **factor de carga**. Para que cada vez que se ingrese pares y se llegue a una relacion entre `cantidad` y `capacidad` haga un redimension en la tabla.

<div align="center">
<img height="200px" width="700px" src="https://i.ibb.co/1zQb3FB/mi-Func-Hash.jpg">
</div>

## Tabla de Hash

<div style="display: flex; align-items: center;">
    <img height="200px" width="400px" src="https://i.ibb.co/w7HCNDs/tabla.jpg">
    <span style="margin-left: 10px">Esta es una tablita de hash. En la cual se ven tres columnas la de datos, la de claves y la de hash. En la foto se ve como con la clave "abc" y "fgh" dan el mismo hash en ese caso hay una colision.</span>
</div>

## Resolucion de colisiones

* **Encadenamiento**: este es el metodo que use para resolver las colisiones. A medida que se ingresan pares y al aplicarle la funcion de hash devuelven el mismo indice, estos pares son agregados a la lista de nodos enlazados.

<div align="center">
<img height="200px" width="700px" src="https://i.ibb.co/1zQb3FB/mi-Func-Hash.jpg">
</div>

* **Probing**: este metodo tiene dos variantes `lineal` y `cuadratico` (supongo que debe haber cubico y mas nombres de funciones). Para explicar estos ejemplos deje sin expresar el par `fgh - 3` ya que ocasiona colision con el par `abc - 1`
    
        - Lineal: este metodo se caracteriza por recorrer el arreglo y ver donde esta vacio. En este caso iria al 0, pero no esta vacio, continua. Se fija en la posicion 1, pero no esta vacia, continua. Llega a la posicion 2 y esta vacia, se inserta ahi.


        - Cuadratica: este metodo se calculara la posicion donde se insertara en base a los intentos que hubieron elevados al cuadrado. En este caso se tuvo que insertar en la posicion 0, pero esta ocupada. Ya realice un intento entonces hago 1² = 1. Pruebo en la posicion 1 ahora, esta ocupado. Sumo uno a mis intentos y lo elevo al cuadrado 2² = 4. Prueba en la posicion 4, no hay nada, inserto ahi.

<div align="center">
<img height="200px" width="700px" src="https://i.ibb.co/X2vvp8h/tabla-Hash-Colisiones.jpg">
</div>

* **Hash doble**: este metodo consta de volver a hacer otra funcion de hash a la clave para obtener otro indice.

## Tamaño de la tabla

El ultimo tema es acerca del tamaño de la tabla. Mientras mas chica es la tabla mas posibilidades de colisiones tenemos y por consecuencia en la eficiencia de las operaciones.

* **Hash abierto**: al tener una tabla chica se produciran muchas colisiones las cuales se solucionaran agregando a la lista de nodos enlazados. A lo cual uno dira *solucionado*, pero no porque seria lo mismo que recorrer una lista y eso tiene una complejidad de O(n) cuando si esta bien optimizado el diccionario las operacion tiene una complejidad de O(1). Haciendo una tabla cada vez mas grande va a permitir que los indices que devuelva la funcion de hash entren en otro rango mayor, reduciendo la cantidad de nodos que habia con el mismo `codigo de hash`.

* **Hash cerrado**: al tener una tabla y que en cada indice si y solo si haya una sola clave va a ser peor. Si se logra ampliar la tabla con los metodos de solucion de colisiones va a llegar un momento en el que no van a ser optimos, porque van a ser tanto los intentos para conseguir un indice libre que perdieron la optimizacion que ganaron.

**En conclusion**: el tamaño de la tabla reduce colisiones y optimiza la eficiencia de las operaciones. Esto siempre si el factor de carga y el uso de memoria son y sean los adecuados.

# Diagrama de memoria

*Algo a comentar*: al momento de hacer el diagrama de memoria me di cuenta que el dibujo de las estructuras que hice al principio no estaba bien y por tratar de corregirlo lo hice en Pinta (una variable de paint), pero creo que se entiende la idea.

<div align="center">
<img height="400px" width="700px" src="https://i.ibb.co/gWb3ZWk/memoria.jpg">
</div>