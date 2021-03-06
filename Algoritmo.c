#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
 
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


typedef struct 
{
    char ID;
    int indice;
    int Marcos;
    int sizeMb;
}Proceso;

//Inicializamos las funciones del programa 
void DibujarMemoria(int arregloMemoria[], int Num_Particiones, int CantProcesos, Proceso Procesos[]);
int TamMemoria();
int esPotencia(int numero);
int TamParticion();
void PrimerAjuste(int *num_proceso, int arregloPart[], int CantParticion, Proceso Procesos[]);
void BorrarProceso(char IDProceso, int ArregloMemoria[], int Cant_Particiones, Proceso Procesos[]);
//Estructura de los procesos

int main ()
{
    //Arreglamos terminal para ingreso de datos
    system("cls");
    //mostramos en terminal que se debe ingresar
    printf(ANSI_COLOR_YELLOW "************************************\n");
    printf("**********DATOS INICIALES***********\n");
    printf("************************************\n\n" ANSI_COLOR_RESET);
    printf("INDICACIONES: \n");
    printf("*Todos los tama%cos son potencias de 2.\n", 164);
    printf("*Todas las medidas est%cn en mb.\n\n", 160);


    /*
    *******************************************************************
    ***EN ESTE APARTADO SE INGRESAN LOS DATOS INICIALES DEL PROBLEMA***
    *******************************************************************
    */

    int Cant_Procesos_Iniciales;
    int Tam_Memoria = TamMemoria(); 
    int Tam_Particion = TamParticion(); 
    int Cant_Particion = Tam_Memoria/Tam_Particion;
    int arregloPart[Cant_Particion];
    Proceso Procesos[Cant_Particion]; //el máximo de procesos es la cantidad de particiones en la memoria. 
    //inicializamos la tabla con 0

    for (int i = 0; i < Cant_Particion; i++)
    {
        arregloPart[i] = 0;
    }
    //Mostramos la cantidad de particiones que se han creado a partir de los datos ingresados
    printf("\nLa cantidad de Particiones es: %d\n", Cant_Particion);
    DibujarMemoria(arregloPart, Cant_Particion, Cant_Procesos_Iniciales, Procesos);
    //Pedimos la cant de procesos
    //Solo me permite ingresar hasta la misma cantidad que particiones 
    Cant_Procesos_Iniciales = 0;

    int Pos_actual = -1;
    

    //Vamos a ingresar los procesos iniciales
// NOMBRE,BLOQUE INICIAL,TAMAÑO 
// 
    while(1)
    {
        printf("\nLa posicion actual del puntero:%d", Pos_actual);
        //bloque inicial del proceso 
        printf("\nIngrese ID del proceso: "); while(getchar()!='\n');  Procesos[Cant_Procesos_Iniciales].ID = getchar();
        do{
            printf("Ingrese bloque inicial: "); scanf("%d", &Procesos[Cant_Procesos_Iniciales].indice);
            if (Procesos[Cant_Procesos_Iniciales].indice>= Cant_Particion || Procesos[Cant_Procesos_Iniciales].indice<0)
            {
                printf(ANSI_COLOR_RED "\nEse valor para bloque inicial es invalido." ANSI_COLOR_RESET);
                continue;
            }
            if (Procesos[Cant_Procesos_Iniciales].indice < Pos_actual)
            {
                printf(ANSI_COLOR_RED "\nNo se puede ubicar en ese espacio.\n " ANSI_COLOR_RESET);
                continue;
            }
            break;
        } while(1);
        
        Pos_actual = Procesos[Cant_Procesos_Iniciales].indice;
        //memoria que ocupa el proceso 
        do
        {
            int Tam_MB = 0;
            //se ingresa el tamaño del proceso en mb
            printf("Ingrese el tama%co del proceso %c (en mb): ", 164, Procesos[Cant_Procesos_Iniciales].ID); scanf("%d", &Tam_MB);
            //no se puede ingresar un tamaño mayor a la cantidad de memoria
            if (Tam_MB> TamMemoria)
            {
                printf(ANSI_COLOR_RED "\nTama%co no permitido.\n " ANSI_COLOR_RESET, 164);
                continue;
            }
            //Asignamos el valor a la estructura de procesos 
            Procesos[Cant_Procesos_Iniciales].sizeMb = Tam_MB;

            //Calculamos la cantidad de Marcos que ocupa el proceso
            //Utilizamos una variable float por el decimal, si tiene un decimal es porque ocupa un marco más
            float CantPaginas = (float) Tam_MB / Tam_Particion;
            if ((int) CantPaginas < CantPaginas)
            {
                CantPaginas++;
            }
            Pos_actual += CantPaginas;
            if (Pos_actual-1 >= Cant_Particion)
            {
                printf(ANSI_COLOR_RED "\nEl tama%co del proceso excede de la memoria\n" ANSI_COLOR_RESET, 164);
                Pos_actual -= CantPaginas;
                continue;
            }
            printf("Las paginas del proceso %c (en mb) son: %d", Procesos[Cant_Procesos_Iniciales].ID, (int) CantPaginas );
            Procesos[Cant_Procesos_Iniciales].Marcos =(int)CantPaginas;
            break;
        } while (1);

        Cant_Procesos_Iniciales++;

        //para cada proceso
        for (int i = 0; i < Cant_Procesos_Iniciales; i++)
        {
            //Reocorremos la tabla principal
            for (int j = 0; j < Cant_Particion; j++)
            {
                if (Procesos[i].indice == j) //Si el indice del proceso coincide con el indice
                {                           //del arreglo

                    for (int k = j; k < j+ Procesos[i].Marcos; k++) //Ponemos un numero correspondiente al proceso en las particiones donde  
                    {                                            //las particiones son ocupadas por el proceso
                        arregloPart[k] = i+1;
                    }
                }
            }
        }

        printf("\n****************************************\n");
        DibujarMemoria(arregloPart, Cant_Particion, Cant_Procesos_Iniciales, Procesos);
        printf("\n****************************************\n");
        printf("%cDesea ingresar otro proceso? (y/n): ", 168); 
        char estado;
        while(getchar()!='\n'); estado = getchar();
        if (estado == 'n') break;
    }
    
    printf(ANSI_COLOR_YELLOW"\n**************************************\n");
    printf("********REPRESENTACION MEMORIA********\n");
    printf("**************************************\n\n"ANSI_COLOR_RESET);
    
    DibujarMemoria(arregloPart, Cant_Particion, Cant_Procesos_Iniciales, Procesos); //dibujamos los espacios de memoria del problema inicial
    
    /*
        *******************************************************************
        *****AHORA VAMOS CON LOS DATOS DEL ALGORITMO DE PRIMER AJUSTE******
        *******************************************************************
    */

   printf(ANSI_COLOR_YELLOW"\n************************************\n");
   printf("*****ALGORITMO DE PRIMER AJUSTE*****\n");
   printf("************************************\n\n"ANSI_COLOR_RESET);

    //creamos el numero de los nuevos procesos
    int num_proceso = Cant_Procesos_Iniciales;

    for (int i = 0; i < Cant_Particion; i++)
    {
        printf("\nIngrese el ID del proceso: ");  while(getchar()!='\n');  Procesos[num_proceso].ID = getchar();
        int TamMB;
        printf("\nIngrese el tama%co del nuevo proceso %c (en mb): ",164 ,Procesos[num_proceso].ID); scanf("%d", &TamMB);
        //asignamos el tamaño en MB al proceso indicado
        Procesos[num_proceso].sizeMb = TamMB;

        float CantPagina = (float) TamMB / Tam_Particion;
        if ((int) CantPagina < CantPagina) CantPagina++;
        //asignamos el tamaño de marcos del proceso a su estructura
        Procesos[num_proceso].Marcos = CantPagina;

        printf("Las paginas del proceso %c (en mb) son: %d", Procesos[num_proceso].ID , (int) CantPagina );
        PrimerAjuste(&num_proceso, arregloPart, Cant_Particion, Procesos);
        DibujarMemoria(arregloPart, Cant_Particion, Cant_Procesos_Iniciales, Procesos);

        char eliminar;
        printf("%cDesea eliminar un proceso? (y/n): ", 168);
        while(getchar()!='\n'); eliminar = getchar();
        if (eliminar == 'y')
        {
            char id;
            printf("Ingrese el ID del proceso a eliminar: " );
            while(getchar()!='\n');  id = getchar();
            BorrarProceso(id , arregloPart , Cant_Particion , Procesos);
            DibujarMemoria(arregloPart, Cant_Particion, Cant_Procesos_Iniciales, Procesos);
        }

        printf("%cDesea ingresar otro proceso? (y/n): ", 168); 
        char estado;
        while(getchar()!='\n'); estado = getchar();
        if (estado == 'n')
        {
            break;
        }
    }
    /*
        ********************************************************************
        *********************ALGORITMO DE PRIMER AJUSTE*********************
        ********************************************************************
    */

    printf(ANSI_COLOR_YELLOW"\n************************************\n");
    printf("***********RESULTADO FINAL**********\n");
    printf("************************************\n\n"ANSI_COLOR_RESET);
    printf("\n\n"); //Marcamos un espacio
    DibujarMemoria(arregloPart, Cant_Particion, Cant_Procesos_Iniciales, Procesos); //Dibujamos la memoria en la terminal
    return 0;
}

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
                printf(ANSI_COLOR_BLUE "\t%d\t%c%c%c  Proceso %c\n" ANSI_COLOR_RESET,i,179,219,179, Procesos[arregloMemoria[i]-1].ID);
                break;
            case 1:
                printf(ANSI_COLOR_YELLOW "\t%d\t%c%c%c  Proceso %c\n" ANSI_COLOR_RESET,i,179,219,179, Procesos[arregloMemoria[i]-1].ID);
                break;
            case 2:
                printf(ANSI_COLOR_CYAN "\t%d\t%c%c%c  Proceso %c\n" ANSI_COLOR_RESET,i,179,219,179, Procesos[arregloMemoria[i]-1].ID);
                break;
            case 3:
                printf(ANSI_COLOR_MAGENTA "\t%d\t%c%c%c  Proceso %c\n" ANSI_COLOR_RESET,i,179,219,179, Procesos[arregloMemoria[i]-1].ID);
                break;
            default:
                printf(ANSI_COLOR_GREEN "\t%d\t%c%c%c  Proceso %c\n" ANSI_COLOR_RESET,i,179,219,179, Procesos[arregloMemoria[i]-1].ID);
                break;
            }
        }
        else
        {
            printf("\t%d\t%c%c%c  Proceso %c\n",i ,179,219,179, Procesos[arregloMemoria[i]-1].ID);
        }
    }
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
    } while (!esPotencia(TamMemoria));
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
    int indicador = 1; //nos dira si se pudo ingresar el proceso o no. 1 para si y 0 para no.  
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

void BorrarProceso(char IDProceso, int ArregloMemoria[], int Cant_Particiones, Proceso Procesos[])
{
    //localizamos el numero el numero del proceso en memoria por su ID
    int numProceso = 0;
    
    for (int i = 0; i < Cant_Particiones; i++)
    {
        if (ArregloMemoria[i] != 0){
            if (Procesos[ArregloMemoria[i]-1].ID == IDProceso)
            {
                numProceso = ArregloMemoria[i];
                break;
            }
        }
    }
    //borramos los rastros del proceso.
    for (int i = 0; i < Cant_Particiones; i++)
    {
        if (ArregloMemoria[i] == numProceso)
        {
            ArregloMemoria[i] = 0;
        }
    }
    
}

