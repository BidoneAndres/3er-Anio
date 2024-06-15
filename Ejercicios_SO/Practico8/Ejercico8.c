#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fifo(int referencia[], int marco[], int nMarcos);
int lru(int referencia[],int marco[], int nMarcos);
int opt(int referencia[], int marco[], int nMarcos); 

int main (int argc, char const *argv[]){
    char line[256]; 
    int nMarcos = 0, referencia[30];
    FILE *archivo;
    int marco3[3] = {10}, marco4[4] = {10}, marco6[6] = {10};
    //Lectura del archivo
    archivo = fopen(argv[3], "r"); 
    if(archivo == NULL){
        printf("No se pudo abrir\n");
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
      
    if(strcmp(argv[2],"FIFO") == 0){
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
                printf("\nLa cantidad de fallos es: %d\n",lru(referencia,marco3,nMarcos));
            break;
            case 4:
                printf("\nLa cantidad de fallos es: %d\n",lru(referencia,marco3,nMarcos));
            break;
            case 6:
                printf("\nLa cantidad de fallos es: %d\n",lru(referencia,marco6,nMarcos));
            break;
            default:
                printf("Cantidad de marcos incorrecta\n");    
            break;
        }
    }else if(strcmp(argv[2],"OPT") == 0){
        printf("Algoritmo: OPTIMO\n");
        switch (nMarcos){
            case 3:
                printf("\nLa cantidad de fallos es: %d\n",opt(referencia,marco3,nMarcos));
            break;
            case 4:
                printf("\nLa cantidad de fallos es: %d\n",opt(referencia,marco4,nMarcos));
            break;
            case 6:
                printf("\nLa cantidad de fallos es: %d\n",opt(referencia,marco6,nMarcos));
            break;
            default:
                printf("Cantidad de marcos incorrecta\n");    
            break;
        }
    } else {
        printf("Algoritmo desconocido\n");
    }
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
    int fallos = 0;
    int tiempo[nMarcos] ;

    /*Si no inicializo en -1 toma el 0 como pagina y puede tener un error*/
    for(int i = 0 ; i<nMarcos ; i++){
        tiempo[i] = -1;
    } 
    /*Voy a almacenar el indice de la ultima referencia que se hizo*/

    for(int i = 0; i < 30; i++){
        printf("\nBuscamos: %d\t", referencia[i]);
        int encontrado = 0;
        // Buscar si la página está en los marcos
        for (int j = 0; j < nMarcos; j++) {
            if (marco[j] == referencia[i]) {
                printf("\t--> %d\t", referencia[i]);
                encontrado = 1;
                tiempo[j] = i;
                break; // No necesitamos seguir buscando en los marcos
            }
        }
        if (!encontrado) {
            int cambiar = 0;

            for (int j = 1; j < nMarcos; j++) {
                if (tiempo[j] < tiempo[cambiar]) {
                    cambiar = j;
                }
            }
            marco[cambiar] = referencia[i]; 
            tiempo[cambiar] = i; 
            printf("\tX-> %d\t", referencia[i]);
            fallos++;
        }
    }
    return fallos;
}
int opt(int referencia[], int marco[], int nMarcos) {
    int fallos = 0;
    int proxima_ocurrencia[nMarcos]; //Voy a guardar el indice de la ultima referencia de cada uno de los marcos
    int i, j, k, max;
        
    for (i = 0; i < nMarcos; i++) {
        int pagina = marco[i];
        for (j = 0; j < 30; j++) {
            if (referencia[j] == pagina) {
                proxima_ocurrencia[i] = j; // Guardamos la próxima ocurrencia de la página
                break;
            }
        }
    }
    
    for (i = nMarcos; i < 30; i++) {
        int fallo = 1;
        for (j = 0; j < nMarcos; j++) {
            if (marco[j] == referencia[i]) { //Inicio la busqueda
                fallo = 0;
            }
        }
        if (fallo) {
            max = 0;

            
            for (j = 1; j < nMarcos; j++) { 
                if (proxima_ocurrencia[j] > proxima_ocurrencia[max]) {
                    max = j;
                }
            }
            marco[max] = referencia[i];
            fallos++;
            for (j = 0; j < nMarcos; j++) {
                if (marco[j] == referencia[i]) {
                    proxima_ocurrencia[j] = -1;
                    break;
                }
            }
            for (j = 0; j < nMarcos; j++) {
                if (proxima_ocurrencia[j] == -1) {
                    continue;
                }
                /*Comprubo cuando van a ocurrir las siguientes referencias a las paginas (Se ahorraria tiempo si
            las supiera desde antes a todas paro no se me ocurre como)*/
                for (k = i + 1; k < 30; k++) {
                    if (referencia[k] == marco[j]) {
                        proxima_ocurrencia[j] = k;
                        break;
                    }
                }
            }
        }
    }
    
    return fallos;
}