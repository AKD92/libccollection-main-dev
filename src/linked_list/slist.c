

/************************************************************************************
    Implementation of Singly Linked List
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include <stdlib.h>
#include <string.h>
#include "slist.h"








int slist_init(SList *list, void (*destroy) (void *data)) {
    
    if (list == NULL)
        return -1;
        
    /*  Initialize the specified list */
    memset((void *) list, 0, sizeof(SList));
    
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    
    return 0;
}





void slist_destroy(SList *list) {

    void *data;
    int rem_result;
    
    
    /*  Check for invalid arguments */
    if (list == NULL)
        return;
    
    
    /*  Remove elements from the head of the List
        until no element is left, and 'destroy' each removed
        element if the 'destroy' function is provided to dispose
        user-specified elements.
    */
    while(slist_size(list) > 0) {
        rem_result = slist_rem_next(list, NULL, &data);
        
        /*  ret-val = 0 means, an object was removed successfully */
        if (rem_result == 0 && list->destroy != NULL) {
            list->destroy((void *) data);
        }
    }
    
    return;
}




int slist_ins_next(SList *list, SListElem *elem, const void *data) {

    SListElem *new_elem;
    
    
    /*  Check for invalid arguments */
    if (list == NULL)
        return -1;
    
    
    /*  Create new node element to hold the element */
    new_elem = (SListElem*) malloc(sizeof(SListElem));
    if (new_elem == 0)
        return -1;
    
    
    /*  Associate the user-specified element with this node element */
    new_elem->data = (void*) data;
    
    
    /*  We insert this new node into the head of the List */
    if (elem == NULL) {
        if (slist_size(list) == 0)
            list->tail = new_elem;
        
        new_elem->next = list->head;
        list->head = new_elem;
        
    }
    
    /*  Insert this new node after the node specified as elem */
    else {
        if (slist_is_tail(list, elem) == 1)
            list->tail = new_elem;

        new_elem->next = elem->next;
        elem->next = new_elem;

    }
    
    slist_size(list) += 1;
    return 0;
}




int slist_rem_next(SList *list, SListElem *elem, void **data) {

    SListElem *old_elem;
    
    
    /*  Check for invalid arguments */
    if (list == NULL || data == NULL)
        return -1;
    if (slist_size(list) == 0)
        return -1;
    
    
    /*  Remove the first node (head) of the List */
    if (elem == NULL) {
        old_elem = slist_head(list);
        *data = old_elem->data;
        list->head = old_elem->next;
        if (slist_is_tail(list, old_elem) == 1)
            list->tail = NULL;
    }
    
    /*  Remove the node which is the next node of the specified elem */
    else {
        if (slist_next(elem) == NULL)
            return -1;

        old_elem = slist_next(elem);
        *data = slist_data(old_elem);
        elem->next = old_elem->next;
        if (slist_is_tail(list, old_elem) == 1)
            list->tail = elem;

    }
    
    slist_size(list) -= 1;
    free((void *) old_elem);
    return 0;
}




int slist_search(SList *list, void *data, SListElem **elem,
                 int (*comparator) (const void *data1, const void *data2)) {
    int cmpres;
    int res;
    register SListElem *n;

    res = 0;
    n = slist_head(list);

    if (data == NULL)
        return -1;
    
    while (n != NULL) {

        cmpres = comparator(data, n->data);
        if (cmpres == 0) {
            *elem = n;
            res = 1;
            break;
        }
        n = slist_next(n);
    }
    return res;
}
