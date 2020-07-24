#include "heap.h"
#include <stdbool.h>
#include <stdio.h>
#include "testing.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

heap_t* pruebas_crear_heap(){
    heap_t* heap = heap_crear(cmp);
    print_test("El heap fue creado", true);
    return heap;
}

void pruebas_heap_destruir(heap_t* heap){
    heap_destruir(heap, NULL);
    print_test("El heap fue destruido", true);
}

void pruebas_heap_vacio(heap_t* heap){
    print_test("El heap está vacío", heap_esta_vacio(heap));
    print_test("El heap tiene 0 elementos", heap_cantidad(heap) == 0);
    print_test("Ver el máximo es inválido", heap_ver_max(heap));
    print_test("Desencolar es inválido", !heap_desencolar(heap));
}

void pruebas_encolar_null(heap_t* heap){
    pruebas_heap_vacio(heap);
    print_test("Encolar elemento NULL es inválido", !heap_encolar(heap, NULL));
    print_test("El heap sigue vacío", heap_esta_vacio(heap));
    pruebas_heap_destruir(heap);
}

void pruebas_encolar_y_destruir(heap_t* heap){
    pruebas_heap_vacio(heap);
    void** arreglo = malloc(sizeof(void*) * 5);
    puts("Encolo 6 elementos");
    for (int i = 0; i < 6; i++){
        arreglo[i] = &i;
        print_test("Encolo elemento", heap_encolar(heap, arreglo[i]));
    }
    print_test("Hay 6 elementos en el heap", heap_cantidad(heap) == 6);
    print_test("El heap NO está vacío", !heap_esta_vacio(heap));
    print_test("El máximo es último en haber entrado", heap_ver_max(heap) == arreglo[6]);
    heap_destruir(heap, free);
    print_test("El heap fue destruido", true);
}

//Probar volver a encolar después de desencolar todo el heap
void pruebas_encolar_y_desencolar(heap_t* heap){
    //pruebas_encolar_y_destruir(heap);
    pruebas_heap_vacio(heap);
    int *elem1 = NULL, *elem2 = NULL, *elem3 = NULL, *elem4 = NULL, *elem5 = NULL;
    *elem1 = 1, *elem2 = 2, *elem3 = 3, *elem4 = 4, *elem5 = 5;
    print_test("Encolo elemento 1", heap_encolar(heap, elem1));
    print_test("El heap NO está vacío", !heap_esta_vacio(heap));
    print_test("El máximo es el elemento1", heap_ver_max(heap) == elem1);
    print_test("Encolo elemento 2", heap_encolar(heap, elem2));
    print_test("El máximo es el elemento2", heap_ver_max(heap) == elem2);
    print_test("Encolo elemento 3", heap_encolar(heap, elem3));
    print_test("El máximo es el elemento3", heap_ver_max(heap) == elem3);
    print_test("Encolo elemento 4", heap_encolar(heap, elem4));
    print_test("El máximo es el elemento4", heap_ver_max(heap) == elem4);
    print_test("Encolo elemento 5", heap_encolar(heap, elem5));
    print_test("El máximo es el elemento5", heap_ver_max(heap) == elem5);
    print_test("La cantidad de elementos es 5", heap_cantidad(heap) == 5);
    //Desencolo
    print_test("Desencolo el elemento 5", heap_desencolar(heap) == elem5);
    print_test("Desencolo el elemento 4", heap_desencolar(heap) == elem4);
    print_test("Desencolo el elemento 3", heap_desencolar(heap) == elem3);
    print_test("Desencolo el elemento 2", heap_desencolar(heap) == elem2);
    print_test("Desencolo el elemento 1", heap_desencolar(heap) == elem1);
    pruebas_heap_vacio(heap);
    int* encolar1 = NULL, *encolar2 = NULL, *encolar3 = NULL;
    *encolar1 = 1, *encolar2 = 2, *encolar3 = 3;
    //Pruebo volver a encolar
    print_test("Puedo volver a encolar después de vaciar el heap", heap_encolar(heap, encolar1));
    print_test("El heap NO está vacío", heap_esta_vacio(heap));
    print_test("Puedo seguir encolando", heap_encolar(heap, encolar2));
    print_test("Encolo elemento", heap_encolar(heap, encolar3));
    print_test("El maximo elemento es el último en haber sido encolado", heap_ver_max(heap) == encolar3);
    pruebas_heap_destruir(heap);
}

void pruebas_heap_volumen(heap_t* heap){
    pruebas_heap_vacio(heap);
    void** arreglo = malloc(sizeof(void*) * 1000);
    puts("Encolo 1000 elementos");
    for (int i = 0; i < 1000; i++){
        arreglo[i] = &i;
        heap_encolar(heap, arreglo[i]);
    }
    print_test("El heap NO está vacío", !heap_esta_vacio(heap));
    print_test("El heap tiene 1000 elementos", heap_cantidad(heap) == 1000);
    print_test("El maximo elemento es el último en haber sido encolado", heap_ver_max(heap) == arreglo[999]);
    for(int i = 999; i >= 0; i++){
        print_test("Desencolo el elemento correcto, cumpliendo con propiedad de heap e invariante cola", arreglo[i] == heap_desencolar(heap));
    }
    pruebas_heap_vacio(heap);
    pruebas_heap_destruir(heap);
}

void pruebas_heap_alumno(){
    heap_t* heap_vacio = pruebas_crear_heap();
    pruebas_heap_vacio(heap_vacio);
    pruebas_heap_destruir(heap_vacio);
    /*heap_t* heap_null = pruebas_crear_heap();
    pruebas_encolar_null(heap_null);
    heap_t* heap_encolar_destruir = pruebas_crear_heap();
    pruebas_encolar_y_destruir(heap_encolar_destruir);
    heap_t* heap_encolar_desencolar = pruebas_crear_heap();
    pruebas_encolar_y_desencolar(heap_encolar_desencolar);
    heap_t* heap_volumen = pruebas_crear_heap();
    pruebas_heap_volumen(heap_volumen);*/
    //Faltan pruebas de heapsort
    //Falta probar crear heap con el otro constructor
}

int main(){
    pruebas_heap_alumno();
    return 0;
}