// list_core.c - Provides implementations for the API functions that allow
// access to a linked list.
//

#include "stdafx.h"

#include "list_core.h"
#include "position.h"
#include "root.h"

////////////////////////////////////////////////////////////////////////////////
// Internal functions

////////////////////////////////////////////////////////////////////////////////
// DisplayError function - Only utilized by this library to write an error
// message out to stderr and then exit the software with a code of EXIT_FAILURE
//

void DisplayError(const char *pszMessage) {
	// can't display a blank message
	if (pszMessage == NULL || pszMessage[0] == '\0') {
		return;
	}
	fprintf(stderr, "%s", pszMessage);
	exit(EXIT_FAILURE);
}

///////////////////////////////////////////////////////////////////////////////
// Functions exposed to callers

///////////////////////////////////////////////////////////////////////////////
// AddTail function

BOOL AddTail(POSITION** ppListHead, void *pvData) {
	if (pvData == NULL) {
		DisplayError(INVALID_LIST_DATA);
	}

	if (ppListHead == NULL || (*ppListHead) == NULL) {
		DisplayError(ADD_ELEMENT_HEAD_NULL);
	}

	POSITION* pNewTail = (POSITION*) calloc(1, sizeof(POSITION));
	if (pNewTail == NULL) {
		DisplayError(FAILED_ALLOC_NEW_NODE);
	}

	/* Set the pListRoot member of the new node to point at
	 * the address referenced by the list head */
	pNewTail->pListRoot = (*ppListHead)->pListRoot;

	/* Set the pNext pointer of the new node to NULL since this node
	 * is going on the tail of the list. */
	pNewTail->pNext = NULL;

	/* Set the pPrev pointer of the new node to the address of the current
	 * list tail since this new node is now the tail. */
	pNewTail->pPrev = (*ppListHead)->pListRoot->pTail;

	/* Set the new node to reference the data passed to this function. */
	pNewTail->pvData = pvData;

	/* Set the (current) tail of the linked list to point at this
	 * node as the next element after it. */
	(*ppListHead)->pListRoot->pTail->pNext = pNewTail;

	/* Set the newly-created node to be the new tail of the list. */
	(*ppListHead)->pListRoot->pTail = pNewTail;

	/* Return success. */
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CreateNewList function

POSITION* CreateNewList(void *pvData) {
	if (pvData == NULL) {
		DisplayError(INVALID_LIST_DATA);
	}

	/* Create a new node to serve as the new head. */
	POSITION* pListHead = (POSITION*) calloc(1, sizeof(POSITION));
	if (pListHead == NULL) {
		DisplayError(FAILED_ALLOC_HEAD);
	}

	/* Create a new root structure to bear information about the
	 * head and tail. */
	ROOT* pListRoot = (ROOT*) calloc(1, sizeof(ROOT));
	if (pListRoot == NULL) {
		DisplayError(FAILED_ALLOC_ROOT);
	}

	/* Set the root structure to point to the newly-created node as
	 * both the head and the tail (since there is just one node in the
	 * list right now). */
	pListRoot->pHead = pListHead;
	pListRoot->pTail = pListHead;

	/* Set the pListRoot of the newly-created head element to reference
	 * back to the root. */
	pListHead->pListRoot = pListRoot;

	/* Since this is the first element, there is nothing for the pNext and
	 * pPrev pointers to reference right now. */
	pListHead->pNext = NULL;
	pListHead->pPrev = NULL;

	/* Initialize the pvData member of the new node with the data
	 * pointer passed to this function. */
	pListHead->pvData = pvData;

	/* Return the address of the newly-created node. */
	return pListHead;
}

///////////////////////////////////////////////////////////////////////////////
// DestroyList function

void DestroyList(POSITION ** ppListHead, LPDEALLOC_ROUTINE lpfnDeallocFunc) {
	if (lpfnDeallocFunc == NULL) {
		DisplayError(NO_DEALLOC_ROUTINE_SPECIFIED);
	}

	if (GetCount(ppListHead) == 0) {
		return;			// Nothing to do since the list has no elements in it
	}

	POSITION *pos = GetHeadPosition(ppListHead);
	if (pos == NULL) {
		return;
	}

	/* First, deallocate all the data by iterating over the
	 list and then calling the deallocation routine. Then, remove the tail of
	 the list.  We work our way back and remove elements tail first. */
	do {
		lpfnDeallocFunc(pos->pvData);
	} while ((pos = RemoveTail(ppListHead)) != NULL);
}

///////////////////////////////////////////////////////////////////////////////
// FindElement function

/*
 * The compare functiopn (LPCOMPARE_ROUTINE) is user implemented.
 * It takes in two parameters:
 *    1. void* of value 1
 *    2. void* of value 2
 *
 *    The function return 1 on equals, 0 otherwise.
 *
 * find_member traverses the linked list starting at the head
 * and finds the first element of interest by using LPCOMPARE_ROUTINE.
 *
 * It takes the address of the value its trying to find a a function
 * pointer of type LPCOMPARE_ROUTINE.  It feeds its first parameter to
 * as a first arguemnt to LPCOMPARE_ROUTINE and the data field in the
 * linked list structure definition as the second argument to the
 * function pointed to by lpfnCompare.
 *
 * On success find_member returns a pointer to the list_entry of interest.
 * On failure it returns NULL.
 */

POSITION* FindElement(POSITION** ppListHead, void *pSearchKey,
		LPCOMPARE_ROUTINE lpfnCompare) {
	if (ppListHead == NULL || (*ppListHead) == NULL) {
		DisplayError(FAILED_SEARCH_NULL_HEAD);
	}

	if (pSearchKey == NULL) {
		DisplayError(FAILED_SEARCH_NULL_KEY);
	}

	if (lpfnCompare == NULL) {
		DisplayError(FAILED_SEARCH_NULL_COMPARER);
	}

	// precautionary measure -- double-check that the list
	// root element's head has been initialized
	POSITION *pos = GetHeadPosition(ppListHead);
	if (pos == NULL) {
		DisplayError(FAILED_SEARCH_NULL_HEAD);
	}

	// Iterate through the list elements and run the compare
	// routine for each.  Once the compare routine returns
	// TRUE, stop and return a pointer to the current element.
	do {
		if (lpfnCompare(pSearchKey, pos->pvData))
			return pos;
	} while ((pos = GetNext(pos)) != NULL);

	/* If we are here, then the desired element could not be located. */

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// ForEach function

void ForEach(POSITION **ppListHead, LPACTION_ROUTINE lpfnForEachRoutine) {
	if (ppListHead == NULL || (*ppListHead) == NULL) {
		return;
	}

	POSITION *pos = (*ppListHead)->pListRoot->pHead;
	free(pos->pListRoot);

	do {
		if (lpfnForEachRoutine != NULL)
			lpfnForEachRoutine(pos->pvData);
	} while ((pos = GetNext(pos)) != NULL);

	(*ppListHead) = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// GetCount function

int GetCount(POSITION** ppElement) {
	// In this case, we can't do anything because we do not know where in the
	// list we are starting from.  Since users of this library generally might
	// be calling this function after everything has been removed from a list,
	// assume that null input means a count of zero should be returned.
	if (ppElement == NULL || *ppElement == NULL) {
		return 0;
	}

	// Get ready to iterate through the list; use the pointer in ppElement
	// to get a reference to the head of the list by calling GetHeadPosition
	POSITION* pos = GetHeadPosition(ppElement);
	if (pos == NULL) {
		// this just means the list has nothing in it.
		return 0;
	}

	int nResult = 1;		// how many elements there are in the list
	while ((pos = GetNext(pos)) != NULL) {
		nResult++;
	}
	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
// GetHeadPosition function

POSITION* GetHeadPosition(POSITION** ppMember) {
	if (ppMember == NULL || *ppMember == NULL)
		DisplayError(ERROR_STARTING_MEMBER_NULL);

	if ((*ppMember)->pListRoot == NULL) {
		DisplayError(FAILED_ALLOC_ROOT);
	}

	return (*ppMember)->pListRoot->pHead;
}

///////////////////////////////////////////////////////////////////////////////
// GetNext function

POSITION* GetNext(POSITION *pos) {
	if (pos == NULL)
		return NULL;

	return pos->pNext;
}

///////////////////////////////////////////////////////////////////////////////
// GetTailPosition function

POSITION* GetTailPosition(POSITION** ppMember) {
	if (ppMember == NULL || *ppMember == NULL)
		DisplayError(ERROR_STARTING_MEMBER_NULL);

	if ((*ppMember)->pListRoot == NULL) {
		DisplayError(FAILED_ALLOC_ROOT);
	}

	return (*ppMember)->pListRoot->pTail;
}

///////////////////////////////////////////////////////////////////////////////
// RemoveElement function

///////////////////////////////////////////////////////////////////////////////
// RemoveElement function

BOOL RemoveElement(POSITION ** ppListHead, void *pSearchKey,
		LPCOMPARE_ROUTINE lpfnSearch) {
	if (ppListHead == NULL || (*ppListHead) == NULL) {
		DisplayError(FAILED_SEARCH_NULL_HEAD);
		return FALSE;
	}

	if (pSearchKey == NULL) {
		DisplayError(FAILED_SEARCH_NULL_KEY);
	}

	if (lpfnSearch == NULL) {
		DisplayError(FAILED_SEARCH_NULL_COMPARER);
	}

	//precuationary measure
	POSITION *pListHead = (*ppListHead)->pListRoot->pHead;

	if (pListHead == NULL) {
		DisplayError(FAILED_SEARCH_NULL_HEAD);
	}

	POSITION *pListMember = FindElement(ppListHead, pSearchKey, lpfnSearch);
	if (pListMember == NULL) {
		return FALSE;
	}

	if (pListMember == pListHead) {
		return RemoveHead(ppListHead);
	}
	if (pListMember == pListHead->pListRoot->pTail) {
		return RemoveTail(ppListHead) != NULL;
	}

	POSITION *pPrevElement = pListMember->pPrev;
	POSITION *pNextElement = pListMember->pNext;

	pPrevElement->pNext = pNextElement;
	pNextElement->pPrev = pPrevElement;

	(*ppListHead) = pListHead;

	//free(member->data);
	free(pListMember);
	pListMember = NULL;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// RemoveHead function

BOOL RemoveHead(POSITION **ppListHead) {
	if (ppListHead == NULL || (*ppListHead) == NULL) {
		DisplayError(FAILED_SEARCH_NULL_HEAD);
	}

	POSITION *pListHead = (*ppListHead);
	POSITION *pNewHead = pListHead->pNext;
	POSITION *pOldHead = pListHead;

	if (pNewHead == NULL) {				//head is the only element
		free(pListHead->pListRoot);
		free(pListHead);
		(*ppListHead) = NULL;
		return TRUE;
	}

	pNewHead->pPrev = NULL;
	(*ppListHead) = pNewHead;

	free(pOldHead);
	pOldHead = NULL;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// RemoveTail function

POSITION* RemoveTail(POSITION **ppListHead) {
	if (ppListHead == NULL || (*ppListHead) == NULL) {
		/* this could be a call from a while loop that is
		 iteerating over the list and removing all elements,
		 so merely return NULL here */
		return NULL;
	}

	POSITION *pListHead = (*ppListHead)->pListRoot->pHead;
	POSITION *pOldTail = pListHead->pListRoot->pTail;
	POSITION *pNewTail = pOldTail->pPrev;

	BOOL bHasElementsLeft = pOldTail->pPrev != NULL;

	if (bHasElementsLeft) {
		// We still have elements in the list
		pNewTail->pNext = NULL;
		pListHead->pListRoot->pTail = pNewTail;
	}

	free(pOldTail);
	pOldTail = NULL;

	if (!bHasElementsLeft) {
		// Nothing is left in the list, null it all out
		pListHead->pListRoot->pHead = NULL;
		pListHead->pListRoot->pTail = NULL;

		// Give ourselves amnesia about what *ppListHead points to,
		// there is just trash there now anyway
		(*ppListHead) = NULL;
	}

	return pNewTail;
}
