#include<stdio.h>
#include<string.h>
#include<stdlib.h>


// Define the node structure.
struct node{
    node *last=NULL,*next=NULL;
    int data=0;
};



// Set up its head, end and its size;
node *head,*end;
int size=0;



// Validate whether the link is null.
int validate(){
    // Check if the head exists.
    if(head==NULL){
        return -1;
    }

    // Check if the node next to head exists.
    if(head->next==NULL){
        return -2;
    }

    // Check if the end exists.
    if(end==NULL){
        return -3;
    }

    // Check if the node prior to end exists.  
    if(end->last==NULL){
        return -4;
    }

    // If everything works.
    return 0;
}



// Initialize the link.
int initialize(){
    // Set up the head and end.
    head=(node*)calloc(1,sizeof(node));
    end=(node*)calloc(1,sizeof(node));
    head->last=NULL;
    head->data=0;
    end->next=NULL;
    end->data=0;

    // Link the head and the end together.
    head->next=end;
    end->last=head;
    return 0;
}



// Append a node with given data to the link.
int append(int DATA){
    // If the link doesn't work.
    if(validate()){
        return -1;
    }

    // Append the data to the original end.
    end->data=DATA;

    // Create a new node and make it the end.
    node *temp=(node*)calloc(1,sizeof(node));
    end->next=temp;
    temp->last=end;
    end=temp;
    temp->data=0;
    temp->next=NULL;

    // Increase the link's size;
    ++size;
    return 0;
}



// Pop the last node and return its data.
int pop(){
    // If the link doesn't work.
    if(validate()){
        return -1;
    }

    // Locate the node to pop.
    node *temp=end->last,*last=end->last->last;
    last->next=end;
    end->last=last;
    int data=temp->data;

    // Free memory.
    free(temp);

    // Decrease the link's size.
    --size;
    if(size<0){
        size=0;
    }

    //Return the popped value.
    return data;
}


// Print the stack.
int show(){
    // If the link doesn't work.
    if(validate()){
        return -1;
    }

    // Print the list from the end to the head.
    node *temp=end->last;
    printf("  size                    %11d\n",size);
    printf("  index          data        position\n");
    int i=0;
    while(temp!=NULL&&temp!=head&&temp!=end){
        printf("  %5d   %11d   0x%011X\n",i,temp->data,temp);
        temp=temp->last;
        ++i;
    }

    // If everything works.
    return 0;
}

// Free the memory.
int release(){
    // Release the nodes.
    node *temp;
    while(head!=NULL&&temp!=NULL){
        temp=head->next;
        free(head);
        head=temp;
    }

    return 0;
}



// The main function.
int main(int argc,char *argv[]){
    // Check the command.
    if(argc==1||strcmp(argv[1],"-h")==0){
        printf("SimStack 1.0.1 (2022/May/12) - The Stack Simulator!\nUsage: simstack -h       show help\n       simstack -i       enter input mode\n");
        release();
        return 0;
    }
    else if(strcmp(argv[1],"-i")){
        printf("Unknown command! Please check \"simstack -h\" for usage!\n");
        release();
        return -1;
    }

    // Define cli messages.
    char credit[66]="SimStack 1.0.1 (2022/May/12) - The Stack Simulator! [Input Mode]\n";
    char help[249]="Usage:  help              show help\n          push [number...]  push given number(s) to the stack\n          pop  [time]       pop from the stack for given times\n          list              list the stack\n          exit              exit input mode\n";
    char in[12]="simstack> ";

    // Initialize the link.
    initialize();

    // Print the credit.
    printf("  %s",credit);

    // Do the work.
    while(validate()==0){
        // Input.
        printf("%s",in);

        // Get the input.
        char raw[512]={0},*cmd;
        fgets(raw,512,stdin);
        raw[strlen(raw)-1]=0;

        // Split the input.
        cmd=strtok(raw," ");

        // If no input.
        if(cmd==NULL){
            continue;
        }

        // Identify the command.
        if(strcmp(cmd,"help")==0){
            printf("  %s",help);
        }
        else if(strcmp(cmd,"push")==0){
            while(true){
                cmd=strtok(NULL," ");
                if(cmd==NULL){
                    break;
                }
                append(atoi(cmd));
            }
        }
        else if(strcmp(cmd,"pop")==0){
            // How many times to pop.
            int times=1;
            cmd=strtok(NULL," ");
            if (cmd!=NULL){
                times=atoi(cmd);
            }
            if(times>size){
                times=size;
            }

            // Pop for given times.
            for(int i=0;i<times;++i){
                if(head==NULL||head->next==end){
                    break;
                }
                pop();
            }
        }
        else if(strcmp(cmd,"list")==0){
            show();
        }
        else if(strcmp(cmd,"exit")==0){
            release();
            return 0;
        }
        else{
            printf("  Unknown command! Please check \"help\" for usage!\n");
        }
    }

    // Error if list not valid.
    printf("  Fatal error! Please check \"help\" for usage!\n");
    release();
    return -1;
}
