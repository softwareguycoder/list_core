// list_core.c - Provides implementations for the API function that allow access to a linked list.
//

#include "stdafx.h"

#include "list_core.h"
#include "position.h"
#include "root.h"

///////////////////////////////////////////////////////////////////////////////
// GetCount function

int GetCount(POSITION ** ppElement) {
	if (ppElement == NULL || *ppElement == NULL) {
		return 0;			// unable to determine element count; assume that
								// this is because we are being asked to count
								// the elements in a list that has no elements
	}

	// Get ready to iterate through the list; use the pointer in ppElement
	// to get a reference to the head of the list by calling GetHeadPosition
	POSITION *pos = GetHeadPosition(ppElement);
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
