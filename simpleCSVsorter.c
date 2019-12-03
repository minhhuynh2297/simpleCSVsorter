#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergeSort.c" 
#include <ctype.h>

node* curr;
node** temp1;
node** temp2;
node** temp3;
node** temp4;

char* deleteQ(char* word){ //this works, but I don't know why it doesn't work in the cod
	char* newWord=(char*)malloc(sizeof((char)100));
	int start=0;
	int finish=strlen(word)-1;
	while(ispunct((unsigned char)word[start])){
		start++;
	}
	while(ispunct((unsigned char)word[finish]) && (finish >= start)){
		finish--;
	}
	for(i = start; i<=finish; i++){
		newWord[i-start]=word[i];
	}
	newWord[i-start] ='\0';

	return newWord;
}

char* deleteSpace(char* word){ //implement this in later
	char* newWord=(char*)malloc(sizeof((char)100));
	int start=0;
	int finish=strlen(word)-1;
	while(isspace((unsigned char)word[start])){
		start++;
	}
	while(isspace((unsigned char)word[finish]) && (finish >= start)){
		finish--;
	}
	for(i = start; i<=finish; i++){
		newWord[i-start]=word[i];
	}
	newWord[i-start] ='\0';

	return newWord;
}

void printFirst(node** head){
	while((*head)->next!=NULL){
		printf("%s,", (*head)->dataType);
		head=&((*head)->next);
	}
	printf("%s\n", (*head)->dataType);
}

void printLL(node** head){ //prints individual linked lists

	while((*head)->next!=NULL){
		printf("%s,", (*head)->data);
		head=&((*head)->next);
	}
	printf("%s\n", (*head)->data);
}

void printBox(node** sortedLL, node** ptr, char* sort){
	temp1=ptr; //always stays at first node of box
	temp2=ptr; //goes to column to be sorted, and stays there
	printFirst(ptr);
	char* data=(char*)malloc(sizeof((char)100)); //holds data
	char* head=(char*)malloc(sizeof((char)100)); //holds columnData

	while((*temp2)!=NULL){ //goes through column to be sorted in box
		i=strcmp(((*temp2)->dataType), sort); //do "
		if(i==0){
			break;
		}
		else{
			temp2=&((*temp2)->next);
		}
	}
	temp1=&((*temp1)->down); //now stays at row 2
	temp2=&((*temp2)->down); //now stays at row 2
	//we are now in useful information rows
	temp3=temp1; //goes down the first column
	temp4=temp2; //goes down the column to be sorted

	while((*sortedLL)->next!=NULL){ //now prints out the sorted LL's

		data=deleteSpace((*sortedLL)->data);
		head=deleteSpace((*sortedLL)->columnData);
		while((*temp3)->down!=NULL && (*temp4)->down!=NULL){ //finds LL to be sorted
			i=strcmp((deleteSpace((*temp4)->data)), data);
			if(i==0){
				break;
			}
			else{
				temp3=&((*temp3)->down);	
				temp4=&((*temp4)->down);			
			}
		}	

		printLL(temp3); //prints LL starting at the head
		temp3=temp1; //goes back to row 2
		temp4=temp2; //goes back to row 2
		sortedLL=&((*sortedLL)->next);
	}
	//prints last LL
		temp3=temp1;
		temp4=temp2;
		data=deleteSpace((*sortedLL)->data);
		head=deleteSpace((*sortedLL)->columnData);
		while((*temp3)->down!=NULL && (*temp4)->down!=NULL){ //finds LL to be sorted
			i=strcmp((deleteSpace((*temp4)->data)), data);
			if(i==0){
				break;
			}
			else{
				temp3=&((*temp3)->down);	
				temp4=&((*temp4)->down);			
			}
		}
		printLL(temp3); 
	free(data);
	free(head);
}

			



void appendDataType(node** ptr, char* data){ //creates nodes in the first row of our "array" that only has dataType (food, calories)

	if((*ptr)==NULL){
		(*ptr)=(node*)malloc(sizeof(node));
		(*ptr)->dataType=data;
		(*ptr)->next=NULL;	

	}
	else{
	
		temp1 = ptr;

		while((*temp1)->next!=NULL){

			temp1=&((*temp1)->next);

		}
		(*temp1)->next=(node*)malloc(sizeof(node));
		(*temp1)->next->dataType=data;
		(*temp1)->next->next=NULL;
	}
}

void appendData(node** ptr, char* data){ //creates the rest of our our box, making nodes that has data, like celery, 200, etc.

	if((*ptr)==NULL){
		(*ptr)=(node*)malloc(sizeof(node));
		(*ptr)->data=data;
		(*ptr)->next=NULL;	

	}
	else{
	
		temp1 = ptr;

		while((*temp1)->next!=NULL){

			temp1=&((*temp1)->next);

		}

		(*temp1)->next=(node*)malloc(sizeof(node));
		(*temp1)->next->data=data;
		(*temp1)->next->next=NULL;



	}
}

void appendSort(node** ptr, char* colData, char* data){ //creates nodes for LL to be sorted
	if((*ptr)==NULL){
		(*ptr)=(node*)malloc(sizeof(node));
		(*ptr)->data=data;
		(*ptr)->columnData=colData;
		(*ptr)->next=NULL;	

	}
	else{
	

		while((*ptr)->next!=NULL){
			ptr=&((*ptr)->next);

		}

		(*ptr)->next=(node*)malloc(sizeof(node));
		(*ptr)->next->data=data;
		(*ptr)->next->columnData=colData;
		(*ptr)->next->next=NULL;

	}
}


char* getWords(int* ptr, char* entireData){ //returns a word, and increases a counter in writeLL
	j=0;
	char* individualWords=(char*)malloc(sizeof((char)100));

	for(i=(*ptr); i<10000; i++){ 

		if(entireData[i]=='\0'){ //exits at end of line;		
			individualWords[j]='\0';
			(*ptr)=-1;
			return individualWords;
		}

		if(entireData[i]!=','){ //writes everything until a comma
			individualWords[j]=entireData[i];
			j++;
		}
		else{ 
			individualWords[j]='\0';
			i++;
			(*ptr)=i;
			return individualWords;
		}
	}
	return individualWords;
}

void writeFirstRow(node** ptr, char* entireData){ //writes the first row with nodes having data type like Food, Calories
	int count=0;
	int* pCount=&count;
	while(count!=-1){
		appendDataType(ptr, getWords(pCount, entireData));		
	}
}

void writeLL(node** ptr, char* entireData){ //makes the rest of the "box", with linked lists holding data, like celery and 200
	int count=0;
	int* pCount=&count;
	while(count!=-1){
		appendData(ptr, getWords(pCount, entireData));		
	}
 
}

void connectLL(node** oldHead, node** newHead){	//makes up and down on every node
	temp1=oldHead;
	temp2=newHead;
	while((*temp1)->next!=NULL || (*temp2)->next!=NULL){
		(*temp1)->down=(*temp2);
		(*temp2)->up=(*temp1);	
		(*temp2)->dataType=(*temp1)->dataType;
		temp1=&((*temp1)->next);
		temp2=&((*temp2)->next);

	}
}

void makeSortLL(node** headLL, node** ptr, char* sortData){ //creates the LL to be sorted
temp1=ptr;
temp2=ptr;

	while((*temp2)->next!=NULL){ //finds column of the category to be sorted	
		i=strcmp((deleteSpace(deleteQ((*temp2)->dataType))), sortData);
		if(i==0){ //found column
			break;
		}
		else{
			temp2=&((*temp2)->next);
		}
	}

	

	//temp1 should still be at the head of the first LL in our box
	//temp 2 should now be at the column to be sorted

	temp1=&((*temp1)->down);
	temp2=&((*temp2)->down);
	
	while((*temp1)->down!=NULL && (*temp2)->down!=NULL){
		appendSort(headLL, (*temp1)->data, (*temp2)->data);
		temp1=&((*temp1)->down);
		temp2=&((*temp2)->down);	
	}

}

int main(int argc, char* argv[]){

	if(argc < 2)
		exit(-1);
	

	int countLL=-1;	

	char *line; //holds line by line 

	line = malloc(10000 * sizeof(char));

	
	FILE *fp = fopen(argv[1], "r"); //reads in the file; 

	if(fp == NULL){
		printf("File not found\n");
		exit(-1);
	}
	node* head=NULL;
	node** ptr=&head;

	fgets(line, 10000, fp);

	writeFirstRow(ptr, line); //first row;

	node** oldRow = &head;

//creates the "box"
	while(!feof(fp)){
		if(feof(fp)){
			break;
		}
		fgets(line, 10000, fp);
		node* newHead=NULL;
		node** newRow=&newHead;
		writeLL(newRow,line);
			
		countLL++;
		connectLL(oldRow, newRow);
		
		oldRow=&((*oldRow)->down);
		

	} 
	free(line);
	//printf("%s\n", argv[2]);
/*	while((*ptr)->next!=NULL){ // we tried to do it, it breaks. color,duration / color works, duration doesn't
		i=strcmp((*ptr)->dataType, argv[2]);
		if(i==0){
			break;
		}
		else{
			printf("Column not found!!!!\n");
			exit(-1);
		}
	
	}
*/

	node* sortedLL=NULL;
	node** headLL=&sortedLL;
	makeSortLL(headLL, ptr, argv[2]);
	mergeSort(headLL);
	printBox(headLL, ptr, argv[2]);
	return 0;
}




















