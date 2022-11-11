#include<stdio.h>
#include"CircularDoublyLinkedList.h"

int main(){
    Lista miLista = crearLista();
    insertarFinal(&miLista, 1);
    insertarFinal(&miLista, 2);
    insertarFinal(&miLista, 3);
    insertarFinal(&miLista, 4);
    printLista(&miLista);
    printf("El tamano de la lista es: %d\n", sizeLista(&miLista));
    printf("La lista al cuadrado es: \n");
    listaCuadrado(&miLista);
    printLista(&miLista);

    //HEMOS VUELTOOOOOOOOOO
    return 0;
}
