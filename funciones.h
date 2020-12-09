#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct 
{
    char ID[2];
    int indice;
    int Marcos;
    int sizeMb;
}Proceso;

//Inicializamos Las funciones del programa
void DibujarMemoria(int arregloMemoria[], int Num_Particiones, int CantProcesos, Proceso Procesos[]);
int TamMemoria();
int esPotencia(int numero);
int TamParticion();
void PrimerAjuste(int *num_proceso, int arregloPart[], int CantParticion, Proceso Procesos[]);
void BorrarProceso(char* IDProceso, int ArregloMemoria[], int Cant_Particiones, Proceso Procesos[]);
int cantMarcos (int TamProceso, int TamParticion);
void EliminarProceso(char id[], int *ArregloPart, Proceso Procesos[], int num_Procesos, int cant_particion);

void DibujarMemoria(int arregloMemoria[], int Num_Particiones, int CantProcesos, Proceso Procesos[])
{
    for (int i = 0; i < Num_Particiones; i++)
    {
        if (arregloMemoria[i] == 0)
        {
            printf("\t%d\t|_|\n", i);
        } 
        else if(arregloMemoria[i]>CantProcesos)
        {
            int num = arregloMemoria[i]-CantProcesos-1;
            if (num > 4)
            {
                srand(time(NULL));
                num = rand()%4;
            }
            
            switch (num)
            {
            case 0:
                printf(ANSI_COLOR_BLUE "\t%d\t%c%c%c  Proceso %c\n" ANSI_COLOR_RESET,i,179,219,179, Procesos[arregloMemoria[i]-1].ID[0]);
                break;
            case 1:
                printf(ANSI_COLOR_YELLOW "\t%d\t%c%c%c  Proceso %c\n" ANSI_COLOR_RESET,i,179,219,179, Procesos[arregloMemoria[i]-1].ID[0]);
                break;
            case 2:
                printf(ANSI_COLOR_CYAN "\t%d\t%c%c%c  Proceso %c\n" ANSI_COLOR_RESET,i,179,219,179, Procesos[arregloMemoria[i]-1].ID[0]);
                break;
            case 3:
                printf(ANSI_COLOR_MAGENTA "\t%d\t%c%c%c  Proceso %c\n" ANSI_COLOR_RESET,i,179,219,179, Procesos[arregloMemoria[i]-1].ID[0]);
                break;
            default:
                printf(ANSI_COLOR_GREEN "\t%d\t%c%c%c  Proceso %c\n" ANSI_COLOR_RESET,i,179,219,179, Procesos[arregloMemoria[i]-1].ID[0]);
                break;
            }
        }
        else
        {
            printf("\t%d\t%c%c%c  Proceso %c\n",i ,179,219,179, Procesos[arregloMemoria[i]-1].ID[0]);
        }
    }
    printf("\n");
}

int TamMemoria()
{
    int tamMemoria;
    do
    {
        printf(" Ingrese tama%co de memoria : ", 164);
        scanf("%d", &tamMemoria);
        if (esPotencia(tamMemoria))
        {
            return tamMemoria;
        }
        else printf(ANSI_COLOR_RED"No se ha ingresado un tama%co de memoria correcto\n"ANSI_COLOR_RESET, 164);   
    } while (!esPotencia(tamMemoria));
}
int TamParticion()
{
    int tamParticion;
    do  
    {
        printf(" Ingrese tama%co de partici%cn : ",164, 162);
        scanf("%d", &tamParticion);
        if (esPotencia(tamParticion))
        {
            return tamParticion;
        }
        else printf(ANSI_COLOR_RED "No se ha ingresado un tama%co de partici%cn correcto\n"ANSI_COLOR_RESET , 164,162);   
    } while (!esPotencia(tamParticion));
}

int esPotencia(int numero)
{
    if (numero<1) return 0;
    if (numero == 2) return 1;
    int i = 2;
    while (1)
    {
        i = i*2;
        if (i == numero) return 1;
        if (i>numero) return 0;
    }
}

void PrimerAjuste(int *num_proceso, int arregloPart[], int CantParticion, Proceso Procesos[])
{
    //Contamos la cantidad de Huecos en memoria 
    int MarcoAnterior = 1, CantHuecos = 0;
    int ContadorIntentos = 0; //Contamos la cantidad de intentos en que se quiere meter el nuevo proceso
    MarcoAnterior = 1; //Ponemos como 1 otra vez marco anterior
    //Iniciamos el bucle for y lo recorremos por el arreglo de particiones
    for (int i = 0; i < CantParticion; i++)
    {
        if (arregloPart[i] == 0 && MarcoAnterior>0) CantHuecos++;
        MarcoAnterior = arregloPart[i];
    }

    MarcoAnterior = 1;
    for (int i = 0; i < CantParticion; i++)
    {
        int TAM_Hueco = 0;  //Iniciamos la variable TAM_hueco, para guardar el tamaño del primer hueco que hallamos en memoria
        //Cada vez que se encuentre 0 en el arreglo 
        if (arregloPart[i] == 0 && MarcoAnterior>0) //Si hay en la pos actual hay  un 0 en el arreglo
        {                                           //y la posicion anterior le partenece a un proceso 
            //hacemos un bucle para sumar el tamaño del hueco 
            for (int j = i; j < CantParticion; j++)
            {
                if (arregloPart[j] == 0) TAM_Hueco++;
                //si es otro número se rompe
                else break;
            }
            MarcoAnterior = arregloPart[i]; 
        }
        //Si no hay 0 pasa a la siguiente iteracion
        else 
        {
            MarcoAnterior = arregloPart[i]; 
            continue;
        }

        //Si el tamaño del hueco es mayor o igual al tamaño del proceso entrante se ingresa al bucle
        if (TAM_Hueco >= Procesos[*num_proceso].Marcos)
        {
            *num_proceso = *num_proceso + 1;
            //Agregamos el numero del proceso en el arreglo en las posiciones que corresponde
            for (int j = i;  j< Procesos[*num_proceso-1].Marcos+i; j++)
            {   
                arregloPart[j] = *num_proceso;
            }
            break;
        }
        else
        {
            ContadorIntentos++;
            if (ContadorIntentos == CantHuecos)
            {
                printf(ANSI_COLOR_RED "\nEl proceso que desea ingresar no alcanza en la memoria. \n" ANSI_COLOR_RESET);
                break;
            }
        }
        
    }
    printf("\n\n"); //Marcamos un espacio
}

void EliminarProceso(char id[], int *ArregloPart, Proceso Procesos[], int num_Procesos, int cant_particion)
{
	int indice; 
	for (int i = 0; i<num_Procesos; i++)
	{
		if (Procesos[i].ID[0] == id[0]) 
		{
			indice = i;
		}
	}

	for(int i = 0; i< cant_particion; i++)
	{
		if (i == indice)
		{
			for (int j = i; j<Procesos[indice].Marcos + i; j++)
			{
				ArregloPart[j] = 0;
			}
		}
	}
}


int cantMarcos (int TamProceso, int TamParticion)
{
    float CantMarcos = (float) TamProceso / TamParticion;
    if ((int)CantMarcos < CantMarcos)
    {
        CantMarcos++;
    }
    return (int) CantMarcos;
}