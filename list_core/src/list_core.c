// list_core.c - Provides implementations for the API function that allow access to a linked list.
//

#include "stdafx.h"

#include "list_core.h"
#include "position.h"
#include "root.h"

///////////////////////////////////////////////////////////////////////////////
// AddHead function

POSITION* AddHead(void *pvData) {
	if (pvData == NULL) {
		HandleError(INVALID_LIST_DATA);
	}

	/* Create a new node to serve as the new head. */
	POSITION* pListHead = (POSITION*) calloc(1, sizeof(POSITION));
	if (pListHead == NULL) {
		HandleError(FAILED_ALLOC_HEAD);
	}

	/* Create a new root structure to bear information about the
	 * head and tail. */
	ROOT* pListRoot = (ROOT*) calloc(1, sizeof(ROOT));
	if (pListRoot == NULL) {
		HandleError(FAILED_ALLOC_ROOT);
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
// AddTail function

BOOL AddTail(POSITION** ppListHead, void *pvData) {
	if (pvData == NULL) {
		HandleError(INVALID_LIST_DATA);
	}

	if (ppListHead == NULL || (*ppListHead) == NULL) {
		HandleError(ADD_ELEMENT_HEAD_NULL);
	}

	POSITION* pNewTail = (POSITION*) calloc(1, sizeof(POSITION));
	if (pNewTail == NULL) {
		HandleError(FAILED_ALLOC_NEW_NODE);
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
