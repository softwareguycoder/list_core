// position.c - Contains implementations of functions that manipulate
// information in instances of POSITION structures
//

#include "stdafx.h"
#include "list_core.h"

#include "position.h"

///////////////////////////////////////////////////////////////////////////////
// Functions exposed to elsewhere in this library

///////////////////////////////////////////////////////////////////////////////
// CreatePosition function

void CreatePosition(LPPPOSITION lppNewPosition) {
	if (lppNewPosition == NULL) {
		return;	// We do not know where to put the address of the newly-
					// allocated POSITION structure instance
	}

	LPPOSITION lpResult = NULL;

	lpResult = (LPPOSITION)malloc(1*sizeof(POSITION));
	if (lpResult == NULL) {
		fprintf(stderr, FAILED_ALLOC_NEW_NODE);
		exit(EXIT_FAILURE);
	}

	memset(lpResult, 0, sizeof(POSITION));

	*lppNewPosition = lpResult;
}

//////////////////////////////////////////////////////////////////////////////
// DestroyPosition function

void DestroyPosition(LPPPOSITION lppPosition) {
  if (lppPosition == NULL || *lppPosition == NULL){
    return; // Required parameter
  }

  // Blank out all the pointer members of the POSITION struct so
  // that prev, next nodes and data are no longer referred to (it may
  // even be the case that pointer member variables may still be set to
  // addresses of free'd memory; when we free() the structure the OS will
  // try to re-free the memory which we do not want)
  memset((*lppPosition), 0, sizeof(POSITION));

  FreeBuffer((void**)lppPosition);
}

//////////////////////////////////////////////////////////////////////////////
// GetData function

void GetData(LPPOSITION lpCurrentPosition,
    void** ppvData) {
  if (lpCurrentPosition == NULL){
    return; // required parameter
  }

  if (ppvData == NULL) {
    return; // required parameter
  }

  *ppvData = lpCurrentPosition->pvData;
}

//////////////////////////////////////////////////////////////////////////////
// GetNext function

void GetNext(LPPOSITION lpCurrentPosition,
    LPPPOSITION lppNext) {
  if (lpCurrentPosition == NULL){
    return; // required parameter
  }

  if (lppNext == NULL) {
    return; // required parameter
  }

  *lppNext = lpCurrentPosition->pNext;
}

//////////////////////////////////////////////////////////////////////////////
// GetPrev function

void GetPrev(LPPOSITION lpCurrentPosition,
    LPPPOSITION lppPrev) {
  if (lpCurrentPosition == NULL){
    return; // required parameter
  }

  if (lppPrev == NULL) {
    return; // required parameter
  }

  *lppPrev = lpCurrentPosition->pPrev;
}

//////////////////////////////////////////////////////////////////////////////
// InitializePosition function

void InitializePosition(LPPOSITION lpPosition, LPPOSITION lpPrev,
		LPPOSITION lpNext, void* pvData) {
	if (lpPosition == NULL) {
		return;		// Nothing to initialize
	}

	lpPosition->pPrev = lpPrev;
	lpPosition->pNext = lpNext;
	lpPosition->pvData = pvData;
}

//////////////////////////////////////////////////////////////////////////////
// IsHeadPosition function

BOOL IsHeadPosition(LPPOSITION lpElement) {
  if (lpElement == NULL){
    return FALSE;   // required parameter
  }

  /* if pPrev is NULL, then it's obvious that this element is the head
   * of whatever linked list it's in, or it's the only element in the list,
   * period. */
  return lpElement->pPrev == NULL;
}

//////////////////////////////////////////////////////////////////////////////
// IsSoleElement function

BOOL IsSoleElement(LPPOSITION lpPosition) {
  if (lpPosition == NULL){
    return FALSE;   // required parameter
  }

  /* if pPrev is NULL AND pNext is NULL, this element is the only
   * element in its linked list, period. */
  return lpPosition->pPrev == NULL
      && lpPosition->pNext == NULL;
}

//////////////////////////////////////////////////////////////////////////////
// IsTailPosition function

BOOL IsTailPosition(LPPOSITION lpPosition) {
  if (lpPosition == NULL){
    return FALSE; // required parameter
  }

  /* if pNext is NULL, then it's obvious that this element is the tail
   * of whatever linked list it's in, or it's the only element in the list,
   * period. Call IsSoleElement to determine whether it's the sole element
   * in the list. */
  return lpPosition->pNext == NULL;
}

  /* if pPrev is NULL, then it's obvious that this element is the head
   * of whatever linked list it's in, or it's the only element in the list,
   * period. */
  return lpPosition->pPrev == NULL;
}

//////////////////////////////////////////////////////////////////////////////
// SetData function

void SetData(LPPOSITION lpCurrentPosition,
    void* pvData) {
  if (lpCurrentPosition == NULL) {
    return; // required parameter
  }

  lpCurrentPosition->pvData = pvData;
}

//////////////////////////////////////////////////////////////////////////////
// SetNext function

void SetNext(LPPOSITION lpCurrentPosition,
    LPPOSITION lpNextPosition) {
  if (lpCurrentPosition == NULL) {
    return; // required parameter
  }

  lpCurrentPosition->pNext = lpNextPosition;
}

//////////////////////////////////////////////////////////////////////////////
// SetPrev function

void SetPrev(LPPOSITION lpCurrentPosition,
    LPPOSITION lpPrevPosition) {
  if (lpCurrentPosition == NULL) {
    return; // required parameter
  }

  lpCurrentPosition->pPrev = lpPrevPosition;
}

///////////////////////////////////////////////////////////////////////////////
