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
	intentoColision1();
	printf("\n");
	intentoColision2();
	printf("\n");
	intentoColision3();

	return pa2m_mostrar_reporte();
}
