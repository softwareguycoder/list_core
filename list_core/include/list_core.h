// list_core.h - Defines the interface to a doubly-linked list.
//
// This file is part of list_core.
//
// list_core is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// list_core is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with list_core.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef __LIST_CORE_H__
#define __LIST_CORE_H__

#include "position.h"

/**
 * @brief Callback signature for an 'action' routine, i.e., a function whose
 * only purpose in life is to run code.
 * @param pvData Reference to the data that is tracked by the current node.
 * @remarks This function allows the caller to supply a function that is
 * called back for each element in the list, and is provided a pointer
 * to the current node's data.
 */
typedef void (*LPACTION_ROUTINE)(void* pvData);

/**
 * @brief Callback signature for a function that compares two objects.
 * @param pvData1 Instance of an object for the left side of the comparison.
 * @param pvData2 Instance of an object for the right side of the comparison.
 * @return TRUE if the objects match; FALSE otherwise.
 */
typedef BOOL (*LPCOMPARE_ROUTINE)(void* pvData1, void* pvData2);

/**
 * @brief Callback that specifies deallocation logic for the data referenced.
 * @param pvData Address of the memory to be freed.
 * @remarks Users should implement this callback to handle data-specific
 * deallocation logic that is triggered, say, when elements are removed
 * from the linked list. If you have stored data in the linked list that had
 * been placed on the stack, then still implement this callback.  In that case,
 * make your callback implementation do nothing.  This callback is inteneded to
 * manage data that has been allocated on the heap.
 */
typedef void (*LPDEALLOC_ROUTINE)(void* pvData);

/**
 * @brief Callback that is a predicate; it simply gives the result of a
 * Boolean expression involving the specified data.
 * @param pvData Data to be used in the Boolean expression implemented by
 * this predicate.
 * @return Result of the predicate expression.
 */
typedef BOOL (*LPPREDICATE_ROUTINE)(void* pvData);

/**
 * @name AddElement
 * @brief Adds a new element to the linked list; creates a new list if the
 * current element pointer is NULL.
 * @param lppElement Address of the current element pointer.  This value is
 * reset to point to the tail of the list after a successful add operation.
 * @param pvData Address of data to be pointed to by the new element.
 * @remarks Adds a new node to the end of the linked list and resets the
 * current element pointer to the address of the new node.
 */
void AddElement(LPPPOSITION lppElement, void* pvData);

/**
 * @name ClearList
 * @brief Removes and deallocates all the elements from the linked list.
 * @param lppElement Address of the current element pointer.  This value is
 * reset to NULL after a successful clear operation.
 * @param lpfnDeallocFunc Address of a function that implements specialized
 * deallocation logic to properly remove the data referred to by each node from
 * the heap.  Supplied by the application.
 * @remarks This function removes all the elements of the list, freeing
 * associated data as it goes. Since there is nothing in the list after this
 * function is complete, the current element pointer's value will be reset to
 * NULL after the operation. A NULL value for the current element pointer
 * signifies that there are zero elements in the list.
 */
void ClearList(LPPPOSITION lppElement, LPDEALLOC_ROUTINE lpfnDeallocFunc);

/**
 * @name CreateList
 * @param lppNewHead Reference to a pointer that will receive the address of
 * the head element of the new linked list.
 * @param pvData Data to be associated with the new linked list's head.  May
 * be NULL.
 * @remarks Creates a new linked list and adds the head element to it,
 * optionally making the head element refer to some data.  The pointer
 * referred to by lppNewHead will now contain the address of the head when this
 * function is done. */
void CreateList(LPPPOSITION lppNewHead, void* pvData);

/**
 * @name DoForEach
 * @brief Executes an action for each of the elements of the linked list.
 * @param lpElement Address of any element in the list.
 * @param lpfnAction Address of a function that specifies the code to run for
 * each element of the list.
 * @remarks The current element pointer is not reset by this operation.  The
 * user-defined function is passed a pointer to the data referenced by the
 * current node.
 */
void DoForEach(LPPOSITION lpElement, LPACTION_ROUTINE lpfnAction);

/**
 * @name FindElement
 * @brief Locates the element that matches the criteria specified and
 * returns the address of the matching element, or NULL if not found.
 * @param lpElement Value of the current element pointer.  The find operation
 * does not update the current element pointer.
 * @param pvSearchKey Address of data to serve as a lookup key.
 * @param lpfnCompare User-specified routine that determines whether a given
 * element's data matches certain criteria.
 * @return Address of the element whose data matches the criteria specified by
 * pvSearchKey and lpfnCompare, or NULL if no element matching the specified
 * criteria could be found.
 * @remarks It is recommended to reset the value of the pointer received to
 * NULL when you're done with it, unless you use it to reset the current
 * element pointer that your application maintains. This function does not
 * alter the value of the current element pointer during the operation. */
LPPOSITION FindElement(LPPOSITION lpElement, void* pvSearchKey,
		LPCOMPARE_ROUTINE lpfnCompare);

/**
 * @name FindElementWhere
 * @brief Locates the first element from the head of the list for which the
 * specified predicate function evalutes to TRUE.
 * @param lpElement Address of any element in the list.  The find operation
 * does not update the current element pointer.  The search starts from the
 * list's head.
 * @param lpfnPredicate Address of a user-specified predicate routine that
 * evaluates a Boolean expression for each element in the list.
 * @return Address of the element whose data matches the criteria specified by
 * the predicate, or NULL if no element matching the specified
 * criteria could be found.
 * @remarks It is recommended to reset the value of the pointer received to
 * NULL when you're done with it, unless you use it to reset the current
 * element pointer that your application maintains. This function does not
 * alter the value of the current element pointer during the operation. */
LPPOSITION FindElementWhere(LPPOSITION lpElement,
		LPPREDICATE_ROUTINE lpfnPredicate);

/**
 * @name GetElementCount
 * @brief Gets the count of the elements in the list.
 * @param lpElement Address of any element from the list.
 * @return Count of elements in the list.
 * @remarks The count operation starts from the head.  The value of the
 * current element pointer is not updated by this operation.
 */
int GetElementCount(LPPOSITION lpElement);

/**
 * @name GetElementCountWhere
 * @brief Gets the count of all elements in the list for which a user-specified
 * predicate function returns TRUE.
 * @param lpElement Address of any element from the list.
 * @param lpfnPredicate Address of a user-specified predicate function that
 * evaluates a Boolean expression for each piece of data referred to by each
 * list element.
 * @return Count of all the list's elements for which the predicate evaluates
 * to TRUE.
 * @remarks The count operation starts from the head.  The value of the
 * current element pointer is not updated by this operation.
 */
int GetElementCountWhere(LPPOSITION lpElement,
		LPPREDICATE_ROUTINE lpfnPredicate);

/**
 * @name RemoveElement
 * @brief Removes an element from the list.
 * @param lppElement Address of the current element pointer maintained by the
 * applications.  Applications should move the current element pointer to the
 * proper element by whichever means prior to calling this function.
 * @param lpfnDeallocFunc Address of a callback that implements application-
 * specific deallocation functionality to properly remove the data each node
 * refers to from the heap.
 * @remarks Once the remove operation is complete, the current element pointer
 * is updated.  In most cases, it's updated to point to the element after the
 * deleted one.  However, if the tail is deleted, then the current element
 * pointer is reset to point to the new tail.  If the last element of the list
 * has been removed, the current element pointer is reset to NULL.  This
 * signifies that the list no longer exists at all.
 */
void RemoveElement(LPPPOSITION lppElement, LPDEALLOC_ROUTINE lpfnDeallocFunc);

#endif //__LIST_CORE_H__
