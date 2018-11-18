#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.


/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/

int comparar_enteros(const void* a, const void* b){

	int numero1 = *(int*)a;
	int numero2 = *(int*)b;
	if(numero1 < numero2)
		return -1;
	else if(numero1 > numero2)
		return 1;
	return 0;
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_heap_vacio(){

	printf("\n PRUEBAS CREAR HEAP VACÍO\n");

    heap_t* heap = heap_crear(NULL);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap obtener clave A, es NULL, no existe", !heap_desencolar(heap));
    print_test("Prueba heap pertenece clave A, es false, no existe", heap_esta_vacio(heap));
    print_test("Prueba heap borrar clave A, es NULL, no existe", !heap_ver_max(heap));

    heap_destruir(heap, NULL);
}

static void prueba_crear_heap_con_arreglo(){

	printf("\n PRUEBAS CREAR HEAP CON ARREGLO\n");

	int* numeros = malloc(sizeof(int*) * 7);
	for(int i = 0; i < 7; i++)
		numeros[i] = i;

	void** vector = malloc(sizeof(void*) * 7);
	for(size_t i = 0; i < 7; i++)
		vector[i] = &numeros[i];

    heap_t* heap = heap_crear_arr(vector, 7, comparar_enteros);

    print_test("Prueba heap crear heap con arreglo", heap);
    print_test("Prueba heap la cantidad de elementos es 7", heap_cantidad(heap) == 7);
    print_test("El máximo es el elemento correcto", *(int*)heap_ver_max(heap) == 6);
    print_test("Prueba heap desencolar máximo es el máximo del vector", *(int*)heap_desencolar(heap) == 6);
   	print_test("Prueba heap está vacío es falso", !heap_esta_vacio(heap));
	print_test("Prueba heap desencolar nuevo máximo", *(int*)heap_desencolar(heap) == 5);
	print_test("Prueba heap cantidad es la correcta", heap_cantidad(heap) == 5);

    heap_destruir(heap, NULL);
    free(numeros);
}

static void prueba_heap_insertar(){

	printf("\nINSERTAR COSAS EN HEAP\n");

    heap_t* heap = heap_crear(comparar_enteros);

    int clave1 = 1;
    int clave2 = 2;
    int clave3 = 3;
    int clave4 = 4;
    int clave5 = 5;
    int clave7 = 7;
    int clave8 = 8;
    int clave9 = 9;

    /* Inserta los valores en desorden*/
    print_test("Prueba heap insertar clave1", heap_encolar(heap, &clave1));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap insertar clave7", heap_encolar(heap, &clave7));
    print_test("Prueba heap insertar clave2", heap_encolar(heap, &clave2));
    print_test("Prueba heap insertar clave4", heap_encolar(heap, &clave4));
    print_test("Prueba heap insertar clave9", heap_encolar(heap, &clave9));
    print_test("Prueba heap insertar clave8", heap_encolar(heap, &clave8));
    print_test("Prueba heap insertar clave3", heap_encolar(heap, &clave3));
    print_test("Prueba heap insertar clave5", heap_encolar(heap, &clave5));
    print_test("Prueba heap la cantidad de elementos es 8", heap_cantidad(heap) == 8);

    print_test("Prueba heap desencolar es clave9", *(int*)heap_desencolar(heap) == clave9);
    print_test("Prueba heap la cantidad de elementos es 7", heap_cantidad(heap) == 7);
    print_test("Prueba heap desencolar es clave8", *(int*)heap_desencolar(heap) == clave8);
    print_test("Prueba heap desencolar es clave7", *(int*)heap_desencolar(heap) == clave7);
    print_test("Prueba heap está vacío es falso", !heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
}

void pruebas_heap_alumno(void){
	prueba_crear_heap_vacio();
	prueba_crear_heap_con_arreglo();
	prueba_heap_insertar();
}