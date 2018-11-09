#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

#define TAM_INICIAL 		30
#define FACTOR_REDIMENSION 	2

/* *****************************************************************
 *                   DEFINICIÓN DE LA ESTRUCTURA
 * *****************************************************************/

struct heap{

	void** vector;
	cmp_func_t funcion_comparar;
	size_t cantidad;
	size_t capacidad;
};


/* *****************************************************************
 *                    PRIMITIVAS DEL HEAP
 * *****************************************************************/


heap_t *heap_crear(cmp_func_t cmp){

	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap)
		return NULL;
	heap->vector = malloc(sizeof(void*) * TAM_INICIAL);
	if(!heap->vector){
		free(heap);
		return NULL;
	}
	heap->cantidad = 0;
	heap->capacidad = TAM_INICIAL;
	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if(destruir_elemento){
		for(size_t i = 0; i < heap->cantidad; i++){
			destruir_elemento(heap->vector[i]);
		}
	}
	free(heap->vector);
	free(heap);
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
	return (heap->cantidad) ? false : true;
}