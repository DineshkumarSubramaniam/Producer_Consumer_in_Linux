/* program to print the producer consumer data's with semaphore */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

// function declaration
void *producer();
void *consumer();
// variable declaration 
sem_t full,empty;
char buffer[10];
int counter = 0 ;

int main()
{
	pthread_t t1,t2;
	//void *thread_result;
	sem_init (&full,0,0);
	sem_init(&empty,0,10);
	// first thread creation(producer)
	if(pthread_create(&t1,NULL,&producer,NULL) !=0)
	{
		perror("Thread failed to create\n");
		exit(EXIT_FAILURE);
	}
	// second thread creation(consumer)
	if(pthread_create(&t2,NULL,&consumer,NULL) !=0)
	{
		perror("Thread failed to create\n");
		exit(EXIT_FAILURE);
	}

	// Joining the thread
	if(pthread_join(t1, NULL)!=0)
	{
		perror("Thread failed to join\n");
		exit(EXIT_FAILURE);
	}

	// Joining the thread
	if(pthread_join(t2, NULL)!=0)
	{
		perror("Thread failed to join\n");
		exit(EXIT_FAILURE);
	}

}

// function 
void *producer()
{
	// declaring an variable
	int i = 0,value;
	char c = 'A';

	// infinite while loop
	while(1)
	{
		// decrements by one the value of the semaphore
		sem_wait(&empty);
		while(counter == 10);
		/*  {
		  break;
		  } */

		// buffer that will save till the buffer size
		buffer[i] = c;
		// condition to increment i value till buffer size
		i = (i + 1) % 10;

		// for printing the stored buffer of producer
		if (i == 0)
		{
			c = 'A';
			printf("Producer : %s\n", buffer);
		}

		// condition to increment the c value
		else
		{
			c++;
		}
                 counter++;
		// Increments by one the value of the semaphore
		sem_post(&full);
	}
	pthread_exit("exit");
}


void *consumer()
{
	int i = 0,value;
	char data[10];

	while(1)
	{
		// Decrements by one the value of the semaphore
		sem_wait(&full);

		while(counter == 0);

		// condition to store the buffer(index) into data(index)
		data[i] = buffer[i];
		// condition to increment i value till buffer size
		i = (i+1) % 10;
		if (i == 0)
		{
			printf("\t\t\t\tConsumer : %s\n",data);
		}
                 counter--;
		// Increments by one the value of the semaphore
		sem_post(&empty);
	}
	pthread_exit("exit");
}


