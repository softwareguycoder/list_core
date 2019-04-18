// stdafx.h - Contains include directives for system header files and commonly-used symbols
//

#ifndef __STDAFX_H__
#define __STDAFX_H__

#define _GNU_SOURCE

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>

/**
 * @brief Custom data type that makes it more fluent to handle Boolean values.
 */
typedef enum {
	FALSE, TRUE
} BOOL;

#include "list_core_symbols.h"

#endif //__STDAFX_H__
