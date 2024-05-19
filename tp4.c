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

// Declaracion de funciones
Nodo *crearListaVacia();
Nodo *crearNodo(Tarea pendientes);
void cargarListaPrincipio(Nodo **Lista, Tarea pendientes);
void cargarListaFinal(Nodo **Lista, Tarea pendientes);
int preguntaSeguir(char seguir);
void cargarDatosUsuario(Nodo **Lista);
void mostrarTarea(Nodo *Lista);
void moverFinal(Nodo **Lista, Nodo *nuevo);
void cambiarListaId(Nodo **ListaPendientes, Nodo **ListaRealizadas, int ID);
void moverListaUsuario(Nodo **ListaPendientes, Nodo **ListaRealizadas);

int main()
{
    srand(time(NULL));

    Nodo *TareasPendientes = crearListaVacia();
    Nodo *TareasRealizadas = crearListaVacia();

    cargarDatosUsuario(&TareasPendientes);

    printf("\n*---------- Lista de Tareas Pendientes ----------*\n");
    mostrarTarea(TareasPendientes);

    moverListaUsuario(&TareasPendientes, &TareasRealizadas);

    printf("\n*---------- Lista de Tareas Pendientes ----------*\n");
    mostrarTarea(TareasPendientes);

    printf("\n*---------- Lista de Tareas Realizadas ----------*\n");
    mostrarTarea(TareasRealizadas);

    return 0;
}

// Definiciones de funciones
Nodo *crearListaVacia()
{
    return NULL;
}

Nodo *crearNodo(Tarea pendientes)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->T.TareaID = pendientes.TareaID;
    nuevo->T.Descripcion = (char *)malloc((strlen(pendientes.Descripcion) + 1) * sizeof(char));
    strcpy(nuevo->T.Descripcion, pendientes.Descripcion);
    nuevo->T.Duracion = pendientes.Duracion;
    nuevo->Siguiente = NULL;
    return nuevo;
}

void cargarListaPrincipio(Nodo **Lista, Tarea pendientes)
{
    Nodo *nuevo = crearNodo(pendientes);

    nuevo->Siguiente = *Lista;
    *Lista = nuevo;
}

void cargarListaFinal(Nodo **Lista, Tarea pendientes)
{
    Nodo *nuevo = crearNodo(pendientes);
    if (*Lista == NULL)
    {
        *Lista = nuevo;
    }
    else
    {
        Nodo *nodoAux = *Lista;
        while (nodoAux->Siguiente)
        {
            nodoAux = nodoAux->Siguiente;
        }

        nodoAux->Siguiente = nuevo;
    }
}

int preguntaSeguir(char seguir)
{
    char cargar = 0; // 0 no sigue cargando, 1 sigue cargando

    if ((seguir == 's') || (seguir == 'S'))
    {
        cargar = 1;
    }

    return cargar;
}

void cargarDatosUsuario(Nodo **Lista)
{
    Tarea aux;
    int cargar = 1; // 0 no carga mas, 1 sigue cargando
    char *Buff = (char *)malloc(1000 * sizeof(char));
    int ID = 999;
    char seguir;

    printf("\n*---------- Ingrese las tareas a realizar ----------*\n");

    while (cargar == 1)
    {
        aux.TareaID = ID + 1;
        ID++;

        printf("\nDescripcion de la tarea: ");
        gets(Buff);

        aux.Descripcion = (char *)malloc((strlen(Buff) + 1) * sizeof(char));
        strcpy(aux.Descripcion, Buff);

        printf("Ingrese el tiempo en el que debe realizar la tarea: ");
        scanf("%d", &aux.Duracion);
        fflush(stdin);

        cargarListaFinal(Lista, aux);

        printf("Ingresar una nueva tarea (S/N): ");
        scanf("%c", &seguir);
        fflush(stdin);

        cargar = preguntaSeguir(seguir);
    }
}

void mostrarTarea(Nodo *Lista)
{
    Nodo *aux = Lista;

    if (aux == NULL)
    {
        printf("\t*------ No hay tareas en esta categoria ------*");
    }
    else
    {
        while (aux)
        {
            printf("\nTarea %d:\n", (aux->T.TareaID - 999));
            printf("\tDescripcion: ");
            puts(aux->T.Descripcion);
            printf("\tDuracion: %d\n", aux->T.Duracion);

            aux = aux->Siguiente;
        }
    }
}

void moverFinal(Nodo **Lista, Nodo *nuevo)
{
    if (*Lista == NULL)
    {
        *Lista = nuevo;
    }
    else
    {
        Nodo *Aux = *Lista;
        while (Aux->Siguiente)
        {
            Aux = Aux->Siguiente;
        }

        Aux->Siguiente = nuevo;
    }
}

void cambiarListaId(Nodo **ListaPendientes, Nodo **ListaRealizadas, int ID)
{
    if (*ListaPendientes == NULL)
    {
        printf("\n*---------- No hay tareas por realizar ----------*\n");
    }
    else
    {
        Nodo *aux = *ListaPendientes;
        Nodo *auxPrevio = NULL;
        
        while (aux && aux->T.TareaID != ID)
        {
            auxPrevio = aux;
            aux = aux->Siguiente;
        }

        if (aux == NULL)
        {
            printf("\n*---------- El numero de tarea cargado no existe ----------*\n");
        }
        else
        {
            if (auxPrevio == NULL)
            {
                *ListaPendientes = aux->Siguiente;
                aux->Siguiente = NULL;

                moverFinal(ListaRealizadas, aux);
            }
            else
            {
                auxPrevio->Siguiente = aux->Siguiente;
                aux->Siguiente = NULL;

                moverFinal(ListaRealizadas, aux);
            }
        }
    }
}





void moverListaUsuario(Nodo **ListaPendientes, Nodo **ListaRealizadas)
{
    int cargar = 0; // 0 no carga, 1 si carga
    char seguir;
    int ID;

    printf("\n\nMarcar tareas como realizadas (S/N): ");
    scanf("%c", &seguir);
    fflush(stdin);

    cargar = preguntaSeguir(seguir);

    while (cargar == 1)
    {
        printf("\nIngrese el numero de tarea que quiere marcar como realizada: ");
        scanf("%d", &ID);
        fflush(stdin);

        ID = ID + 999; // Le reste 999 en la impresion de pantalla por lo que el usuario ingresara mayores o iguales a 1

        cambiarListaId(ListaPendientes, ListaRealizadas, ID);

        printf("\n*---------- Lista de Tareas Pendientes ----------*\n");
        mostrarTarea(*ListaPendientes);

        printf("\nCargar mas tareas como realizadas (S/N): ");
        scanf("%c", &seguir);
        fflush(stdin);

        cargar = preguntaSeguir(seguir);
    }
}
