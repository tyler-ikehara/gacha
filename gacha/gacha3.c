#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct info {				//structure to hold the character's rarity and name
	char type[20];
	char name[50];
};


void menu(char *com[25], char *rar[10], char *srar[5], struct info *collect[100], int count);		//function prototypes
void namestore(char *com[25], char *rar[10], char *srar[5]);
void onePull(char *com[25], char *rar[10], char *srar[5], struct info *collect[100], int *count);
void elevenPull(char *com[25], char *rar[10], char *srar[5], struct info *collect[100], int *count);
void again(char *com[25], char *rar[10], char *srar[5], struct info *collect[100], int *count);
void viewCollect(struct info *collect[100], int *count);
void removeCharacter(struct info *collect[100], int *count);

int main(void){
	struct info *collection[100];					//defining collection structure to hold all characters
	char *common[25];
	char *rare[10];
	char *superrare[5];						//defining arrays to hold the characters to be pulled
	int i;
	int count=0;							//count to detect which id or position the character to be pulled will hold
	for (i=0;i<25;i++)
		common[i]=(char *)malloc(sizeof(common));		//malloc functions to allocate data space for string arrays and structures
	for (i=0;i<10;i++)
		rare[i]=(char *)malloc(sizeof(rare));
	for (i=0;i<5;i++)
		superrare[i]= (char *)malloc(sizeof(superrare));
	for (i=0;i<100;i++)
		collection[i]= (struct info *)malloc(sizeof(struct info));
	namestore(common, rare, superrare);				//inserts names into the arrays defined above
	srand(time(0));							//sets time of rand function to the time of the clock of the system which makes it so rand doesn't keep returning the same value
	menu(common,rare, superrare, collection, count);		//goes to menu function
}

void menu(char *com[25], char *rar[10], char *srar[5], struct info *collect[100], int count){		//menu function
	char check;
	printf("Welcome to the Gacha Game!\nPress 'P' to pull once, 'E' to pull 11 times, 'C' to view your collection or 'Q' to quit.\n");
	scanf(" %c", &check);
		switch(check){						//switch statement to determine what the user wants to do
			case 'P':
			case 'p':
			{
				if(count>=101){				//space check to see if there is room in the collection to add another character
					printf("There is not enough space in your collection to pull.\nMoving to collection page now.\n");
                                        viewCollect(collect, &count);	//brings you to collection to edit it so that there is space
                                        menu(com,rar,srar,collect, count);
                                        break;
                                }
				onePull(com,rar,srar,collect,&count);	//if enough space, pulls once
				again(com,rar,srar,collect,&count);	//goes into another menu function
				break;
			}
			case 'E':
			case 'e':
			{
				if(count>=90){ 				//space check but to see if there is room for 11 characters
                                        printf("There is not enough space in your collection to pull 11 times.\nMoving to collection page now.\n");
                                        viewCollect(collect, &count);
                                        menu(com, rar,  srar, collect, count);
                                        break;
                                }
				elevenPull(com, rar, srar, collect, &count);	//if there is space, pulls 11 times
				again(com, rar, srar, collect, &count);
				break;
			}
			case 'C':
			case 'c':
			{
				viewCollect (collect, &count);		//collection viewing and editing function
				menu(com,rar,srar, collect, count);
			}
			case 'Q':
			case 'q':
			{
				exit(0);				//quits program
			}
			default:
			{						//checks for invalid inputs
				printf("That is an invalid input\n");
				menu(com,rar,srar, collect, count);
				break;
			}
		}
}

void namestore(char *com[25], char *rar[10], char *srar[5]){		//function to get names of the characters from a file
	int i=0,j=0,k=0;
	char buf[100], bufrar[100], bufsrar[100];	
	FILE *common, *rare, *superrare;				//setting up pointers to files
	common=fopen("common.txt", "r");
		while ((fgets(buf,100,common)!=0)&&i<25)		//reads line to line and then copies the string into a buffer array
		{
			buf[strlen(buf)-1]='\0';			//truncates the null symbol at the end of the string
			strcpy(com[i],buf);				//copies the buffer string into the array defined in the main
			i++;
		}
		fclose(common);						//closes the file
	rare=fopen("rare.txt", "r");					//same structure as above but from the rare file
                while ((fgets(bufrar,100,rare)!=0)&&(j<10))
                {							
                        bufrar[strlen(bufrar)-1]='\0';
			strcpy(rar[j],bufrar);
                        j++;
                }
		fclose(rare);
	superrare=fopen("superrare.txt", "r");				//same as above but from superrare file
                while ((fgets(bufsrar,100,superrare)!=0)&&k<5)
                {
                        bufsrar[strlen(bufsrar)-1]='\0';
			strcpy(srar[k],bufsrar);
                        k++;
                }
		fclose(superrare);
	}

void onePull(char *com[25], char *rar[10], char *srar[5], struct info *collect[100], int *count){		//function to pull once
	int rarity;
	rarity=(rand()+100)%100;					//sets the rarity parameter by taking a random number modulo 100 getting a random number from 1-100
		if (rarity<=2){						//2 percent chance pull (superrare)
			int randsr=rand()%5;				//to determine which of the 5 superrare characters to be pulled
			printf("\aYou pulled a\033[0;36m super rare\033[0m %s!\n", srar[randsr]);
			strcpy(collect[*count]->type,"Super Rare");	//copies the rarity and name into the collection
			strcpy(collect[*count]->name,srar[randsr]);
		}
			else if(rarity<=13){				//same as above but with a 10 percent chance pull (rare)
			int randr=rand()%10;
			printf("You pulled a\033[0;35m rare\033[0m %s!\n", rar[randr]);
			strcpy(collect[*count]->type,"Rare");
                        strcpy(collect[*count]->name,rar[randr]);
		}
				else{
				int randc=rand()%25;			//same as above but with a 88 percent chance pull (common)
				printf("You pulled a common %s!\n", com[randc]);
				strcpy(collect[*count]->type,"Common");
                        	strcpy(collect[*count]->name,com[randc]);
				}
	(*count)++;							//increments the count variable to move to the next collection id
	}
void elevenPull(char *com[25], char *rar[10], char *srar[5], struct info *collect[100], int *count){	//function to pull 11 times
	int i=0;
	for (i=0;i<11;i++)
		onePull(com, rar, srar, collect, count);	//does the one pull function 11 times
	}

void again(char *com[25], char *rar[10], char *srar[5], struct info *collect[100], int *count){		//menu function after pulling
	char check1;
	printf("Would you like to pull again? Type 'P' for one pull, 'E' for eleven pulls, 'M' to return to the menu, or 'Q' to quit\n");
	scanf(" %c",&check1);
		switch(check1){					//switch statement that checks if you want to pull again
			case 'p':
			case 'P':
			{
				if(*count>=101){		//space check
					printf("There is not enough space in your collection to pull.\nMoving to collection page now.\n");
					viewCollect(collect, count);
					menu(com,rar,srar,collect,*count);
					break;
				}
				onePull(com, rar, srar, collect, count);
				again(com, rar, srar, collect, count);
				break;
			}
			case 'e':
			case 'E':
			{
				if(*count>=90){			//11 space check
					printf("There is not enough space in your collection to pull 11 times.\nMoving to collection page now.\n");
					viewCollect(collect, count);
					menu(com, rar, srar, collect, *count);
					break;
				}
				elevenPull(com, rar, srar, collect, count);
				again(com, rar, srar, collect, count);
				break;
			}
			case 'q':
			case 'Q':
			{
				exit(0);
			}
			case 'm':
			case 'M':
			{
				menu(com, rar, srar, collect, *count);
				break;
			}
			default:
			{
 				printf("That is an invalid input\n");
                                again(com,rar,srar, collect, count);
                                break;
			}
		}
}
			

void viewCollect(struct info *collect[100], int *count){		//function to view collection
	int i;
	char check;
	printf("Welcome to your collection.\n");
	for (i=0;i<*count;i++){						//for loop set to go from 0 to what count is currently at
		printf("ID:#%-3d", i);
		if(strcmp(collect[i]->type,"Super Rare")==0)		//logic for printing color associated with rarity
			printf(" \033[0;36m%s \033[0m%-20s",collect[i]->type, collect[i]->name);
		else if(strcmp(collect[i]->type,"Rare")==0)
			printf(" \033[0;35m%s \033[0m%-20s",collect[i]->type, collect[i]->name);
		else
			printf(" %s %-20s",collect[i]->type, collect[i]->name);	//prints each element in the structure collect
		if((i+1)%5==0)						//every 5 iterations prints newline
			printf("\n");
		}
	printf("\nPress 'R' to remove a character from your collection, or 'Q' to quit\n");
	scanf(" %c", &check);
		switch (check){						//switch statement to see what the user wants to do
			case 'R':
			case 'r':
			{
				removeCharacter(collect, count);	//remove character function
				break;
			}
			case 'Q':
			case 'q':
			{
				break;
			}
			default:
			{
				printf("That is not a valid input\n");
				viewCollect (collect, count);
				break;
			}
		}
	}				
void removeCharacter(struct info *collect[100], int *count){		//function to remove character
	int stat=1;
	while(stat==1){							//keeps iterating until the stat parameter is flipped
	printf("Please enter the ID number of the character you wish to remove.(0-99)\n");
	int id, i,k;
	scanf(" %d", &id);						//scans the id of the character to be removed
	k=id;
		while(id<(*count)){					//until the scanned number reaches the current count number keeps running the loop
			if(id==100)					//automatically stops at 100 which is the max size of the collection structure
				break;
			strcpy(collect[id]->type, collect[id+1]->type);	//copies the current structure element with the next element (basically to move each element 1 id lower)
			strcpy(collect[id]->name, collect[id+1]->name);
			id++;
			}
	*count=*count-1;						//sets the count to be 1 less as 1 character was removed
	printf("Character #%d removed.\nHere is your new collection.\n",k);	//prints the new collection after removal
	for (i=0;i<*count;i++){                                         //for loop set to go from 0 to what count is currently at
                printf("ID:#%-3d", i);
                if(strcmp(collect[i]->type,"Super Rare")==0)            //logic for printing color associated with rarity
                        printf(" \033[0;36m%s \033[0m%-20s",collect[i]->type, collect[i]->name);
               	else if(strcmp(collect[i]->type,"Rare")==0)
                        printf(" \033[0;35m%s \033[0m%-20s",collect[i]->type, collect[i]->name);
                else
                        printf(" %s %-20s",collect[i]->type, collect[i]->name); //prints each element in the structure collect 
                if((i+1)%5==0)                                          //every 5 iterations prints newline
                        printf("\n");
                }
	printf("\nWould you like to keep removing? ('Y' or 'N')\n");
	char check;
	scanf(" %c", &check);						//if they don't want to remove anymore, the stat parameter is flipped and the loop is exited
		if (check=='N'||check=='n')
			stat=0;
	}
}
