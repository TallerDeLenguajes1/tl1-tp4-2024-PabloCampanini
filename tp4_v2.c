// 1) Desarrolle una interfaz de carga de tareas para solicitar tareas pendientes, en la cual se
// solicite descripción y duración de la misma (el id debe ser generado automáticamente por
// el sistema, de manera autoincremental comenzando desde el número 1000). Al cabo de
// cada tarea consulte al usuario si desea ingresar una nueva tarea o finalizar la carga.

// 2) Implemente una interfaz para elegir qué tareas de la lista de pendientes deben ser
// transferidas a la lista de tareas realizadas.

// 3) Implemente una funcionalidad que permita listar todas las tareas pendientes y realizadas.

// 4) Implemente una funcionalidad que permita consultar tareas por id o palabra clave y
// mostrarlas por pantalla, indicando si corresponde a una tarea pendiente o realizada.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea
{
    int TareaID; // Numerico autoincremental comenzando en 100
    char *Descripcion;
    int Duracion; // Entre 10 - 100
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

//Declaracion de funciones
Nodo * crearListaVacia();
Nodo * crearNodo(Tarea pendientes);
void cargarListaPrincipio(Nodo * Lista);
void cargarListaFinal(Nodo * Lista);
void cargarDatosUsuario(Nodo * Lista, Tarea pendientes);



int main(){
    srand(time(NULL));

    Nodo * TareasPendientes = crearListaVacia();
    Nodo * TareasRealizadas = crearListaVacia();
    Tarea pendientes;
    

    return 0;
}

//Definiciones de funciones
Nodo * crearListaVacia(){
    return NULL;
}

Nodo *crearNodo(Tarea pendientes)
{
    Nodo * nuevo = (Nodo *)malloc()
    return ;
}
