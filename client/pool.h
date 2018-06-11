/* pool logic */

#ifndef XDAG_POOL_H
#define XDAG_POOL_H

#include "hash.h"

#define MAX_CONNECTIONS_COUNT          8192
#define XDAG_POOL_CONFIRMATIONS_COUNT  16
#define CONFIRMATIONS_COUNT            XDAG_POOL_CONFIRMATIONS_COUNT   /*16*/

enum disconnect_type
{
	DISCONNECT_BY_ADRESS = 1,
	DISCONNECT_BY_IP = 2,
	DISCONNECT_ALL = 3
};

extern xdag_hash_t g_xdag_mined_hashes[XDAG_POOL_CONFIRMATIONS_COUNT];
extern xdag_hash_t g_xdag_mined_nonce[XDAG_POOL_CONFIRMATIONS_COUNT];

/* initialization of the pool */
extern int xdag_initialize_pool(const char *pool_arg);

/* gets pool parameters as a string, 0 - if the pool is disabled */
extern char *xdag_pool_get_config(char *buf);

/* sets pool parameters */
extern int xdag_pool_set_config(const char *pool_config);

/* output to the file a list of miners */
extern int xdag_print_miners(FILE *out, int printOnlyConnections);

// disconnect connections by condition
// condition type: all, ip or address
// value: address of ip depending on type
extern void disconnect_connections(enum disconnect_type type, char *value);

#endif
