#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>



// Generate file with random characters for given length.
int RandomFileGenerator(char OUTPUT_FILENAME[],int OUTPUT_LENGTH){
    // Check the parameters.
    if(OUTPUT_LENGTH<=0){
        printf("Invalid output length! Please check \"rlreader -h\" for usage!\n");
        return -1;
    }
    if(OUTPUT_FILENAME==NULL){
        printf("Invalid output filename! Please check \"rlreader -h\" for usage!\n");
    }

    // Open the file.
    FILE *fileOut=fopen(OUTPUT_FILENAME,"w");
    if(fileOut==NULL){
        printf("Error opening the output file! Please check \"rlreader -h\" for usage!\n");
        fclose(fileOut);
        return -1;
    }

    // Seed for RNG.
    srand(time(0));

    // Write to the file.
    char c=32+rand()%94,cTemp=32+rand()%94;
    int repeat=0;
    for(int i=0;i<OUTPUT_LENGTH;++i){
        repeat=rand()%2;
        if(repeat){
            c=cTemp;
        }
        else{
            c=32+rand()%94;
        }

        fputc(c,fileOut);
        cTemp=c;
    }

    fclose(fileOut);
    return 0;
}



int RunLengthEncoder(char INPUT_FILENAME[],char OUTPUT_FILENAME[]){
    // Open the files and check the parameters.
    FILE *fileIn=fopen(INPUT_FILENAME,"r"),*fileOut=fopen(OUTPUT_FILENAME,"w");
    if(fileIn==NULL){
        printf("No such input file or directory! Please check \"rlreader -h\" for usage!\n");
        fclose(fileIn);
        fclose(fileOut);
        return -1;
    }
    if(fileOut==NULL){
        printf("Error opening the output file! Please check \"rlreader -h\" for usage!\n");
        fclose(fileIn);
        fclose(fileOut);
        return -1;
    }

    // Do the encoding work.
    char c=fgetc(fileIn),cTemp=0;
    unsigned char repeat=1;
    cTemp=c;
    while(!feof(fileIn)){
        // Overflow detection.
        if(repeat==255){
            fputc(repeat,fileOut);
            fputc(c,fileOut);
            repeat=0;
            continue;
        }

        // Read the current character.
        c=fgetc(fileIn);

        // New character detection.
        if(c==cTemp){
            ++repeat;
        }
        else{
            fputc(repeat,fileOut);
            fputc(cTemp,fileOut);
            repeat=1;
            cTemp=c;
        }
    }

    fclose(fileIn);
    fclose(fileOut);
    return 0;
}



int RunLengthDecoder(char INPUT_FILENAME[],char OUTPUT_FILENAME[]){
    // Open the files and check the parameters.
    FILE *fileIn=fopen(INPUT_FILENAME,"r"),*fileOut=fopen(OUTPUT_FILENAME,"w");
    if(fileIn==NULL){
        printf("No such input file or directory! Please check \"rlreader -h\" for usage!\n");
        fclose(fileIn);
        fclose(fileOut);
        return -1;
    }
    if(fileOut==NULL){
        printf("Error opening the output file! Please check \"rlreader -h\" for usage!\n");
        fclose(fileIn);
        fclose(fileOut);
        return -1;
    }

    // Do the decoding work.
    char c=0;
    unsigned char repeat=0;
    while(true){
        // Read the input file.
        repeat=fgetc(fileIn);
        c=fgetc(fileIn);

        // EOF Detection.
        if(feof(fileIn)){
            break;
        }

        // Write to the output file.
        for(int i=0;i<repeat;++i){
            fputc(c,fileOut);
        }
    }

    fclose(fileIn);
    fclose(fileOut);
    return 0;
}



int main(int argc,char *argv[]){
    // Check the command.
    if(argc==1||strcmp(argv[1],"-h")==0){
        printf("RunLengthReader 1.0.0 (2022/May/16) - Decoder and encoder for 8-bit RLE compression!\nUsage: rlreader -h                  show help\n       rlreader -e [file] [file]    encode the first file and output to the second file.\n       rlreader -d [file] [file]    decode the first file and output to the second file.\n       rlreader -g [file] [length]  generate a file of random visible characters for given length.\n");
        return 0;
    }
    if(argc<4){
        printf("Not Enough parameters! Please check \"rlreader -h\" for usage!\n");
        return -1;
    }
    if(argc>4){
        printf("Too many parameters! Please check \"rlreader -h\" for usage!\n");
        return -1;
    }
    if(strcmp(argv[1],"-e")&&strcmp(argv[1],"-d")&&strcmp(argv[1],"-g")){
        printf("Unknown command! Please check \"bmzoomer -h\" for usage!\n");
        return -1;
    }
    if(strcmp(argv[1],"-e")==0){
        RunLengthEncoder(argv[2],argv[3]);
    }
    if(strcmp(argv[1],"-d")==0){
        RunLengthDecoder(argv[2],argv[3]);
    }
    if(strcmp(argv[1],"-g")==0){
        RandomFileGenerator(argv[2],atoi(argv[3]));
    }

    return 0;
}