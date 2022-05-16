#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int main (int argc,char *argv[]){
    FILE *file=NULL;
    if(argc>=2){
        file=fopen(argv[1],"rb+");
    }
    if(file==NULL){
        perror("No such file or directory");
        return(-1);
    }

    int raw=0;
    if(argc>=3){
        raw=atoi(argv[2]);
    }


    printf("\033[47;30m  \033[0m");
    for(int i=0;i<48;++i){
        if(i%2==0){
            printf("\033[47;30m%02X\033[0m",i);
        }
        else{
            printf("\033[47;31m%02X\033[0m",i);
        }
    }
    printf("\n");

    int bin=0,i=0;
    while(!raw&&!feof(file)){
        if(i%48==0){
            if((i/48)%2==0){
                printf("\033[0m\033[47;30m%02X",i/48);
            }
            else{
                printf("\033[0m\033[47;31m%02X",i/48);
            }
        }

        bin=fgetc(file);
        if(bin==0xFFFFFFFF){
            break;
        }
        else if(bin==0xFF){
            if(i%2==0){
                printf("\033[0;37m%02X\033[0m",bin);
            }
            else{
                printf("\033[1;37m%02X\033[0m",bin);
            }
        }
        else if(bin==0x00){
            if(i%2==0){
                printf("\033[0;30m%02X\033[0m",bin);
            }
            else{
                printf("\033[0;30m%02X\033[0m",bin);
            }
        }
        else{
            if(i%2==0){
                printf("\033[40;32m%02X\033[0m",bin);
            }
            else{
                printf("\033[40;36m%02X\033[0m",bin);
            }
        }
        if((i+1)%48==0){
            printf("\n");
        }
        ++i;
    }
    printf("\033[0m\n");
    while(raw&&!feof(file)){
        bin=fgetc(file);
        printf("%02X",bin);
    }

    fclose(file);
    return(0);
}