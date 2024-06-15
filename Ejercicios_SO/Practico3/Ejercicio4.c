/*4) Escriba un programa que reciba por linea de comando el nombre de
un archivo y lo copie en un archivo con la extension ".bak". Use
open(), close(), read() y write().

Tip: Usará open() dos veces, una el leer el archivo origen y otra
al crear y escribir en el archivo de destino. Para el segundo caso
puede utilizar
  fd = open("test.txt", O_RDWR|O_CREAT, 0644);
o lo que es lo mismo
  fd = open("test.txt", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH );
vea la página de manual 'man 2 open'

Tip: El programa en si tiene tres partes
  - abrir los archivos
  - recorrer (loop) el origen y escribir en destino
  - cerrar los archivos
el loop termina analizando el valor retornado por read()*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define MAX 256

int main ( int argc , char *argv[]){
    
    char buffer[MAX]; 
    int fd = open (argv[1], O_RDONLY);
    int destino = open ("test.txt",O_RDWR|O_CREAT, 0644)
    ssize_t n;
    ssize_t write;
    while((n=read(fd,buffer, MAX))>0){
            write = write (destino , buffer , n);
    }
    close(fd);
    close (destino);

    return 0;
}
