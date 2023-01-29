

/************************************************************************************
    Implementation of AVL Tree Mutation Algorithms (Insertion, Deletion)
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/








#include "avl.h"
#include "avl_internal.h"
#include <stdlib.h>
#include <string.h>








int avl_insert(AvlTree *pTree, const void *pKey, const void *pElem) {
    
    int iRetVal;
    int opExpand;
    BNode *pTarget;
    BNode *pX;
    
    if (pTree == 0 || pKey == 0)
        return -1;
    
    
    /* Search for the pKey in our AvlTree */
    pTarget = avl_search_node((const AvlTree *) pTree, pKey, avl_root(pTree));
    
    
    /* Key not found, we have got an External BNode */
    /* So make it Internal and assing this Key and Elem to it */
    if (avl_is_external(pTarget) == 1) {
        
        opExpand = bst_expandExternal(pTarget);
        if (opExpand != 0)
            return -1;
        
        pTarget->pKey = (void *) pKey;
        pTarget->pElement = (void *) pElem;
        pTree->size = pTree->size + 1;
        
        pX = avl_findUnbalancedNodeX(pTree, pTarget, AVL_INSERTION);
        if (pX != 0) {
            avl_restructure(pTree, pX);
        }
        
        iRetVal = 0;
    }
    else {
        
        
        /* We have got an Internal BNode, it means Key already exist */
        /* In this situation we cannot insert the given Key into our AvlTree */
        iRetVal = -1;
    }
    
    return iRetVal;
}



int avl_remove(AvlTree *pTree, const void *pKey, void **pRemovedKey, void **pRemovedElem) {
    
    int iRetVal;
    int isRemNodeExternal;
    int isLeftExternal, isRightExternal;
    int isBothInternal;
    BNode *pRemNode;
    BNode *pLeftChild, *pRightChild;
    BNode *pChildExternal, *pInorderInternal, *pInorderExternal;
    BNode *pExternal;
    BNode *pX, *pB, *pParent;
    
    if (pTree == 0 || pKey == 0)
        return -1;
    
    pChildExternal = 0;
    pRemNode = bst_search_node((const BisTree *) pTree, pKey, bst_root(pTree));
    isRemNodeExternal = bst_is_external(pRemNode);
    
    if (isRemNodeExternal == 1) {
        iRetVal = -1;
    }
    else {
        
        if (pRemovedKey != 0)
            *pRemovedKey = pRemNode->pKey;
        if (pRemovedElem != 0)
            *pRemovedElem = pRemNode->pElement;
        
        pLeftChild = bst_leftchild(pRemNode);
        pRightChild = bst_rightchild(pRemNode);
        
        isLeftExternal = bst_is_external(pLeftChild);
        isRightExternal = bst_is_external(pRightChild);
        
        
        /* Both childs are internal if Left And Right childs are NOT External */
        isBothInternal = !(isLeftExternal | isRightExternal);
        
        if (isBothInternal == 0) {
            
            
            /* Find the External child of pRemNode and pChildExternal will be the External one */
            if (isLeftExternal == 1)
                pChildExternal = pLeftChild;
            if (isRightExternal == 1)
                pChildExternal = pRightChild;
            
            pExternal = pChildExternal;
        }
        else if (isBothInternal == 1) {
            
            
            /* Find next Internal BNode in the "InOrder" serial */
            /* Next Internal BNode = pInorderInternal */
            pInorderExternal = pRightChild;
            while (bst_is_external(pInorderExternal) != 1) {
                pInorderExternal = bst_leftchild(pInorderExternal);
            }
            pInorderInternal = bst_parent(pInorderExternal);
            
            
            /* Copy pKey and pElement pointers to pRemNode */
            pRemNode->pKey = pInorderInternal->pKey;
            pRemNode->pElement = pInorderInternal->pElement;
            pInorderInternal->pKey = 0;
            pInorderInternal->pElement = 0;
            
            pExternal = pInorderExternal;
        }
        
        
        /* Remove internal node pInorderInternal */
        bst_removeAboveExternal(pTree, pExternal, &pParent);
        pTree->size = pTree->size - 1;
        pB = pParent;
        
        REPEAT:
        pX = avl_findUnbalancedNodeX(pTree, pB, AVL_REMOVAL);
        if (pX != 0) {
            pB = avl_restructure(pTree, pX);
            pX = 0;
            goto REPEAT;
        }
        
        iRetVal = 0;
    }
    
    return iRetVal;
}


