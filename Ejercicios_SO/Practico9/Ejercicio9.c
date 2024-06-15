#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para la función read
#include <fcntl.h>  // Para las constantes O_RDONLY
#include <string.h>

#define TAMANIO 2048 // Longitud máxima de un registro

int main() {
    int fd = open("osbooks.iso2709", O_RDONLY);
    char tag[4];
    char buff[TAMANIO];

    if (fd == -1) {
        perror("Error al abrir el archivo");
        exit (1);
    }

    
    int n;
    while ((n = read(fd, buff, TAMANIO)) > 0) {
        
        printf("%.*s\n", 24, buff);

       
        int directoryLength = atoi(strncpy((char[6]){0}, buff + 12, 5));
        int baseAddress = atoi(strncpy((char[6]){0}, buff, 5));
        for (int i = 0; i < directoryLength; i += 12) {
            /*En esta linea cargo el tag*/
            strncpy(tag, buff + baseAddress + i, 3);
            tag[3] = '\0';

            int final = atoi(strncpy((char[6]){0}, buff + baseAddress + i + 3, 4));
            int comienzo = atoi(strncpy((char[6]){0}, buff + baseAddress + i + 7, 5));
            
            // Imprimir el campo
            printf("%s %.*s\n", tag, final, buff + comienzo);
        }
    }

    close(fd);
    return 0;
}