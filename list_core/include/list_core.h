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
 * @brief Creates a linked list and makes the first node refer to the data
 * specified.
 * @param pvData Address of the data that the first node should refer to.
 * @returns Address of a POSITION structure that locates where the new
 * node is in the list.
 * @remarks Be sure to note that this function always creates a new linked
 * list.
 */
POSITION* AddHead(void* pvData);

/**
 * @brief Adds a new member to the linked list.
 * @param ppListHead Address of the address of a POSITION structure that
 * denotes the location of the list's head.
 * @param pvData Address of the data to place in the new linked list node.
 * @returns TRUE if the add operation succeeded; FALSE otherwise.
 */
BOOL AddTail(POSITION** ppListHead, void* pvData);


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

#endif /* __LIST_CORE_H__ */
