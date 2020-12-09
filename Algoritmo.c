#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define BLK "\e[0;30m"
#define BLKHB "\e[0;100m"
#define BHGRN "\e[1;92m"
#define BLUB "\e[44m"
#define WHTHB "\e[0;107m"
#define UGRN "\e[4;32m"

int main(void) 
{
    printf( BLUB "\n\n************************************\n");
    printf("**********DATOS INICIALES***********\n");
    printf("************************************\n\n" ANSI_COLOR_RESET);
    printf("INDICACIONES: \n");
    printf("*Todos los tamaños son potencias de 2.\n");
    printf("*Todas las medidas están en mb.\n\n");


  FILE* archivo = fopen("./PrimerAjuste.txt","r");

  if (archivo == NULL)
  {
    perror("No se pudo abrir");
    exit(-1);
  }

  char caracter;
  int Tam_Memoria ;
  int Tam_Particion;
  
  	//Esto solo pasa una vez en el programa 
    while (fgetc(archivo) != '$'); 
    fscanf(archivo,"%d\t%d",&Tam_Memoria,&Tam_Particion );
    
	if(!esPotencia(Tam_Memoria) || !esPotencia(Tam_Particion))
	{
		printf("Los tamaños no son potencias de 2"); 
		exit(-1);
	}
	else
	{
    printf("tamaño de memoria: %d\n", Tam_Memoria);
    printf("tamaño de partición: %d\n", Tam_Particion);
	}

  
  /*
    *******************************************************************
    ***EN ESTE APARTADO SE INGRESAN LOS DATOS INICIALES DEL PROBLEMA***
    *******************************************************************
 */
 	int Cant_Procesos_Iniciales;  
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
     printf(ANSI_COLOR_YELLOW"\n\n*********Los procesos iniciales (ID) son los siguientes:********"ANSI_COLOR_RESET);

   //Vamos a ingresar los procesos iniciales
  // NOMBRE,BLOQUE INICIAL,TAMAÑO 
	int cont = 0; 
    while(1)
    {
        //bloque inicial del proceso 
		while (fgetc(archivo) != '$');
        fscanf(archivo,"%s\t%d\t%d", Procesos[Cant_Procesos_Iniciales].ID, &Procesos[Cant_Procesos_Iniciales].indice,&Procesos[Cant_Procesos_Iniciales].sizeMb);

        if (Procesos[Cant_Procesos_Iniciales].indice>= Cant_Particion || Procesos[Cant_Procesos_Iniciales].indice<0)
        {
			    printf(ANSI_COLOR_RED "\nEse valor para bloque inicial es invalido." ANSI_COLOR_RESET);
			    exit(-1);
        }
		    if (Procesos[Cant_Procesos_Iniciales].sizeMb> Tam_Memoria)
        {
            printf(ANSI_COLOR_RED "\nTamaño no permitido.\n " ANSI_COLOR_RESET);
			exit(-1);
		    } 
        
        printf("\n\nID: %s\n", Procesos[Cant_Procesos_Iniciales].ID);
        printf("Posición inicial: %d\n", Procesos[Cant_Procesos_Iniciales].indice);
        printf("Tamaño de memoria: %d\n", Procesos[Cant_Procesos_Iniciales].sizeMb);
          

    	//Calculamos la cantidad de Marcos que ocupa el proceso
    	//Utilizamos una variable float por el decimal, si tiene un decimal es porque ocupa un marco más
        float CantPaginas = (float) Procesos[Cant_Procesos_Iniciales].sizeMb / Tam_Particion;
        if ((int) CantPaginas < CantPaginas)
        {
            CantPaginas++;
        }

        printf("Las paginas del proceso %s (en mb) son: %d", Procesos[Cant_Procesos_Iniciales].ID, (int) CantPaginas );
		Procesos[Cant_Procesos_Iniciales].Marcos =(int)CantPaginas;

		Cant_Procesos_Iniciales++;

    if (fgetc(archivo) == '#')
		{
			break;
		}
	}	

	//EN LA MEMORIA SIMULADA INGRESAMOS COMO NUMERO EL EL ORDEN EN QUE LOS PROCESOS HAN ENTRADO.
    //para cada proceso
    for (int i = 0; i < Cant_Procesos_Iniciales; i++)
    {
        //Reocorremos la tabla principal
        for (int j = 0; j < Cant_Particion; j++)
        {
            if (Procesos[i].indice == j) //Si el indicedelproceso coincide con el indice del arreglo
            {                           
                for (int k = j; k < j+ Procesos[i].Marcos; k++) //Ponemos un numero correspondiente al proceso en las particiones donde  
                {                                            //las particiones son ocupadas por el proceso
                    arregloPart[k] = i+1;
                }
            }
        }
    }
	printf("\n");
	

	printf( BLUB "\n**************************************\n");
  	printf("********REPRESENTACION MEMORIA********\n");
 	 printf("**************************************\n\n"ANSI_COLOR_RESET);

  DibujarMemoria(arregloPart, Cant_Particion, Cant_Procesos_Iniciales, Procesos);

  
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

    //tamaños de los procesos
    while (1)
    {
	  	while(fgetc(archivo) != '$');
		  caracter = fgetc(archivo);

		  if (caracter == '&')
      {
		    fscanf(archivo, "%s\t%d", Procesos[num_proceso].ID, &Procesos[num_proceso].sizeMb);
		
		    int CantMarcos;
		    CantMarcos = cantMarcos(Procesos[num_proceso].sizeMb, Tam_Particion); //calcula a traves del tamaño proceso y cantidad q va a ocupar. Antes de la funcion
		    Procesos[(int)num_proceso].Marcos = CantMarcos; //Aginar cant marcos a la estructura de procesos. DSp de la funcion

		    PrimerAjuste(&num_proceso, arregloPart , Cant_Particion, Procesos);

		    printf("Marcos: %d, numProceso: %d", (int) CantMarcos, num_proceso);
		    printf("\nNombre de proceso: %s \n", Procesos[num_proceso-1].ID);
		    printf("Tamaño de proceso: %d MB\n\n", Procesos[num_proceso-1].sizeMb);
		  DibujarMemoria(arregloPart, Cant_Particion, Cant_Procesos_Iniciales, Procesos);

    
	  	}
      
		  if (caracter == '!')  
		  {
			char id[4]; 
			fscanf(archivo, "%s\n", id);
			 if(Procesos[0].ID[0] == id[0]) printf("\nSe ha eliminado el proceso %s\n\n", Procesos[0].ID);
			 EliminarProceso(id, arregloPart, Procesos, num_proceso, Cant_Particion);
      		DibujarMemoria(arregloPart, Cant_Particion, Cant_Procesos_Iniciales, Procesos);
		} 
	      if (fgetc(archivo) == '#')
		  {
		    break;
	    }
    } 

  printf(" ******** ");
  printf(BHGRN UGRN"PRIMER AJUSTE"ANSI_COLOR_RESET);
  printf(" TERMINADO");
  printf(" ********\n\n");

  
  
  fclose(archivo);
  return 0;
  
}



