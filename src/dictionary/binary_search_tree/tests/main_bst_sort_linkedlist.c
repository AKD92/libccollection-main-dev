

#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include "avl.h"




static int cmpInt(const void *arg1, const void *arg2);


int main(void) {
    
    List numList;
    ListElem *elem;
    int *pElem;
    unsigned int iTotal, i;
    
    list_init(&numList, free);
    
    printf("Enter total integers to input:\n");
    scanf("%u", &iTotal);
    
    printf("Enter each number:");
    for (i = 0; i < iTotal; i++) {
        pElem = (int *) malloc(sizeof(int));
        scanf("%d", pElem);
        list_ins_next(&numList, list_tail(&numList), (const void *) pElem);
    }
    printf("\n\n");
    
    printf("Printing integers from Linked List (Size: %u)\n", list_size(&numList));
    elem = list_head(&numList);
    while (elem != 0) {
        pElem = (int *) list_data(elem);
        printf("%d (%p): ", *pElem, pElem);
        elem = list_next(elem);
    }
    printf("\n\n");
    
    printf("Applying TreeSort Algorithm to Linked List\n");
    avl_treesort_desc(&numList, cmpInt);
    
    printf("Printing After Sorting Integers (Size: %u)\n", list_size(&numList));
    elem = list_head(&numList);
    while (elem != 0) {
        pElem = (int *) list_data(elem);
        printf("%d (%p): ", *pElem, pElem);
        elem = list_next(elem);
    }
    printf("\n\n");
    
    list_destroy(&numList);
    
    return 0;
}




static int cmpInt(const void *arg1, const void *arg2) {
    
    int *a, *b;
    
    a = (int *) arg1;
    b = (int *) arg2;
    return (*a - *b);
}
