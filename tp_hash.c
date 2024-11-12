#include "src/hash.h"
#include "src/csv.h"
#include "src/split.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
} pokemon_t;

bool parsear_entero(const char *campo, void *ctx)
{
	int *numero = ctx;

	if (campo == NULL || numero == NULL)
		return false;

	return sscanf(campo, "%d", numero) == 1;
}

bool parsear_nombre(const char *campo, void *ctx)
{
	if (campo == NULL || ctx == NULL)
		return false;

	char **nombre = ctx;

	if (*nombre != NULL) {
		free(*nombre);
	}

	size_t longitud = strlen(campo);

	if (longitud == 0) {
		return false;
	}

	*nombre = malloc(longitud + 1);

	if (*nombre == NULL) {
		return false;
	}

	strcpy(*nombre, campo);

	return true;
}

bool parsear_tipo(const char *campo, void *ctx)
{
	char *tipo = ctx;

	if (campo == NULL || strlen(campo) != 1)
		return false;

	*tipo = campo[0];

	return true;
}

struct archivo_csv *abrir_archivo(const char *ruta)
{
	struct archivo_csv *archivo = abrir_archivo_csv(ruta, ';');

	if (archivo == NULL) {
		printf("No se pudo abrir el archivo %s\n", ruta);
		return NULL;
	}

	return archivo;
}

pokemon_t *crear_pokemon(char *nombre, char tipo, int fuerza, int destreza,
			 int resistencia)
{
	pokemon_t *pokemon = malloc(sizeof(pokemon_t));

	if (pokemon == NULL) {
		printf("No se pudo reservar memoria\n");
		return NULL;
	}

	pokemon->nombre = malloc(strlen(nombre) + 1);

	if (pokemon->nombre == NULL) {
		printf("No se pudo reservar memoria\n");
		free(pokemon);
		return NULL;
	}

	strcpy(pokemon->nombre, nombre);

	pokemon->tipo = tipo;
	pokemon->fuerza = fuerza;
	pokemon->destreza = destreza;
	pokemon->resistencia = resistencia;

	return pokemon;
}

void agregar_pokemon(struct archivo_csv *archivo, hash_t *hash)
{
	bool (*funciones[])(const char *,
			    void *) = { parsear_nombre, parsear_tipo,
					parsear_entero, parsear_entero,
					parsear_entero };

	char *nombre = malloc(100);

	if (nombre == NULL) {
		printf("No se pudo reservar memoria\n");
		return;
	}

	char tipo;
	int fuerza, destreza, resistencia;

	void *ctx[] = { &nombre, &tipo, &fuerza, &destreza, &resistencia };

	while (leer_linea_csv(archivo, 5, funciones, ctx) == 5) {
		pokemon_t *pokemon = crear_pokemon(nombre, tipo, fuerza,
						   destreza, resistencia);

		if (pokemon == NULL) {
			printf("No se pudo crear el pokemon\n");
			free(nombre);
			cerrar_archivo_csv(archivo);
			hash_destruir(hash);
			return;
		}

		if (!hash_insertar(hash, pokemon->nombre, pokemon, NULL)) {
			printf("No se pudo insertar el pokemon %s\n",
			       pokemon->nombre);
			free(pokemon->nombre);
			free(pokemon);
		}
	}

	free(nombre);
}

void destructor_pokemon(void *elemento)
{
	pokemon_t *pokemon = elemento;

	free(pokemon->nombre);
	free(pokemon);
}

bool imprimir_pokemon(char *clave, void *valor, void *extra)
{
	pokemon_t *pokemon = valor;

	printf("Nombre: %s, Tipo: %c, Fuerza: %d, Destreza: %d, Resistencia: %d\n",
	       pokemon->nombre, pokemon->tipo, pokemon->fuerza,
	       pokemon->destreza, pokemon->resistencia);

	return true;
}

void interaccion(struct archivo_csv *archivo, hash_t *hash)
{
	char opcion = 0;

	printf("Ingrese una opción: ");
	printf("M (Para mostrar todos los pokemones) o B (Para buscar un pokemon): ");

	if (scanf(" %c", &opcion) != 1) {
		cerrar_archivo_csv(archivo);
		hash_destruir(hash);
		return;
	}

	if (opcion == 'M' || opcion == 'm') {
		printf("\n");
		hash_iterar(hash, imprimir_pokemon, NULL);
		printf("\n");
	} else if (opcion == 'B' || opcion == 'b') {
		char nombre[100];

		printf("Ingrese el nombre del pokemon ");

		if (scanf(" %99[^\n]", nombre) != 1) {
			cerrar_archivo_csv(archivo);
			hash_destruir(hash);
			return;
		}

		printf("\n");

		pokemon_t *pokemon = hash_buscar(hash, nombre);

		if (pokemon == NULL) {
			printf("No se encontró el pokemon %s\n", nombre);
			printf("\n");
		} else {
			printf("Pokemon encontrado!!!\n");
			printf("Nombre: %s, Tipo: %c, Fuerza: %d, Destreza: %d, Resistencia: %d\n",
			       pokemon->nombre, pokemon->tipo, pokemon->fuerza,
			       pokemon->destreza, pokemon->resistencia);
			printf("\n");
		}
	} else {
		printf("Opción inválida\n");
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Uso: %s archivo.csv\n", argv[0]);
		return 1;
	}

	struct archivo_csv *archivo = abrir_archivo(argv[1]);

	hash_t *pokemones = hash_crear(10);

	if (pokemones == NULL) {
		fprintf(stderr, "No se pudo crear el hash\n");
		cerrar_archivo_csv(archivo);
		return 1;
	}

	agregar_pokemon(archivo, pokemones);

	interaccion(archivo, pokemones);

	hash_destruir_todo(pokemones, destructor_pokemon);

	cerrar_archivo_csv(archivo);

	return 0;
}