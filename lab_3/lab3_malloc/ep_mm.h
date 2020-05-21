#ifndef EP_MM_H
#define EP_MM_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

extern int mm_init(void);
extern void *mm_malloc(size_t size);
extern void mm_free(void *bp);
extern void *mm_realloc(void *ptr, size_t size);
/*
 *	static void *extend_heap(size_t words);
 *	static void *coalesce(void *bp);
 *	static void *find_fit(size_t asize);
 *	static void place(void *bp, size_t asize);
 *	static void add_to_free_list(void *bp);
 *	static void delete_from_free_list(void *bp);
 */
extern void check_all_mem();
extern void check_free_mem();

#endif
