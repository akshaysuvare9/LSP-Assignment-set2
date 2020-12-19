#define _GNU_SOURCE
#define _FILE_OFFSET_BITS 64
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/resource.h>
void *print_message_function(void *ptr);
int main(int argc, char **argv)
{
		int num,i;
		struct rlimit v;
		if(argc!=2)
		{
				printf("Usage: mtspawn no_of_threads\n");
				return 0;
		}
		num=atoi(argv[1]);
		if (prlimit(getpid(),RLIMIT_NPROC, NULL, &v) == -1)
				perror("prlimit fail");
		if((num > v.rlim_cur ) && (num >v.rlim_max))
		{
				printf("attention....... limit exceeded soft=%lld hard=%lld\n",(long long) v.rlim_cur, (long long) v.rlim_max);
				return 0;
		}
		pthread_t *thread;
		thread=malloc(sizeof(pthread_t)*num);
		const char *message1="Thread..";
		int iret[num];
		for(i=0;i<num;i++)
		{
				iret[i] = pthread_create( &thread[i], NULL, print_message_function, (void*)message1);
				if(iret[i])
				{
						perror("thread");
						exit(EXIT_FAILURE);
				}

				printf("thread %d created returns:%ld\n",i,thread[i]);
		}
		for(i=0;i<num;i++)
		{
				printf("thread %ld is joined\n",thread[i]);
				pthread_join(thread[i],NULL);
		}
		exit(EXIT_SUCCESS);
}
void *print_message_function(void *ptr)
{
		char *message;
		message = (char*)ptr;
		printf("%s\n",message);
		sleep(3); //optional
}
