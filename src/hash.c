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
	if (hash == NULL)
		return 0;

	return hash->cantidad;
}

void hash_dimensionar(hash_t *hash, size_t nueva_capacidad)
{
	nodo_t **tabla_nueva = calloc(nueva_capacidad, sizeof(nodo_t *));

	if (tabla_nueva == NULL)
		return;

	for (size_t i = 0; i < hash->capacidad; i++) {
		nodo_t *nodo = hash->tabla[i];

		while (nodo != NULL) {
			size_t indice = (size_t)hash->hash_func(
				nodo->clave, nueva_capacidad);

			nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));

			if (nuevo_nodo == NULL)
				return;

			nuevo_nodo->clave =
				calloc(strlen(nodo->clave) + 1, sizeof(char));

			if (nuevo_nodo->clave == NULL) {
				free(nuevo_nodo);
				return;
			}

			strcpy(nuevo_nodo->clave, nodo->clave);

			nuevo_nodo->valor = nodo->valor;
			nuevo_nodo->siguiente = tabla_nueva[indice];
			tabla_nueva[indice] = nuevo_nodo;

			nodo = nodo->siguiente;
		}
	}

	for (size_t i = 0; i < hash->capacidad; i++) {
		nodo_t *nodo = hash->tabla[i];

		while (nodo != NULL) {
			nodo_t *temp = nodo;
			nodo = nodo->siguiente;

			free(temp->clave);
			free(temp);
		}
	}

	free(hash->tabla);

	hash->tabla = tabla_nueva;
	hash->capacidad = nueva_capacidad;

	return;
}

bool hash_insertar(hash_t *hash, char *clave, void *valor, void **encontrado)
{
	if (hash == NULL || clave == NULL)
		return false;

	if ((float)hash->cantidad / (float)hash->capacidad >= 0.75)
		hash_dimensionar(hash, hash->capacidad * 2);

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

	if (encontrado)
		*encontrado = NULL;

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

	return true;
}

void *hash_buscar(hash_t *hash, char *clave)
{
	if (hash == NULL || clave == NULL)
		return NULL;

	size_t indice = (size_t)hash->hash_func(clave, hash->capacidad);

	nodo_t *nodo = hash->tabla[indice];

	while (nodo != NULL) {
		if (strcmp(nodo->clave, clave) == 0)
			return nodo->valor;

		nodo = nodo->siguiente;
	}

	return NULL;
}

bool hash_contiene(hash_t *hash, char *clave)
{
	return hash_buscar(hash, clave) != NULL;
}

void *hash_quitar(hash_t *hash, char *clave)
{
	if (hash == NULL || clave == NULL)
		return NULL;

	size_t indice = (size_t)hash->hash_func(clave, hash->capacidad);

	nodo_t *nodo = hash->tabla[indice];
	nodo_t *nodo_anterior = NULL;

	while (nodo != NULL) {
		if (strcmp(nodo->clave, clave) == 0) {
			if (nodo_anterior == NULL)
				hash->tabla[indice] = nodo->siguiente;
			else
				nodo_anterior->siguiente = nodo->siguiente;

			void *valor = nodo->valor;
			free(nodo->clave);
			free(nodo);

			hash->cantidad--;

			return valor;
		}

		nodo_anterior = nodo;
		nodo = nodo->siguiente;
	}

	return NULL;
}

size_t hash_iterar(hash_t *hash, bool (*f)(char *, void *, void *), void *ctx)
{
	if (hash == NULL || f == NULL)
		return 0;

	size_t cantidad = 0;

	for (size_t i = 0; i < hash->capacidad; i++) {
		nodo_t *nodo = hash->tabla[i];

		while (nodo != NULL) {
			if (f != NULL && !f(nodo->clave, nodo->valor, ctx))
				return cantidad + 1;

			cantidad++;
			nodo = nodo->siguiente;
		}
	}

	return cantidad;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (hash == NULL)
		return;

	for (size_t i = 0; i < hash->capacidad; i++) {
		nodo_t *nodo = hash->tabla[i];

		while (nodo != NULL) {
			nodo_t *nodo_siguiente = nodo->siguiente;

			if (destructor)
				destructor(nodo->valor);

			free(nodo->clave);
			free(nodo);

			nodo = nodo_siguiente;
		}
	}

	free(hash->tabla);
	free(hash);
}