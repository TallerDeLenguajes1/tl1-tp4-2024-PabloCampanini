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

// DECLARACION DE LAS FUNCIONES
Nodo *crearListaVacia();
void esListaVacia(Nodo *Lista);
Nodo *crearNuevoNodo(Tarea pendiente, int ID, char *Buff);
// void cargarNodoComienzoLista(Nodo **Lista, Tarea pendiente, int ID, char *Buff);
void cargarNodoFinLista(Nodo **Lista, Tarea pendiente, int ID, char *Buff);
int seguirCargando(char pregunta);
void cargarDatosDeUsuario(Nodo **Lista, Tarea pendiente);
void mostrarListaPendientes(Nodo *Lista);


int main()
{
    srand(time(NULL));

    // DEFINICION DE VARIABLES
    Nodo *tareasPendientes = crearListaVacia(); // Creo una lista de tareas pendientes vacia
    Nodo *tareasRealizadas = crearListaVacia(); // Creo una lista de tareas cumplidas
    Tarea pendiente;
    esListaVacia(tareasPendientes); // Verifico que la lista se creo correctamente
    cargarDatosDeUsuario(&tareasPendientes, pendiente); // Carga todas las tareas que quiera el usuario
    mostrarListaPendientes(tareasPendientes);   // Muestra la lista de tareas pendientes

    return 0;
}

// DEFINICION DE LAS FUNCIONES
Nodo *crearListaVacia()
{
    return NULL;
}

void esListaVacia(Nodo *Lista)
{
    if (Lista == NULL)
    {
        printf("No hay tareas pendientes\n");
    }
    else
    {
        printf("Aun hay tareas por realizar\n");
    }
}

Nodo *crearNuevoNodo(Tarea pendiente, int ID, char *Buff)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo)); // Nodo auxiliar
    nuevo->T.TareaID = ID;                      // Cargo el ID de la Tarea Pendiente

    nuevo->T.Descripcion = (char *)malloc((strlen(Buff) + 1) * sizeof(char)); // Reserva de memoria con Buff
    strcpy(nuevo->T.Descripcion, Buff);                                       // Copio contenido del Buff en descripcion

    nuevo->T.Duracion = 10 + rand() % 91; // Aleatorio entre 10 - 100

    nuevo->Siguiente = NULL; // Asigno a NULL de manera temporal

    return nuevo;
}

// void cargarNodoComienzoLista(Nodo **Lista, Tarea pendiente, int ID, char *Buff)
// {
//     Nodo *nuevo = crearNuevoNodo(pendiente, ID, Buff);
//     nuevo->Siguiente = *Lista;
//     *Lista = nuevo;
// }

void cargarNodoFinLista(Nodo **Lista, Tarea pendiente, int ID, char *Buff)
{
    Nodo *nuevo = crearNuevoNodo(pendiente, ID, Buff);
    if (*Lista == NULL)
    {
        *Lista = nuevo;
    }
    else
    {
        Nodo *aux = *Lista;

        while (aux->Siguiente)
        {
            aux = aux->Siguiente;
        }

        aux->Siguiente = nuevo;
    }
}

int seguirCargando(char pregunta)
{
    if ((pregunta == 'S') || (pregunta == 's'))
    {
        return 0; // Retorna 0 para no salir del cargado
    }

    return 1; // Retorna 1 para salir del cargado
}

void cargarDatosDeUsuario(Nodo **Lista, Tarea pendiente)
{
    // VARIABLES AUXILIARES
    int salir = 0; // Salir 0 = NO y 1 = SI
    char pregunta;
    char *Buff = (char *)malloc(10000 * sizeof(char)); // Almacenamiento temporal de descripcion

    int ID = 1000;

    printf("Lista de pendientes: \n");

    while (salir == 0)
    {
        printf("\tTarea a realizar : ");
        gets(Buff); // Cargado descripcion por consola

        // cargarNodoComienzoLista(Lista, pendiente, ID, Buff);
        cargarNodoFinLista(Lista, pendiente, ID, Buff);

        printf("¿Quiere cargar otra tarea a la lista?\n\t\tIngrese S para si o N para no: ");
        scanf("%c", &pregunta);

        fflush(stdin);

        ID = ID + 1; // Autoincremento del ID iniciado en 1000 para el primer elemento de la lista

        salir = seguirCargando(pregunta); // 0 = NO, 1 = SI
    }

    free(Buff);
}

void mostrarListaPendientes(Nodo *Lista)
{
    Nodo *mostrar;
    Nodo *Aux = Lista;
    printf("Lista de pendientes:\n\n");

    while (!(Aux == NULL))
    {
        printf("Tarea %d:\n", ((Aux->T.TareaID) - 999));
        printf("\tPendiente:");
        puts(Aux->T.Descripcion);
        printf("\n");
        printf("\tDuracion: %d\n", Aux->T.Duracion);

        mostrar = Aux;
        Aux = Aux->Siguiente;
    }
}
