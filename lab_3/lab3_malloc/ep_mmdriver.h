#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <float.h>

#include "ep_mm.h"
#include "memlib.h"

/* Misc */
#define MAXLINE 1024	   /* max string size */
#define HDRLINES 4		   /* number of header lines in a trace file */
#define LINENUM(i) (i + 5) /* cnvt trace request nums to linenums (origin 1) */
/* 
* Alignment requirement in bytes (either 4 or 8) 
*/
#define ALIGNMENT 8

/* Returns true if p is ALIGNMENT-byte aligned */
#define IS_ALIGNED(p) ((((unsigned int)(p)) % ALIGNMENT) == 0)

/********************
 * Global variables
 *******************/
int verbose = 0;	   /* global flag for verbose output */
static int errors = 0; /* number of errs found when running student malloc */
char msg[MAXLINE];	   /* for whenever we need to compose an error message */

/****************************** 
 * The key compound data types 
 *****************************/

/* Records the extent of each block's payload */
typedef struct range_t
{
	char *lo;			  /* low payload address */
	char *hi;			  /* high payload address */
	struct range_t *next; /* next list element */
} range_t;

/* Characterizes a single trace operation (allocator request) */
typedef struct
{
	enum
	{
		ALLOC,
		FREE,
		REALLOC
	} type;	   /* type of request */
	int index; /* index for free() to use later */
	int size;  /* byte size of alloc/realloc request */
} traceop_t;

/* Holds the information for one trace file*/
typedef struct
{
	int sugg_heapsize;	 /* suggested heap size (unused) */
	int num_ids;		 /* number of alloc/realloc ids */
	int num_ops;		 /* number of distinct requests */
	int weight;			 /* weight for this trace (unused) */
	traceop_t *ops;		 /* array of requests */
	char **blocks;		 /* array of ptrs returned by malloc/realloc... */
	size_t *block_sizes; /* ... and a corresponding array of payload sizes */
} trace_t;

typedef struct
{
	/* defined for both libc malloc and student malloc package (mm.c) */
	double ops;	 /* number of ops (malloc/free/realloc) in the trace */
	int valid;	 /* was the trace processed correctly by the allocator? */
	double secs; /* number of secs needed to run the trace */

	/* defined only for the student malloc package */
	double util; /* space utilization for this trace (always 0 for libc) */

	/* Note: secs and util are only defined if valid is true */
} stats_t;

static int add_range(range_t **ranges, char *lo, int size,
					 int tracenum, int opnum);

static void remove_range(range_t **ranges, char *lo);

static void clear_ranges(range_t **ranges);

static trace_t *read_trace(char *filename);

void free_trace(trace_t *trace);

static int eval_mm_valid(trace_t *trace, int tracenum, range_t **ranges);

void app_error(char *msg);

void unix_error(char *msg);

void malloc_error(int tracenum, int opnum, char *msg);

int run_trace(char *filename);


