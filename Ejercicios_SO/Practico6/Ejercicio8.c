#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimir( int marcos[] , int nMarcos , int referencia[] , int falloPagina, int i);
int fifo(int referencia[], int marco[], int nMarcos);
int optimo(int referencia[],int marco[], int nMarcos);
int lru(int referencia[],int marco[], int nMarcos);

int main (int argc, char const *argv[]){
    char line[256]; 
    int nMarcos = 0, referencia[30];
    int marco3[3] = {10}, marco4[4] = {10}, marco6[6] = {10};
    //Lectura del archivo
    FILE *archivo = fopen(argv[4] , "r");


    int cantidadProcesos = 0;

    printf("Lee cantidad de marcos...\n");

    fscanf(archivo , "%d" , &nMarcos);
    
    if(archivo == NULL){
        printf("No se abrio el archivo\n");
        exit(1);
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

    if(strcmp(argv[2],"FIF") == 0){
        printf("Algoritmo: FIFO\n");
        switch (nMarcos){
            case 3:
                printf("Llamada a fifo con marco3\n");
                printf("\nLa cantidad de fallos es: %d",fifo(referencia,marco3,nMarcos));
            break;
            case 4:
                printf("Llamada a fifo con marco4\n");
                printf("\nLa cantidad de fallos es: %d",fifo(referencia,marco4,nMarcos));
            break;
            case 6:
                printf("Llamada a fifo con marco6\n");
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
                printf("\nLa cantidad de fallos es: %d",lru(referencia,marco3,nMarcos));
            break;
            case 4:
                printf("Llamada a lru con marco4\n");
                printf("\nLa cantidad de fallos es: %d",lru(referencia,marco3,nMarcos));
            break;
            case 6:
                printf("Llamada a lru con marco6\n");
                printf("\nLa cantidad de fallos es: %d",lru(referencia,marco3,nMarcos));
            break;
            default:
                printf("Cantidad de marcos incorrecta\n");  
            break;
        }
    }else if(strcmp(argv[2],"OPT") == 0){
         printf("Algoritmo: OPTIMO\n");
         switch (nMarcos){
             case 3:
                 printf("Llamada a opt con marco3\n");
             break;
             case 4:
                 printf("Llamada a opt con marco4\n");
             break;
             case 6:
                 printf("Llamada a opt con marco6\n");
             break;
             default:
                 printf("Cantidad de marcos incorrecta\n");    
             break;
         }
     }
    return 0;
}
//Funciones de algoritmos
int fifo(int referencia[], int marco[], int nMarcos){
    printf("Entro");
    int falloPagina = 1;
    int fallos = 0;
    int cambiar = 0;

    printf("M\t");
    for(int m = 0 ; m<nMarcos ; m++){
        printf("%d\t" , m);
    }
    print("\n");
    for(int i = 0 ; i<30 ; i++){
        printf(referencia[i]);
        for(int j = 0 ; j < nMarcos ; nMarcos++){
            if( marco[j] == referencia[i]){
                falloPagina=0;
            }
        }

        if(falloPagina == 1){
            
            marco[cambiar] = referencia[i];
            cambiar++;

            if( cambiar >= nMarcos){
                cambiar = 0;
            }

            fallos++;
        }
        imprimir(marco, nMarcos , referencia, falloPagina , i);

        falloPagina = 1;
    }
    return fallos;
}
int lru(int referencia[],int marco[], int nMarcos){
    int falloPagina = 1;
    int fallos = 0;
    int masPequenio[10] = {0};
    int cambiar = 0;

    printf("M\t");
    for(int m = 0 ; m<nMarcos ; m++){
        printf("%d\t" , m);
    }
    print("\n");

    for(int i = 0 ; i<30 ; i++){
        for(int j = 0 ; j < nMarcos ; nMarcos++){
            if( marco[j] == referencia[i]){
                falloPagina=0;
            }
        }

        if(falloPagina == 1){
            
            //Busco por cual remplazar fijandome cual es el de la referencia mas cercana
            for(int a = 0 ; a < nMarcos ; a++){
                if(masPequenio[marco[a]] < masPequenio[cambiar])
                    cambiar=a;
            }

            marco[cambiar] = referencia[i];
            fallos++;
        }

        for(int b = 0 ; b < 10 ; b++){
            if( b != referencia[i]){
                masPequenio[ b ]++; 
            }
        }
        masPequenio[referencia[i]]=0;

        imprimir(marco, nMarcos , referencia, falloPagina , i);

        falloPagina = 1;
    }
    return fallos;
}

int optimo(int referencia[],int marco[], int nMarcos){
    int cadenaReferencia[9] = {0};
    int fallos = 0;
    int falloPagina = 1;
    int cambiar = 0;

    /*Lo utilizo para saber la cadena de referencias*/
    for( int i = 0 ; i < 30 ; i++){
        cadenaReferencia[referencia[i]]++;
    }

    for( int j = 0 ; j < 30 ; j++){
        
        /*Recorro los marcos*/
        for( int z = 0 ; z < nMarcos ; z++){
            if( marco[z] == referencia[j]){
                falloPagina=0;
            }
        }

        if(falloPagina == 1){
            print("Entro");
            //Busco por cual remplazar basandome en la cadena de referencia
            for(int a = 0 ; a < nMarcos ; a++){
                if(cadenaReferencia[marco[a]] > cadenaReferencia[cambiar]){
                    cambiar=a;
                }
            }

            marco[cambiar] = referencia[j];
            fallos++;
        }

        cadenaReferencia[referencia[j]]--;
        falloPagina = 1;
    }
    return fallos;

}

void imprimir( int marcos[] , int nMarcos , int referencia[] , int falloPagina, int i){
    
    printf("%d" , referencia[i]);
    for(int i = 0 ; i < nMarcos ; i++){
        printf("%d\t" , marcos[i] );
    }
    if( falloPagina == 1){
        printf("*");
    }
    printf("\n");
}