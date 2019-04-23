// root.h - Defines the ROOT structure which comprises part of the doubly-linked
// list of clients.  The POSITION reference is an individual node of the list.
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

#ifndef __ROOT_H__
#define __ROOT_H__

/**
 * @brief Forward declaration of POSITION structure
 */
typedef struct _tagPOSITION POSITION;

/**
 * @brief Contains the locations of the head and the tail of the linked list.
 */
typedef struct _tagROOT {
	POSITION* pHead;
	POSITION* pTail;  // tail is only valid for the head node
} ROOT;

#endif /* __ROOT_H__ */
