/*
Ejercicio 1:
1) Compile el ejemplo que crea 5 hilos (4-threads.c) utilizando:

    $ gcc -Wall -pthread -o ht ht.c

Notas cobre el ejemplo:
a) pthread_create crea el hilo, 
   el primer argumento almacena el Id del Hilo,
   el segundo pasa parámetros iniciales
   el tercero indica cual es la función que ejecuta el hilo, 
   el cuarto es el *unico* argumento que podemos pasar al hilo.

b) Todos los hilos deben invocar pthread_exit al terminar.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define AMOUN_THREADS 6 // Esta variable define la cantidad de hilos a utilizar.

void *funcion(void *param);

int main(int argc, char * argv[]){
    
    pthread_t threads[AMOUN_THREADS];
    pthread_attr_t attr;
    
    int create=0; //En esta variable se va a almacenar la direccion de retorno de la funcion pthread_create
    
    for ( int i = 0 ; i<AMOUN_THREADS;i++){
        create = pthread_create(&threads[i] , NULL , funcion , (void *)&i);

        if(create){
            printf("No se ha podido crear el hilo N%d",i);
            exit (1);
        }
    }
    pthread_exit(NULL);
    return 0;
}
void *funcion(void *param)
{
	int *idThread = param;

	printf("I'm the thread #%d\n", *idThread);
	sleep(1);
	printf("BYE\n");
	sleep(1);
	pthread_exit(0);
}