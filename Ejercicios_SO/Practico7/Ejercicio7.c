#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MEM_TOTAL 64
#define MEM_PI 8

int proxId = 1;

struct mem
{
    int id;
    int procesoAsignado;
    int espacioMem;
    int espacioOcupado;
    struct mem *next;
};

struct mem *crearParticionMemoria(int pAsignado, int eMem)
{
    struct mem *nuevoNodo = (struct mem *)malloc(sizeof(struct mem));
    if (nuevoNodo == NULL)
    {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    nuevoNodo->id = proxId;
    nuevoNodo->procesoAsignado = pAsignado;
    nuevoNodo->espacioMem = eMem;
    nuevoNodo->espacioOcupado = eMem;
    nuevoNodo->next = NULL;
    proxId++;
    return nuevoNodo;
}

struct mem *buscarProcesoEnMemoria(struct mem **cabeza, int pAsignado)
{
    struct mem *temp = *cabeza;
    while (temp != NULL)
    {
        if (temp->procesoAsignado == pAsignado)
        {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

int liberarProcesoMemoria(struct mem *cabeza, int pAsignado)
{
    struct mem *temp = cabeza;
    while (temp != NULL)
    {
        if ((temp->procesoAsignado) == pAsignado)
        {

            (temp->procesoAsignado) = 0;
            (temp->espacioOcupado) = 0;
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

void imprimirListadoEnMemoria(struct mem *cabeza)
{
    struct mem *temp = cabeza;
    while (temp != NULL)
    {
        printf("ID:%d\tProceso asignado:%d\tEspacio memoria:%d\tEspacio ocupado:%d\n", temp->id, temp->procesoAsignado, temp->espacioMem, temp->espacioOcupado);
        temp = temp->next;
    }
}

struct mem *checkearMemoriaDisponible(struct mem **cabeza, int mem)
{
    struct mem *temp = *cabeza;
    while (temp != NULL)
    {
        if ((temp->procesoAsignado == 0) & (temp->espacioMem >= mem))
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
struct mem *buscarMemoriaPorId(struct mem **cabeza, int ident)
{
    struct mem *temp = *cabeza;
    while (temp != NULL)
    {
        if ((temp->id) == ident)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
int buscarHuecosWorstFit(struct mem **cabeza, int mem)
{
    struct mem *temp = *cabeza;
    int i = 0;
    int arrayDeHuecos[50] = {0};
    while (temp != NULL)
    {
        if ((temp->procesoAsignado == 0) & (temp->espacioMem >= mem))
        {
            arrayDeHuecos[i] = temp->id;
            i++;
        }
        temp = temp->next;
    }
    i = 0;
    int mejorId = 0;
    int fragInterna = 0;
    while (arrayDeHuecos[i] != 0)
    {
        temp = buscarMemoriaPorId(cabeza, arrayDeHuecos[i]);
        printf("**Buscando %d\n", arrayDeHuecos[i]);
        if (i == 0)
        {
            mejorId = arrayDeHuecos[i];
            fragInterna = (temp->espacioMem) - mem;
            i++;
        }
        else
        {

            if (fragInterna < ((temp->espacioMem) - mem))
            {
                mejorId = arrayDeHuecos[i];
                fragInterna = (temp->espacioMem) - mem;
                i++;
            }
            else
            {
                i++;
            }
        }
    }
    // printf("MEJOR ID PARA WORST FIT:%d por %d\n",mejorId,fragInterna);
    /*printf("nodos con huecos:\n");
for(int j=0;j<5;j++){
    printf("%d\n",arrayDeHuecos[j]);
}*/
    return mejorId;
}
int buscarHuecosBestFit(struct mem **cabeza, int mem)
{
    struct mem *temp = *cabeza;
    int i = 0;
    int arrayDeHuecos[50] = {0};
    while (temp != NULL)
    {
        if ((temp->procesoAsignado == 0) & (temp->espacioMem >= mem))
        {
            arrayDeHuecos[i] = temp->id;
            i++;
        }
        temp = temp->next;
    }
    i = 0;
    int mejorId = 0;
    int fragInterna = 0;
    while (arrayDeHuecos[i] != 0)
    {
        temp = buscarMemoriaPorId(cabeza, arrayDeHuecos[i]);
        printf("**Buscando %d\n", arrayDeHuecos[i]);
        if (i == 0)
        {
            mejorId = arrayDeHuecos[i];
            fragInterna = (temp->espacioMem) - mem;
            i++;
        }
        else
        {

            if (fragInterna > ((temp->espacioMem) - mem))
            {
                mejorId = arrayDeHuecos[i];
                fragInterna = (temp->espacioMem) - mem;
                i++;
            }
            else
            {
                i++;
            }
        }
    }
    // printf("MEJOR ID PARA BEST FIT:%d por %d\n",mejorId,fragInterna);
    /* printf("nodos con huecos:\n");
 for(int j=0;j<5;j++){
     printf("%d\n",arrayDeHuecos[j]);
 }*/
    return mejorId;
}

struct mem *agregarParticion(struct mem **cabeza, int pAsignado, int eMem)
{
    struct mem *nuevoNodo = crearParticionMemoria(pAsignado, eMem);
    int acum = 0;
    // primer nodo:
    if (*cabeza == NULL && (nuevoNodo->espacioMem <= 56))
    {
        *cabeza = nuevoNodo;
        return nuevoNodo;
    }
    else
    {
        struct mem *temp = checkearMemoriaDisponible(cabeza, eMem);
        if (temp != NULL)
        { // encontro un lugar desocupado que entre
            temp->espacioOcupado = eMem;
            temp->procesoAsignado = pAsignado;
            return temp;
        }
        else
        {
            temp = *cabeza;
            while (temp->next != NULL)
            {
                acum = acum + temp->espacioMem;
                temp = temp->next;
            }
            if (56 - acum >= eMem)
            {
                temp->next = nuevoNodo;
                return nuevoNodo;
            }
            printf("ERROR AL ASIGNAR MEMORIA PARA PROCESO %d\n", pAsignado);
            return NULL;
        }
    }
}


struct mem *agregarParticionBestFit(struct mem **cabeza, int pAsignado, int eMem)
{
    struct mem *nuevoNodo = crearParticionMemoria(pAsignado, eMem);
    int acum = 0;
    // primer nodo:
    if (*cabeza == NULL && (nuevoNodo->espacioMem <= 56))
    {
        *cabeza = nuevoNodo;
        return nuevoNodo;
    }
    else
    {
        struct mem *temp =NULL;
        int idBestFit=buscarHuecosBestFit(cabeza,eMem);
        if(idBestFit!=0){
            temp = buscarMemoriaPorId(cabeza, idBestFit);
             temp->espacioOcupado = eMem;
            temp->procesoAsignado = pAsignado;
            printf("INGRESANDO PROCESO EN HUECO\n");
            return temp;
        }
        
        else
        {
            temp = *cabeza;
            while (temp->next != NULL)
            {
                acum = acum + temp->espacioMem;
                temp = temp->next;
            }
            if (56 - acum >= eMem)
            {
                temp->next = nuevoNodo;
                return nuevoNodo;
            }
            printf("ERROR AL ASIGNAR MEMORIA PARA PROCESO %d\n", pAsignado);
            return NULL;
        }
    }
}

struct mem *agregarParticionWorstFit(struct mem **cabeza, int pAsignado, int eMem)
{
    struct mem *nuevoNodo = crearParticionMemoria(pAsignado, eMem);
    int acum = 0;
    // primer nodo:
    if (*cabeza == NULL && (nuevoNodo->espacioMem <= 56))
    {
        *cabeza = nuevoNodo;
        return nuevoNodo;
    }
    else
    {
        struct mem *temp =NULL;
        int idBestFit=buscarHuecosWorstFit(cabeza,eMem);
        if(idBestFit!=0){
            temp = buscarMemoriaPorId(cabeza, idBestFit);
             temp->espacioOcupado = eMem;
            temp->procesoAsignado = pAsignado;
            printf("INGRESANDO PROCESO EN HUECO\n");
            return temp;
        }
        
        else
        {
            temp = *cabeza;
            while (temp->next != NULL)
            {
                acum = acum + temp->espacioMem;
                temp = temp->next;
            }
            if (56 - acum >= eMem)
            {
                temp->next = nuevoNodo;
                return nuevoNodo;
            }
            printf("ERROR AL ASIGNAR MEMORIA PARA PROCESO %d\n", pAsignado);
            return NULL;
        }
    }
}
int main(int argc, char const *argv[])
{

    int numProcesos;
    char algoritmo[3];
    int procesos[50][4];
    strcat(algoritmo, argv[3]);

    // valido el algoritmo elegido
    if (strcmp(algoritmo, "PI") && (strcmp(algoritmo, "PD")) && (strcmp(algoritmo, "DPA")) && (strcmp(algoritmo, "DFF")) && (strcmp(algoritmo, "DWF")))
    {
        printf("ALGORITMO %s NO RECONOCIDO\n", algoritmo);
        exit(1);
    }

    // Procesado del archivo
    FILE *file;
    int num;
    int contador = 0;
    int bufferAux[100];
    file = fopen("input_file.txt", "r");
    while (fscanf(file, "%d", &num) != EOF)
    {
        if (contador == 0)
        {
            numProcesos = num;
            contador++;
        }
        else
        {
            bufferAux[contador - 1] = num;
            contador++;
        }
    }
    printf("Cantidad de procesos:%d\n", numProcesos);

    for (int i = 0; i < numProcesos; i++)
    {
        procesos[i][0] = bufferAux[4 * i];
        procesos[i][1] = bufferAux[4 * i + 1];
        procesos[i][2] = bufferAux[4 * i + 2];
        procesos[i][3] = bufferAux[4 * i + 3];
    }
    printf("PID\tARRT\tTAM\tFINALT\t\n");
    int tTotal = 0;
    for (int i = 0; i < numProcesos; i++)
    {
        printf("%d\t%d\t%d\t%d\t\n", procesos[i][0], procesos[i][1], procesos[i][2], procesos[i][3]);
        // para ver hasta cuanto tiene que mostrarse como se ordenan los procesos e memoria
        if (i == 0)
        {
            tTotal = procesos[i][3] + procesos[i][1];
        }
        else
        {
            if (procesos[i][3] + procesos[i][1] > tTotal)
            {
                tTotal = procesos[i][3] + procesos[i][1]; // tiempo maximo de ejecucion
            }
        }
    }

    printf("TIEMPO DE EJECUCION DE TODO EL PROGRAMA:%dseg", tTotal);

    printf("\nArrancando simuacion...\n");
    printf("Memoria total:%dmb\n", MEM_TOTAL);

    int memDisponible;
    int counter = 0;

    int memPartida[MEM_PI] = {0}; // defino mi memoria  partida en MEM_PI
    memPartida[7] = 100;          // ocupada por el sistema operativo
    int memoriaOcupadaPorProceso[MEM_PI] = {0};
    memoriaOcupadaPorProceso[MEM_PI - 1] = 100;

    int memoriaPorParticion;
    // stats:
    int usoMemoria = 0;
    int fallos = 0;
    int fragmentacionInterna = 0;
    int fragmentacionExterna = 0;
    int procesosEjecutados=numProcesos;
    // PI:
    if (!strcmp(algoritmo, "PI"))
    {
        memDisponible = MEM_TOTAL - MEM_PI;
        memoriaPorParticion = MEM_TOTAL / MEM_PI; // defino cuanta memoria tiene cada bloque

        printf("Algoritmo elegido:Particion fija de igual tamano\n");
        printf("Creando particiones de igual tamano de %dmb...\n", MEM_PI);
        printf("Memoria dispnible:%dmb, el sistema operativo ocupa 8mb\n", memDisponible);

        printf("\t");
        for (int i = 0; i < MEM_PI; i++)
        {
            printf("\tP[%d](%dmb)", i + 1, memoriaPorParticion);
        }
        printf("\n");

        while (counter < tTotal)
        {
            // proceso entrada
            for (int i = 0; i < numProcesos; i++)
            {
                if (counter == procesos[i][1])
                { // significa que arribo un proceso
                    for (int j = 0; j < MEM_PI; j++)
                    { // busco memoria disponible
                        if (memPartida[j] == 0 && (memoriaPorParticion >= procesos[i][2]))
                        {
                            memPartida[j] = procesos[i][0];
                            memoriaOcupadaPorProceso[j] = procesos[i][2];

                            usoMemoria += procesos[i][2];
                            fragmentacionInterna += memoriaPorParticion - procesos[i][2];
                            break;
                        }
                        else
                        {
                            if (j == MEM_PI - 2)
                            {
                                printf("FALLO\n");
                                fallos++;
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < numProcesos; i++)
            {
                if (counter == (procesos[i][1] + procesos[i][3]))
                {
                    for (int j = 0; j < MEM_PI; j++)
                    {
                        if (memPartida[j] == procesos[i][0])
                        {
                            memPartida[j] = 0;
                            memoriaOcupadaPorProceso[j] = 0;
                        }
                    }
                }
            }

            if (counter <= 9)
            {
                printf("t=%dseg:\t", counter);
            }
            else
            {
                printf("t=%dseg:", counter);
            }
            printf("\t");
            for (int i = 0; i < MEM_PI; i++)
            {
                if (memPartida[i] == 100)
                {
                    printf("SO(8mb)   \t");
                }
                else
                {
                    printf("%d(%dmb)   \t", memPartida[i], memoriaOcupadaPorProceso[i]);
                }
            }
            printf("\n");

            // para impresion mas rapida
            if (counter % 10 == 0)
            {
                sleep(1);
            }
            counter++;
        }
    }

    if (!strcmp(algoritmo, "PD"))
    {
        printf("Algoritmo elegido:Particion fija de distinto tamano\n");
        // definimos como vamos a particionar la memoria
        int capacidadMemoria[10] = {8, 4, 6, 8, 5, 5, 4, 8, 8, 8};
        int cantidadDeParticiones = 10; // en este caso
        int memoria[10][3] = {0};
        memoria[9][1] = 100; // SO
        // MEMORIA
        // capacidad de memoria|id del proceso guardado|Tamano del proceso guardado
        for (int i = 0; i < cantidadDeParticiones; i++)
        {
            memoria[i][0] = capacidadMemoria[i];
            printf("P[%d](%dmb),", i + 1, memoria[i][0]);
        }
        printf("\n");

        // printf("\t");
        for (int i = 0; i < cantidadDeParticiones; i++)
        {
            printf("P[%d](%dmb)\t", i + 1, memoria[i][0]);
        }
        printf("\n");

        while (counter < tTotal)
        {
            // proceso entrada
            for (int i = 0; i < numProcesos; i++)
            {
                if (counter == procesos[i][1])
                { // significa que arribo un proceso
                    for (int j = 0; j < cantidadDeParticiones; j++)
                    { // busco memoria disponible
                        if (memoria[j][1] == 0 && (memoria[j][0] >= procesos[i][2]))
                        {
                            memoria[j][1] = procesos[i][0]; // asigno el id a la memoria
                            memoria[j][2] = procesos[i][2]; // asigno la memoria que ocupa el proceso

                            usoMemoria += procesos[i][2];
                            fragmentacionInterna += memoria[i][0] - procesos[i][2];
                            break;
                        }
                        else
                        {
                            if (j == (cantidadDeParticiones - 2))
                            {
                                printf("FALLO\n");
                                fallos++;
                            }
                        }
                    }
                }
            }
            // salida de proceso
            for (int i = 0; i < numProcesos; i++)
            {
                if (counter == (procesos[i][1] + procesos[i][3]))
                {
                    for (int j = 0; j < MEM_PI; j++)
                    {
                        if (memoria[j][1] == procesos[i][0])
                        {
                            memoria[j][1] = 0;
                            memoria[j][2] = 0;
                        }
                    }
                }
            }
            /*
                        if (counter <= 9)
                        {
                            printf("t=%dseg:\t", counter);
                        }
                        else
                        {
                            printf("t=%dseg:", counter);
                        }
                        printf("\t");*/
            for (int i = 0; i < cantidadDeParticiones; i++)
            {
                if (memoria[i][1] == 100)
                {
                    printf("SO(8mb)   \t");
                }
                else
                {
                    printf("%d(%dmb)   \t", memoria[i][1], memoria[i][2]);
                }
            }
            printf("\n");

            // para impresion mas rapida
            if (counter % 10 == 0)
            {
                sleep(1);
            }
            counter++;
        }
    }

    // asignacion dinamica
    if (!strcmp(algoritmo, "DPA"))
    {

        printf("Algoritmo elegido:Primer ajuste (dinmico)\n");
        struct mem *cabeza = NULL;
        while (counter < tTotal)
        {
            // proceso entrada
            for (int i = 0; i < numProcesos; i++)
            {
                if (counter == procesos[i][1])
                {

                    struct mem *temp = agregarParticion(&cabeza, procesos[i][0], procesos[i][2]);
                    if (temp == NULL)
                    {
                        fallos++; // no se pudo asignar memoria a este proceso
                        procesos[i][0]=0;
                        procesos[i][1]=0;
                        procesos[i][2]=0;
                        procesos[i][3]=0;
                        procesosEjecutados--;
                    }
                    else{
                    printf("\nTiempo:%d, entrada de proceso %d(%dmb)\n", counter, procesos[i][0],procesos[i][2]);
                    imprimirListadoEnMemoria(cabeza);
                    fragmentacionInterna+=(temp->espacioMem)-(temp->espacioOcupado);
                    }
                    
                }
            }

            // proceso salida
            for (int i = 0; i < numProcesos; i++)
            {
                if (counter == (procesos[i][1] + procesos[i][3]))
                {
                    liberarProcesoMemoria(cabeza, procesos[i][0]);
                    printf("\nTiempo:%d, salida de proceso %d\n", counter, procesos[i][0]);
                    imprimirListadoEnMemoria(cabeza);
                }
            }

            counter++;
        }
        //contamos fragmentacion externa como el promedio de los huecos
        struct mem* temp=cabeza;
        int j=0;
        int acumulador=0;
        while(temp->next!=NULL){
            acumulador+=temp->espacioMem;
            j++;
            temp=temp->next;
        }
        fragmentacionExterna=acumulador/j;
    }
if (!strcmp(algoritmo, "DFF"))
    {

        printf("Algoritmo elegido:Mejor ajuste (dinmico)\n");
        struct mem *cabeza = NULL;
        while (counter < tTotal)
        {
            // proceso entrada
            for (int i = 0; i < numProcesos; i++)
            {
                if (counter == procesos[i][1])
                {

                    struct mem *temp = agregarParticionBestFit(&cabeza, procesos[i][0], procesos[i][2]);
                    if (temp == NULL)
                    {
                        fallos++; // no se pudo asignar memoria a este proceso
                        procesos[i][0]=0;
                        procesos[i][1]=0;
                        procesos[i][2]=0;
                        procesos[i][3]=0;
                        procesosEjecutados--;
                    }
                    else{
                    printf("\nTiempo:%d, entrada de proceso %d(%dmb)\n", counter, procesos[i][0],procesos[i][2]);
                    imprimirListadoEnMemoria(cabeza);
                    fragmentacionInterna+=(temp->espacioMem)-(temp->espacioOcupado);
                    usoMemoria+=temp->espacioOcupado;
                    }
                    
                }
            }

            // proceso salida
            for (int i = 0; i < numProcesos; i++)
            {
                if (counter == (procesos[i][1] + procesos[i][3]))
                {
                    liberarProcesoMemoria(cabeza, procesos[i][0]);
                    printf("\nTiempo:%d, salida de proceso %d\n", counter, procesos[i][0]);
                    imprimirListadoEnMemoria(cabeza);
                }
            }

            counter++;
        }
        //contamos fragmentacion externa como el promedio de los huecos
        struct mem* temp=cabeza;
        int j=0;
        int acumulador=0;
        while(temp->next!=NULL){
            acumulador+=temp->espacioMem;
            j++;
            temp=temp->next;
        }
        fragmentacionExterna=acumulador/j;
    }

if (!strcmp(algoritmo, "DWF"))
    {

        printf("Algoritmo elegido:Mejor ajuste (dinmico)\n");
        struct mem *cabeza = NULL;
        while (counter < tTotal)
        {
            // proceso entrada
            for (int i = 0; i < numProcesos; i++)
            {
                if (counter == procesos[i][1])
                {

                    struct mem *temp = agregarParticionWorstFit(&cabeza, procesos[i][0], procesos[i][2]);
                    if (temp == NULL)
                    {
                        fallos++; // no se pudo asignar memoria a este proceso
                        procesos[i][0]=0;
                        procesos[i][1]=0;
                        procesos[i][2]=0;
                        procesos[i][3]=0;
                        procesosEjecutados--;
                    }
                    else{
                    printf("\nTiempo:%d, entrada de proceso %d(%dmb)\n", counter, procesos[i][0],procesos[i][2]);
                    imprimirListadoEnMemoria(cabeza);
                    fragmentacionInterna+=(temp->espacioMem)-(temp->espacioOcupado);
                    usoMemoria+=temp->espacioOcupado;
                    }
                    
                }
            }

            // proceso salida
            for (int i = 0; i < numProcesos; i++)
            {
                if (counter == (procesos[i][1] + procesos[i][3]))
                {
                    liberarProcesoMemoria(cabeza, procesos[i][0]);
                    printf("\nTiempo:%d, salida de proceso %d\n", counter, procesos[i][0]);
                    imprimirListadoEnMemoria(cabeza);
                }
            }

            counter++;
        }
        //contamos fragmentacion externa como el promedio de los huecos
        struct mem* temp=cabeza;
        int j=0;
        int acumulador=0;
        while(temp->next!=NULL){
            acumulador+=temp->espacioMem;
            j++;
            temp=temp->next;
        }
        fragmentacionExterna=acumulador/j;
    }



    usoMemoria += 8; // por uso de SO
    printf("FALLOS TOTALES:%d\n", fallos);
    printf("MEMORIA USADA %dmb\n", usoMemoria);
    printf("FRAGMENTACION INTERNA PROMEDIO: %0.2f0mb\n", (float)fragmentacionInterna / procesosEjecutados);
    printf("FRAGMENTACION EXTERNA PROMEDIO:%f\n",(float) fragmentacionExterna);
    return 0;
}