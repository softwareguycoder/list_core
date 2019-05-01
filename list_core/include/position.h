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
 * @brief Defines a node of the linked list and also serves to locate the
 * node.
 */
typedef struct _tagPOSITION {
  ROOT* pListRoot;

  struct _tagPOSITION* pPrev;
  struct _tagPOSITION* pNext;

  void* pvData;
} POSITION, *LPPOSITION, **LPPPOSITION;

/**
 * @name CreatePosition
 * @brief Allocates memory for a new instance of the POSITION structure.
 * @param lppNewPosition Address of a pointer whose value is to be filled
 * with the address of the newly-allocated POSITION structure.
 */
void CreatePosition(LPPPOSITION lppNewPosition);

/**
 * @name GetData
 * @brief Gets the address of the data referenced by this node.
 * @param lpCurrentPosition Address of a POSITION instance denoting the node
 * to query.
 * @param ppvData Address of a pointer variable that will be filled with the
 * data's storage location.
 */
void GetData(LPPOSITION lpCurrentPosition,
    void** ppvData);

/**
 * @name GetNext
 * @brief Gets the address of the next node after this one.
 * @param lpCurrentPosition Address of a POSITION instance denoting the node
 * to query.
 * @param lppNext Address of a pointer variable that will be filled with the
 * next node's storage location, or NULL if there is no next node.
 */
void GetNext(LPPOSITION lpCurrentPosition,
    LPPPOSITION lppNext);

/**
 * @name GetPrev
 * @brief Gets the address of the prev node after this one.
 * @param lpCurrentPosition Address of a POSITION instance denoting the node
 * to query.
 * @param lppNext Address of a pointer variable that will be filled with the
 * previous node's storage location, or NULL if there is no previous node.
 */
void GetPrev(LPPOSITION lpCurrentPosition,
    LPPPOSITION lppPrev);

/**
 * @name InitializePosition
 * @brief Initializes the members of an instance of the POSITION structure.
 * @param lpPosition Address of the POSITION structure whose members are to
 * be set to the new values.
 * @param lpPrev Address of a POSITION structure that references the previous
 * node in the linked list.  May be NULL.
 * @param lpNext Address of a POSITION structure that references the next
 * node in the linked list.  May be NULL.
 * @param pvData Address of storage containing data to which the
 * node should refer.  May be NULL.
 */
void InitializePosition(LPPOSITION lpPosition, LPPOSITION lpPrev,
    LPPOSITION lpNext, void* pvData);

/**
 * @name SetData
 * @brief
 * @param lpCurrentPosition
 * @param pvData
 */
void SetData(LPPOSITION lpCurrentPosition,
    void* pvData);

/**
 * @name SetNext
 * @brief
 * @param lpCurrentPosition
 * @param lpNextPosition
 */
void SetNext(LPPOSITION lpCurrentPosition,
    LPPOSITION lpNextPosition);

/**
 * @name SetPrev
 * @brief
 * @param lpCurrentPosition
 * @param lpPrevPosition
 */
void SetPrev(LPPOSITION lpCurrentPosition,
    LPPOSITION lpPrevPosition);

#endif /* __POSITION_H__ */
