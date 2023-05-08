/* program to check the producer consumer problem using with semaphore and mutex */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>



// function declaration
void * producer1();
void * producer2();
void * consumer();
// declaration of variables
int count = 0;
char buffer[5];



//declaration of mutex
pthread_mutex_t mutex1,mutex2;
// declaration of sem_t
sem_t full, empty;
/* in success it return 0. on failure it return -1 */


int main()
{
    pthread_t pro1,pro2,con;
    sem_init(&full,0,0);
    sem_init(&empty,0,5);
    
    // 	Creating a thread for producer1
    if(pthread_create(&pro1,NULL,&producer1,NULL) !=0)
    {
        perror("Thread failed to create\n");
        exit(EXIT_FAILURE);
    }
    
    // 	Creating a thread for producer1
    if(pthread_create(&pro2,NULL,&producer2,NULL) !=0)
    {
        perror("Thread failed to create\n");
        exit(EXIT_FAILURE);
    }
    
    // 	Creating a thread for consumer
    if(pthread_create(&con,NULL,&consumer,NULL) !=0)
    {
        perror("Thread failed to create\n");
        exit(EXIT_FAILURE);
    }





   // Joining the thread producer
    if(pthread_join(pro1, NULL)!=0)
    {
        perror("Thread failed to join\n");
        exit(EXIT_FAILURE);
    }



       // Joining the thread producer
    if(pthread_join(pro2, NULL)!=0)
    {
        perror("Thread failed to join\n");
        exit(EXIT_FAILURE);
    }




   /* Joining the thread consumer
    if(pthread_join(con, NULL)!=0)
    {
        perror("Thread failed to join\n");
        exit(EXIT_FAILURE);
    }

*/



   exit(EXIT_SUCCESS);
}



// function for producer1
void *producer1()
{
    // declaring an variable
    int i = 0;
    char c = 'A';
       
       // infinite while loop
    while(1)
    {
	// decrements by one the value of the semaphore
        sem_wait(&empty);
        // locks the mutex1
        pthread_mutex_lock(&mutex1);
        
        //locks when count becomes 5 
        while(count == 5);
        
	// buffer that will save till the buffer size
        buffer[i] = c;
	// condition to increment i value till buffer size
        i = (i + 1) % 5;
        
	// for printing the stored buffer of producer
        if (i == 0)
        {
            c = 'A';
            printf("Producer 1 : %s\n", buffer);
        }


	// condition to increment the c value
       else
        {
            c++;
        }
               count++;
              // un-locking the mutex1
               pthread_mutex_unlock(&mutex1);
		// Increments by one the value of the semaphore
               sem_post(&full);
     }
     
     pthread_exit("exit");
}




// function for producer2
void *producer2()
{
    // declaring an variable
    int i = 0;
    char c = 'A';
       
       // infinite while loop
    while(1)
    {
	// decrements by one the value of the semaphore
        sem_wait(&empty);
        // locks the mutex1
        pthread_mutex_lock(&mutex1);
        
        //locks when count becomes 5 
        while(count == 5);
        
	// buffer that will save till the buffer size
        buffer[i] = c;
	// condition to increment i value till buffer size
        i = (i + 1) % 5;
        
	// for printing the stored buffer of producer
        if (i == 0)
        {
            c = 'A';
            printf("Producer 2 : %s\n", buffer);
        }


	// condition to increment the c value
       else
        {
            c++;
        }
               count++;
              // un-locking the mutex1
               pthread_mutex_unlock(&mutex1);
		// Increments by one the value of the semaphore
               sem_post(&full);
     }
     
     pthread_exit("exit");
}




//function for consumer to consume
void *consumer()
{
    int i = 0;
    char data[5];
    
    while(1)
    {
	// Decrements by one the value of the semaphore
         sem_wait(&full);
         // locking mutex 2
         pthread_mutex_lock(&mutex2);
         while(count == 0);
	 // condition to store the buffer(index) into data(index)
         data[i] = buffer[i];
	// condition to increment i value till buffer size
         i = (i+1) % 5;
         if (i == 0)
         {
            printf("Consumer : %s\n",data);
         }
            count--;
            // un-locking the mutex2
            pthread_mutex_unlock(&mutex2);
	    // Increments by one the value of the semaphore
            sem_post(&empty);
    }
    pthread_exit("exit");
}
