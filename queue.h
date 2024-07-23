#ifndef QUEUES
#define QUEUES

#include "header.h"
#define commite_key 0x1234
#define family_key 0x2002


typedef struct {
   int starvation_rate;
}Family;

typedef struct {
    int data; // Example field
} Bags;


/* For access the Queue */
int get_queue(int key){

    int queue;

    if ( (queue = msgget(key, IPC_CREAT | 0777)) == -1 ) {
        perror("Queue Access Error\n");
        exit(-1);
    }

    return queue;
}

/*
int check_queue_empty(int queue, long queue_type){ // zeha ll families to find the family with higher stravation .

    if(msgrcv(queue, NULL, 0, queue_type, IPC_NOWAIT) == -1){
        if(errno == E2BIG)
            return 0; // There is data

    }
    return 1; // Empty queue
}
*/

int check_queue_empty(int queue) {
    if (msgrcv(queue, NULL, 0, 0, IPC_NOWAIT) == -1) {
        if (errno == E2BIG)
            return 0; // There is data
    }
    return 1; // Empty queue
}





#endif
