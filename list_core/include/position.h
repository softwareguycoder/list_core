// position.h - Defines the interface to the POSITION data structure.
//
// Copyright (c) 2019 by Brian Hart.
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

#ifndef __POSITION_H__
#define __POSITION_H__

/**
 * @brief Structure that encapsulates a node of the linked list.
 *
 * Each element of this doubly-linked list maintains pointers to its
 * previous and next neighbors as well as an additional pointer optionally
 * referring to data that is being tracked by the list.  It is recommended that
 * such data be dynamically allocated.
 */
typedef struct _tagPOSITION {
  void* pvData;
  struct _tagPOSITION* pPrev;
  struct _tagPOSITION* pNext;
} POSITION, *LPPOSITION, **LPPPOSITION;

/**
 * @name CreatePosition
 * @brief Creates a new POSITION structure instance and returns a reference to
 * it.
 * @param lppPosition Address of a pointer that will receive the address of the
 * newly-allocated POSITION instance.
 */
void CreatePosition(LPPPOSITION lppPosition);

/**
 * @name DestroyPosition
 * @brief Removes an instance of POSITION from the heap.
 * @param lppPosition Address of a pointer to the instance of POSITION to be
 * deallocated.  This pointer is reset to have the value NULL.
 */
void DestroyPosition(LPPPOSITION lppPosition);

/**
 * @name GetNextPosition
 * @brief Given the address of a list element, returns the address of the
 * next element in the list.
 * @param lpElement Address of any of the elements in the list.
 * @return Address of the element that follows the element provided, or NULL
 * if the element specified was already the tail of the list.
 * @remarks The value passed to this function is not altered by the operation.
 */
LPPOSITION GetNextPosition(LPPOSITION lpElement);

/**
 * @name GetPrevPosition
 * @brief Given the address of a list element, returns the address of the
 * previous element in the list.
 * @param lpElement Address of any of the elements in the list.
 * @return Address of the element that preceds the element provided, or NULL
 * if the element specified is already the head of the list.
 * @remarks The value passed to this function is not altered by the operation.
 */
LPPOSITION GetPrevPosition(LPPOSITION lpElement);

/**
 * @name IsPositionHead
 * @brief Determines whether the specified element is the head of the list.
 * @param lpElement Address of any of the elements of a list.
 * @return TRUE if the specified element is either the head of the list or
 * its sole element; FALSE otherwise.
 * @remarks This function does not alter the address referred to by its
 * argument.
 */
BOOL IsPositionHead(LPPOSITION lpElement);

/**
 * @name IsPositionTail
 * @brief Determines whether the specified element is the tail of the list.
 * @param lpElement Address of any of the elements of a list.
 * @return TRUE if the specified element is either the tail of the list or
 * its sole element; FALSE otherwise.
 * @remarks This function does not alter the address referred to by its
 * argument.
 */
BOOL IsPositionTail(LPPOSITION lpElement);

/**
 * @name IsSoleElement
 * @brief Determines whether the specified element is from a list that only has
 * one node.
 * @param lpElement Address of any of the elements of a list.
 * @return TRUE if the specified element is the sole element of the list.
 * @remarks This function does not alter the address referred to by its
 * argument.
 */
BOOL IsSoleElement(LPPOSITION lpElement);

/**
 * @name MoveToHeadPosition
 * @brief Resets the element pointer passed to refer to the head of the list.
 * @param lppElement Address of the current element pointer.
 * @remarks The current element pointer is reset to point to the head element.
 * Head elements are defined to be those who have a pPrev pointer that is NULL.
 */
void MoveToHeadPosition(LPPPOSITION lppElement);

/**
 * @name MoveToTailPosition
 * @brief Resets the current element pointer to point to the tail of the list.
 * @param lppElement Address of the current element pointer.
 * @remarks The value of lppElement is reset to the tail, or NULL if the list
 * has no elements.
 */
void MoveToTailPosition(LPPPOSITION lppElement);

/**
 * @name SetNextPosition
 * @brief Sets the value of the next pointer of the specified element.
 * @param lpElement Address of the element whose next pointer should
 * be updated.
 * @param lpValue New value for the specified element's next pointer.
 */
void SetNextPosition(LPPOSITION lpElement, LPPOSITION lpValue);

/**
 * @name SetPositionData
 * @brief Sets the address of the data to which the specified list element
 * should refer.
 * @param lpElement Address of the element whose data pointer should
 * be updated.
 * @param pvData Address value to be copied into the element's data pointer.
 */
void SetPositionData(LPPOSITION lpElement, void* pvData);

/**
 * @name SetPrevPosition
 * @brief Sets the value of the previous pointer of the specified element.
 * @param lpElement Address of the element whose previous pointer should
 * be updated.
 * @param lpValue New value for the specified element's previous pointer.
 */
void SetPrevPosition(LPPOSITION lpElement, LPPOSITION lpValue);

#endif /* __POSITION_H__ */
