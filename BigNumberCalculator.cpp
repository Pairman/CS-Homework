#include<stdio.h>
#include<string.h>
#include<stdlib.h>



// Check if an operator is legal.
int CheckOp(char op){
    if(op!='+'&&op!='-'){
        return 1;
    }

    return 0;
}



// Check if a number is legal.
int CheckNum(char *str){
    // Get the length of the number, and check if it exceeds the limit.
    int len=strlen(str);
    if(len>508){
        return 1;
    }

    // Check the first digit.
    if(str[0]<'0'||str[0]>'9'){
        if(str[0]!='+'&&str[0]!='-'){
            return 1;
        }
    }

    // Check the other digits.
    for(int i=1;i<len;++i){
        if(str[i]<'0'||str[i]>'9'){
            return 1;
        }
    }

    return 0;
}



// Convert a number from char array to int array;
int *StrToInt(char *str){
    // Create an int array to store the number.
    int *num=(int*)calloc(512,sizeof(int));

    // Store the length and sign of the number at num[1] and num[0].
    int len=strlen(str),i=0;
    switch(str[0]){
        case '+': num[0]=1; num[1]=len-1; i=1; break;
        case '-': num[0]=-1; num[1]=len-1; i=1; break;
        default: num[0]=1; num[1]=len; break;
    }

    // Convert the char array to int array.
    for(int i=512-len;i<512;++i){
        num[i]=str[i-512+len]-'0';
    }

    // Fix the sign and length.
    if(str[0]=='+'||str[0]=='-'){
        num[512-len]=0;
    }
    int nonzero=0;
    for(int i=512-len;i<512;++i){
        if(num[i]){
            ++nonzero;
        }
    }
    if(!nonzero){
        num[0]=1;
    }

    // Fix the length.
    while(num[512-num[1]]==0){
        --num[1];
    }
    if(!num[1]){
        num[1]=1;
    }

    return num;
}



// Compare two numbers' absolute value and return the index of the difference.
int CompareAbs(int *numA,int *numB){
    // If lengths are different.
    if(numA[1]>numB[1]){
        return numA[1];
    }
    else if(numA[1]<numB[1]){
        return -numB[1];
    }

    // If lengths are the same.
    for(int i=512-numA[1];i<512;++i){
        if(numA[i]!=numB[i]){
            if(numA[i]>numB[i]){
                return 512-i;
            }
            else if(numA[i]<numB[i]){
                return -512+i;
            }
        }
    }

    return 0;
}



// Add two numbers together.
int *add(int *numA,int *numB){
    // Create an array for the result and determine its sign.
    int *ret=(int*)calloc(512,sizeof(int)); 
    ret[1]=((numA[1]>=numB[1])?numA[1]:numB[1])+1;
    if(numA[0]==numB[0]){
        ret[0]=numA[0];
    }

    // Do the addition.
    for(int i=511;i>=511-ret[1];--i){

        ret[i]+=numA[i]+numB[i];
        ret[i-1]=ret[i]/10;
        ret[i]%=10;
    }

    // Check whether to increase the length of the result.
    if(ret[512-ret[1]]==0){
        --ret[1];
        }
    // Fix the length.
    while(ret[512-ret[1]]==0){
        --ret[1];
    }
    if(!ret[1]){
        ret[1]=1;
    }

    return ret;
}

// Subtract the second number from the first number.
int *sub(int *numa,int *numb){
    // Create an array for the result and determine its sign.
    int *ret=(int*)calloc(512,sizeof(int));

    // Compare the numbers and determine the sign. Return if the two equal, or swap if needed.
    int cmp=CompareAbs(numa,numb),*numA=nullptr,*numB=nullptr;
    if(cmp==0){
        ret[0]=1;
        ret[1]=1;
        return ret;
    }
    else if(cmp<0){
        ret[1]=-cmp;
        numA=numb;
        numB=numa;
        if(numa[0]>=numb[0]){
            ret[0]=-1;
        }
        else if(numa[0]<numb[0]){
            ret[0]=1;
        }
    }
    else if(cmp>0){
        ret[1]=cmp;
        numA=numa;
        numB=numb;
        if(numa[0]>=numb[0]){
            ret[0]=1;
        }
        else if(numa[0]<numb[0]){
            ret[0]=-1;
        }
    }

    // Do the substraction.
    for(int i=511;i>3;--i){
        if((numA[i]%10)<(numB[i]%10)){
            ret[i]+=10;
            ret[i-1]--;
        }
        ret[i]+=(numA[i]%10)-(numB[i]%10);
    }

    // Fix the length.
    while(ret[512-ret[1]]==0){
        --ret[1];
    }
    if(!ret[1]){
        ret[1]=1;
    }

    return ret;
}

// Print a big number.
void printn(int *num){
    // Print the sign.
    if(num[0]<0){
        printf("-");
    }

    // Print the number, including the fix for zero.
    for(int i=512-num[1];i<512;++i){
        printf("%d",num[i]);
    }
}

// Main function with command-line interfaces.
int main(int argc,char *argv[]){
    // printf("cmp -h: %d\n",strcmp(argv[1],cmdh));
    // printf("cmp -c: %d\n",strcmp(argv[1],cmdc));

    // Check the command.
    if(argc==1||strcmp(argv[1],"-h")==0){
        printf("BigCal 1.0.3 (2022/Jun/26) - Addition or substraction calculator for big numbers!\nUsage: bigcal -h                               show help\n       bigcal -c [number] [operator] [number]  add or substract two numbers for the given operator\n");
        return 0;
    }
    if(argc>5){
        printf("Too many parameters! Please check \"bigcal -h\" for usage!\n");
        return -1;
    }
    if(strcmp(argv[1],"-c")!=0){
        printf("Unknown command! Please check \"bigcal -h\" for usage!\n");
        return -1;
    }
    if(argc!=5){
        printf("Not enough parameters! Please check \"bigcal -h\" for usage!\n");
        return -1;
    }

    // Store the arguments in the expression.
    char op=0,strA[508]={0},strB[508]={0};
    op=argv[3][0];
    strcpy(strA,argv[2]);
    strcpy(strB,argv[4]);

    // Check the expression.
    int chkOp=CheckOp(op),chkStrA=CheckNum(strA),chkStrB=CheckNum(strB);
    if(chkOp){
        printf("Illegal operator! Please check \"bigcal -h\" for usage!\n");
    }
    if(chkStrA||chkStrB){
        printf("Illegal number(s)! Please check \"bigcal -h\" for usage!\n");
    }

    // Standarize the expression.
    if(op=='-'){
        op='+';
        if(strB[0]=='+'){
            strB[0]='-';
        }
        else if(strB[0]=='-'){
            strB[0]='+';
        }
        else{
            char tmp[508]={0};
            tmp[0]='-';
            strcat(tmp+1,strB);
            strcpy(strB,tmp);
        }
    }

    // If valid, convert the numbers.
    int *numA=StrToInt(strA),*numB=StrToInt(strB);

    // See whether to do addition or substraction.
    int *ret=nullptr;
    if(numA[0]==numB[0]){
        ret=add(numA,numB);
    }
    else if(numA[0]==-numB[0]){
        ret=sub(numA,numB);
    }

    // Print the result.
    printn(ret);
    printf("\n");

    // Free the memory and exit the program.
    free(numA);
    free(numB);
    free(ret);
    return 0;
}
