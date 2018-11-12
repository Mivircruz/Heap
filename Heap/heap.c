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
 *                   	FUNCIONES AUXILIARES
 * *****************************************************************/

void swap(void* a, void* b){
	void* aux = b;
	b = a;
	a = aux;
}

void downheap(void* arreglo, size_t pos_padre, cmp_func_t cmp){

	pos_hijo_izq = pos_padre*2 + 1;
	pos_hijo_der = pos_padre*2 + 2;

	while(cmp(arreglo[pos_padre], arreglo[pos_hijo_izq]) < 0 || cmp(arreglo[pos_padre], arreglo[pos_hijo_der]) < 0){
		if(cmp(arreglo[pos_hijo_izq], arreglo[pos_hijo_der]) < 0){
			swap(arreglo[pos_padre], arreglo[pos_hijo_der]);
			pos_padre = pos_hijo_der;
		}
		else{
			swap(arreglo[pos_padre], pos_hijo_izq);
			pos_padre = pos_hijo_der;
		}
		pos_hijo_izq = pos_padre*2 + 1;
		pos_hijo_der = pos_padre*2 + 2;
	}

}

void upheap(void* arreglo, size_t pos_hijo, cmp_func_t cmp){

	pos_padre = (pos_hijo-1)/2;

	while(cmp(arreglo[pos_padre], arreglo[pos_hijo]) < 0)
		swap(arreglo[pos_padre], arreglo[pos_hijo]);
}

void heapify(void* arreglo[], size_t n, cmp_func_t cmp){

	for(size_t i = n/2 - 1; 0 < i; i--)
		downheap(arreglo, i, cmp);
}

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

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){

	heap_t* heap = heap_crear(cmp);
	if(!heap)
		return NULL;

	heapify(arreglo, n, cmp);
	free(heap->vector);
	heap->vector = arreglo;
	heap->cantidad = n;
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



void *heap_ver_max(const heap_t *heap){
	if(heap_esta_vacio(heap))
		return NULL;

	return *(heap->vector);
}

bool heap_encolar(heap_t *heap, void *elem){

	if(heap->cantidad == heap->capacidad){
		void** aux = realloc(sizeof(void*) * heap->capacidad * FACTOR_REDIMENSION);
		if(!aux)
			return false;
		heap->vector = aux;
		heap->capacidad = heap->capacidad * FACTOR_REDIMENSION;
	}
	heap->vector[heap->cantidad] = elem;
	upheap(heap->vector, heap->cantidad, heap->cmp);
	heap->cantidad++;
	return true;

}

void *heap_desencolar(heap_t *heap){

	if(heap_esta_vacio(heap))
		return NULL;

	swap(heap->vector[heap->cantidad-1], heap->vector[0]);
	heap->cantidad--;
	downheap(heap->vector, 0, heap->cmp);
	return 	heap->vector[heap->cantidad];;
}


void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos, cantidad, cmp);
	size_t ultimo_relativo = cant;
	for(size_t i = 0; i < cant-1; i++){
		swap(elementos[0], elementos[ultimo_relativo]);
		downheap(elementos, 0, cmp);
	}
}