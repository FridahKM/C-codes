#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define true 0 //true boolean
#define false 1 //false boolean

struct item{
    char itemId[10], itemName[20];
	int itemQtn, itemOut;
};
struct item its[30];//the maximum array elements.
int count = 0;	//Incremented with every new item
FILE *f;	//for the file pointer

char textFile[20];

void initializeFiles(){
    if(f==NULL){
        f=fopen("Bradosa.txt","w");
        f=fopen("Latiana.txt","w");
        f=fopen("Dohuri.txt","w");
    }
}

int selWareHse;
void displayWarehouses(){
    printf("\* Kindly select one of the warehouses listed below. *\n");
    printf("\t1.Bradosa\n");
    printf("\t2.Latiana\n");
    printf("\t3.Dohuri\n");
    printf("Enter your choice:\n");
    scanf("%d", &selWareHse);

    while(selWareHse<1 || selWareHse>3)
    {
         printf("Invalid choice. Select a number between 1 and 3\n");
         scanf("%d", &selWareHse);
    }

    displayMenu();
}

int readFile(){ // read file function

    int n = 0;
    int i;

    if(selWareHse==1){
        f=fopen("Bradosa.txt", "r");}
    else if(selWareHse==2){
        f=fopen("Latiana.txt", "r");}
    else if(selWareHse==3){
        f=fopen("Dohuri.txt", "r");}

    if (f == NULL){
        return -1;
        displayMenu();
    }

    fscanf(f, "%d\n", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(f, "%s", &its[i].itemId);
        fscanf(f, "%s", &its[i].itemName);
        fscanf(f, "%d", &its[i].itemQtn);
        fscanf(f, "%d", &its[i].itemOut);

    }
    fclose(f);
    return n;
}

int writeFile(){

    int i;
    if(selWareHse==1){
        f=fopen("Bradosa.txt", "w");}
    else if(selWareHse==2){
        f=fopen("Latiana.txt", "w");}
    else if(selWareHse==3){
        f=fopen("Dohuri.txt", "w");}

    if (f == NULL){
        return -1;
        displayMenu();
    }

    fprintf(f, "%d\n", count);
    for (i = 0; i < count; i++){
        //Obtain info on item
        fputs(its[i].itemId, f);
        fprintf(f, "\n");
        fputs(its[i].itemName, f);
        fprintf(f, "\n");
        fprintf(f, "%d\n", its[i].itemQtn);
        fprintf(f, "%d\n", its[i].itemOut);

    } // writing information from the function to the text file.
    fclose(f);
    return 0;
}


//main menu
void displayMenu(){
    int option;
	count = readFile();
	if(count < 0) // there is no file located.
		initializeFiles();
    // Main Menu
    do {
        printf("***************************************************************************\n");
        printf("*** \t WELCOME TO SUNGAI TUNA PLANT WAREHOUSE MANAGEMENT SYSTEM \t***\n");
        printf("***************************************************************************\n");
        printf("Select one of the options below\n");
        printf("\t1.Create new part to inventory\n");
        printf("\t2.Request for parts from the warehouse\n");
        printf("\t3.Add new stock of parts in warehouse\n");
        printf("\t4.Check all available parts in warehouse\n");
        printf("\t5.Check parts less than 10 in warehouse\n");
        printf("\t6.Search for a part in the warehouse\n");
        printf("\t0.Exit\n");
        printf("Enter your choice:\n");
        scanf("%d", &option);

         while(option<0 || option>6)
        {
             printf("Invalid choice. Select a number between 0 and 6\n");
             scanf("%d", &option);
        }

        switch(option){
        case 1:
            newItem();
            quit();
            break;
        case 2:
            reduceQnt();
            quit();
            break;
        case 3:
            increaseQnt();
            quit();
            break;
        case 4:
            checkInventory();
            quit();
            break;
        case 5:
            checkBelow10();
            quit();
            break;
        case 6:
            searchItem();
            quit();
            break;
        }

    }while(option!=0);

}

int checkId(int i, int j)	//checking the input id
{
	count=readFile();
    printf("Product ID: ");
    fflush(stdin);
	gets(its[count].itemId);
    if (strcmp(its[i].itemId,its[j].itemId)==0){
        printf("ID NUMBER IS ALREADY TAKEN!\n");
        return checkId(i++,j--);
    }
}

void newItem(){
    printf("\nENTER NEW PRODUCTS\n");
	readFile();	//reading the files
    if (count>0) {
  	    count=readFile();
  		checkId(0,count); // to check if the id is already used.
    }
	else{
		printf("\nProduct ID Number: ");
		fflush(stdin);
		gets(its[count].itemId);
    }
    printf("Product Name: ");gets(its[count].itemName);
    printf("Quantity of the product: ");scanf("%d",&its[count].itemQtn);
    printf("Distributed Amount: ");scanf("%d",&its[count].itemOut);
    count++; // increment count for the product positions and how many are they in the array.

	writeFile(); // putting/saving this to the file.
	printf("Record successfully added!!!\n");
}

void reduceQnt(){
    int quant,i;
    char id[10];
    int z=false;
    count=readFile();
    printf("\nEnter the product ID: ");
    fflush(stdin);
	gets(id);
    for (i=0; i<count; i++){
        if (strcmp(id,its[i].itemId)==0) // if the id that the user want to find and the data id that has been saved at file is matched.
        {
        	z=true;
            printf("\nItem found! Containing: \n");//display the match
            printf("\nPart name: %s",its[i].itemName);
            printf("\nPart Quantity: %d",its[i].itemQtn);

            printf("\nEnter the quantity you want to request: ");
            fflush(stdin);
			scanf("%d",&quant);
            if (quant>its[i].itemQtn){		// if the quantity is less than the users quantity
               puts("\nInsufficient quantity in warehouse.\nReduce request amount or restock.\n ");
             break; // break and back to the choices.
				}

            its[i].itemOut += quant;
            its[i].itemQtn -= quant;
			}

	}
    if(z==false){	//if the product id is not available.
        printf("Cant find the part of id %s.\n",&id);
    }
	writeFile();
}

void increaseQnt(){
    int quant,i;
    char id[10];
    int z=false;
    count=readFile();
    printf("\nEnter the product ID: ");
    fflush(stdin);
	gets(id);
    for (i=0; i<count; i++){
        if (strcmp(id,its[i].itemId)==0) // if the id that the user want to find and the data id that has been saved at file is matched.
        {
        	z=true;
            printf("\nItem found! Containing: \n");//display the match
            printf("\nPart name: %s",its[i].itemName);
            printf("\nPart Quantity: %d",its[i].itemQtn);

            printf("\nEnter the quantity you add to store: ");
            fflush(stdin);
			scanf("%d",&quant);

            its[i].itemQtn += quant;
			}

	}
    if(z==false){	//if the product id is not available.
        printf("Cant find the part of id %s.\n",&id);
    }
	writeFile();
}

void checkInventory(){
    count = readFile(); // the output is how many products inside the file.
    if (count < 0)
    puts("cannot open file");
	printf(" \t\t\t\t *****  INVENTORY *****\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("S.N.|    NAME     |    PART ID    |    QUANTITY   | QUANTITY OUT |\n");
    printf("------------------------------------------------------------------------------------\n");

    int i=0;
    while (i<count){ // getting the details on each product updates.
    printf("%d \t %s \t %s \t %d \t \t %d\n",i+1,its[i].itemName,its[i].itemId,its[i].itemQtn,its[i].itemOut);
	i++;
	}
}

void checkBelow10(){
    int i;
    count= readFile();	// call the read function
    printf("\nParts with less then 10 items left: ");
    for (i=0; i<count; i++){
        if(its[i].itemQtn<10){// printing the details
            printf("\nName of the part: %s", its[i].itemName);
            printf("\nPart Id: %s",its[i].itemId);
            printf("\nQuantity left: %d ",its[i].itemQtn);
            printf("\nNumber of parts distributed: %d \n",its[i].itemOut);
		}
		writeFile();
    }
}

void searchItem(){
    char searchId[20];
    printf("\nEnter Id of part to search: ");
    scanf("%s", &searchId);
    count= readFile();	// call the read function
    int i;
    for (i=0; i<count; i++){
        if(strcmp(its[i].itemId,searchId)==0){
            printf("\nName of the part: %s", its[i].itemName);
            printf("\nPart Id: %s",its[i].itemId);
            printf("\nQuantity left: %d ",its[i].itemQtn);
            printf("\nNumber of parts distributed: %d \n",its[i].itemOut);
        }
    }
}

void quit(){
    int leave;
    printf("Do you want to exit the system?\n 1.Yes\n 2.No\n");
    scanf("%d", &leave);
    while(leave<0 || leave>2){
         printf("Invalid choice. Select a number between 1 and 2\n");
         scanf("%d", &leave);
    }if(leave==1){
        printf("Thank you for using this program");
    }
    if(leave==2){
        displayMenu();
    }else{
        exit(0);
    }
}

int main()
{
    displayWarehouses();
    return 0;
}

