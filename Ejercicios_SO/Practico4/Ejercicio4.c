/*4) Intercambio de mensajes entre dos procesos utilizando un archivo
Sean dos procesos, A y B, los cuales van a 'hablar'entre si
El proceso A crea un archivo, ej. comunicador.txt, y escribe dentro de el 
un mensaje. Luego lee periodicamente el archivo y espera que el mensaje 'cambie',
cuando descubre que ha cambiado termina.*/
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define LECTURA 64

int main ( int argc , char * argv[]){
       int escribir;
       int fd=0;
       ssize_t leer;
       char buffR[LECTURA], buffW[LECTURA];
       fd=open("Comunicador.txt",O_RDWR|O_CREAT,0644);
       
       if(fd < 0){
              printf("El archivo no fue abierto con exito...");
              exit(1);
       }

       strcpy(buffW , "Hola como andas?");
       strcpy(buffR , "Hola como andas?");


       escribir = write( fd , buffW , LECTURA );

       if( escribir < 0){
              printf("El archivo no se ha podido escribir...");
              exit (2);
       }



       while(strcmp(buffR , buffW) == 0){    
              sleep(1);
              leer = read(fd , buffR , LECTURA);
       }
       printf("El archivo a sido encontrado correctamente");
       close(fd);
       return 0;
}