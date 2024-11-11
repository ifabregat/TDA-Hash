#include "pa2m.h"
#include "src/hash.h"

void crearHash()
{
	hash_t *hash = hash_crear(3);
	pa2m_afirmar(hash != NULL, "Puedo crear un hash");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La cantidad de elementos en el hash es 0");
	hash_destruir(hash);
}

void crearHashConCapacidadMenorA3()
{
	hash_t *hash = hash_crear(2);
	pa2m_afirmar(hash != NULL,
		     "Puedo crear un hash con capacidad menor a 3");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La cantidad de elementos en el hash es 0");
	hash_destruir(hash);
}

void insertarUnElemento()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int valor = 1;
	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash, clave, &valor, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	hash_destruir(hash);
}

void insertarVariosElementos()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "clave1";
	int valor1 = 1;
	char *clave2 = "clave2";
	int valor2 = 2;
	char *clave3 = "clave3";
	int valor3 = 3;
	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash, clave1, &valor1, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &encontrado),
		     "Puedo insertar un segundo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, &encontrado),
		     "Puedo insertar un tercer elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos en el hash es 3");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	hash_destruir(hash);
}

void insertoElementosConMismaClave()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int valor = 1;
	int valor2 = 2;
	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash, clave, &valor, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_insertar(hash, clave, &valor2, &encontrado),
		     "Puedo insertar un segundo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == &valor,
		     "Se encontró un elemento previo con la misma clave");
	hash_destruir(hash);
}

void intentoColision1()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "clave1";
	int valor1 = 1;
	char *clave2 = "clave2";
	int valor2 = 2;
	char *clave3 = "clave3";
	int valor3 = 3;
	void *encontrado = NULL;

	pa2m_afirmar(hash_insertar(hash, clave1, &valor1, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &encontrado),
		     "Puedo insertar un segundo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2");
	pa2m_afirmar(encontrado == NULL, "Se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, &encontrado),
		     "Puedo insertar un tercer elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos en el hash es 3");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	hash_destruir(hash);
}

void intentoColision2()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "abc";
	int valor1 = 1;
	char *clave2 = "fgh";
	int valor2 = 2;
	void *encontrado = NULL;

	pa2m_afirmar(hash_insertar(hash, clave1, &valor1, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &encontrado),
		     "Puedo insertar un segundo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	hash_destruir(hash);
}

void intentoColision3()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "abc";
	int valor1 = 1;
	char *clave2 = "fgh";
	int valor2 = 2;
	char *clave3 = "def";
	int valor3 = 3;
	char *clave4 = "ijk";
	int valor4 = 4;
	char *clave5 = "klm";
	char *clave6 = "pqr";
	int valor6 = 6;
	char *clave7 = "mno";
	int valor7 = 7;
	char *clave8 = "opq";
	int valor8 = 8;
	void *encontrado = NULL;

	pa2m_afirmar(hash_insertar(hash, clave1, &valor1, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &encontrado),
		     "Puedo insertar un segundo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, &encontrado),
		     "Puedo insertar un tercer elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos en el hash es 3");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave4, &valor4, &encontrado),
		     "Puedo insertar un cuarto elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "La cantidad de elementos en el hash es 4");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave5, NULL, &encontrado),
		     "Puedo insertar un quinto elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 5,
		     "La cantidad de elementos en el hash es 5");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave6, &valor6, &encontrado),
		     "Puedo insertar un sexto elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 6,
		     "La cantidad de elementos en el hash es 6");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave7, &valor7, &encontrado),
		     "Puedo insertar un séptimo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 7,
		     "La cantidad de elementos en el hash es 7");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave8, &valor8, &encontrado),
		     "Puedo insertar un octavo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 8,
		     "La cantidad de elementos en el hash es 8");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	hash_destruir(hash);
}

void busquedaDeUnElementoValido()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int valor = 1;
	char *clave2 = "clave2";
	int valor2 = 2;
	char *clave3 = "clave3";
	int valor3 = 3;
	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash, clave, &valor, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &encontrado),
		     "Puedo insertar un segundo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, &encontrado),
		     "Puedo insertar un tercer elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos en el hash es 3");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_buscar(hash, clave2) == &valor2,
		     "Puedo buscar un elemento en el hash");
	hash_destruir(hash);
}

void buscarUnElementoNoIngresado()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int valor = 1;
	char *clave2 = "clave2";
	int valor2 = 2;
	char *clave3 = "clave3";
	int valor3 = 3;
	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash, clave, &valor, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &encontrado),
		     "Puedo insertar un segundo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, &encontrado),
		     "Puedo insertar un tercer elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos en el hash es 3");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_buscar(hash, "clave4") == NULL,
		     "No puedo buscar un elemento que no está en el hash");
	hash_destruir(hash);
}

void buscarUnElementoNulo()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int valor = 1;
	char *clave2 = "clave2";
	int valor2 = 2;
	char *clave3 = "clave3";
	int valor3 = 3;
	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash, clave, &valor, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &encontrado),
		     "Puedo insertar un segundo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, &encontrado),
		     "Puedo insertar un tercer elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos en el hash es 3");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");
	pa2m_afirmar(hash_buscar(hash, NULL) == NULL,
		     "No puedo buscar un elemento que no está en el hash");
	hash_destruir(hash);
}

void buscarUnElementoConIndiceIgual()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "abc";
	int valor1 = 1;
	char *clave2 = "fgh";
	int valor2 = 2;
	void *encontrado = NULL;

	pa2m_afirmar(hash_insertar(hash, clave1, &valor1, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &encontrado),
		     "Puedo insertar un segundo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_buscar(hash, clave2) == &valor2,
		     "Puedo buscar un elemento en el hash");

	hash_destruir(hash);
}

void buscarOtroElementoConIndicesIguales()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "abc";
	int valor1 = 1;
	char *clave2 = "fgh";
	int valor2 = 2;
	char *clave3 = "def";
	int valor3 = 3;
	char *clave4 = "ijk";
	int valor4 = 4;
	char *clave5 = "klm";
	char *clave6 = "pqr";
	int valor6 = 6;
	char *clave7 = "mno";
	int valor7 = 7;
	char *clave8 = "opq";
	int valor8 = 8;
	void *encontrado = NULL;

	pa2m_afirmar(hash_insertar(hash, clave1, &valor1, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &encontrado),
		     "Puedo insertar un segundo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, &encontrado),
		     "Puedo insertar un tercer elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos en el hash es 3");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave4, &valor4, &encontrado),
		     "Puedo insertar un cuarto elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "La cantidad de elementos en el hash es 4");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave5, NULL, &encontrado),
		     "Puedo insertar un quinto elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 5,
		     "La cantidad de elementos en el hash es 5");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave6, &valor6, &encontrado),
		     "Puedo insertar un sexto elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 6,
		     "La cantidad de elementos en el hash es 6");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave7, &valor7, &encontrado),
		     "Puedo insertar un séptimo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 7,
		     "La cantidad de elementos en el hash es 7");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave8, &valor8, &encontrado),
		     "Puedo insertar un octavo elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 8,
		     "La cantidad de elementos en el hash es 8");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_buscar(hash, clave6) == &valor6,
		     "Puedo buscar un elemento en el hash");

	hash_destruir(hash);
}

void iterarUnHashNulo()
{
	hash_t *hash = NULL;
	pa2m_afirmar(hash_iterar(hash, NULL, NULL) == 0,
		     "No puedo iterar un hash nulo");
}

void iterarUnHashConCeroElementos()
{
	hash_t *hash = hash_crear(3);
	pa2m_afirmar(hash_iterar(hash, NULL, NULL) == 0,
		     "No puedo iterar un hash con 0 elementos");
	hash_destruir(hash);
}

bool imprimirElementos(char *clave, void *valor, void *ctx)
{
	return true;
}

void iterarUnHashConVariosElementos()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "clave1";
	int valor1 = 1;
	char *clave2 = "clave2";
	int valor2 = 2;
	char *clave3 = "clave3";
	int valor3 = 3;
	char *clave4 = "clave4";
	int valor4 = 4;
	char *clave5 = "clave5";
	int valor5 = 5;
	char *clave6 = "clave6";
	int valor6 = 6;
	void *encontrado = NULL;

	pa2m_afirmar(hash_insertar(hash, clave1, &valor1, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos en el hash es 3");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave4, &valor4, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 4,

		     "La cantidad de elementos en el hash es 4");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave5, &valor5, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 5,
		     "La cantidad de elementos en el hash es 5");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave6, &valor6, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 6,
		     "La cantidad de elementos en el hash es 6");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	size_t cantidad = hash_iterar(hash, imprimirElementos, NULL);
	printf("Cantidad: %ld\n", cantidad);
	pa2m_afirmar(cantidad == 6,
		     "Puedo iterar un hash con varios elementos");

	hash_destruir(hash);
}

bool cortarcon3Iteraciones(char *clave, void *valor, void *ctx)
{
	int *contador = ctx;
	(*contador)++;

	if (*contador == 3)
		return false;

	return true;
}

void iterar3Elementosde6()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "clave1";
	int valor1 = 1;
	char *clave2 = "clave2";
	int valor2 = 2;
	char *clave3 = "clave3";
	int valor3 = 3;
	char *clave4 = "clave4";
	int valor4 = 4;
	char *clave5 = "clave5";
	int valor5 = 5;
	char *clave6 = "clave6";
	int valor6 = 6;
	void *encontrado = NULL;

	pa2m_afirmar(hash_insertar(hash, clave1, &valor1, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos en el hash es 3");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave4, &valor4, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "La cantidad de elementos en el hash es 4");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave5, &valor5, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 5,
		     "La cantidad de elementos en el hash es 5");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	pa2m_afirmar(hash_insertar(hash, clave6, &valor6, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 6,
		     "La cantidad de elementos en el hash es 6");
	pa2m_afirmar(encontrado == NULL, "No se encontró un elemento previo");

	size_t contador = 0;

	size_t cantidad = hash_iterar(hash, cortarcon3Iteraciones, &contador);
	printf("Cantidad: %ld\n", cantidad);

	pa2m_afirmar(
		cantidad == 3,
		"Puedo iterar un hash con varios elementos y cortar la iteración");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de Creación de Hash");
	crearHash();
	printf("\n");
	crearHashConCapacidadMenorA3();
	pa2m_nuevo_grupo("Pruebas de Inserción de Elementos en Hash");
	insertarUnElemento();
	printf("\n");
	insertarVariosElementos();
	printf("\n");
	insertoElementosConMismaClave();
	pa2m_nuevo_grupo("Pruebas de Colisiones en Hash");
	intentoColision1();
	printf("\n");
	intentoColision2();
	printf("\n");
	intentoColision3();
	pa2m_nuevo_grupo("Pruebas de busqueda de elementos en Hash");
	busquedaDeUnElementoValido();
	printf("\n");
	buscarUnElementoNulo();
	printf("\n");
	buscarUnElementoNoIngresado();
	printf("\n");
	buscarUnElementoConIndiceIgual();
	printf("\n");
	buscarOtroElementoConIndicesIguales();
	pa2m_nuevo_grupo("Pruebas de iteracion de elementos en Hash");
	iterarUnHashNulo();
	printf("\n");
	iterarUnHashConCeroElementos();
	printf("\n");
	iterarUnHashConVariosElementos();
	printf("\n");
	iterar3Elementosde6();

	return pa2m_mostrar_reporte();
}
