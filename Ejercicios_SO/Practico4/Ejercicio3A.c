/*
3) Hacer que un proceso finalice a otro
Variante de los anteriores, pero esta vez tenemos dos procesos, A y B
A funciona como en 2
B espera un cierto tiempo y luego escribe el archivo esperado por A*/
#include <sys/types.h>
 #include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


int main ( int argc , char * argv[]){

       int fd=0;

       printf("Buscando el archivo 'FinalizadorA.txt'");
       while( (fd=open("FinalizadorA.txt",O_RDONLY)) < 0){    
              sleep(1);
       }
       printf("El archivo a sido encontrado correctamente");
       close(fd);
       return 0;
}
