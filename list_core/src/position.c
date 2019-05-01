// position.c - Contains implementations of functions that manipulate
// information in instances of POSITION structures
//

#include "stdafx.h"
#include "list_core.h"

#include "position.h"

///////////////////////////////////////////////////////////////////////////////
// Functions exposed to users

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

///////////////////////////////////////////////////////////////////////////////
// InitializePosition

void InitializePosition(LPPOSITION lpPosition, LPPOSITION lpPrev,
		LPPOSITION lpNext, void* pvData) {
	if (lpPosition == NULL) {
		return;		// Nothing to initialize
	}

	lpPosition->pPrev = lpPrev;
	lpPosition->pNext = lpNext;
	lpPosition->pvData = pvData;
}

void SetData(LPPOSITION lpCurrentPosition,
    void* pvData) {
  if (lpCurrentPosition == NULL) {
    return; // required parameter
  }

  lpCurrentPosition->pvData = pvData;
}

void SetNext(LPPOSITION lpCurrentPosition,
    LPPOSITION lpNextPosition) {
  if (lpCurrentPosition == NULL) {
    return; // required parameter
  }

  lpCurrentPosition->pNext = lpNextPosition;
}

void SetPrev(LPPOSITION lpCurrentPosition,
    LPPOSITION lpPrevPosition) {
  if (lpCurrentPosition == NULL) {
    return; // required parameter
  }

  lpCurrentPosition->pPrev = lpPrevPosition;
}

///////////////////////////////////////////////////////////////////////////////
