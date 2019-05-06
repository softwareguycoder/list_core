// position.c - Contains implementations of functions that manipulate
// information in instances of POSITION structures
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

  *lppPosition = (LPPOSITION)malloc(sizeof(POSITION));
  memset(*lppPosition, 0, sizeof(POSITION));
}

void DestroyPosition(LPPPOSITION lppPosition) {
  if (lppPosition == NULL || *lppPosition == NULL) {
    return;
  }

  free((void*)(*lppPosition));
  *lppPosition = NULL;
}

void GetHeadPosition(LPPPOSITION lppElement) {
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
  } while((*lppElement = GetPrev(*lppElement)) != NULL);
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

void GetTailPosition(LPPPOSITION lppElement) {
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
  } while((*lppElement = GetNext(*lppElement)) != NULL);
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

  return lpElement->pPrev == NULL
      && lpElement->pNext == NULL;
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
