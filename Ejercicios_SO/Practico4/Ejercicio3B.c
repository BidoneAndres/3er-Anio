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

#include LECTURA 64

int main ( int argc , char * argv[]){

       int fd=0;
       ssize_t read;
       char buff[]
       fd=open("FinalizadorB.txt",O_RDONLY);


       printf("Consultando el archivo....");
       while(true){    
              sleep(1);
              read = read(fd , buff , LECTURA);
              if(buff[0] == '0'){
                     printf("El programa finalizara...");
                     exit (1);
              }
              
       }
       printf("El archivo a sido encontrado correctamente");
       close(fd);
       return 0;
}