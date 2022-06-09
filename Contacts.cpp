#include<iostream>
#include<stdlib.h>
#include<string.h>



// Define the contact structor.
struct Contact{
    char name[24]={0},phone[24]={0},email[24]={0},address[24]={0},work[24]={0};
};
unsigned char countContacts=0;
Contact contacts[256];



// Match the keyword in the second string
int strmatch(char keyword[],char str[]){
    // Allocate memory for later use
    char *clip=(char*)calloc(strlen(keyword),sizeof(char));

    // Match the characters
    for(int i=0;i<=strlen(str)-strlen(keyword);++i){
        // Clip the str into clip
        for(int j=0;j<strlen(keyword);++j){
            clip[j]=str[i+j];
        }
        // Compare the keyword and the clipped
        if(!strcmp(keyword,clip)){
            free(clip);
            return 1;
        }
    }

    // Return 0 if no occurences
    free(clip);
    return 0;
}



// Show one contact by given index;
int show(unsigned char index){
    // Contact validation.
    if(index>=countContacts){
        return -1;
    }

    // Show the given contact.
    printf("%5d  %24s  %24s  %24s  %24s  %24s\n",index,contacts[index].name,contacts[index].phone,contacts[index].email,contacts[index].address,contacts[index].work);
    return 0;
}



// List the contacts.
int list(){
    printf("\033[47;30mList the contacts.\033[0m\n");

    // Show one by one.
    printf("%s  %24s  %24s  %24s  %24s  %24s\n","Index","Name","Phone","Email","Address","Work");
    for(unsigned char index=0;index<countContacts;++index){
        show(index);
    }

    // Show the statistics.
    printf("Stored %d contacts in total 256 slots.\n",countContacts);

    return 0;
}



// Add a contact to the contacts.
int add(){
    printf("\033[47;30mAdd a contact to the contacts.\033[0m\n");

    // Input and check the name and phone number.
    Contact contactToAdd;
    printf("(No more than 23 characters) Please input the name: ");
    std::cin.getline(contactToAdd.name,23);
    if(strcmp(contactToAdd.name,"")==0){
        printf("Invalid name!\n");
        return -1;
    }
    printf("(No more than 23 characters and no spaces) Please input the phone number: ");
    std::cin.getline(contactToAdd.phone,23);
    if(strcmp(contactToAdd.phone,"")==0){
        printf("Invalid phone number!\n");
        return -1;
    }
    for(int i=0;i<strlen(contactToAdd.phone);++i){
        if(contactToAdd.phone[i]<'0'||contactToAdd.phone[i]>'9'){
            printf("Invalid phone number!\n");
            return -1;
        }
    }

    // Repetition detection.
    for(int index=0;index<countContacts;++index){
        if(strcmp(contacts[index].phone,contactToAdd.phone)==0){
            printf("Same phone number exists thus not added!\n");
            return -1;
        }
    }

    // Input other information.
    printf("(Optional) (No more than 23 characters and no spaces) Please input the email: ");
    std::cin.getline(contactToAdd.email,23);
    for(int i=0;i<strlen(contactToAdd.email);++i){
        if((contactToAdd.email[i]<'0'||contactToAdd.email[i]>'9')){
            if((contactToAdd.email[i]<'a'||contactToAdd.email[i]>'z')&&(contactToAdd.email[i]<'A'||contactToAdd.email[i]>'Z')){
                if(contactToAdd.email[i]!='@'&&contactToAdd.email[i]!='_'&&contactToAdd.email[i]!='-'&&contactToAdd.email[i]!='.'){
                    printf("Invalid email!\n");
                    return -1;
                }
            }
        }
    }
    // Check whether contains '@'
    int emailContainAt=0;
    for(int i=0;i<strlen(contactToAdd.email);++i){
        if(contactToAdd.email[i]=='@'){
            emailContainAt=1;
        }
    }
    if(strlen(contactToAdd.email)==0){
        emailContainAt=1;
    }
    if(!emailContainAt){
        printf("Invalid email!\n");
        return -1;
    }
    // Repetition detection.
    for(int index=0;index<countContacts;++index){
        if(strcmp(contacts[index].email,contactToAdd.email)==0){
            printf("Same email exists thus not added!\n");
            return -1;
        }
    }
    printf("(Optional) (No more than 23 characters) Please input the address: ");
    std::cin.getline(contactToAdd.address,23);
    printf("(Optional) (No more than 23 characters) Please input the work: ");
    std::cin.getline(contactToAdd.work,23);

    contacts[countContacts]=contactToAdd;

    // Update the size of the contact with overflow detection.
    if(countContacts<255){
        ++countContacts;
    }
    printf("Contact added successfully.\n");
    return 0;
}



// Search in the contacts by name or phone number.
int search(){
    printf("\033[47;30mSearch in the contacts by name or phone number.\033[0m\n");

    // Input the search keyword.
    char input[24]={0},search[24]={0};
    int select=0;
    int countResults=0,equalResults[255]={0};
    printf("Please input the search keyword: ");
    std::cin.getline(search,23);

    // Search
    for(int i=0;i<countContacts;++i){
        if(strmatch(search,contacts[i].name)||strmatch(search,contacts[i].phone)||strmatch(search,contacts[i].email)||strmatch(search,contacts[i].address)||strmatch(search,contacts[i].work)){
            equalResults[i]=1;
            ++countResults;
        }
    }

    // Show the results.
    if(countResults){
        printf("%s  %24s  %24s  %24s  %24s  %24s\n","Index","Name","Phone","Email","Address","Work");
        for(int index=0;index<countContacts;++index){
            if(equalResults[index]){
                show(index);
            }
        }
    }

    // Show the statistics after the search.
    printf("Found %d search results among %d contacts.\n",countResults,countContacts);
    return 0;
}



// Remove a contact from the contacts by index.
int remove(){
    printf("\033[47;30mRemove a contact from the contacts by index.\033[0m\n");

    // Get and check the index.
    printf("Please input index for the contact to remove: ");
    char input[24]={0};
    std::cin.getline(input,23);
    int index=atoi(input);
    if(index<0||index>=countContacts){
        printf("Invalid index to remove!\n");
        return -1;
    }

    printf("Are you sure to remove this contact?\n");
    printf("%s  %24s  %24s  %24s  %24s  %24s\n","Index","Name","Phone","Email","Address","Work");
    show(index);
    printf("Input the index again to confirm: ");
    char confirmInput[24]={0};
    std::cin.getline(confirmInput,23);
    int confirmIndex=atoi(confirmInput);
    if(confirmIndex!=index){
        printf("Abort contact removal.\n");
        return -1;
    }

    // Erase the target contact.
    Contact contactNew;
    contacts[index]=contactNew;

    // Resort the erased contacts to the end.
    for(int indexI=0;indexI<countContacts;++indexI){
        for(int indexJ=0;indexJ<countContacts-indexI-1;++indexJ){
            if(strcmp(contacts[indexJ].name,contactNew.name)==0||strcmp(contacts[indexJ].phone,contactNew.phone)==0){
                contacts[indexJ]=contacts[indexJ+1];
                contacts[indexJ+1]=contactNew;
            }
        }
    }

    // Update the size of the contact with overflow detection.
    if(countContacts!=0){
        --countContacts;
    }

    printf("Contact removed successfully.\n");
    return 0;
}



// Modify a contact in the contacts by index.
int modify(){
    printf("\033[47;30mModify a contact in the contacts by index.\033[0m\n");

    // Get and check the index.
    printf("Please input index for the contact to modify: ");
    char input[24]={0};
    int select=0;
    std::cin.getline(input,23);
    int index=atoi(input);
    if(input[0]<'0'||input[0]>'9')
    if(index<0||index>=countContacts){
        printf("Invalid index to modify!\n");
        return -1;
    }

    // Copy the target contact and modify.
    Contact contactInput=contacts[index];
    printf("Modify the name? \"1\"/other for yes/no: ");
    std::cin.getline(input,23);
    select=atoi(input);
    if(select==1){
        printf("(No more than 23 characters) Please input the new name: ");
        std::cin.getline(contactInput.name,23);

    }

    printf("Modify the phone number? \"1\"/other for yes/no: ");
    std::cin.getline(input,23);
    select=atoi(input);
    if(select==1){
        printf("(No more than 23 characters and no spaces) Please input the new phone number: ");
        std::cin.getline(contactInput.phone,23);
    }
    if(strcmp(contactInput.phone,"")==0){
        printf("Invalid phone number!\n");
        return -1;
    }
    for(int i=0;i<strlen(contactInput.phone);++i){
        if(contactInput.phone[i]<'0'||contactInput.phone[i]>'9'){
            printf("Invalid phone number!\n");
            return -1;
        }
    }
    // Repetition detection.
    for(int i=0;i<countContacts;++i){
        if(i!=index&&strcmp(contacts[i].phone,contactInput.phone)==0){
            printf("Same phone number exists thus not modified!\n");
            return -1;
        }
    }

    printf("Modify the email? \"1\"/other for yes/no: ");
    std::cin.getline(input,23);
    select=atoi(input);
    if(select==1){
        printf("(No more than 23 characters and no spaces) Please input the new email: ");
        std::cin.getline(contactInput.email,23);
    }
    for(int i=0;i<strlen(contactInput.email);++i){
        if((contactInput.email[i]<'0'||contactInput.email[i]>'9')){
            if((contactInput.email[i]<'a'||contactInput.email[i]>'z')&&(contactInput.email[i]<'A'||contactInput.email[i]>'Z')){
                if(contactInput.email[i]!='@'&&contactInput.email[i]!='_'&&contactInput.email[i]!='-'&&contactInput.email[i]!='.'){
                    printf("Invalid email!\n");
                    return -1;
                }
            }
        }
    }
    // Check whether contains '@'
    int emailContainAt=0;
    for(int i=0;i<strlen(contactInput.email);++i){
        if(contactInput.email[i]=='@'){
            emailContainAt=1;
        }
    }
    if(strlen(contactInput.email)==0){
        emailContainAt=1;
    }
    if(!emailContainAt){
        printf("Invalid email!\n");
        return -1;
    }
    // Repetition detection.
    for(int i=0;i<countContacts;++i){
        if(i!=index&&strcmp(contacts[i].email,contactInput.email)==0){
            printf("Same email exists thus not modified!\n");
            return -1;
        }
    }
    

    printf("Modify the address? \"1\"/other for yes/no: ");
    std::cin.getline(input,23);
    select=atoi(input);
    if(select==1){
        printf("(No more than 23 characters) Please input the new address: ");
        std::cin.getline(contactInput.address,23);
    }


    printf("Modify the work? \"1\"/other for yes/no: ");
    std::cin.getline(input,23);
    select=atoi(input);
    if(select==1){
        printf("(No more than 23 characters) Please input the new work: ");
        std::cin.getline(contactInput.work,23);
    }

    contacts[index]=contactInput;
    printf("Contact modified successfully!\n");
    return 0;
}



// Load contacts from \".ctx\" file.
int load(){
    printf("\033[47;30mLoad contacts from \".ctx\" file.\033[0m\n");
    printf("Loading from file will lose your current contacts in the memory!\nProceed? '1'/other for yes/no: ");
    char input[24]={0};
    std::cin.getline(input,23);
    if(strlen(input)!=1||input[0]!='1'){
        printf("Loading cancelled.\n");
        return 1;
    }
    // Load the file.
    int fileType=0;
    char filename[64]={0};
    printf("Please input the filename to load: ");
    std::cin.getline(filename,63);
    FILE *file=fopen(filename,"rb");
    if(file==NULL){
        printf("No such input file or directory!\n");
        fclose(file);
        return -1;
    }

    // Filetype validation.
    fread(&fileType,1,sizeof(fileType),file);
    if(fileType!=0x00435458){
        printf("Wrong file type!\n");
        fclose(file);
        return -1;
    }

    // Read the size of the contacts.
    fread(&countContacts,1,sizeof(unsigned char),file);

    // Read the contacts.
    fread(&contacts,1,sizeof(contacts),file);

    // Close the file.
    fclose(file);
    return 0;
}



// Save contacts to \".ctx\" file and exit.
int save(){
    printf("\033[47;30mSave contacts to \".ctx\" file and exit.\033[0m\n");

    // Whether to save the file.
    char input[23]={0};
    int save=1;
    printf("Save the file? '1'/'2'/other for yes/no/back: ");
    std::cin.getline(input,23);
    save=atoi(input);
    if(save!=1&&save!=2){
        printf("Saving cancelled.\n");
        return 1;
    }
    if(save==2){
        printf("Terminating the program without saving.\n");
        return 0;
    }

    // Create the file.
    unsigned int fileType=0x00435458;
    char filename[64]={0};
    printf("Please input the filename to save: ");
    std::cin.getline(filename,63);
    FILE *file=fopen(filename,"wb");
    if(file==NULL){
        printf("Error creating the file!\n");
        fclose(file);
        return -1;
    }

    // Write the filetype.
    fwrite(&fileType,sizeof(fileType),1,file);

    // Read the size of the contacts.
    fwrite(&countContacts,sizeof(countContacts),1,file);

    // Read the contacts.
    fwrite(&contacts,sizeof(contacts),1,file);

    fclose(file);
    printf("File saved successfully.\n");
    printf("Terminating the program.\n");
    return 0;
}



int main(){
    char input[512]={0};
    int select=0;
    while(true){
        printf("\033[47;30mContacts 1.2.1 (2022/Jun/9) - A lightweight contacts manager supporting up to 256 contacts. \033[0m\n");
        printf("\"0\"  List the contacts.\n\"1\"  Search in the contacts by name or phone number.\n\"2\"  Add a contact to the contacts.\n\"3\"  Remove a contact from the contacts by index.\n\"4\"  Modify a contact in the contacts by index.\n\"5\"  Load contacts from \".ctx\" file.\n\"6\"  Save contacts to \".ctx\" file and exit.\nPlease select an option by entering its index: ");
        std::cin.getline(input,511);
        select=atoi(input);
        switch(select){
            case 0: // list
                list();
                break;
            case 1: // search
                search();
                break;
            case 2: // add
                add();
                break;
            case 3: // remove
                remove();
                break;
            case 4: // modify
                modify();
                break;
            case 5: // load
                load();
                break;
            case 6: // save
                if(save()!=1){
                    return 0;
                }
                break;
            default:
                printf("Invalid option!\n");
        }
        select=0;

        // Wait for the enter to be pressed.
        printf("Press enter to continue.\n");
        while(getchar()!='\n'){}
    }

    return 0;
}
