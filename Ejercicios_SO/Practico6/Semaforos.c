
#include <semaphore.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 100

/*-----Declaro el semaforo como una variable global------*/

sem_t *mutex; /*En este caso mutex es el nombre del semaforo*/
//int empty = N;

void *productor(void *param);
void *consumidor(void *param);

int main(int argc , char * argv[]){
    
    /*Declaro el productor y el consumidor que voy a utilizar en el programa...*/
    pthread_t produc;
    pthread_t cons; 
    int rc, t;
    mutex = sem_open ("semaphoreTest", O_CREAT | O_EXCL,0644,1);
    pthread_attr_t attr;

    
    /*Aca voy a crear los hilos necesarios, que van a ejecutar sus debidas funciones*/
    pthread_attr_init( &attr );
    rc=pthread_create( &produc , &attr , productor , (void *) &t );
    

    pthread_attr_init( &attr );
    rc=pthread_create( &cons , &attr , consumidor , (void *) &t );
    
    /*Espera a que los hilos terminen*/ 
    pthread_join(produc, NULL);
    pthread_join(cons, NULL);

    /*Cierre del semáforo*/
    sem_close(mutex);
    sem_unlink("semaphoreTest");
    
    return 0;
}

void *productor( void *param ){
    /*Esta va a ser la fucion del productor*/
    int comprobar = 0;
    

    comprobar = sem_wait(mutex);
    if(comprobar < 0){
        printf("No se ha podido ejecutar la funcion de down()");
        exit(1);
    }
    printf("El productor esta produciendo...\n");
    
    sleep(3);

    printf("El productor dejo de producir...\n");

    comprobar = sem_post(mutex);

    pthread_exit(0);

} 

void *consumidor( void *param){
    /*Esta va a ser la funcion del consumidor*/
    int comprobar = 0;

    comprobar = sem_wait(mutex); /*Funcion de down en el semaforo*/
    if(comprobar < 0){
        printf("No se ha podido ejecutar la funcion de down()");
        exit(1);
    }
    printf("El consumidor esta consumiendo...\n");
    
    sleep(3);

    printf("El consumidor dejo de consumir...\n"); /*Funcion de up en el semaforo*/

    comprobar = sem_post(mutex);

    pthread_exit(0);
}

/*QUEDA COMPLETARLO UN POCO*/