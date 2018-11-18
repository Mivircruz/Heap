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

void swap(void** a, void** b){

	void* aux = *b;
	*b = *a;
	*a = aux;
}

void downheap(void* arreglo[], size_t pos_padre, size_t pos_hijo_izq, size_t pos_hijo_der, cmp_func_t cmp, size_t tam){

	if(pos_hijo_der > tam || pos_hijo_izq > tam)
		return;

	size_t pos_hijo_a_cambiar;

	if(arreglo[pos_hijo_der] && arreglo[pos_hijo_izq]){

		if(cmp(arreglo[pos_padre], arreglo[pos_hijo_izq]) < 0 ||  cmp(arreglo[pos_padre], arreglo[pos_hijo_der]) < 0){
			pos_hijo_a_cambiar = (cmp(arreglo[pos_hijo_izq], arreglo[pos_hijo_der]) < 0) ? pos_hijo_der : pos_hijo_izq;
			
				
			
		}
	}
	else{
		pos_hijo_a_cambiar = (arreglo[pos_hijo_izq] && !arreglo[pos_hijo_der]) ? pos_hijo_izq : pos_hijo_der;
		if(cmp(arreglo[pos_padre], arreglo[pos_hijo_a_cambiar]) > 0)
			return;
	}
	swap(&(arreglo[pos_padre]), &(arreglo[pos_hijo_a_cambiar]));
	pos_padre = pos_hijo_a_cambiar;
	
	return downheap(arreglo, pos_padre, pos_padre*2 + 1, pos_padre*2 + 2, cmp, tam);

}

void upheap(void* arreglo[], size_t pos_hijo, cmp_func_t cmp){

	size_t pos_padre = (pos_hijo-1)/2;

	while(cmp(arreglo[pos_padre], arreglo[pos_hijo]) < 0)
		swap(&(arreglo[pos_padre]), &(arreglo[pos_hijo]));
}

void heapify(void* arreglo[], size_t n, cmp_func_t cmp){

	for(int i = (int)(n/2 - 1); 0 <= i; i--)
		downheap(arreglo, i, i*2+1, i*2+2, cmp, n);
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
	heap->funcion_comparar = cmp;
	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){

	if(destruir_elemento){
		for(size_t i = 0; i < heap->cantidad; i++)
			destruir_elemento(heap->vector[i]);
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
		void** aux = realloc(heap->vector, sizeof(void*) * heap->capacidad * FACTOR_REDIMENSION);
		if(!aux)
			return false;
		heap->vector = aux;
		heap->capacidad = heap->capacidad * FACTOR_REDIMENSION;
	}
	heap->vector[heap->cantidad] = elem;
	upheap(heap->vector, heap->cantidad, heap->funcion_comparar);
	heap->cantidad++;
	return true;

}

void *heap_desencolar(heap_t *heap){

	if(heap_esta_vacio(heap))
		return NULL;

	void* a_devolver = heap->vector[0];
	swap(&(heap->vector[0]), &(heap->vector[heap->cantidad-1]));
	heap->cantidad--;
	downheap(heap->vector, 0, 1, 2,  heap->funcion_comparar, heap->cantidad);
	return a_devolver;
}


void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos, cant, cmp);
	size_t ultimo_relativo = cant;
	for(size_t i = 0; i < cant-1; i++){
		swap(&(elementos[0]), &(elementos[ultimo_relativo]));
		downheap(elementos, 0, 1, 2, cmp, cant);
	}
}