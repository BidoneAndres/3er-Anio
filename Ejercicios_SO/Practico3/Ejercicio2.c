#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define COUNT 64
int main(int argc , char* argv[]){
    
    FILE fd;
    char buff[COUNT];
    fd=open("PruebaEj2.txt", O_RDONLY);
    int read;

    while((read=read(fd , buff , COUNT))){
    	printf("%s\n",buff);
    }
    close(fd);
    return 0;
}
