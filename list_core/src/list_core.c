// list_core.c - Implementations of functions that provide the functionality
// of a doubly-linked list.
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

#include "stdafx.h"
#include "list_core.h"

#include "position.h"

//////////////////////////////////////////////////////////////////////////////
// Publicly-exposed functions

//////////////////////////////////////////////////////////////////////////////
// AddElement function

void AddElement(LPPPOSITION lppElement, void* pvData) {
  if (*lppElement == NULL) {
    CreateList(lppElement, pvData);
    return;
  }

  LPPOSITION lpNew = NULL;

  CreatePosition(&lpNew);

  SetPositionData(lpNew, pvData);

  SetPrevPosition(lpNew, *lppElement);
  SetNextPosition(*lppElement, lpNew);

  *lppElement = lpNew;
}

//////////////////////////////////////////////////////////////////////////////
// AddElementToTail function

void AddElementToTail(LPPPOSITION lppElement, void* pvData) {
	MoveToTailPosition(lppElement);

	AddElement(lppElement, pvData);
}

//////////////////////////////////////////////////////////////////////////////
// ClearList function

void ClearList(LPPPOSITION lppElement,
    LPDEALLOC_ROUTINE lpfnDeallocFunc) {
  if (lppElement == NULL || *lppElement == NULL) {
    return; // Required parameter
  }

  if (lpfnDeallocFunc == NULL) {
    return; // Required parameter
  }

  MoveToTailPosition(lppElement);

  while(*lppElement != NULL) {
    RemoveElement(lppElement, lpfnDeallocFunc);
  }
}

//////////////////////////////////////////////////////////////////////////////
// CreateList function

void CreateList(LPPPOSITION lppNewHead, void* pvData) {
  if (lppNewHead == NULL) {
    return;
  }

  CreatePosition(lppNewHead);

  SetPositionData(*lppNewHead, pvData);
}

//////////////////////////////////////////////////////////////////////////////
// DeallocateNothing function

void DeallocateNothing(void* pvData){ /* no-op */ }

//////////////////////////////////////////////////////////////////////////////
// DefaultFree function

void DefaultFree(void* pvData) {
	if (pvData == NULL) {
		return;
	}

	free(pvData);
}

//////////////////////////////////////////////////////////////////////////////
// DoForEach function

void DoForEach(LPPOSITION lpElement, LPACTION_ROUTINE lpfnAction) {
  if (lpElement == NULL || lpfnAction == NULL) {
    return;
  }

  MoveToHeadPosition(&lpElement);

  do {
    lpfnAction(lpElement->pvData);
  } while((lpElement = lpElement->pNext) != NULL);
}
//////////////////////////////////////////////////////////////////////////////
// FindElement function

LPPOSITION FindElement(LPPOSITION lpElement,
    void* pvSearchKey, LPCOMPARE_ROUTINE lpfnCompare) {
  if (lpElement == NULL || lpfnCompare == NULL) {
    return NULL;  // Required parameters
  }

  MoveToHeadPosition(&lpElement);
  do {
	void *pvCurrentEltData = lpElement->pvData;
    if (lpfnCompare(pvSearchKey, pvCurrentEltData)) {
      return lpElement;
    }
  } while((lpElement = lpElement->pNext) != NULL);

  return NULL;  // If we get here, no element's data meets the criteria
                  // dicated by the predicate
}

//////////////////////////////////////////////////////////////////////////////
// FindElementWhere function

LPPOSITION FindElementWhere(LPPOSITION lpElement,
    LPPREDICATE_ROUTINE lpfnPredicate) {
  if (lpElement == NULL || lpfnPredicate == NULL) {
    return NULL;  // Required parameters
  }

  MoveToHeadPosition(&lpElement);
  do {
    if (lpfnPredicate(lpElement->pvData)) {
      return lpElement;
    }
  } while((lpElement = lpElement->pNext) != NULL);

  return NULL;  // If we get here, no element's data meets the criteria
                  // dicated by the predicate
}

//////////////////////////////////////////////////////////////////////////////
// GetElementCount function

int GetElementCount(LPPOSITION lpElement) {
  int nResult = 0;
  if (lpElement == NULL) {
    return nResult;
  }

  MoveToHeadPosition(&lpElement);
  do {
    nResult++;
  } while((lpElement = lpElement->pNext) != NULL);

  return nResult;
}

//////////////////////////////////////////////////////////////////////////////
// GetElementCountWhere function

int GetElementCountWhere(LPPOSITION lpElement,
  LPPREDICATE_ROUTINE lpfnPredicate) {
  int nResult = 0;
  if (lpElement == NULL) {
    return nResult;
  }

  if (lpfnPredicate == NULL) {
    return nResult;
  }

  MoveToHeadPosition(&lpElement);
  do {
    if (lpfnPredicate(lpElement->pvData))
      nResult++;
  } while((lpElement = lpElement->pNext) != NULL);

  return nResult;
}

//////////////////////////////////////////////////////////////////////////////
// RemoveElement function

void RemoveElement(LPPPOSITION lppElement,
    LPDEALLOC_ROUTINE lpfnDealloc) {
  if (lppElement == NULL || *lppElement == NULL) {
    return; // Required parameter
  }

  if (lpfnDealloc == NULL) {
    return; // Required parameter
  }

  // Deallocate the node's data using the caller-specified
  // routine
  lpfnDealloc((*lppElement)->pvData);

  // Remove the single element that is in the list
  if (IsSoleElement(*lppElement)) {
    free(*lppElement);
    *lppElement = NULL; // nothing in the list left
    return;
  }

  // Remove the tail from the list
  if (IsPositionTail(*lppElement)) {
    *lppElement = (*lppElement)->pPrev;
    free((*lppElement)->pNext);
    (*lppElement)->pNext = NULL;
    return;
  }

  *lppElement = (*lppElement)->pNext;

  // Remove the head from the list
  if (IsPositionHead((*lppElement)->pPrev)) {
      (*lppElement)->pPrev->pNext = NULL;
      free((*lppElement)->pPrev);
      (*lppElement)->pPrev = NULL;
      return;
  }

  // Remove an element that has neighbors on both sides
  (*lppElement)->pPrev = (*lppElement)->pPrev->pPrev;

  free((*lppElement)->pPrev->pNext);
  (*lppElement)->pPrev->pNext = *lppElement;
}

///////////////////////////////////////////////////////////////////////////////
// Sum function

int Sum(LPPOSITION lpElement, LPSUMMATION_ROUTINE lpfnSumRoutine)
{
  int nResult = -1;
  if (lpElement == NULL){
    return nResult;  // Required parameter
  }

  if (lpfnSumRoutine == NULL) {
    return nResult;  // Required parameter
  }

  MoveToHeadPosition(&lpElement);
  do {
    nResult += lpfnSumRoutine(lpElement->pvData);
  } while((lpElement = lpElement->pNext) != NULL);

  return nResult;
}

//////////////////////////////////////////////////////////////////////////////
