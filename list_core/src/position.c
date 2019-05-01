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

	POSITION* pResult = NULL;

	pResult = (LPPOSITION)malloc(1*sizeof(POSITION));
	if (pResult == NULL) {
		fprintf(stderr, FAILED_ALLOC_NEW_NODE);
		exit(EXIT_FAILURE);
	}

	memset(pResult, 0, sizeof(POSITION));

	*lppNewPosition = pResult;
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

///////////////////////////////////////////////////////////////////////////////
