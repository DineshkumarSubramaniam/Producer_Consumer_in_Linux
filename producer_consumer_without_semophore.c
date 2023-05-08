/* program to print the producer consumer data's without mutex and semaphore */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

// function declaration
void *producer();
void *consumer();
// variable declaration
int counter = 0;
char buffer[10];

int main()
{
	pthread_t t1,t2;
	//void *thread_result;

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
	int i = 0;
	char c = 'A';

	// infinite while loop
	while(1)
	{
		while(counter == 10);
		/* {
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
		// incrementing the counter variable
		counter++;
	}
	pthread_exit("exit");
}


//function
void *consumer()
{
	// declaring an variable
	int i = 0;
	char data[10];
	// Infinite while loop
	while(1)
	{ 

		while(counter == 0);
		// condition to store the buffer(index) into data(index)
		data[i] = buffer[i];
		// condition to increment i value till buffer size
		i = (i+1) % 10;
		if (i == 0)
		{
			printf("\t\t\tConsumer : %s\n",data);
		}
		// decrementing the counter variable
		counter--;

	}
	pthread_exit("exit");
}

