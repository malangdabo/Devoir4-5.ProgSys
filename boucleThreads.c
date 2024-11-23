#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 10

int enCoursExecution ;
pthread_mutex_t mutex ;

void *bouclerThreads(void* arg)
{
    int idThreads = *((int*)arg);
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if (idThreads == enCoursExecution)
        {
            printf("Thread %d en cours d'Execution.\n",idThreads+1);
            enCoursExecution = (enCoursExecution+1) % N ;
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        
    }
    return  NULL ;
}

int main()
{
    pthread_t threads[N];
    int idThreads[N];
    if(pthread_mutex_init(&mutex,NULL) != 0)
    {
        perror("Erreur d'Initialisation du MUTEX");
        return 1; 
    }
    while(1) 
    {
        for(int i = 0 ; i < N ; i++)
        {
            idThreads[i] = i ;
            if(pthread_create(&threads[i],NULL,bouclerThreads,&idThreads[i]) != 0)
            {
                perror("Erreur lors de la Creation de Theead");
                return 1;
            }
        }
        for(int i = 0 ; i < N ; i++)
            pthread_join(threads[i],NULL);
        pthread_mutex_destroy(&mutex);
    }
}









