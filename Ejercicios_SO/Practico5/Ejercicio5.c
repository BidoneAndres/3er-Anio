/*
2) Cliente-Servidor con pipes sin nombre. Escribiremos un programa que
creara dos hijos los cuales se comunicaran utilizando pipes sin nombre.
Uno de los hijos obtiene la hora del sistema como antes, y envía ese dato
utilizando pipes. El segundo recibe los datos y los muestra por pantalla.
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#define LONG 32

int main ( int argc , char * argv[] ){
    
    int pd[2];
    
    int escribir , leer, STATUS;

    time_t tInicial;

    char tiempo[LONG], buffer[LONG];

    int a , b; 

    pipe( pd );

    a = fork ();

    if(a == 0){
            tInicial = time(0);
            strcpy(tiempo, ctime(&tInicial));

            escribir = write ( pd[1] , tiempo , LONG );
            if(escribir < 0){
                printf ( "No se ha podido escribir la tuberia con exito...");

                exit (1);

            }

    }else{
        wait (&STATUS);
        b = fork();
        if ( b == 0 ){
            leer = read( pd[0] , buffer , LONG);
            printf("%s" , buffer);
        }
    }

    
    
    return 0;
}