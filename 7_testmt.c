#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include<unistd.h>
#define SIZE 4096
#include<sys/sysinfo.h>
typedef struct{
		unsigned long offset;
		unsigned long size;
}PART;

char file[50]; /* source file name */
char fileout[50]; /* target file name */

void* func1(void *arg);

int main(int argc, char *argv[]){
		char 		data[SIZE];
		struct stat 	f_stat;
		int 		fin1, fout1, x, chk, i=0,n=0,j=0;
		printf("%d processors available.\n",n=get_nprocs());
		PART **part;

		pthread_t 	*t; // two threads to share the load of main thread

		//dynamic memory allocation
		part=malloc(sizeof(PART*)*n);
		for(i=0;i<n;i++)
				part[i]=malloc(sizeof(PART));
		t=malloc(sizeof(pthread_t)*n);

		if(argc < 3){
				puts("Not enough arguments.");
				puts("parallelCopy sourceFile targetFile");
				return -1;
		}
		strcpy(file, argv[1]);
		stat(file, &f_stat); 	// getting the meta info of file
		strcpy(fileout, argv[2]);

		// dividing the size of file in n parts
		part[0]->size = f_stat.st_size / n; 
		part[0]->offset=0;
		for(i=1;i<n;i++)
		{
				part[i]->offset = part[i-1]->size+part[i-1]->offset;
				part[i]->size = part[i-1]->size;
		}
		printf("Size of file is %lu \n", f_stat.st_size);
		/* creating part1 by main thread */
		fin1 = open(file, O_RDONLY);
		fout1 = open(fileout, O_WRONLY|O_CREAT, 0666);

		/*creating n threads to copy 2 n 3rd part of file */
		for(i=0;i<n-1;i++)
		{
				pthread_create(&t[i], NULL, func1, part[i+1]);
				printf("%ld thread is created\n",t[i]);
		}
		while(j < part[0]->size){	
				x = read(fin1, data, SIZE);
				write(fout1, data, x);
				j += x;
		}
		for(i=0;i<n-1;i++)
		{
				pthread_join(t[i], NULL); // making main to wait for t2
		}
		printf("file is copied");
		close(fout1);
		close(fin1);
		return 0;
}

void* func1(void *arg){
		int fin, fout, x,i;
		long int prev;
		PART *part;
		char data[SIZE];
		part = (PART *)arg;
		fin = open(file, O_RDONLY);
		fout = open(fileout, O_WRONLY);
		lseek(fin, part->offset, SEEK_SET);
		lseek(fout, part->offset, SEEK_SET);
		while(i < part->size){
				x = read(fin, data, SIZE);
				write(fout, data, x);
				i += x;
				//		printf("copied i=>%d size=>%ld\n",i,part->size);
		}
		printf("%ld thread is done.\n",pthread_self());
		close(fout);
		close(fin);
}
