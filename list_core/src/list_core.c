// list_core.c - Provides implementations for the API functions that allow
// access to a linked list.
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

#include "stdafx.h"

#include "list_core.h"
#include "position.h"
#include "root.h"

///////////////////////////////////////////////////////////////////////////////
// Internal functions

// Forward declaration of DisplayError
void DisplayError(const char *pszMessage);

///////////////////////////////////////////////////////////////////////////////
// CreateNode function

/**
 * @brief Allocates memory for a new instance of a POSITION structure that
 * represents a node in the linked list.
 * @remarks If this function fails to allocate the needed memory, it will
 * write a message to this effect to STDERR and then cause the calling
 * program to exit.
 */
POSITION* CreateNode() {
	/* Create a new node */
	POSITION* pNewNode = (POSITION*) calloc(1, sizeof(POSITION));
	if (pNewNode == NULL) {
		DisplayError(FAILED_ALLOC_NEW_NODE);
	}
	return pNewNode;
}

///////////////////////////////////////////////////////////////////////////////
// CreateRoot function

/**
 * @brief Creates a new instance in memory of the ROOT structure
 * and returns the address of this instance.
 * @remarks If this function fails to allocate the needed memory, then the
 * function forces the calling program to terminate.
 */
ROOT* CreateRoot() {
	/* Create a new root structure to bear information about the
	 * head and tail. */
	ROOT* pListRoot = (ROOT*) calloc(1, sizeof(ROOT));
	if (pListRoot == NULL) {
		DisplayError(FAILED_ALLOC_ROOT);
	}
	return pListRoot;
}

///////////////////////////////////////////////////////////////////////////////
// DisplayError function

/**
 * @brief Prints the value of pszMessage to STDERR and exits the software.
 * @param pszMessage Message to be sent to STDERR.
 */
void DisplayError(const char *pszMessage) {
	// can't display a blank message
	if (IsNullOrWhiteSpace(pszMessage)) {
		return;
	}
	fprintf(stderr, "%s", pszMessage);
	exit(EXIT_FAILURE);
}

///////////////////////////////////////////////////////////////////////////////
// ValidateData function

/**
 * @brief Checks that valid data (i.e., a non-NULL pointer) was supplied.
 * @param pvData Pointer to be tested.
 * @remarks If this function detects that its argument is a NULL pointer, it
 * writes an error message to STDERR and exits the calling program.
 */
void ValidateData(void* pvData) {
	if (pvData == NULL) {
		DisplayError(INVALID_LIST_DATA);
	}
}

///////////////////////////////////////////////////////////////////////////////
// IsListHeadValid function

/**
 * @brief Examines the POSITIOn reference passed and returns a value that
 * indicates whether it is a valid refrence to the head of the linked list.
 * @param ppListHead Address of a pointer to a POSITION structure that refers
 * to the element that is at the head of the list.
 * @returns TRUE if the list head reference is valid; FALSE otherwise.
 * @remarks This function checks its argument for being a NULL pointer and
 * that it refers to a valid address.  If this is not the case, this function
 * returns FALSE.  */
BOOL IsListHeadValid(POSITION** ppListHead) {
	return ppListHead != NULL && (*ppListHead) != NULL;
}

///////////////////////////////////////////////////////////////////////////////
// ValidateSearchKey function

/**
 * @brief Validates that the pointer to the search key given is not NULL.
 * @param pSearchKey Pointer to a data value to be used as a search key.
 * @remarks This function determines whether pSearchKey references an address
 * in memory. If it does not, the function writes an error message to STDERR
 * and then causes the calling program to terminate.
 */
void ValidateSearchKey(void* pSearchKey) {
	if (pSearchKey == NULL) {
		DisplayError(FAILED_SEARCH_NULL_KEY);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Functions exposed to callers

///////////////////////////////////////////////////////////////////////////////
// AddTail function

BOOL AddTail(POSITION** ppListHead, void *pvData) {
	ValidateData(pvData);

	if (!IsListHeadValid(ppListHead)) {
	    return FALSE;
	}

	POSITION* pNewTail = CreateNode();

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
	ValidateData(pvData);

	/* Create a new node to serve as the new head. The CreateNode
	 * function causes the program to exit if it fails. */
	POSITION* pListHead = CreateNode();

	/* Create a new root structure to bear information about the
	 * head and tail. */
	ROOT* pListRoot = CreateRoot();

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

void DestroyList(POSITION** ppListHead, LPDEALLOC_ROUTINE lpfnDeallocFunc) {
	if (!IsListHeadValid(ppListHead)){
	    return;
	}

	if (lpfnDeallocFunc == NULL) {
		DisplayError(NO_DEALLOC_ROUTINE_SPECIFIED);
	}

	if (GetCount(ppListHead) == 0) {
		return;        // Nothing to do since the list has no elements in it
	}

	POSITION *pos = GetHeadPosition(ppListHead);
	if (pos == NULL) {
		return;
	}

	/* First, deallocate all the data by iterating over the
	 list and then calling the deallocation routine. Then,
	 remove the tail of the list.  We work our way back and
	 remove elements tail first. */
	do {
		lpfnDeallocFunc(pos->pvData);
	} while ((pos = RemoveTail(ppListHead)) != NULL);
}

///////////////////////////////////////////////////////////////////////////////
// FindElement function

/**
 * The compare functiopn (LPCOMPARE_ROUTINE) is user implemented.
 * It takes in two parameters:
 *    1. void* of value 1
 *    2. void* of value 2
 *
 *    The function return 1 on equals, 0 otherwise.
 *
 * FindElement traverses the linked list starting at the head
 * and finds the first element of interest by using LPCOMPARE_ROUTINE.
 *
 * It takes the address of the value its trying to find a a function
 * pointer of type LPCOMPARE_ROUTINE.  It feeds its first parameter to
 * as a first arguemnt to LPCOMPARE_ROUTINE and the data field in the
 * linked list structure definition as the second argument to the
 * function pointed to by lpfnCompare.
 *
 * On success FindElement returns a pointer to the list_entry of interest.
 * On failure it returns NULL.
 */

POSITION* FindElement(POSITION** ppListHead, void *pSearchKey,
		LPCOMPARE_ROUTINE lpfnCompare) {
    if (GetCount(ppListHead) == 0) {
        return NULL;
    }

	if (!IsListHeadValid(ppListHead)) {
	    return NULL;
	}

	ValidateSearchKey(pSearchKey);

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
	if (!IsListHeadValid(ppListHead)) {
	    return;
	}

	POSITION *pos = GetHeadPosition(ppListHead);
	if (pos == NULL) {
		DisplayError(FAILED_OPERATION_NULL_HEAD);
	}

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

	/* Here we use a while instead of a 'do while' loop. This is because we
	 * have firmly established, by this point in the code, that the list
	 * contains more than zero elements.  Therefore, we set our counter to
	 * 1 to start and attempt to go the next element right off the bat. */

	int nResult = 1;        // how many elements there are in the list
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

BOOL RemoveElement(POSITION** ppListHead, void *pSearchKey,
		LPCOMPARE_ROUTINE lpfnSearch) {
	if (!IsListHeadValid(ppListHead)) {
	    return FALSE;
	}

	ValidateSearchKey(pSearchKey);

	if (lpfnSearch == NULL) {
		DisplayError(FAILED_SEARCH_NULL_COMPARER);
	}

	//precuationary measure
	POSITION *pListHead = GetHeadPosition(ppListHead);
	if (pListHead == NULL) {
		return FALSE;
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

	if (pNewHead == NULL) {                //head is the only element
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
