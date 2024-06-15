/*3) Escriba un programa que lea el directorio raiz (/) y muestre su
contenido por pantalla. Use opendir(), readdir() y closedir().*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
int main( int argc, char * argv[]){

    DIR *fd;
    fd= opendir("/");
    struct dirent *read;

    while((read=readdir(fd))!=NULL){
        printf("%s\n",read->d_name);
    }
    
    closedir(fd);
    
    return 0;
}



