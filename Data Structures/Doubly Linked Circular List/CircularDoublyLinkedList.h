#include<stdio.h>
#include<stdlib.h>


typedef struct Nodo{
    int valor;
    struct Nodo *siguiente;
    struct Nodo *anterior;
}Nodo; 

typedef struct Lista{
    int size;
    Nodo *inicio;
}Lista;

//Fincion para crear la lista circular doblemente enlazada
Lista crearLista(){
    Lista lista;
    lista.inicio = NULL;
    lista.size = 0;
    return lista;
}

//Funcion para verficar si la lista esta vacia
int listaVacia(Lista *lista){
    int state = lista->inicio == NULL ? 1 : 0;
    return state;
}

//Funcion para recorrer la lista circular doblemente enlazada
void recorrerLista(Lista *lista){
    int var = 0;
    Nodo *temporal = lista->inicio;
    do{
        printf("El elemento actual es: %d \n", temporal->valor);
        printf("Mostrar anterior presione [1]\n");
        printf("Salir presione [2]\n");
        scanf("%d", &var);
        temporal = temporal->anterior;
    }while(var != 2);
}

//Funcion para imprimir la lista 
void printLista(Lista *lista){
    int size = lista->size;
    if(listaVacia(lista)){
        printf("La lista esta vacia\n");
        return;
    }else{
        printf("Elementos de la lista\n");
        Nodo *actual = lista->inicio; 
        while(size != 0){ //Recorremos la lista
            printf("%d\n", actual->valor);
            actual = actual->siguiente; //Avanzamos al siguiente nodo
            size--; //Decrementamos el tamaño de la lista
        }
    }
}

void primerNodo(Lista *lista, int valor){
    Nodo *nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->valor = valor;
    nodo->siguiente = nodo;
    nodo->anterior = nodo;
    lista->inicio = nodo; //Anterior y siguiente apuntan al mismo nodo ya que no se tienen NULL
}

//Funcion para insertar un elemento al final de la lista
void insertarFinal(Lista *lista, int valor){ 
    if(listaVacia(lista)){
        primerNodo(lista, valor);
    }else{
        Nodo *nuevoNodo, *temporal;
        nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
        nuevoNodo->valor = valor;
        nuevoNodo->siguiente = lista->inicio;
        nuevoNodo->anterior = lista->inicio->anterior;
        lista->inicio->anterior = nuevoNodo;
        temporal = lista->inicio;
        while(temporal->siguiente != lista->inicio){
            temporal = temporal->siguiente;
        }
        temporal->siguiente = nuevoNodo;
    }
    lista->size++; //Incrementamos el tamaño de la lista
}

//Funcion para insertar un elemento al inicio de la lista
void insertarInicio(Lista *lista, int valor){
    if(listaVacia(lista)){
        primerNodo(lista, valor);
    }else{
        Nodo *nuevoNodo, *temporal;
        nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
        nuevoNodo->valor = valor;
        nuevoNodo->siguiente = lista->inicio;
        nuevoNodo->anterior = lista->inicio->anterior;
        lista->inicio->anterior = nuevoNodo;
        temporal = lista->inicio;
        while(temporal->siguiente != lista->inicio){
            temporal = temporal->siguiente;
        }
        temporal->siguiente = nuevoNodo;
        lista->inicio = nuevoNodo; //El inicio de la lista apunta al nuevo nodo
    }
    lista->size++; //Incrementamos el tamaño de la lista
}

//Funcion para insertar un elemento en medio de la lista
void insertarMedio(Lista *lista, int valor){ 
    if(listaVacia(lista))
        primerNodo(lista, valor);
    else{
        int length = lista->size / 2;
        Nodo *nuevoNodo, *temporal;
        temporal = lista->inicio;
        nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
        for (int i = 0; i < length-1; i++)
            temporal = temporal->siguiente;
        nuevoNodo->valor = valor;
        nuevoNodo->siguiente = temporal->siguiente;
        nuevoNodo->anterior = temporal->anterior;
        temporal->siguiente = nuevoNodo;
    }
    lista->size++; //Incrementamos el tamaño de la lista
}




//Funcion para borrar el primer elemento de la lista
void borrarElemento(Lista *lista, int posicion){
    if(lista->inicio == NULL){
        printf("La lista esta vacia\n");
        return;
    }else{
        Nodo *temporal = lista->inicio;
        posicion = posicion % lista->size;
        for(int i = 0; i < posicion-1; ++i){
            temporal = temporal->siguiente;
        }
            temporal->anterior->siguiente = temporal->siguiente;
            temporal->siguiente->anterior = temporal->anterior;
            free(temporal);
            lista->size--;
    }
}


//Funcion para borrar el ultimo elemento de la lista
void borrarValor(Lista *lista, int cantidad){
    if(lista->inicio == NULL){
        printf("La lista esta vacia\n");
        return;
    }else{
        Nodo *temporal = lista->inicio;
        while(temporal->siguiente != lista->inicio && temporal->valor != cantidad){
            temporal = temporal->siguiente;
        }
        if (temporal->valor == cantidad){
            temporal->anterior->siguiente = temporal->siguiente;
            temporal->siguiente->anterior = temporal->anterior;
            free(temporal);
            lista->size--;
        }
        else
            return;
    }
    
}

//Funcion para duplicar la lista (Extra)
void duplicarLista(Lista *lista){
    int var = 0;
    Nodo *temporal = lista->inicio;
    do{
        printf("El elemento actual es: %d \n", temporal->valor);
        printf("Mostrar anterior presione [1]\n");
        printf("Salir presione [2]\n");
        scanf("%d", &var);
        temporal->valor *= 2;
        temporal = temporal->anterior;
    }while(var != 2);
}

//Funcion para agregar multiples elementos a la lista
void agregarMulti(Lista *lista, int index, int num){
    int pos = index % lista -> size; 
    Nodo* temp = lista -> inicio;

    if (temp) {
        int i;

        for (i = 0; i < pos; ++i)
            temp = temp -> siguiente;

        for (i = 0; i < num; ++i) {
            int valor;
            printf("Ingrese el valor del elemento: ");
            scanf("%d", &valor);

            // Añadir nodo
            Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo*));

            if (nuevo == NULL) {
                printf("No hay memoria\n");
                return;
            }

            nuevo -> anterior = temp;
            nuevo -> siguiente = temp -> siguiente;
            temp -> siguiente = nuevo;
            temp = nuevo;

            lista -> size++;
        }
    } else {
        printf("Error: lista vacía\n");
    }
}


//Funcion que arroja el tamaño de la lista
int sizeLista(Lista *lista){
    return lista->size;
}

//Funcion que eleva los elementos de la lista al cuadrado (Extra)
void listaCuadrado(Lista *lista){
    Nodo *temporal = lista->inicio;
    do{
        temporal->valor *= temporal->valor;
        temporal = temporal->siguiente;
    }while(temporal != lista->inicio);
}

//Funcion para borrar toda la lista 
void borrarLista(Lista *lista){
    if(listaVacia(lista)){
        printf("La lista esta vacia\n");
        return;
    }else{
        Nodo *temporal = lista->inicio;
        while(temporal->siguiente != lista->inicio){
            temporal = temporal->siguiente;
            free(temporal->anterior);
        }
        free(temporal);
        lista->inicio = NULL;
    }
}

void borrarMulti(Lista *lista, int x) {
    Nodo* current = lista -> inicio;
    int i;
    
    for (i = 0; i < lista -> size; ++i){
        if (current -> valor == x) {
            Nodo* temp = current;
            current = current -> siguiente;

            temp -> anterior -> siguiente = temp -> siguiente;
            temp -> siguiente -> anterior = temp -> anterior;
            free(temp);
            lista -> size--;

            
        } else {
            current = current -> siguiente;
        } 
    }
}

int buscarValor(Lista* lista, int x) {
    Nodo* current = lista -> inicio;
    int i;

    for (i = 0; i < lista -> size; ++i){
        if (current -> valor == x)
            return i;
        
        current = current -> siguiente;
    }

    return -1;
}
