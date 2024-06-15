/*ESTE CODIGO NO ES EL CODIGO FINAL, ES PARA VER COMO FUNCIONAN LAS OPERACIONES
, DESPUES VOY A IMPLEMENTAR CON EL CODIGO QUE ESTA EN EL GIT*/

/* BEGIN código del libro */

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define N 100 /* number of slots in the buffer*/ 
typedef int semaphore; //Defino un tipo especial de enteros 

//Comente esta parte porque no la entiendo muy bien

/* semaphores are a special kind of int 
semaphore mutex = 1;  controls access to critical region 
semaphore empty = N;  counts empty buffer slots 
semaphore full = 0;  counts full buffer slots */



int main(){

	int prod , cons;
    sem_t *mutex;
	
    /*Declaro las variables que van a utilizarse para el semaforo
    estas son del tipo semaphore que es un tipo especial de int declarado arriba*/
    
    semaphore comprobar;
    semaphore empty;
    
    
    /*En esta parte creo el semaforo con el nombre SemaphoreTest
    Por ahora funciona todo bien*/
    mutex = sem_open("SemaphoreTest", O_CREAT);
	
    
    if(mutex < 0){
        printf("Ah ocurrido un herror al crear el semaforo");
        exit (1);
    }


    /*Creo los procesos que van a funcionar como consumidor y productor*/
	prod = fork();
    
    /*En esta parte falla, no entra a los if, todavia estoy viendo que onda
    La idea de este codigo es que sea un tester, para luego poder implementarlo */
    if(prod == 0){
        
        /*ESTA ES LA PARTE DEL PRODUCTOR*/

        comprobar = sem_wait(mutex); //Compruebo el estado del semaforo, si esta en 1 lo pongo en 0

        if(comprobar < 0 ){
            printf("A ocurrido un error al realizar el down");
        }
        
        printf (" El productor esta produciendo el item");
        
        sleep(10);
        
        comprobar = sem_post(mutex); //Funciona como un up basicamente, este va a dar la orden para que siga el consumidor 
        if(comprobar < 0 ){
            printf("A ocurrido un error al realizar el up");
        }
        
    }else{
        cons = fork();
            printf("llego");
        if( cons == 0 ){
            /*ESTA ES LA PARTE DEL CONSUMIDOR*/
            printf("llego");
            comprobar = sem_wait(mutex);
            
            if(comprobar < 0 ){
                printf("A ocurrido un error al realizar el down");
            }

            printf ( "El consumidor esta consumiendo...");

            sleep(10);

            comprobar = sem_post(mutex);

            if(comprobar < 0 ){
                printf("A ocurrido un error al realizar el up");

            }

        }
    }



	return 0;
}




