#ifndef SEMAPHORES
#define SEMAPHORES

#include "header.h"


char *SAFEAREA_SEMAPHORE = "1234";   //sem key to manage between splittors and collectors
char *CONTAINER_SEMAPHORE = "5678";
char *READ_SAFEAREA_SEMAPHORE  = "1478";
char *FamilyBags_SEMAPHORE= "8888";


char *Bags_SEMAPHORE= "2242";


/*
 * Sem: 1
 * P1: Sem --> 0 through operation, when finish release it to 1 Sem --> 1
 */
sem_t* get_semaphore( char* key){

    sem_t* sem = sem_open(key, O_CREAT, 0777, 0);
    if(sem == SEM_FAILED){
        perror("Semaphore Open Error\n");
        exit(-1);
    }

    return sem;
}

void attach_semaphore(sem_t* sem){

    // When return 0 for successful access
    if (sem_wait(sem) < 0){
        perror("Semaphore Wait Error\n");
        exit(-1);
    }

}

void detach_semaphore(sem_t* sem){

    // When return -1 then wrong issue happened
    if (sem_post(sem) < 0){
        perror("Semaphore Release Error\n");
        exit(-1);
    }



}


void close_semaphore(sem_t* sem){
    // Close the Semaphore
    sem_close(sem);
}

void create_semaphore(char* key){

    sem_t* sem = sem_open(key, O_CREAT, 0777, 0);
    if(sem == SEM_FAILED){
        perror("Semaphore Creation Error\n");
        exit(-1);
    }

    // When return -1 then wrong issue happened
    if (sem_post(sem) < 0){
        perror("Semaphore Release Error\n");
        exit(-1);
    }

    sem_close(sem);

}




#endif
