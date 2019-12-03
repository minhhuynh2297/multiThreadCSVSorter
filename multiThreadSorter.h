#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.c" 
#include <ctype.h>

node* curr;
node** temp1;
node** temp2;
node** temp3;
node** temp4;
node** temp5;
node** temp6;
node** temp7;
node** temp8;
node** temp9;
node** temp10;
node** temp11;
node** temp12;

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

int countLL(node** head){
	int count=1;
	while((*head)->next!=NULL){
		count++;
		head=&((*head)->next);
	}
	return count;
}

int countCol(node** head){
	int count=1;
	while((*head)->down!=NULL){
		count++;
		head=&((*head)->down);
	}
	return count;
}

void printFirstFile(node** head, FILE* output){
	while((*head)->next!=NULL){
		fprintf(output, "%s,", (*head)->dataType);
		head=&((*head)->next);
	}	
	fprintf(output, "%s", (*head)->dataType);
	fprintf(output, "\n"); 
}

void printLLFile(node** head, FILE* output){ //prints individual linked lists
	while((*head)->next!=NULL){
	//printf("%s,", (*head)->data);
	fprintf(output, "%s,", (*head)->data);
	head=&((*head)->next);
	}

	//printf("%s\n", (*head)->datsa);
	fprintf(output, "%s", (*head)->data);
	fprintf(output, "\n"); 
}

void printBoxFile(node** sortedLL, node** ptr, char* sort, FILE* output){
	temp1=ptr; //always stays at first node of box
	temp2=ptr; //goes to column to be sorted, and stays there
	printFirstFile(ptr, output);
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

		printLLFile(temp3, output); //prints LL starting at the head
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
	printLLFile(temp3, output); 
	free(data);
	free(head);
	fclose(output);
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

void printMaster(node** head){
	printFirst(head);
	while((*head)->down!=NULL){
		printLL(&((*head)->down));
		head=&((*head)->down);
	}
}

void printBox(node** sortedLL, node** ptr, char* sort){
	temp12=ptr; //always stays at first node of box
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
	temp12=&((*temp12)->down); //now stays at row 2
	temp2=&((*temp2)->down); //now stays at row 2
	//we are now in useful information rows
	temp3=temp12; //goes down the first column
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
		temp3=temp12; //goes back to row 2
		temp4=temp2; //goes back to row 2
		sortedLL=&((*sortedLL)->next);
	}
	//prints last LL
		temp3=temp12;
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
	
		temp11 = ptr;

		while((*temp11)->next!=NULL){

			temp11=&((*temp11)->next);

		}
		(*temp11)->next=(node*)malloc(sizeof(node));
		(*temp11)->next->dataType=data;
		(*temp11)->next->next=NULL;
	}
}

void createMaster(node** master){
	appendDataType(master, "Color\0");
	appendDataType(master, "director_name\0");
	appendDataType(master, "num_critic_for_reviews\0");
	appendDataType(master, "duration\0");
	appendDataType(master, "director_facebook_likes\0");
	appendDataType(master, "actor_3_facebook_likes\0");
	appendDataType(master, "actor_2_name\0");
	appendDataType(master, "actor_1_facebook_likes\0");
	appendDataType(master, "gross\0");
	appendDataType(master, "genres\0");
	appendDataType(master, "actor_1_name\0");
	appendDataType(master, "movie_title\0");
	appendDataType(master, "num_voted_users\0");
	appendDataType(master, "cast_total_facebook_likes\0");
	appendDataType(master, "actor_3_name\0");
	appendDataType(master, "facenumber_in_poster\0");
	appendDataType(master, "plot_keywords\0");
	appendDataType(master, "movie_imdb_link\0");
	appendDataType(master, "num_user_for_reviews\0");
	appendDataType(master, "language\0");
	appendDataType(master, "country\0");
	appendDataType(master, "content_rating\0");
	appendDataType(master, "budget\0");
	appendDataType(master, "title_year\0");
	appendDataType(master, "actor_2_facebook_likes\0");
	appendDataType(master, "imdb_score\0");
	appendDataType(master, "aspect_ratio\0");
	appendDataType(master, "movie_facebook_likes\0");
}

void appendData(node** ptr, char* data){ //creates the rest of our our box, making nodes that has data, like celery, 200, etc.

	if((*ptr)==NULL){
		(*ptr)=(node*)malloc(sizeof(node));
		(*ptr)->data=data;
		(*ptr)->next=NULL;	

	}
	else{
	
		temp10 = ptr;

		while((*temp10)->next!=NULL){

			temp10=&((*temp10)->next);

		}

		(*temp10)->next=(node*)malloc(sizeof(node));
		(*temp10)->next->data=data;
		(*temp10)->next->next=NULL;



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

void copyLL(node** dest, node** src, int code){
	temp8=src;
	if(code == 0){ //appendDataType
		while((*src)->next!=NULL){
			appendDataType(dest, (*src)->dataType);
			src=&((*src)->next);
		}
			appendDataType(dest, (*src)->dataType);
	}

	else if(code==1){ //appendData
		while((*src)->next!=NULL){
			appendData(dest, (*src)->data);
			src=&((*src)->next);
		}
		appendData(dest, (*src)->data);
	}
}



char* getWords(int* ptr, char* entireData){ //returns a word, and increases a counter in writeLL
	j=0;
	char* individualWords=(char*)malloc(sizeof((char)100));
	char* finishWords=(char*)malloc(sizeof((char)100));

	for(i=(*ptr); i<10000; i++){ 

		if(entireData[i]=='\0'){ //exits at end of line;		
			individualWords[j]='\0';
			(*ptr)=-1;
			int trim = strlen(individualWords);
			finishWords=strncpy(finishWords, individualWords, trim-1);
			return finishWords;
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

void fillNULL(node** ptr){
	temp9=ptr;
	int counter=1;
	while((*ptr)->next!=NULL){
		ptr=&((*ptr)->next);
		counter++;
	}
	while(counter<28){
		appendData(temp9, "NULL");
		counter++;
	}
	//printLL(ptr);
	//printf("%d\n", counter);
}

void nullWriteLL(node** ptr, node** master, node** head, char* entireData){
	int count=0;
	while(count!=-1 && (*master)->next!=NULL && (*head)->next!=NULL) {
		//printf("goes in\n");
		if(strcmp((*master)->dataType, (*head)->dataType)==0){
			appendData(ptr, getWords(&count, entireData));
			master=&((*master)->next);
			head=&((*head)->next);
		}
		else{
			while(strcmp((*master)->dataType, (*head)->dataType)!=0){	
				appendData(ptr, "NULL");
				master=&((*master)->next);	
				
			}
			appendData(ptr, getWords(&count, entireData));
		}	

	}
		if(strcmp((*master)->dataType, (*head)->dataType)==0){
			appendData(ptr, getWords(&count, entireData));
			master=&((*master)->next);
			head=&((*head)->next);
		}
		else{
			while(strcmp((*master)->dataType, (*head)->dataType)!=0){
				appendData(ptr, "NULL");
				master=&((*master)->next);	
			}
			appendData(ptr, getWords(&count, entireData));
		}
	//printLL(ptr);	
}

void connectLL(node** oldHead, node** newHead){	//makes up and down on every node
	temp6=oldHead;
	temp7=newHead;
	//printf("%s\n", (*temp1)->dataType);
	//printf("%s\n", (*temp2)->data);
	while((*temp6)->next!=NULL && (*temp7)->next!=NULL){
		(*temp6)->down=(*temp7);
		(*temp7)->up=(*temp6);	
		(*temp7)->dataType=(*temp6)->dataType;
		temp6=&((*temp6)->next);
		temp7=&((*temp7)->next);
	//	printf("%s\n", (*temp1)->dataType);
	//	printf("%s\n", (*temp2)->data);
	}
	if((*temp6)->next!=NULL && (*temp7)->next==NULL){
			printf("not a square matrix\n");
			exit(0);
		}
	if((*temp6)->next==NULL && (*temp7)->next!=NULL){
		printf("not a square matrix\n");
		exit(0);
	}	

}

void connectMaster(node** master, node** fakeMaster, node** sortedLL, char* sort){
	temp1=fakeMaster;
	temp2=fakeMaster;
	node* replace=(node*)malloc(sizeof(node));
	while((*master)->down!=NULL){
		master=&((*master)->down);
	}
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
	//up to here is good
	//printMaster(master);
	
	while((*sortedLL)->next!=NULL){
		replace=(node*)malloc(sizeof(node));
		data=(*sortedLL)->data;
	//	printf("DATA: %s\n", data);
		temp3=temp1;
		temp4=temp2;
		while((*temp3)->down!=NULL && (*temp4)->down!=NULL){

			if(strcmp((*temp4)->data, data)==0){
				copyLL(&replace, temp3, 1);
				replace=replace->next;
		//		printLL(&replace);
		//		printf("\n");	
				connectLL(master, &replace);
				master=&((*master)->down);
				break;
			}
		
			temp3=&((*temp3)->down);
			temp4=&((*temp4)->down);
			if(strcmp((*temp4)->data, data)==0){
			//	printf("connected\n");
			//	printf("temp3: %s\n", (*temp3)->data);
				copyLL(&replace, temp3, 1);
				replace=replace->next;
			//	printLL(&replace);
			//	printf("\n");	
				connectLL(master, &replace);
				master=&((*master)->down);
				break;
			}
		}
		temp3=temp1;
		temp4=temp2;
		sortedLL=&((*sortedLL)->next);
	}
		replace=(node*)malloc(sizeof(node));
		data=(*sortedLL)->data;
		//printf("DATA: %s\n", data);
		temp3=temp1;
		temp4=temp2;
		//printf("temp3: %s\n", (*temp3)->data);
		//printf("temp4: %s\n", (*temp4)->data);
		while((*temp3)->down!=NULL && (*temp4)->down!=NULL){
		//	printf("temp4: %s\n", (*temp4)->data);

			if(strcmp((*temp4)->data, data)==0){
			//	printf("connected\n");
			//	printf("temp3: %s\n", (*temp3)->data);
				copyLL(&replace, temp3, 1);
				replace=replace->next;
			//	printLL(&replace);
			//	printf("\n");	
				connectLL(master, &replace);
				master=&((*master)->down);
				break;
			}
		
			temp3=&((*temp3)->down);
			temp4=&((*temp4)->down);
		}
	if((*temp4)->down==NULL){
		if(strcmp((*temp4)->data, data)==0){
		//	printf("connected\n");
		//	printf("temp3: %s\n", (*temp3)->data);
			copyLL(&replace, temp3, 1);
			replace=replace->next;
		//	printLL(&replace);
		//	printf("\n");	
			connectLL(master, &replace);
			master=&((*master)->down);
			}
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
	if((*temp2)->next==NULL){
		i=strcmp((deleteSpace(deleteQ((*temp2)->dataType))), sortData);
		if(i!=0){
			printf("Chosen Sort Variable is Wrong");
			exit(0);
		}	
	}

	//temp1 should still be at the head of the first LL in our box
	//temp 2 should now be at the column to be sorted

	temp1=&((*temp1)->down);
	temp2=&((*temp2)->down);


	
	while((*temp1)->down!=NULL && (*temp2)->down!=NULL){
		appendSort(headLL, (*temp1)->dataType, (*temp2)->data);
		temp1=&((*temp1)->down);
		temp2=&((*temp2)->down);	

	}
	appendSort(headLL, (*temp1)->dataType, (*temp2)->data);
	
}
