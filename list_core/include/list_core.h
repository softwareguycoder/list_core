/*
 * list_core.h
 *
 *  Created on: Apr 18, 2019
 *      Author: bhart
 */

#ifndef __LIST_CORE_H__
#define __LIST_CORE_H__

#include "root.h"
#include "position.h"

///////////////////////////////////////////////////////////////////////////////
// Callback signatures

/**
 * @brief Callback that does an action for the current item in the list.
 * @param pData Address of the current element in the list.
 * @remarks Use this as the function signature for a function whose address
 * is to be provided to the ForEach function that will specify the actions
 * to be executed for each element in the list.
 */
typedef void (*LPACTION_ROUTINE)(void*);

/**
 * @brief Callback to be used to compare two elements of the linked list.
 * @param pKey Address of a memory location that holds the search key.
 * @param pData Address of the current element in the list.
 * @returns TRUE if the current element of the list has information matching
 * the search key; FALSE otherwise.
 * @remarks Use this as the function signature for a comparison routine whose
 * address is to be provided to the FindElement function.
 */
typedef BOOL (*LPCOMPARE_ROUTINE)(void*, void*);

/**
 * @brief Callback to be used to deallocate the storage occupied by the
 * current element of the list.
 * @param pData Pointer to the memory storage occupied by the current list
 * element.
 * @remarks Provide the address of a function matching the signature of this
 * routine to the DestroyList function.  The function referenced will be called
 * once for each element in the list. */
typedef void (*LPDEALLOC_ROUTINE)(void*);

///////////////////////////////////////////////////////////////////////////////
// Functions

/**
 * @brief Adds a new member to the linked list.
 * @param ppListHead Address of the address of a POSITION structure that
 * denotes the location of the list's head.
 * @param pvData Address of the data to place in the new linked list node.
 * @returns TRUE if the add operation succeeded; FALSE otherwise.
 */
BOOL AddTail(POSITION** ppListHead, void* pvData);

/**
 * @brief Creates a new linked list and makes the first node refer to
 * the data specified.
 * @param pvData Address of the data that the first node should refer to.
 * @returns Address of a POSITION structure that locates where the new
 * node is in the list.
 * @remarks Be sure to note that this function always creates a new linked
 * list.
 */
POSITION* CreateNewList(void* pvData);

/**
 * @brief Removes all the elements from the list and frees the data
 * referenced by each element.
 * @param ppListHead Address of a pointer to the head of the list. This
 * value may be updaed by the function.
 * @param lpfnDeallocFunc Address of a function that is called for
 * each member of the list.  Should implement the proper deallocation of
 * the memory occupied by the current list element's data.
 * @remarks Iterates over the list, calling the function pointed to by
 * lpfnDeallocFunc for each member.  The function that gets called is
 * fed a pointer to the pvData member of the current list element.  This
 * pointer should have free() or some other cleanup routine called on it.
 * Once this iteration is complete, the list itself has all its elements
 * removed and the elements themselves removed from memory.
 */
void DestroyList(POSITION** ppListHead, LPDEALLOC_ROUTINE lpfnDeallocFunc);

/**
 * @brief Searches the list for an element containing data that matches the
 * search key, and then returns the address of the POSITION structure that
 * addresses the element's position.
 * @param ppListHead Address of a pointer to the head of the list. This
 * value may be updated by the function.
 * @param pSearchKey Address of the value to be used to match against data
 * in the linked list by the comparer routine.
 * @parm lpfnCompare Address of a function having the signature specified
 * by the LPCOMPARE_ROUTINE type. Functions should match the data in the
 * search key to data in the linked list.
 * @returns Address of a POSITION that locates the found item in the list
 * or NULL if either (a) the item was not found, or (b) a problem occurred.
 * @remarks Iterates through the list starting at the head, calling the
 * function pointed to by lpfnCompare for each one.  Stops when the element
 * is reached for which the function returns TRUE, or the end of the list has
 * been reached.
 */
POSITION* FindElement(POSITION** ppListHead, void *pSearchKey,
		LPCOMPARE_ROUTINE lpfnCompare);

/**
 * @brief Executes an action for each member of a non-empty list.
 * @param ppListHead Reference to the head node of the list.
 * @param lpfnForEachRoutine Reference to the function to be executed for each
 * element.  This function is passed a reference to the element.
 */
void ForEach(POSITION **ppListHead, LPACTION_ROUTINE lpfnForEachRoutine);

/**
 * @name GetCount
 * @brief Gets the count of elements in the linked list.
 * @param ppElement Address of a pointer to a POSITION structure that locates
 * any of the elements in the linked list.
 * @returns An integer with a value of either a positive integer or zero if
 * there are no elements.  If ppElement is NULL then this function returns
 * zero.
 */
int GetCount(POSITION** ppElement);

/**
 * @brief Gets the address of a POSITION structure that references the head
 * of the linked list.
 * @param ppMember Address of the POSITION structure that references any
 * existing element of the list.
 * @returns Address of a POSITION structure that references the head of the
 * list.
 * @remarks This function returns NULL if the ppMember parameter is NULL or
 * the head could not be located, maybe because the linked list is currently
 * empty.
 */
POSITION* GetHeadPosition(POSITION** ppMember);

/**
 * @brief Gets a reference to the next element in the linked list.
 * @param pos Address of a POSITION structure that references the current item
 * in the linked list.
 * @returns Address of a POSITION structure that references the element in the
 * linked list that comes after the one passed to this function.
 * @remarks If you have already reached the tail of the list when this function
 * is called, then the function returns NULL.
 */
POSITION* GetNext(POSITION *pos);

/**
 * @brief Gets the address of a POSITION structure that references the tail
 * of the linked list.
 * @param ppMember Address of the POSITION structure that references any
 * existing element of the list.
 * @returns Address of a POSITION structure that references the tail of the
 * list.
 * @remarks This function returns NULL if the ppMember parameter is NULL or
 * the tail could not be located, maybe because the linked list is currently
 * empty.
 */
POSITION* GetTailPosition(POSITION** ppMember);

/**
 * @brief Removes an element from the list.
 * @param ppListHead Address of a pointer to the head element of the list.
 * @param pSearchKey Pointer to storage that holds the value to be used
 * as a search key.
 * @param lpfnSearch Pointer to a function that is to be called to compare
 * the value of the data referenced by the current element to the criteria
 * in pSearchKey.  If a match is found, the element is removed from the list.
 * @returns TRUE if an element was removed from the list; FALSE otherwise.
 * @remarks Note that this function does not deallocate the data referenced
 * by the element removed from the list.
 */
BOOL RemoveElement(POSITION** ppListHead, void* pSearchKey,
        LPCOMPARE_ROUTINE lpfnSearch);

/**
 * @brief Removes the element at the head of the linked list.
 * @param ppListHead Address of the POSITION structure that references the head
 * element of the list.
 * @returns TRUE if the remove operation succeeded; FALSE otherwise.
 * @remarks Returns FALSE if the ppListHead value is NULL or if the operation
 * failed.
 */
BOOL RemoveHead(POSITION** ppListHead);

/**
 * @brief Removes the element at the tail of the linked list.
 * @param ppListHead Address of the POSITION structure that references the head
 * element of the list.
 * @returns Address of the POSITIOn of the new tail; NULL if the list is empty.
 */
POSITION* RemoveTail(POSITION** ppListHead);



#endif /* __LIST_CORE_H__ */
