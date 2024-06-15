/*
1) Escriba un programa que muestre en orden todos los argumentos
pasados por linea de comando. Para ello argumente la funcion main()
de su programa de la siguiente manera

	int main(int argc, char *argv[])

De esta manera "argc" contiene la cantidad de elementos de la linea
de comando, mientras que "argv[]" es un array de char que contiene
cada uno de los componentes.

Tip: Solo debe recorrer el arreglo argv imprimiendo su contenidox|

for ( i = 0; i < argc; i++ ) {
  ... argv[i] ...
}

*/
int main(int argc , char* argv[]){
    
    for(int i = 0 ; i < argc ; i++)
        printf("%s\n", argv[i]);
    
    return 0;
}
