/*1) Cliente-Servidor con archivos. Exploraremos la posibilidad de "comunicar" 
dos procesos mediante archivos externos. Escriba un programa que "cree" dos
archivos, a-inout y b-inout. Luego deberá crear dos hijos, cada hijo deberá 
abrir los archivos PERO de modo que el primer hijo abra "a" para lectura y 
"b" para escritura, en cambio el segundo abrira "a" para escritura y "b"
para lectura. Una vez realizado esto el primer hijo debera obtener la hora
del sistema (usando ctime()), escribirá esta informacion en "b", cuando esto
ocurra, el segundo proceso hijo obtendra a su vez la hora al leera de 
"b", y la mostrara por pantalla. Al finalizar ambos procesos hijos,
el padre deberá reportar el estado de terminacion.
*/

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define LONG 32

int main ( int argc , char *argv[] ){

    int a_fd;
    int b_fd;
    int STATUS, escribir, leer;


    int a;
    int b;

    time_t tInicial;
    char tiempo[LONG], buff[LONG];

    a_fd = open("a-inout.txt",O_CREAT,0664);
    b_fd = open("b-inout.txt",O_CREAT,0664);

    if(a_fd < 0 || b_fd < 0){
      printf("Los archivos no han sido creados con exito...");
      exit(1);
    }


    a = fork();

    if( a == 0 ){
        tInicial = time(0);
        strcpy(tiempo, ctime(&tInicial));

        a_fd = open("a-inout.txt",O_RDONLY,0664);
        b_fd = open("b-inout.txt",O_RDWR,0664);

        if(a_fd < 0 || b_fd < 0){
            printf("Los archivos no han sido abiertos con exito...");  
            exit(2);
        }
        escribir = write ( b_fd , tiempo , LONG );

        if(escribir < 0){
            printf("El archivo no pudo escribirse con exito...");
        }
    }else{
        wait(&STATUS);

        b = fork(); 

        if( b == 0){
            a_fd = open("a-inout.txt",O_RDWR,0664);
            b_fd = open("b-inout.txt",O_RDONLY,0664);
            if(a_fd < 0 || b_fd < 0){
                printf("Los archivos no han sido abiertos con exito...");  
                exit(3);
            }

            leer = read(b_fd , buff , LONG);
            printf("%s",buff);
        }
    }

    close(a_fd);
    close(b_fd);

    return 0;

}