#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fifo(int referencia[], int marco[], int nMarcos);

int main (int argc, char const *argv[]){
    char line[256]; 
    int nMarcos = 0, referencia[30];
    FILE *archivo;
    int marco3[3] = {10}, marco4[4] = {10}, marco6[6] = {10};
    //Lectura del archivo
    archivo = fopen(argv[3], "r"); 
    if(archivo == NULL){
        printf("No se pudo abrir\n");
    }else{
        printf("Se pudo abrir\n");
    }

    if(fgets(line,sizeof(line), archivo) != NULL){//Lee la primera linea
        nMarcos = atoi(line);
    }else{
        printf("Error al leer la primera linea\n");
        fclose(archivo);
    }
    if(fgets(line, sizeof(line), archivo) != NULL){
        if(strlen(line) >= 30){//Lee la segunda linea
            for(int i = 0; i < 30; i++){
                referencia[i] = line[i] - '0';
            }
        }else{
            printf("La segunda linea no tiene 30 caracteres\n");
            fclose(archivo);
        }
    }else{
        printf("Error al leer la segunda linea\n");
        fclose(archivo);
    }
    fclose(archivo);  
    // Impresion del archivo
    printf("Nro marcos: %d\n", nMarcos);
    for(int i = 0; i < 30; i++){
        printf("%d\t", referencia[i]);
    }
    printf("\n");  
    //Eleccion del algoritmo y la cant de marcos
    if(strcmp(argv[2],"FIF") == 0){
        printf("Algoritmo: FIFO\n");
        switch (nMarcos){
            case 3:
                // printf("Llamada a fifo con marco3\n");
                printf("\nLa cantidad de fallos es: %d",fifo(referencia,marco3,nMarcos));
            break;
            case 4:
                //printf("Llamada a fifo con marco4\n");
                printf("\nLa cantidad de fallos es: %d",fifo(referencia,marco4,nMarcos));
            break;
            case 6:
                // printf("Llamada a fifo con marco6\n");
                printf("\nLa cantidad de fallos es: %d",fifo(referencia,marco6,nMarcos));
            break;
            default:
                printf("Cantidad de marcos incorrecta\n");    
            break;
        }
    }else if(strcmp(argv[2],"LRU") == 0){
        printf("Algoritmo: LRU\n");
        switch (nMarcos){
            case 3:
                printf("Llamada a lru con marco3\n");
            break;
            case 4:
                printf("Llamada a lru con marco4\n");
            break;
            case 6:
                printf("Llamada a lru con marco6\n");
            break;
            default:
                printf("Cantidad de marcos incorrecta\n");    
            break;
        }
    }//else{
    //     printf("Algoritmo: OPTIMO\n");
    //     switch (nMarcos){
    //         case 3:
    //             printf("Llamada a opt con marco3\n");
    //         break;
    //         case 4:
    //             printf("Llamada a opt con marco4\n");
    //         break;
    //         case 6:
    //             printf("Llamada a opt con marco6\n");
    //         break;
    //         default:
    //             printf("Cantidad de marcos incorrecta\n");    
    //         break;
    //     }
    // }

}
//Funciones de algoritmos
int fifo(int referencia[], int marco[], int nMarcos){
    int cWhile = 0, mViejo = 0, limite = nMarcos-1, fallos = 0;
    for(int i = 0; i < 30; i++){
        printf("\nBuscamos: %d\t", referencia[i]);
        int cont = 0;
        while(referencia[i] != marco[cWhile] && cont != limite){
            if(cWhile == (nMarcos-1)){
                cWhile = 0;
            }else{
                cWhile++;
            }
            cont++;
        }
        if(referencia[i] == marco[cWhile]){
            printf("\t--> %d\t", referencia[i]);
        }else if(cont == limite){
            marco[mViejo] = referencia[i];
            if(mViejo == (nMarcos-1)){
                mViejo = 0;
            }else{
                mViejo++;
            }
            printf("\tX-> %d\t", referencia[i]);
            fallos++;
        }
    }
return fallos;
}
int lru(int referencia[],int marco[], int nMarcos){
    
}