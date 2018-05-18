//
//  utils.h
//  xdag
//
//  Created by Rui Xie on 3/16/18.
//  Copyright © 2018 xrdavies. All rights reserved.
//

#ifndef XDAG_UTILS_HEADER_H
#define XDAG_UTILS_HEADER_H

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#ifdef _WIN32
#define DELIMITER "\\"
#else
#define DELIMITER "/"
#endif

extern uint64_t get_timestamp(void);

extern void xdag_init_path(char *base);
extern FILE* xdag_open_file(const char *path, const char *mode);
extern void xdag_close_file(FILE *f);
extern int xdag_file_exists(const char *path);
extern int xdag_mkdir(const char *path);

/* dead lock detector */

#define DEAD_LOCK_DETECT 0
extern void start_check_deadlock_thread(void);
extern void apply_lock_before(uint64_t tid, pthread_mutex_t* mutex_ptr, const char* name);
extern void apply_lock_after(uint64_t tid, pthread_mutex_t* mutex_ptr);
extern void apply_unlock(uint64_t tid, pthread_mutex_t* mutex_ptr);

extern void test_deadlock(void);

#if DEAD_LOCK_DETECT
#define XDAG_MUTEX_TRYLOCK(x) pthread_mutex_trylock(&x)

#define XDAG_MUTEX_LOCK(x) \
do {\
	apply_lock_before(pthread_self(), &x, #x);\
	pthread_mutex_trylock(&x);\
	apply_lock_after(pthread_self(), &x);\
} while(0)

#define XDAG_MUTEX_UNLOCK(x) \
do {\
	pthread_mutex_unlock(&x);\
	apply_unlock(pthread_self(), &x);\
} while(0)
	
#else
#define XDAG_MUTEX_TRYLOCK(x) pthread_mutex_trylock(&x)
#define XDAG_MUTEX_LOCK(x) pthread_mutex_lock(&x)
#define XDAG_MUTEX_UNLOCK(x) pthread_mutex_unlock(&x)
#endif



#endif /* utils_h */
