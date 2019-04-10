//By Sharishth
#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>//sleep,read,write
pthread_t Student[1000];
pthread_t TA;
//pthread_t TA1;
int i1,i=0,n;
int TAs;
int inchair;//awake sate
sem_t signal,signal1;
void *fun();//indicate
void *wake();//wake up TA

void *help();
void *sleeping();
void *next();
////////////////////////////
main()
{
 sem_init(&signal,1,1);
 sem_init(&signal1,1,1);
 int n1;
 printf("\nEnter Number of students=> ");
 scanf("%d",&n1);
 n=n1;
 	
	
		printf("\nTA is sleeping\n");
	
 for(i1=0;i<n;i++)
 {
 	pthread_create(&Student[i1],NULL,&fun,NULL);
 	pthread_join(Student[i1],NULL);
 }
 
}
//////////////////////////
void *fun()
{
	
	if(i==1)
	{
		pthread_create(&TA,NULL,&wake,NULL);
		pthread_join(TA,NULL);
		//TAs=1 is awake state
	}
	printf("\nStudent %d created\n",i);
	if(i==(n-1))
	{
		
		printf("%d students in total",n);

		if(n>4)
		{
			printf("\nstudents after Student 4 will have to come again later\n");
		}
		
	}
}
//////////////////
void *wake()
{
	
	int x;
	sem_wait(&signal);
	x=TAs;
	x++;
	sleep(1);
	TAs=x;
	printf("\nTa is Awaked by the student who entered");
	sem_post(&signal);
	if(TAs==1)
	{
		pthread_create(&TA,NULL,&help,NULL);
		pthread_join(TA,NULL);
	}
	
}
//////////////////
void *help()
{
	inchair=1;
	printf("\nTA is Helping a Student\n");
	printf("%d in office chair is occupied\n",inchair );
	if (inchair==1)
	{
		printf("\nRest of the Student please wait outside\n");
		printf("Done helping, Next?\n");
		inchair=0;
		printf("\nin office chair is empty\n");
		pthread_create(&TA,NULL,&sleeping,NULL);
		pthread_join(TA,NULL);
		//i++;//new
	}
	for(i1=1;i<n;i++)
	{
		pthread_create(&TA,NULL,&wake,NULL);
		pthread_join(TA,NULL);
	}

}	
void *sleeping()
{
	int y;
	sem_wait(&signal1);
	y=TAs;
	y=0;
	sleep(1);
	TAs=y;
	printf("\nTa can sleep");
	sem_post(&signal1);
}