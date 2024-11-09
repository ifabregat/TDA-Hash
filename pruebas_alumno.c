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

void insertarElementoEnHash()
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

int main()
{
	pa2m_nuevo_grupo("Pruebas de Creación de Hash");
	crearHash();
	printf("\n");
	crearHashConCapacidadMenorA3();
	pa2m_nuevo_grupo("Pruebas de Inserción de Elementos en Hash");
	insertarElementoEnHash();

	return pa2m_mostrar_reporte();
}
