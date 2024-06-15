/*
2) Finalizar un programa utilizando el contenido de un archivo externo
Similar al anterior, pero ahora queremos 'ver' que contiene el archivo.
Si contiene un valor '1' entonces prosigue
Si contiene el valor '0' termina*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define LECTURA 10
int main ( int argc , char * argv[]){

       int fd=0;
       char buff[LECTURA] = {""};
       ssize_t leer;

       fd = open("Finalizador.txt", O_RDONLY);
       
        if(fd < 0){
            printf("No funciono");
            exit(1);
        }

       do{
              leer = read (fd,buff,LECTURA);

       }while(buff[0] != '0');


       printf("El archivo contiene 0");
       close(fd);
       return 0;
}


