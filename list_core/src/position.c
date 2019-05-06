// position.c - Contains implementations of functions that manipulate
// information in instances of POSITION structures
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
// Internal-use-only functions

LPPOSITION GetNext(LPPOSITION pos) {
	if (pos == NULL) {
		return NULL;  // Required parameter
	}

	return pos->pNext;
}

LPPOSITION GetPrev(LPPOSITION pos) {
	if (pos == NULL) {
		return NULL;
	}
	return pos->pPrev;
}

//////////////////////////////////////////////////////////////////////////////
// Publicly-exposed functions

void CreatePosition(LPPPOSITION lppPosition) {
	if (lppPosition == NULL) {
		return;
	}

	*lppPosition = (LPPOSITION) malloc(sizeof(POSITION));
	memset(*lppPosition, 0, sizeof(POSITION));
}

void DestroyPosition(LPPPOSITION lppPosition) {
	if (lppPosition == NULL || *lppPosition == NULL) {
		return;
	}

	free((void*) (*lppPosition));
	*lppPosition = NULL;
}

LPPOSITION GetNextPosition(LPPOSITION lpElement) {
	if (lpElement == NULL) {
		return NULL;
	}
	return lpElement->pNext;
}

LPPOSITION GetPrevPosition(LPPOSITION lpElement) {
	if (lpElement == NULL) {
		return NULL;
	}
	return lpElement->pPrev;
}

BOOL IsPositionHead(LPPOSITION lpElement) {
	if (lpElement == NULL) {
		return FALSE;
	}
	return lpElement->pPrev == NULL;
}

BOOL IsPositionTail(LPPOSITION lpElement) {
	if (lpElement == NULL) {
		return FALSE;
	}
	return lpElement->pNext == NULL;
}

BOOL IsSoleElement(LPPOSITION lpElement) {
	if (lpElement == NULL) {
		return FALSE;
	}

	return lpElement->pPrev == NULL && lpElement->pNext == NULL;
}

void MoveToHeadPosition(LPPPOSITION lppElement) {
	if (lppElement == NULL || *lppElement == NULL) {
		return;  // nothing in the list to do anything with
	}

	do {
		/* If we are already given a position that points
		 to the head, there is nothing to do but return
		 the same thing as we were given. */
		if (IsPositionHead(*lppElement)) {
			return;
		}
	} while ((*lppElement = GetPrev(*lppElement)) != NULL);
}

void MoveToTailPosition(LPPPOSITION lppElement) {
	if (lppElement == NULL || *lppElement == NULL) {
		return;  // nothing in the list to do anything with
	}

	do {
		/* If we are already given a position that points
		 to the tail, there is nothing to do but return
		 the same thing as we were given. */
		if (IsPositionTail(*lppElement)) {
			return;
		}
	} while ((*lppElement = GetNext(*lppElement)) != NULL);
}

void SetNextPosition(LPPOSITION lpElement, LPPOSITION lpValue) {
	lpElement->pNext = lpValue;
}

void SetPositionData(LPPOSITION lpElement, void* pvData) {
	if (lpElement == NULL) {
		return; // Required parameter
	}
	lpElement->pvData = pvData;
}

void SetPrevPosition(LPPOSITION lpElement, LPPOSITION lpValue) {
	lpElement->pPrev = lpValue;
}
