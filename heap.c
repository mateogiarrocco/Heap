#define _GNU_SOURCE
#include "heap.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#define TAM_INICIAL 8
#define TAM_REDIMENSION 2
#define REDIMENSION_MIN 4


/* *****************************************************************
 *                DEFINICION Y PRIMITIVAS DEL HEAP
 * *****************************************************************/

typedef struct heap heap_t{
	void** datos;
	size_t cant;
    size_t tam;
    cmp_func_t comparar;
};


heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	heap->datos = malloc(sizeof(void*));
	heap->cant = 0;
	heap->tam = TAM_INICIAL;
	heap->comparar = cmp;
	return heap;
}


heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	heap->datos = malloc(sizeof(void*) * n);
	for(int i = 0; i < n; i++){
		heap->datos[i] = arreglo[i];
	}
	heap->cant = 0;
	heap->tam = 0;
	heap->cmp = cmp;
	return heap;
}

//Redimensiona el tamaño del heap
bool heap_redimensionar(heap_t* heap, size_t tam_nuevo){
	void **nuevo = realloc(heap->datos, tam_nuevo * sizeof(void *));
	if(!nuevo) return false;
	heap->datos = nuevo;
	heap->tam = tam_nuevo;
	return true;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){

}


void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){

}


size_t heap_cantidad(const heap_t *heap){
	return heap->cant;
}


bool heap_esta_vacio(const heap_t *heap){
	if(!heap) return false;
	return heap->cant == 0;
}

size_t buscar_pos_padre(size_t pos_elemento){
	return (pos_elemento - 1) / 2;
}

size_t buscar_pos_hijo_izq(size_t pos_elemento){
	return (pos_elemento * 2) + 1;
}

size_t buscar_pos_hijo_der(size_t pos_elemento){
	return (pos_elemento * 2) + 2;
}

bool heap_encolar(heap_t *heap, void *elem){
	if(!heap || !elem) return false;
	if(heap->cant == heap->tam){
		if(!heap_redimensionar(heap, TAM_REDIMENSION * heap->tam)) return false;
	}
	heap->datos[heap->cant] = elem;
	heap->cant++;
	if(!prop_heap(heap, (heap->cant - 1))) upheap(heap, (heap->cant - 1), heap->comparar);
	return true;
}

void *heap_ver_max(const heap_t *heap){
	if(heap_esta_vacio(heap)) return NULL;
	return heap->datos[0];
}

void *heap_desencolar(heap_t *heap){
	if(heap_esta_vacio(heap)) return NULL;
	void *valor = heap->datos[0];
	heap->datos[0] = heap->datos[heap->cant];
	downheap(heap, heap->comparar);
	heap->cant--;
	return valor;
}

//Devuelve true si el elemento cumple la prioridad de heap.
//Devuelve false en caso contrario
bool prop_heap(const heap_t* heap, size_t posicion){
	if(heap_esta_vacio(heap)) return false;
	if(heap->cant == 1) return true;
	size_t padre = buscar_pos_padre(posicion);
	if(heap->comparar(heap->datos[posicion], heap->datos[padre]) > 0) return false;
	return true;
}

//Función recursiva que realiza el swap
void _upheap(heap_t* heap, size_t pos_padre, size_t pos_swap, size_t pos_otro_hijo, cmp_func_t cmp){
	if(prop_heap(heap, pos_swap)) return;
	void* dato_ref = NULL;
	size_t pos_ref = 0;
	dato_ref = heap->datos[pos_padre];
	heap->datos[pos_padre] = heap->datos[pos_swap];
	heap->datos[pos_swap] = datos_ref;
	pos_ref = pos_padre;
	pos_padre = pos_swap;
	pos_swap = pos_ref;
	if(!prop_heap(heap, pos_otro_hijo)) _upheap(heap, pos_padre, pos_otro_hijo, pos_swap, cmp);
	_upheap(heap, pos_padre(pos_padre), pos_padre, NULL, cmp);
}


void upheap(heap_t* heap, size_t pos_hijo, cmp_func_t cmp){
	if(!heap) return;
	size_t padre = buscar_pos_padre(pos_hijo);
	if(pos_hijo == buscar_pos_hijo_izq(padre)){
		size_t hijo_der = buscar_pos_hijo_der(padre);
		_upheap(heap, padre, pos_hijo, hijo_der, cmp);
	}else if(pos_hijo == buscar_pos_hijo_der(padre)){
		size_t hijo_izq = buscar_pos_hijo_izq(padre);
		_upheap(heap, padre, pos_hijo, hijo_izq, cmp);
	}
}

size_t calculo_maximo(heap_t* heap, cmp_func_t cmp, size_t pos_padre, size_t hijo_izq, size_t hijo_der){
	//hijo izq mayor que hijo der
	if(heap->comparar(hijo_izq, hijo_der) > 0){
		//hijo izq mayor que padre
		if(heap->comparar(hijo_izq, pos_padre) > 0){
			return hijo_izq;
		}else{
			return pos_padre;
		}
	}else{
		if(heap->comparar(hijo_der, pos_padre) > 0){
			return hijo_der;
		}else{
			return pos_padre;
		}
	}
}

//Función recursiva que realiza el swap
void _downheap(heap_t* heap, size_t tamaño, size_t pos_padre, cmp_func_t cmp){
	if(heap->datos[pos_padre] == heap_ver_max(heap)) return;
	void* dato_ref = NULL;
	size_t pos_ref = 0;
	size_t hijo_izq = buscar_pos_hijo_izq(pos_padre);
	size_t hijo_der = buscar_pos_hijo_der(pos_padre);
	size_t max = calculo_maximo(heap, cmp, pos_padre, hijo_izq, hijo_der);
	if(max != pos_padre){
		dato_ref = heap->datos[pos_padre];
		pos_ref = pos_padre;
		heap->datos[pos_padre] = heap->datos[max];
		//pos_padre = max;
		heap->datos[max] = dato_ref;
		//max = pos_ref;
		_downheap(heap, tamaño, max, cmp);
	}
}

void downheap(heap_t* heap, cmp_func_t cmp){
	if(!heap) return;
	size_t pos_padre = heap_ver_max(heap);
	_downheap(heap, heap->cant, pos_padre, cmp);
}