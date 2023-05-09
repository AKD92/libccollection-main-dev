

/************************************************************************************
    Implementation of Queue Data Structure (Base is Linked List)
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/







#include <stdlib.h>
#include "queue.h"







int queue_enqueue(Queue *queue, const void *data) {
    
    return slist_ins_next((SList *) queue, slist_tail(queue), data);
}




int queue_dequeue(Queue *queue, void **data) {
    
    return slist_rem_next((SList *) queue, NULL, data);
}



