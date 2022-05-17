#include<iostream>
#include<stdlib.h>
#include<string.h>



// Define the contact structor.
struct Contact{
    char name[24]={0},phone[24]={0},email[24]={0},address[24]={0},work[24]={0};
};
unsigned char countContacts=0;
Contact contacts[256];



// Show one contact by given index;
int show(unsigned char index){
    // Contact validation.
    // if(strcmp(contacts[index].name,"")==0||strcmp(contacts[index].phone,"")==0){
    //     return -1;
    // }

    // Show the given contact.
    printf("  %5d  %24s  %24s  %24s  %24s  %24s\n",index,contacts[index].name,contacts[index].phone,contacts[index].email,contacts[index].address,contacts[index].work);
    return 0;
}



// List the contacts.
int list(){
    printf("  \033[47;30mList the contacts.\033[0m\n");

    // Show one by one.
    printf("  %s  %24s  %24s  %24s  %24s  %24s\n","Index","Name","Phone","Email","Address","Work");
    for(unsigned char index=0;index<countContacts;++index){
        show(index);
    }

    // Show the statistics.
    printf("  Stored %d contacts in total 256 slots.\n",countContacts);
    return 0;
}



// Add a contact to the contacts.
int add(){
    printf("  \033[47;30mAdd a contact to the contacts.\033[0m\n");

    // Input and check the name and phone number.
    Contact contactToAdd;
    printf("  Please input the name: ");
    std::cin>>contactToAdd.name;
    if(strcmp(contactToAdd.name,"")==0){
        printf("  Invalid name!\n");
        return -1;
    }
    printf("  Please input the phone number: ");
    std::cin>>contactToAdd.phone;
    if(strcmp(contactToAdd.name,"")==0){
        printf("  Invalid phone number!\n");
        return -1;
    }

    // Repetition detection.
    for(int index=0;index<countContacts;++index){
        if(strcmp(contacts[index].phone,contactToAdd.phone)==0){
            printf("  Contact already exists thus not added!\n");
            return -1;
        }
    }

    // Input other information.
    printf("  (Optional) Please input the email: ");
    std::cin>>contactToAdd.email;
    printf("  (Optional) Please input the address: ");
    std::cin>>contactToAdd.address;
    printf("  (Optional) Please input the work: ");
    std::cin>>contactToAdd.work;

    contacts[countContacts]=contactToAdd;

    // Update the size of the contact with overflow detection.
    if(countContacts<255){
        ++countContacts;
    }
    printf("  Contact added successfully.\n");
    return 0;
}

// Search in the contacts by name or phone number.
int search(){
    printf("\033[47;30mSearch in the contacts by name or phone number.\033[0m\n");

    // Input and check the name and phone number, and then search.
    int select=0;
    char search[24]={0};
    int countResults=0,equalResults[255]={0};
    printf("  Please input \"0\"/\"1\" to search by name/phone: ");
    std::cin>>select;
    switch(select){
        case 0:
            printf("  Please input the name: ");
            std::cin>>search;
            for(int index=0;index<countContacts;++index){
                if(strcmp(contacts[index].name,search)==0){
                    equalResults[index]=1;
                    ++countResults;
                }
            }
            break;
        case 1:
            printf("  Please input the phone: ");
            std::cin>>search;
            for(int index=0;index<countContacts;++index){
                if(strcmp(contacts[index].phone,search)==0){
                    equalResults[index]=1;
                    ++countResults;
                }
            }
            break;
        default:
            printf("  Invalid option!\n");
            return -1;
    }

    // Show the results.
    if(countResults){
        printf("  %s  %24s  %24s  %24s  %24s  %24s\n","Index","Name","Phone","Email","Address","Work");
        for(int index=0;index<countContacts;++index){
            if(equalResults[index]){
                show(index);
            }
        }
    }

    // Show the statistics after the search.
    printf("  Found %d search results among %d contacts.\n",countResults,countContacts);
    return 0;
}



// Remove a contact from the contacts by index.
int remove(){
    printf("  \033[47;30mRemove a contact from the contacts by index.\033[0m\n");

    // Get and check the index.
    printf("  Please input index for the contact to remove: ");
    char input[24]={0};
    std::cin>>input;
    int index=atoi(input);
    if(index<0||index>255){
        printf("  Invalid index to remove!\n");
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
    --countContacts;
    if(countContacts<0){
        countContacts=0;
    }
    printf("  Contact removed successfully.\n");
    return 0;
}



// Modify a contact in the contacts by index.
int modify(){
    printf("  \033[47;30mModify a contact in the contacts by index.\033[0m\n");

    // Get and check the index.
    printf("  Please input index for the contact to remove: ");
    char input[24]={0},select[24]={0};
    std::cin>>input;
    int index=atoi(input);
    if(index<0||index>255){
        printf("  Invalid index to remove!\n");
        return -1;
    }

    // Copy the target contact and modify.
    Contact contactInput=contacts[index];
    printf("  Modify the name? \"1\"/other for yes/no: ");
    std::cin>>select;
    if(strcmp(select,"1")==0){
        printf("  Please input the new name: ");
        std::cin>>contactInput.name;
    }

    printf("  Modify the phone number? \"1\"/other for yes/no: ");
    std::cin>>select;
    if(strcmp(select,"1")==0){
        printf("  Please input the new phone number: ");
        std::cin>>contactInput.phone,23,stdin;
    }

    printf("  Modify the email? \"1\"/other for yes/no: ");
    std::cin>>select;
    if(strcmp(select,"1")==0){
        printf("  Please input the new email: ");
        std::cin>>contactInput.email;
    }

    printf("  Modify the address? \"1\"/other for yes/no: ");
    std::cin>>select;
    if(strcmp(select,"1")==0){
        printf("  Please input the new address: ");
        std::cin>>contactInput.address;
    }


    printf("  Modify the work? \"1\"/other for yes/no: ");
    std::cin>>select;
    if(strcmp(select,"1")==0){
        printf("  Please input the new work: ");
        std::cin>>contactInput.work;
    }

    contacts[index]=contactInput;
    printf("  Contact modified successfully!\n");
    return 0;
}


// Load contacts from \".ctx\" file.
int load(){
    printf("  \033[47;30mLoad contacts from \".ctx\" file.\033[0m\n");

    // Load the file.
    int fileType=0;
    char filename[64]={0};
    printf("  Please input the filename to load: ");
    std::cin>>filename;
    FILE *file=fopen(filename,"rb");
    if(file==NULL){
        printf("No such input file or directory!\n");
        fclose(file);
        return -1;
    }

    // Filetype validation.
    fread(&fileType,1,sizeof(fileType),file);
    if(fileType!=0x00435458){
        printf("  Wrong file type!\n");
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



// Save contacts to \".ctx\" file or exit.
int save(){
    printf("  \033[47;30mSave contacts to \".ctx\" file or exit.\033[0m\n");

    // Whether to save the file.
    int save=1;
    printf("  Save the file? '1'/other for yes/no: ");
    std::cin>>save;
    if(save!=1){
        printf("  Terminating the program without saving.\n");
        return 0;
    }

    // Create the file.
    unsigned int fileType=0x00435458;
    char filename[64]={0};
    printf("  Please input the filename to save: ");
    std::cin>>filename;
    FILE *file=fopen(filename,"wb");
    if(file==NULL){
        printf("  Error creating the file!\n");
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
    printf("  File saved successfully.\n");
    printf("  Terminating the program.\n");
    return 0;
}



int main(){
    int select=0;
    while(true){
        printf("  \033[47;30mContacts 1.0.0 (2022/May/16) - A Lightweight Contacts Manager!\033[0m\n");
        printf("  \"0\"  List the contacts.\n  \"1\"  Add a contact to the contacts.\n  \"2\"  Search in the contacts by name or phone number.\n  \"3\"  Remove a contact from the contacts by index.\n  \"4\"  Modify a contact in the contacts by index.\n  \"5\"  Load contacts from \".ctx\" file.\n  \"6\"  Save contacts to \".ctx\" file or exit.\n  Please select an option by entering its index: ");
        std::cin>>select;
        printf("select %d\n",select);
        switch(select){
            case 0: // list
                list();
                break;
            case 1: // add
                add();
                break;
            case 2: // search
                search();
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
                save();
                return 0;
            default:
                printf("  Invalid option!\n");
        }
        printf("  Press enter to continue\n");
    }

    return 0;
}
