

/************************************************************************************
    Program Interface of Binary Heap Data Structure & Binary Heap Algorithms
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef BINARY_HEAP_DATA_STRUCTURE_H
#define BINARY_HEAP_DATA_STRUCTURE_H







/**********************************************************************************************/
/***********************************                       ************************************/
/***********************************    DATA STRUCTURES    ************************************/
/***********************************                       ************************************/
/**********************************************************************************************/




struct BinaryHeap_ {
    
    void *pArrayElem;                          /* Underlying memory blocks for the storage of elements  */
    
    unsigned int elemCount;                    /* Number of elements the heap is currently holding      */
    unsigned int elemWidth;                    /* The size of each element, in Bytes                    */
    
    int (*fpCompare)                           /* User specifed function for comparing array elements   */
            (const void *arg1, const void *arg2);
    
    void *pSwapMemory;                         /* Temporary memory used for faster swapping of elements */
                                               /* Size of this pSwapMemory must be equal to elemWidth   */
    
};
typedef struct BinaryHeap_ BiHeap;






/**********************************************************************************************/
/***********************************                       ************************************/
/***********************************   PUBLIC INTERFACES   ************************************/
/***********************************                       ************************************/
/**********************************************************************************************/



/*
 *  Initializes a binary deap data structure.
 *
 *  Parameter:
 *      heap                :   The binary heap data structure to be initialized
 *      pArray              :   The array which holds the elements of this data structure
 *                              The data from this array is not copied. All the heap
 *                              operation on this data structure will change the positions
 *                              of elements of this array (in-place)
 *      nCount              :   Number of elements this array holds at the time of calling
 *                              this function
 *      nWidth              :   Size of each element in bytes
 *      fpCompare           :   Comparison function to compare the elements in the array
 *                              This function should implement the 'total order' comparison
 *                              e.g. when comparing between a and b,
 *                              return negative value if a < b
 *                              return zero (0) if a = b and
 *                              return positive value if a > b
 *
 *  Returns
 *      (int)           (success) 0 for successful initialization
 *                      (failure) -1 for error
*/
int bh_init
(
    BiHeap *heap,
    void *pArray,
    unsigned int nCount,
    unsigned int nWidth,
    int (*fpCompare) (const void *arg1, const void *arg2)
);





/*
 *  Destroyes the specified binary heap data structure.
 *
 *  Parameter:
 *      heap                :   The binary heap data structure to be destroyed
 *
 *  Returns
 *      (void)
*/
void bh_destroy(BiHeap *heap);





/*
 *  Returns or sets the array the specified binary heap is currently using.
 *
 *  Parameter:
 *      heap                :   The binary heap data structure
 *
 *  Returns
 *      (void *)        Pointer to the array
*/
#define bh_array(heap)                  ((heap)->pArrayElem)





/*
 *  Returns or sets the number of elements the specified
 *  binary heap is currently holding.
 *
 *  Parameter:
 *      heap                :   The binary heap data structure
 *
 *  Returns
 *      (unsigned int)  Number of elements inside the heap
*/
#define bh_size(heap)                   ((heap)->elemCount)





/*
 *  Returns or sets size of each element in bytes of the specified
 *  binary heap.
 *
 *  Parameter:
 *      heap                :   The binary heap data structure
 *
 *  Returns
 *      (unsigned int)  Size of each element is bytes
*/
#define bh_width(heap)                  ((heap)->elemWidth)





/*
 *  Returns the zero based positional index number of the parent
 *  element for the specified positional index number of the
 *  child element.
 *
 *  Parameter:
 *      uChild              :   Positional index number of the child element
 *
 *  Returns
 *      (unsigned int)  Positional index number of the parent element
*/
#define bh_parent_index(uChild)          (((uChild) - 1) / 2)       /* Wikipedia - Binary Heap */





/*
 *  Returns the zero based positional index number of the left
 *  child element for the specified positional index number of the
 *  parent element.
 *
 *  Parameter:
 *      uParent             :   Positional index number of the parent element
 *
 *  Returns
 *      (unsigned int)  Positional index number of the left child element
*/
#define bh_leftchild_index(uParent)      (((uParent) * 2) + 1)





/*
 *  Returns the zero based positional index number of the right
 *  child element for the specified positional index number of the
 *  parent element.
 *
 *  Parameter:
 *      uParent             :   Positional index number of the parent element
 *
 *  Returns
 *      (unsigned int)  Positional index number of the right child element
*/
#define bh_rightchild_index(uParent)     (((uParent) * 2) + 2)





/*
 *  Swaps two elements specified by their zero based positional
 *  index number on the specified binary heap data structure.
 *
 *  Parameter:
 *      index1              :   Positional index number of the first element
 *      index2              :   Positional index number of the second element
 *
 *  Returns
 *      (int)           (success) 0 if the elements are swapped
 *                      (failure) -1 if heap is NULL or indexes are out of bounds
*/
int bh_swap(unsigned int index1, unsigned int index2, BiHeap *heap);





/*
 *  Push the element at the specified zero based positional index number
 *  into the bottom of the specified binary heap data structure
 *  such that the element will be lighter (smaller in comparison)
 *  than it's parent element.
 *  This operation is normally applied on the max binary heaps
 *  (where the most maximum element stays on top of the heap).
 *
 *  Parameter:
 *      heap                :   The binary heap data structure on which
 *                              the operation is being applied
 *      index               :   Zero based positional index number of the
 *                              element which is being pushed into the bottom
 *                              of the heap
 *
 *  Returns
 *      (int)           (success) 0 if the element is already at the bottom of the heap
 *                      (success) positive number denoting the number of swaps needed
 *                                to push the element
 *                      (failure) -1 if heap is NULL or index is out of bounds
*/
int bh_sink_light(BiHeap *heap, unsigned int index);





/*
 *  Push the element at the specified zero based positional index number
 *  into the top of the specified binary heap data structure
 *  such that the element will be heavier (larger in comparison)
 *  than both of it's child elements.
 *  This operation is normally applied on the max binary heaps
 *  (where the most maximum element stays on top of the heap).
 *
 *  Parameter:
 *      heap                :   The binary heap data structure on which
 *                              the operation is being applied
 *      index               :   Zero based positional index number of the
 *                              element which is being pushed into the top
 *                              of the heap
 *
 *  Returns
 *      (int)           (success) 0 if the element is already at the top of the heap
 *                      (success) positive number denoting the number of swaps needed
 *                                to push the element
 *                      (failure) -1 if heap is NULL or index is out of bounds
*/
int bh_swim_heavy(BiHeap *heap, unsigned int index);





/*
 *  Push the element at the specified zero based positional index number
 *  into the bottom of the specified binary heap data structure
 *  such that the element will be heavier (larger in comparison)
 *  than it's parent element.
 *  This operation is normally applied on the min binary heaps
 *  (where the most minimum element stays on top of the heap).
 *
 *  Parameter:
 *      heap                :   The binary heap data structure on which
 *                              the operation is being applied
 *      index               :   Zero based positional index number of the
 *                              element which is being pushed into the bottom
 *                              of the heap
 *
 *  Returns
 *      (int)           (success) 0 if the element is already at the bottom of the heap
 *                      (success) positive number denoting the number of swaps needed
 *                                to push the element
 *                      (failure) -1 if heap is NULL or index is out of bounds
*/
int bh_sink_heavy(BiHeap *heap, unsigned int index);





/*
 *  Push the element at the specified zero based positional index number
 *  into the top of the specified binary heap data structure
 *  such that the element will be lighter (smaller in comparison)
 *  than both of it's child elements.
 *  This operation is normally applied on the min binary heaps
 *  (where the most minimum element stays on top of the heap).
 *
 *  Parameter:
 *      heap                :   The binary heap data structure on which
 *                              the operation is being applied
 *      index               :   Zero based positional index number of the
 *                              element which is being pushed into the top
 *                              of the heap
 *
 *  Returns
 *      (int)           (success) 0 if the element is already at the top of the heap
 *                      (success) positive number denoting the number of swaps needed
 *                                to push the element
 *                      (failure) -1 if heap is NULL or index is out of bounds
*/
int bh_swim_light(BiHeap *heap, unsigned int index);





/*
 *  Rearranges the elements of the specified binary heap data structure
 *  such that the rearrangement will conform to the minimum heap property,
 *  where the most minimum element will be at the top of the heap.
 *
 *  Parameter:
 *      heap                :   Binary heap data structure which is being transformed
 *
 *  Returns
 *      (int)           (success) 0 if the transformation succeeded
 *                      (failure) -1 if heap is NULL
*/
int bh_build_minheap(BiHeap *heap);





/*
 *  Rearranges the elements of the specified binary heap data structure
 *  such that the rearrangement will conform to the maximum heap property,
 *  where the most maximum element will be at the top of the heap.
 *
 *  Parameter:
 *      heap                :   Binary heap data structure which is being transformed
 *
 *  Returns
 *      (int)           (success) 0 if the transformation succeeded
 *                      (failure) -1 if heap is NULL
*/
int bh_build_maxheap(BiHeap *heap);





/*
 *  Sorts the elements of the specified array using the HeapSort algorithm
 *  in ascending order.
 *  Time complexity of this algorithm is O(nlogn), where n = nCount
 *  This algorithm is in-place.
 *  This algorithm is not a stable algorithm.
 *  This function is a wrapper for the 'bh_heapsort_asc' function.
 *
 *  Parameter:
 *      pArray              :   Pointer to the array which is being sorted
 *      nCount              :   Number of elements the specified array holds
 *      nWidth              :   Size of each element in bytes
 *      fpCompare           :   Comparison function to compare the elements in the array
 *                              This function should implement the 'total order' comparison
 *                              e.g. when comparing between a and b,
 *                              return negative value if a < b
 *                              return zero (0) if a = b and
 *                              return positive value if a > b
 *
 *  Returns
 *      (int)           (success) 0 if the operation succeeded
 *                      (failure) -1 pArray is NULL or nWidth is 0 or fpCompare is 0
*/
int bh_heapsort
(
    void *pArray,
    unsigned int nCount,
    unsigned int nWidth,
    int (*fpCompare) (const void *agr1, const void *arg2)
);





/*
 *  Sorts the elements of the specified array using the HeapSort algorithm
 *  in ascending order.
 *  Time complexity of this algorithm is O(nlogn), where n = nCount
 *  This algorithm is in-place.
 *  This algorithm is not a stable algorithm.
 *
 *  Parameter:
 *      pArray              :   Pointer to the array which is being sorted
 *      nCount              :   Number of elements the specified array holds
 *      nWidth              :   Size of each element in bytes
 *      fpCompare           :   Comparison function to compare the elements in the array
 *                              This function should implement the 'total order' comparison
 *                              e.g. when comparing between a and b,
 *                              return negative value if a < b
 *                              return zero (0) if a = b and
 *                              return positive value if a > b
 *
 *  Returns
 *      (int)           (success) 0 if the operation succeeded
 *                      (failure) -1 pArray is NULL or nWidth is 0 or fpCompare is 0
*/
int bh_heapsort_asc
(
    void *pArray,
    unsigned int nCount,
    unsigned int nWidth,
    int (*fpCompare) (const void *agr1, const void *arg2)
);





/*
 *  Sorts the elements of the specified array using the HeapSort algorithm
 *  in descending order.
 *  Time complexity of this algorithm is O(nlogn), where n = nCount
 *  This algorithm is in-place.
 *  This algorithm is not a stable algorithm.
 *
 *  Parameter:
 *      pArray              :   Pointer to the array which is being sorted
 *      nCount              :   Number of elements the specified array holds
 *      nWidth              :   Size of each element in bytes
 *      fpCompare           :   Comparison function to compare the elements in the array
 *                              This function should implement the 'total order' comparison
 *                              e.g. when comparing between a and b,
 *                              return negative value if a < b
 *                              return zero (0) if a = b and
 *                              return positive value if a > b
 *
 *  Returns
 *      (int)           (success) 0 if the operation succeeded
 *                      (failure) -1 pArray is NULL or nWidth is 0 or fpCompare is 0
*/
int bh_heapsort_desc
(
    void *pArray,
    unsigned int nCount,
    unsigned int nWidth,
    int (*fpCompare) (const void *agr1, const void *arg2)
);






#endif


