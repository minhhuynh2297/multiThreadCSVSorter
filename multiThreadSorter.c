#include <string.h> 
#include <dirent.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <pthread.h>
#include "multiThreadSorter.h"
int cT=0; 
node* master = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct _thread_args{
	char* directory;
	char* sort;

}thread_args;

void countThreads(const char *name){ // this is good 
    DIR *dir; //directory stream
    struct dirent *entry; //holds file serial # and file name

    if (!(dir = opendir(name))){ 
	printf("Error directory could not be opened or does not exist \n");
		return; 
        }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) { // checks if it a directory 
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){ //skips hidden paths
                continue; 
		} 
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name); //directly prints entry->d_name into path[1024]
		//printf("Name of Directory:%s\n",entry->d_name);
		cT++;
            countThreads(path);
            } 
	else if(entry->d_type = DT_REG){// list stuff in directory such as files and checks is its a csv. 
			char *str = entry->d_name;
			//printf("Name of file: %s\n",entry->d_name);
			char ch = '.';
			char *ret;
			char *csv;
			csv = ".csv"; 
			ret = strrchr(str, ch);

				if (strcmp(ret,csv)==0){
					cT++;
				} 

	        }
    }
    closedir(dir);
}

void printnumbers(int number){
	int i = 0; 
	while( i < number){
		if(i == number -1){
		printf("%d",i);
		break;
		} 

	printf("%d,",i);
	i++;
	}
	printf("\n");
}
//counts number of directories
void traverse_count(int* counter, char* directory){ // this is good 
    DIR *dir; //directory stream
    struct dirent *entry; //holds file serial # and file name

    if (!(dir = opendir(directory))){ 
	printf("Error directory could not be opened or does not exist \n");
		return; 
        }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) { // checks if it a directory 
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){ 
                continue; 
		} 
            snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name); 
		(*counter)++;
            traverse_count(counter, path);
            } 
    }
    closedir(dir);
}

void csv_count(int* counter, char* directory){
    DIR *dir; //directory stream
    struct dirent *entry; //holds file serial # and file name

    if (!(dir = opendir(directory))){ 
	printf("Error directory could not be opened or does not exist \n");
		return; 
        }

    while ((entry = readdir(dir)) != NULL) {
	if(entry->d_type = DT_REG){// list stuff in directory such as files and checks is its a csv. 
		char *str = entry->d_name;
		//printf("Name of file: %s\n",entry->d_name);
		char ch = '.';
		char *ret;
		char *csv;
		csv = ".csv"; 
		ret = strrchr(str, ch);

			if (strcmp(ret,csv)==0){
				(*counter)++;
			} 

       		 }
	}
}

//gives LL of all directory paths
void traverse(char *directory, node** dirList) {
	DIR *dir;
	struct dirent *entry;
	dir = opendir(directory);
	if(dir == NULL) {
		return;
	}
	appendData(dirList, directory);
	while((entry = readdir(dir))!=NULL){
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..")==0){
		continue;
		}
		if(entry->d_type == DT_DIR){
			char pathway[1024];
			snprintf(pathway, sizeof(pathway), "%s/%s", directory, entry->d_name);
			appendData(dirList, pathway);
			traverse(pathway, dirList);
			}

	        }
	return;
}


void* append_thread(void* sort){
	pthread_mutex_lock(&mutex);
	thread_args* append_args = (thread_args*)sort;
	char *line; //holds line by line 
	line = malloc(10000 * sizeof(char));
	char* fileName = malloc(sizeof(char)*1000);
	strcpy(fileName, append_args->directory);
	FILE* fp = fopen(fileName, "r");
	if(fp == NULL){
		printf("File not found\n");
		exit(-1);
	}
	//head to the csv file
	node* head=NULL; 

	//data to be sorted, sorted
	node* sortedLL=NULL;
	//create the "master" LL for the new, unsorted data to be attached to
	node* fakeMaster=NULL;
	node* tester=NULL;
	copyLL(&fakeMaster, &master, 0);
	//printFirst(&fakeMaster);
	fgets(line, 10000, fp);
	if(strlen(line)==0){
		printf("Empty CSV\n");
		exit(0);
	}
	writeFirstRow(&head, line); 
	
	node** oldRow = &fakeMaster;
	while((*oldRow)->down!=NULL){
		oldRow=&((*oldRow)->down);
	}

	while(!feof(fp)){
		fgets(line, 10000, fp);
		if(feof(fp)){
			break;
		}
	//	printf("%s\n", line);
		node* newHead=NULL;
		node** newRow=&newHead;
		nullWriteLL(newRow, &fakeMaster, &head, line);
		fillNULL(newRow);
	//	printf("%s\n", newHead->data);	
		connectLL(oldRow, newRow);
	//	printLL(newRow);
	//	printf("%s\n", (*oldRow)->down->data);		
		oldRow=&((*oldRow)->down);
	} 
	//printf("%s\n", fakeMaster->down->dataType);
	makeSortLL(&sortedLL, &fakeMaster, append_args->sort);
	mergeSort(&sortedLL);
//	printLL(&sortedLL);
	//printMaster(&fakeMaster);
	//printLL(&sortedLL);
	connectMaster(&master, &fakeMaster, &sortedLL, append_args->sort);	
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}


void* traverse_thread(void* args){
	char* newDir = malloc(sizeof(char) * 1000);
	//printf("%s\n", (char*)directory);
	thread_args* arguments = (thread_args*)args;
	strcpy(newDir, arguments->directory);
	int counter=0;
	csv_count(&counter, newDir);
	DIR *dir;
	struct dirent *entry;
	dir = opendir(newDir);
	if(dir == NULL) {
		return;
	}
	pthread_t thread1[counter];
	
	while((entry = readdir(dir))!=NULL){
		i=0;
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..")==0){
		continue;
		}
		if(entry->d_type = DT_REG){// list stuff in directory such as files and checks is its a csv. 
	
			char *str = entry->d_name;
			char ch = '.';
			char *ret;
			char *csv;
			csv = ".csv"; 
			ret = strrchr(str, ch);

				if (strcmp(ret,csv)==0){
				
					char path[1024];
					snprintf(path, sizeof(path), "%s/%s", newDir, entry->d_name);
					arguments->directory=path;
					pthread_mutex_unlock(&mutex);
					pthread_create(&thread1[i], NULL, append_thread, arguments);
					pthread_join(thread1[i], NULL);
					i++;
				}
						
			} 

	        }
	
	pthread_exit(0);
}

	
int main(int argc,char* argv[]){
	char * column = (char*)malloc(sizeof(char*)*200);
	char * directory = (char*)malloc(sizeof(char*)*200);
	char* output = (char*)malloc(sizeof(char*)*200);
	column = argv[2];
	
	if(strcmp(argv[1], "-c")!=0){
		printf("need -c\n");
		exit(0);
	}
	if(argc < 3 || argc > 7){
		printf("wrong input\n");
		exit(0);
	}
	
	if(argc==3){
		strcpy(directory, ".");
		strcpy(output, ".");
	}
	else if(argc==5){
		if(strcmp(argv[3], "-d")==0){
			strcpy(directory, argv[4]);
			strcpy(output, "");
		}
		else{
			strcpy(directory, ".");
			strcpy(output, argv[4]);
		}
	}
	else{
		strcpy(directory, argv[4]);
		strcpy(output, argv[6]);
	}
		
	if(argc!=3 && argv[3]!=NULL){
		if(strcmp(argv[3], "-d")!=0 && strcmp(argv[3], "-o")!=0){
		printf("need -d or -o\n");
		exit(0);
		}
	}
	if(argc > 5 && argv[5]!=NULL && strcmp(argv[5], "-o")!=0){
		printf("need -o\n");
		exit(0);
	}

	countThreads("test");
	printf("Initial PID:%d\n",getpid());
	printf("TIDS of all spawned Threads: ");
	int number = cT; 
	printnumbers(number);
	printf("Total number of Threads: %d\n",cT);


	int countDir=1;
	node* sortMaster=NULL;
	//gets number of directories
	traverse_count(&countDir, directory);
	//printf("%d\n", countDir);
	//create LL of categories

	createMaster(&master);	
	
	//send threads
	pthread_t thread[countDir];
	
	
	DIR *dir;
	struct dirent *entry;
	dir = opendir(directory);

	if(dir == NULL){
		return;
	}

	node* dirLL=NULL;
	char* newDirectory;
	traverse(directory, &dirLL);
	//printf("%s\n", dirLL->data);	
	thread_args* input=(thread_args*)malloc(sizeof(thread_args));
	input->sort=column;
	
	for(i=0; i<countDir; i++){
		node** temp5 = &dirLL;
		input->directory = (*temp5)->data;	
		pthread_create(&thread[0], NULL, traverse_thread, input); 
		temp5 = &(dirLL->next);
	}

	for(i=0; i<countDir; i++){
		pthread_join(thread[0], NULL);
	}
	//printMaster(&master);

	makeSortLL(&sortMaster, &master, column);
	mergeSort(&sortMaster);
	if(opendir(output) == NULL){
		int status;
		status = mkdir(output, S_IRWXU);
		if(status==1){
			printf("ERROR MAKING NEW DIRECTORY\n");
			exit(0);
		}
	}
	
	FILE *output1;
	
	char part1[100];
	char part2[100];
	memset(part1, '\0', sizeof(part1));
	strcpy(part1, "AllFiles-sorted-<");
	strcpy(part2, ">.csv");
	char fileName[100];
	strcpy(fileName, strcat(strcat(part1,column), part2));
	output1=fopen(fileName, "w");
	printBoxFile(&sortMaster, &master, column, output1);

} 
 

























