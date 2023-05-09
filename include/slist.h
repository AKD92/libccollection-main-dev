

/************************************************************************************
    Program Interface (Function Prototypes) of Singly Linked List
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED




#include <stdlib.h>





/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************      DATA STRUCTURES      **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



struct SListElem_ {

    void *data;
    struct SListElem_ *next;

};
typedef struct SListElem_ SListElem;




struct SList_ {

    unsigned int size;
    void (*destroy) (void *data);                     /* Called when a List object is destroyed */

    SListElem *head;
    SListElem *tail;

};
typedef struct SList_ SList;





/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************     PUBLIC INTERFACE      **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*
 *  Returns the number of data elements the linked list is currently holding.
 *
 *  Parameter:
 *      list        :   Pointer to a singly linked list
 *
 *  Returns:
 *      (unsigned int)  Number of elements the specified list is holding.
*/
#define slist_size(list) ((list)->size)





/*
 *  Returns a pointer to a ListElem object which is next to
 *  the specific ListElem object.
 *
 *  Parameter:
 *      elem        :   Pointer to a ListElem object
 *
 *  Returns:
 *      (ListElem *)    Pointer to the next ListElem object
*/
#define slist_next(elem) ((elem)->next)





/*
 *  Returns a pointer to a ListElem object which is the head
 *  of the specified linked list.
 *
 *  Parameter:
 *      list        :   Pointer to a linked list object
 *
 *  Returns:
 *      (ListElem *)    Pointer to the ListElem object which is the head
*/
#define slist_head(list) ((list)->head)





/*
 *  Returns a pointer to a ListElem object which is the tail (last)
 *  of the specified linked list.
 *
 *  Parameter:
 *      list        :   Pointer to a linked list object
 *
 *  Returns:
 *      (ListElem *)    Pointer to the ListElem object which is the tail
*/
#define slist_tail(list) ((list)->tail)





/*
 *  Checks if the specified ListElem object is the head of the
 *  specified linked list object or not.
 *
 *  Parameter:
 *      list        :   Pointer to a linked list object
 *      elem        :   Pointer to a ListElem object
 *
 *  Returns:
 *      1 if elem is the head of list
 *      0 if it does not
*/
#define slist_is_head(list, elem) ((elem) == (list)->head ? 1 : 0)





/*
 *  Checks if the specified ListElem object is the tail of the
 *  specified linked list object or not.
 *
 *  Parameter:
 *      list        :   Pointer to a linked list object
 *      elem        :   Pointer to a ListElem object
 *
 *  Returns:
 *      1 if elem is the tail of list
 *      0 if it does not
*/
#define slist_is_tail(list, elem) ((elem) == (list)->tail ? 1 : 0)





/*
 *  Returns a pointer to the data element of the specified ListElem object.
 *
 *  Parameter:
 *      elem        :   Pointer to a ListElem object
 *
 *  Returns:
 *      (void *)        Pointer to the data element
*/
#define slist_data(elem) ((elem)->data)





/*
 *  Initializes a singly linked list with an optional destruction
 *  function for the data elements.
 *  This destruction function will only be called when list_destroy
 *  will be executed.
 *
 *  Parameter:
 *      list        :   Pointer to a singly linked list which is being initialized
 *      destroy     :   Pointer to a destruction function for data elements
 *                      (can be NULL)
 *
 *  Returns:
 *      0 for successful
*/
int slist_init(SList *list, void (*destroy) (void *data));





/*
 *  Destroyes a previously initialized singly linked list.
 *  If the list is NULL, this function does nothing.
 *
 *  Parameter:
 *      list        :   Pointer to a singly linked list which is being destroyed
 *
 *  Returns:
 *      (void)
*/
void slist_destroy(SList *list);





/*
 *  Inserts a data element into the linked list.
 *  The data element will be inserted right after the ListElem
 *  element provided.
 *
 *  Parameter:
 *      list        :   Pointer to a singly linked list
 *      elem        :   Pointer to a ListElem object after which the specified data
 *                      pointer will be inserted
 *                      If elem is 0 (NULL), the data pointer will be inserted
 *                      on the head (top) of the linked list and the element which
 *                      was the head of the linked list will be the 2nd element
 *      data        :   Pointer to a data element which will be inserted into the list
 *
 *  Returns:
 *      0 for successful
 *      -1 if an error occurs
*/
int slist_ins_next(SList *list, SListElem *elem, const void *data);





/*
 *  Removes a data element from the linked list which is next to
 *  the specified ListElem.
 *
 *  Parameter:
 *      list        :   Pointer to a singly linked list
 *      elem        :   Pointer to a ListElem object which is the previous ListElem object
 *                      If elem is 0 (NULL), the head (top) of the linked list will be
 *                      removed and the rest of the ListElem objects will be adjusted properly
 *      data        :   Pointer to a pointer which will receive the pointer to the
 *                      data element of the removed ListElem object
 *                      (can not be NULL)
 *
 *  Returns:
 *      0 for successful
 *      -1 if an error occurs
*/
int slist_rem_next(SList *list, SListElem *elem, void **data);





/*
 *  Check if an element exists into the linked list or not.
 *
 *  Parameter:
 *      list        :   Pointer to a singly linked list
 *      data        :   Pointer to a data element which is being searched
 *      elem        :   Pointer to a ListElem pointer which will point to the element container found,
 *                      If not found, it won't be touched and will contain original value.
 *      comparator  :   Pointer to a comparison function by which the data elements
 *                      will be compared with each other
 *
 *  Returns:
 *      1 if data exists on the linked list
 *      0 if data does not exist
 *      -1 if data is NULL
*/
int slist_search(SList *list, void *data, SListElem **elem,
                 int (*comparator) (const void *data1, const void *data2));





#endif


