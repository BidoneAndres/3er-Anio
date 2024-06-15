#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REGISTROS 1000
#define LONG_LIDER 24
#define LONG_ENTRADA_DIRECTORIO 12

struct Nodo{
    char etiqueta[4];
    int longitud;
    int inicio;
};

void copiarLider(char *registro, char *lider);
void copiarDirectorio(char *registro, struct Nodo *directorio, int numEntradas);
void imprimirRegistro(char *registro, struct Nodo *directorio, int numEntradas);

int main() {
    FILE *archivo;
    char registro[MAX_REGISTROS][1000];
    archivo = fopen("osbooks.iso2709", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

   
    int i = 0;
    while (fgets(registro[i], 1000, archivo) != NULL) {
        i++;
    }

   
    for (int j = 0; j < i; j++) {
        char lider[LONG_LIDER + 1];
        copiarLider(registro[j], lider);
        printf("Registro %d:\n", j + 1);
        printf("Líder: %s\n", lider);

        int baseDatos = atoi(&lider[12]);
        int numEntradas = (baseDatos - LONG_LIDER - 1) / LONG_ENTRADA_DIRECTORIO;

        struct Nodo directorio[numEntradas];
        copiarDirectorio(registro[j], directorio, numEntradas);
        imprimirRegistro(registro[j], directorio, numEntradas);

        printf("\n");
    }

    fclose(archivo);
    return 0;
}


void copiarLider(char *registro, char *lider) {
    strncpy(lider, registro, LONG_LIDER);
    lider[LONG_LIDER] = '\0';
}

void copiarDirectorio(char *registro, struct Nodo *directorio, int numEntradas) {
    for (int i = 0; i < numEntradas; i++) {
        strncpy(directorio[i].etiqueta, registro + LONG_LIDER + i * LONG_ENTRADA_DIRECTORIO, 3);
        directorio[i].etiqueta[3] = '\0';

        char longitudStr[5];
        strncpy(longitudStr, registro + LONG_LIDER + i * LONG_ENTRADA_DIRECTORIO + 3, 4);
        longitudStr[4] = '\0';
        directorio[i].longitud = atoi(longitudStr);

        char inicioStr[6];
        strncpy(inicioStr, registro + LONG_LIDER + i * LONG_ENTRADA_DIRECTORIO + 7, 5);
        inicioStr[5] = '\0';
        directorio[i].inicio = atoi(inicioStr);
    }
}

void imprimirRegistro(char *registro, struct Nodo *directorio, int numEntradas) {
    for (int i = 0; i < numEntradas; i++) {
        printf("Etiqueta: %s\n", directorio[i].etiqueta);
        printf("Longitud: %d\n", directorio[i].longitud);
        printf("Datos: ");
        fwrite(registro + directorio[i].inicio, 1, directorio[i].longitud - 1, stdout);
        printf("\n");
    }
}