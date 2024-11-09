#include "hash.h"
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
	char *clave;
	void *valor;
	struct nodo *siguiente;
} nodo_t;

struct hash {
	nodo_t **tabla;
	size_t cantidad;
	size_t capacidad;
	int (*hash_func)(char *, size_t);
};

int hash_func(char *clave, size_t capacidad)
{
	size_t hash = 0;

	for (size_t i = 0; clave[i] != '\0'; i++)
		hash += (size_t)clave[i];

	return (int)(hash % capacidad);
}

hash_t *hash_crear(size_t capacidad_inicial)
{
	if (capacidad_inicial < 3)
		capacidad_inicial = 3;

	hash_t *hash = calloc(1, sizeof(hash_t));

	if (hash == NULL)
		return NULL;

	hash->tabla = calloc(capacidad_inicial, sizeof(nodo_t *));

	if (hash->tabla == NULL) {
		free(hash);
		return NULL;
	}

	hash->capacidad = capacidad_inicial;
	hash->hash_func = hash_func;

	return hash;
}

size_t hash_cantidad(hash_t *hash)
{
	return hash->cantidad;
}

bool hash_insertar(hash_t *hash, char *clave, void *valor, void **encontrado)
{
	if (hash == NULL || clave == NULL)
		return false;

	int indice = hash->hash_func(clave, hash->capacidad);

	nodo_t *nodo = hash->tabla[indice];

	while (nodo != NULL) {
		if (strcmp(nodo->clave, clave) == 0) {
			if (encontrado)
				*encontrado = nodo->valor;

			nodo->valor = valor;
			return true;
		}
		nodo = nodo->siguiente;
	}

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));

	if (nuevo_nodo == NULL)
		return false;

	nuevo_nodo->clave = calloc(strlen(clave) + 1, sizeof(char));

	if (nuevo_nodo->clave == NULL) {
		free(nuevo_nodo);
		return false;
	}

	strcpy(nuevo_nodo->clave, clave);

	nuevo_nodo->valor = valor;
	nuevo_nodo->siguiente = hash->tabla[indice];
	hash->tabla[indice] = nuevo_nodo;

	hash->cantidad++;

	if (!encontrado)
		*encontrado = NULL;

	return true;
}

void hash_destruir(hash_t *hash)
{
	for (size_t i = 0; i < hash->capacidad; i++) {
		nodo_t *nodo = hash->tabla[i];

		while (nodo != NULL) {
			nodo_t *nodo_aux = nodo->siguiente;
			free(nodo->clave);
			free(nodo);
			nodo = nodo_aux;
		}
	}

	free(hash->tabla);
	free(hash);
}