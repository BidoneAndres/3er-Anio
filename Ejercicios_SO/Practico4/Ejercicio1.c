/*1) Finalizar un programa utilizando un archivo externo
Escriba un programa que verifique periódicamente la
existencia de un archivo (nombre a elección)
Si descubre que existe entonces termina.*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main ( int argc , char * argv[]){

       int fd=0;

       while(open("Finalizador.txt",O_RDONLY) < 0){
              sleep(1);
       }
       printf("El archivo a sido creado correctamente");
       close(fd);
       return 0;
}

