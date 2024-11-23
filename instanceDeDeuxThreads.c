#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>


#define NMAX 10

sem_t semaphore;
// int valeur = 0;

void *fonctionIncrementation()
{
    FILE *fichier = fopen("courbe.data", "a");
    if(!fichier)
	{
		perror("Erreur de Creation du fichier");
		return  0;	
	}

    for(int i = 0 ; i <= NMAX ; i++)
    {   
        sem_wait(&semaphore);
        // valeur = i;
        fprintf(fichier,"%d \n",i);
        sem_post(&semaphore);
        sleep(1);
    }
    pthread_exit(NULL);
}
void *fonctionDecrementation()
{
    FILE *fichier = fopen("courbe.data", "a");
    if(!fichier)
	{
		perror("Erreur de Creation du fichier");
		return  0;	
	}
    for(int i = -NMAX ; i < 0 ; i++)
    {   
        sem_wait(&semaphore);
        // valeur = i;
        fprintf(fichier,"%d\n",i);
        sem_post(&semaphore);
        sleep(1);
    }
    fclose(fichier);
    pthread_exit(NULL);
}
int main(int argc , char *argv[])
{
    pthread_t thread1,thread2;
    sem_init(&semaphore,0,1);

    pthread_create(&thread1,NULL,fonctionIncrementation, NULL);
    wait(NULL);
    pthread_create(&thread2,NULL,fonctionDecrementation,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    sem_destroy(&semaphore);

    printf("Les Resultas sont Enregistre avec succes dans le fichier : << Courbe.data >> \n");

}

/*
============== POUR LA COURBE ========================

gnuplot> set terminal pngcairo  //Nous avons le Terminal pngcairo

Terminal type is now 'pngcairo'
Options are ' background "#ffffff" enhanced fontscale 1.0 size 640, 480 '
gnuplot> set output 'imageCourbe.png'
gnuplot> plot 'courbe.data' with lines lw 3 smooth bezier

pour l'Afficher on peut aussi le faire avec  la Commande : atril 

==> atril imageCourbe.png
*/