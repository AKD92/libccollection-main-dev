

/************************************************************************************
    Implementation of Binary Heap Algorithms for Sorting arrays (Traditional Heap Sort)
    Using Binary Heap Data Structure
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bh.h"







int bh_heapsort
(
    void *pArray,
    unsigned int nCount,
    unsigned int nWidth,
    int (*fpCompare) (const void *agr1, const void *arg2)
)
{
    
    return bh_heapsort_asc(pArray, nCount, nWidth, fpCompare);
}



int bh_heapsort_asc
(
    void *pArray,
    unsigned int nCount,
    unsigned int nWidth,
    int (*fpCompare) (const void *agr1, const void *arg2)
)
{
    
    BiHeap heap;
    register unsigned int iCurrent;
    
    
    /* Check for invalid algorithm arguments */
    if (pArray == 0 || fpCompare == 0 || nWidth == 0)
        return -1;
    if (nCount < 2)
        return 0;
    
    
    /* Build a Binary MAX Heap on top of the pArray */
    bh_init(&heap, pArray, nCount, nWidth, fpCompare);
    bh_build_maxheap(&heap);
    
    
    /* SINK all lighter elements down the Binary MAX Heap (pArray) */
    iCurrent = nCount - 1;
    while (iCurrent >= 1) {
        
        bh_swap (0, iCurrent, &heap);
        bh_size(&heap) = bh_size(&heap) - 1;
        bh_sink_light(&heap, 0);
        iCurrent = iCurrent - 1;
    }
    
    /* Destroy temporary Binary Heap wrapper object */
    bh_destroy(&heap);
    return 0;
}



int bh_heapsort_desc
(
    void *pArray,
    unsigned int nCount,
    unsigned int nWidth,
    int (*fpCompare) (const void *agr1, const void *arg2)
)
{
    
    BiHeap heap;
    register unsigned int iCurrent;
    
    
    /* Check for invalid algorithm arguments */
    if (pArray == 0 || fpCompare == 0 || nWidth == 0)
        return -1;
    if (nCount < 2)
        return 0;
    
    
    /* Build a Binary MIN Heap on top of the pArray */
    bh_init(&heap, pArray, nCount, nWidth, fpCompare);
    bh_build_minheap(&heap);
    
    
    /* SINK all heavier elements down the Binary MIN Heap (pArray) */
    iCurrent = nCount - 1;
    while (iCurrent >= 1) {
        
        bh_swap (0, iCurrent, &heap);
        bh_size(&heap) = bh_size(&heap) - 1;
        bh_sink_heavy(&heap, 0);
        iCurrent = iCurrent - 1;
    }
    
    /* Destroy temporary Binary Heap wrapper object */
    bh_destroy(&heap);
    return 0;
}


