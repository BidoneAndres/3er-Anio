/*
2) Finalizar un programa utilizando el contenido de un archivo externo
Similar al anterior, pero ahora queremos 'ver' que contiene el archivo.
Si contiene un valor '1' entonces prosigue
Si contiene el valor '0' termina*/
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#define MAX 8

int main ( int argc , char * argv[]){

       int fd=0;
       
       fd=open("FinalizadorA.txt",O_CREAT);
       
       printf("El archivo a sido creado correctamente");
       
       close(fd);
       
       return 0;
}