/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Jason Jiao",
    /* First member's email address */
    "joeshow79@gmail.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

// FIXME: since the allocation is ALIGNMENT bytes aligned
// the granularity of the allocation is ALIGNMENT bytes?
#define SEGLIST_MIN_LEVEL 3
// maximum capacity is 16M since maximum heap is MAX_HEAP(20M)
#define SEGLIST_MAX_LEVEL 24
#define SEGLIST_START_LEVEL 3

#define SEGLIST_CLASSES (SEGLIST_MAX_LEVEL - SEGLIST_MIN_LEVEL + 1)

//  get the class level of the seglist from which try to allocate mem
#define GET_ALLOCATION_FROM_CLASS(size) (log2n_of_power2(roundup_to_power2(size)) - SEGLIST_START_LEVEL)
// get the class level of the seglist to which try to put the free mem record
#define GET_ALLOCATION_CLASS(size) (GET_ALLOCATION_FROM_CLASS(size + 1) - 1)

#define ASSERT_CLASS(cls) { \
    assert(cls >= (SEGLIST_MIN_LEVEL - SEGLIST_START_LEVEL)); \
    assert(cls <= (SEGLIST_MAX_LEVEL - SEGLIST_START_LEVEL)); \
    }

/*#define BASETYPE int*/
typedef unsigned int BASETYPE ;
/*#define PTRTYPE (BASETYPE *)*/
typedef BASETYPE *  PTRTYPE;

#define HEADER_SIZE (sizeof(void*))
#define FOOTER_SIZE (sizeof(void*))
#define MIN_PAYLOAD_SIZE (2 * sizeof(void*))

#define VALUE_OF_PTR(ptr) (*((PTRTYPE)ptr))
#define RAW_PTR_TO_SLPTR(ptr) ((PTRTYPE)ptr + 1)

#define HEADER_PTR(ptr) ((PTRTYPE)ptr - 1)
#define FOOTER_PTR(ptr, size) ((PTRTYPE)((char*)((PTRTYPE)ptr - 1) + size))
#define BLOCK_PTR(ptr) ptr
#define BLOCK_NEXT_PTR(ptr) ptr
#define BLOCK_PREV_PTR(ptr) ((PTRTYPE)ptr + 1)
#define SET_BLOCK_NEXT_PTR(ptr, p) (VALUE_OF_PTR(BLOCK_NEXT_PTR(ptr)) = (BASETYPE)p)
#define SET_BLOCK_PREV_PTR(ptr, p) (VALUE_OF_PTR(BLOCK_PREV_PTR(ptr)) = (BASETYPE)p)

#define BLOCK_SIZE_HEADER(ptr) ((VALUE_OF_PTR(HEADER_PTR(ptr))) & (-2))
#define SET_HEADER(ptr, size)  VALUE_OF_PTR(HEADER_PTR(ptr)) = size; \
    VALUE_OF_PTR(HEADER_PTR(ptr)) |= 0x1;    // Allocated flag
#define SET_FOOTER(ptr, size)  VALUE_OF_PTR(FOOTER_PTR(ptr, size)) = size; \
    VALUE_OF_PTR(FOOTER_PTR(ptr, size)) |= 0x1;    // Allocated flag

#define SPLIT_BLOCK_PTR(ptr, size) ((PTRTYPE)((char*)((PTRTYPE)ptr + 2) + size))
#define SPLIT_BLOCK_PAYLOAD_SIZE(orig, alloc) (orig - alloc - HEADER_SIZE - FOOTER_SIZE)

#define BLOCK_OVERHEAD_SIZE (HEADER_SIZE + FOOTER_SIZE)
#define BLOCK_PAYLOAD_SIZE(size) (size - HEADER_SIZE - FOOTER_SIZE)
#define BLOCK_TOTAL_SIZE(size) (size + HEADER_SIZE + FOOTER_SIZE)
#define BLOCK_MINIMUM_SIZE (HEADER_SIZE + FOOTER_SIZE + MIN_PAYLOAD_SIZE)

int roundup_to_power2(size_t n) {
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    // needed for 64bit data
    /*n |= n >> 32;*/
    ++n;

    return n;
}

// compute the lgn of a power of 2 value
int log2n_of_power2(size_t v) {
    int ret = -1;

    while(v) {
        v = v&(-2);
        v = v >> 1;
        ret ++;
    }

    return ret;
}

/*// buggy*/
/*int log2n_debruijn(size_t v) {*/
	/*unsigned long debruijn = 0x022fdd63cc95386d;*/
    /*long convert[64] = {*/
        /*0, 1, 2, 53, 3, 7, 54, 27,*/
        /*4, 38, 41, 8, 34, 55, 48, 28,*/
        /*62, 5, 39, 46, 44, 42, 22, 9,*/
        /*24, 35, 59, 56, 49, 18, 29, 11,*/
        /*63, 52, 6, 26, 37, 40, 33, 47,*/
        /*61, 45, 43, 21, 23, 58, 17, 10,*/
        /*51, 25, 36, 32, 60, 20, 57, 16,*/
        /*50, 31, 19, 15, 30, 14, 13, 12*/
    /*};*/

    /*printf("log2n: %d\n",  ((long)v * debruijn) );*/
    /*int ret = convert[(v * debruijn) >> 58];*/
    /*printf("log2n: %d:%d\n", v, ret);*/
    /*return ret;*/
/*}*/

/**
 * seglist
 */
typedef struct seglist_t {
    /*roots[0]  free block with size range in: 2^SEGLIST_MIN_LEVEL ~ 2^(SEGLIST_MIN_LEVEL+1)-1*/
    /*roots[1]  2^(SEGLIST_MIN_LEVEL+1) ~ 2^(SEGLIST_MIN_LEVEL+2)-1*/
    /*...*/
    /*roots[-1]  2^(SEGLIST_MAX_LEVEL)*/

    /**
     *BLOCK
     *  [   size    |a]
     *  [   next      ]
     *  [   prev      ]
     *  [             ]
     *  [   ....      ]
     *  [             ]
     *  [   size    |a]
     */

    PTRTYPE roots[SEGLIST_CLASSES];
} seglist_t;

/**
 *
 */
void seglist_init(struct seglist_t* seglist){
    for (int i = 0; i < SEGLIST_CLASSES; ++i) {
        seglist->roots[i] = NULL;
    }
}

void seglist_dump(struct seglist_t* sl) {
    printf("=================SEGLIST DUMP=================\n");

    for(int i = 0; i < SEGLIST_CLASSES; ++i) {

        PTRTYPE p = sl->roots[i];
        if(NULL != p) printf("\n");

        while (NULL != p) {
            printf("SEGLIST[%d]:\t", i);
            printf("[(addr) %x][(sz) %d]\t((next) %x : (prev) %x) -> \n", (BASETYPE)(p), BLOCK_SIZE_HEADER(p),
                    VALUE_OF_PTR(BLOCK_NEXT_PTR(p)), VALUE_OF_PTR(BLOCK_PREV_PTR(p)));

            p = (PTRTYPE)VALUE_OF_PTR(BLOCK_NEXT_PTR(p));
        }
    }
    /*printf("------------------------------------------\n");*/
}

/**
 * Record free memory ptr into appropirate seglist items
 *
 * fptr: ptr to free block
 * size: size of free block, must be the size of ALIGNMENT bytes aligned memory block
 */
void seglist_add_item(struct seglist_t* seglist, PTRTYPE new_block_ptr, size_t size){
    printf("seglist_add_item %x:%d\n", (BASETYPE)new_block_ptr, size);

    assert(size <= (1 << SEGLIST_MAX_LEVEL));
    assert(size >= ALIGNMENT);

    // Reallocate the free memory into seperate classes list
    // Example;
    //   Remainder  |  Half=(Remainder+8)/2  |  Residual=Remainder-Half
    //   120        |             64         |          56
    //    56        |             32         |          24
    //    24        |             16         |          8
    //    8         |             8          |          0

    /*size_t remainder = size;*/
    /*void* ptr = fptr;*/
    /*while(remainder) {*/
        /*size_t half = (remainder + ALIGNMENT) / 2;*/
        /*size_t residual = remainder - residual;*/
        /*size_t cls = log2n(half) - SEGLIST_MIN_LEVEL;*/

        /*ASSERT_CLASS(cls)*/

        /*// TODO*/
        /*void* cptr = seglist->roots[cls];*/

        /*ptr = ptr + half;*/
        /*remainder = residual;*/
    /*}*/

    /** (new_block_ptr - 1)  = size;*/
    /*printf("Header ptr:%x\n", HEADER_PTR(new_block_ptr));*/
    SET_HEADER(new_block_ptr, size);
    SET_FOOTER(new_block_ptr, size);

    int to_cls = GET_ALLOCATION_CLASS(size);
    assert(to_cls >= 0);

    PTRTYPE tptr = seglist->roots[to_cls];
    if(NULL != tptr) {
        SET_BLOCK_NEXT_PTR(new_block_ptr, VALUE_OF_PTR(BLOCK_NEXT_PTR(tptr)));

        PTRTYPE onext = BLOCK_NEXT_PTR(tptr);
        PTRTYPE pnext = (PTRTYPE)VALUE_OF_PTR(onext);
        if(NULL != pnext) {
            SET_BLOCK_PREV_PTR(BLOCK_PREV_PTR(pnext), new_block_ptr);
        }
    } else {
        SET_BLOCK_NEXT_PTR(new_block_ptr, NULL);
    }

    SET_BLOCK_PREV_PTR(new_block_ptr, tptr);
    seglist->roots[to_cls] = BLOCK_PTR(new_block_ptr);

    seglist_dump(seglist);
}

void* seglist_try_malloc(struct seglist_t* seglist, size_t size){
    // step1: search from the free list, if found then return
    size_t asize = ALIGN(size);
    /*int cls = GET_ALLOCATION_FROM_CLASS(asize);*/
    int cls = GET_ALLOCATION_CLASS(asize);

    printf("seglist_try_malloc from class %d for %d->%d bytes mem\n", cls, size, asize);

    ASSERT_CLASS(cls);

    for(int i = cls; i < SEGLIST_CLASSES; ++i) {
        PTRTYPE ptr = seglist->roots[cls];

        if(NULL != ptr) {
            PTRTYPE pnext = (PTRTYPE)(*ptr);

            // TODO: verify pnext is valid pointer
            seglist->roots[cls] = pnext;

            size_t block_size = BLOCK_SIZE_HEADER(ptr);

            assert(block_size >= asize);

            // if the margin bytes can not reside one minimum block
            // then assign the margin bytes to the request
            if ((block_size >=asize) &&
                    (block_size < asize + BLOCK_MINIMUM_SIZE)) {
                        SET_HEADER(ptr, block_size);
                       return ptr;
            } else {
               // split and return the memory
               size_t new_block_sz = SPLIT_BLOCK_PAYLOAD_SIZE(block_size, asize);
               PTRTYPE new_block_ptr = SPLIT_BLOCK_PTR(ptr, asize);
               /*SET_HEADER(HEADER_PTR(new_block_ptr), new_block_sz);*/
               /*SET_FOOTER(FOOTER_PTR(new_block_ptr, new_block_sz), new_block_sz);*/

               seglist_add_item(seglist, new_block_ptr, new_block_sz);
               /*int to_cls = GET_ALLOCATION_TO_CLASS(new_block_sz);*/
               /*assert(to_cls >= 0);*/

                /*PTRTYPE tptr = seglist->roots[to_cls];*/
                /*if(NULL != tptr) {*/
                    /*SET_BLOCK_NEXT_PTR(new_block_ptr, VALUE_OF_PTR(BLOCK_NEXT_PTR(tptr)));*/

                    /*PTRTYPE onext = BLOCK_NEXT_PTR(tptr);*/
                    /*PTRTYPE pnext = VALUE_OF_PTR(onext);*/
                    /*if(NULL != pnext) {*/
                        /*SET_BLOCK_PREV_PTR(BLOCK_PREV_PTR(pnext), new_block_ptr);*/
                    /*}*/

                /*} else {*/
                    /*SET_BLOCK_NEXT_PTR(new_block_ptr, NULL);*/
                /*}*/

                /*SET_BLOCK_PREV_PTR(new_block_ptr, tptr);*/
                /*seqlist->roots[to_cls] = BLOCK_PTR(new_block_ptr);*/

                return ptr;
            }
        }
    }

    // failed to allocate
    return NULL;
}

seglist_t* seglist_g;

/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    int sl_size = ALIGN(sizeof(struct seglist_t));
    seglist_g= (seglist_t*)mem_sbrk(sl_size);

    seglist_init(seglist_g);

    // shift  4 byte for 8 byte alignment requirement
    // the 4 bytes are leaked from seglist point of view
    mem_sbrk(4);

    return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    /*printf("mm_malloc begin\n");*/
#ifdef DEBUG
    int newsize = ALIGN(size + SIZE_T_SIZE);
    void *p = mem_sbrk(newsize);
    if (p == (void *)-1)
	return NULL;
    else {
        *(size_t *)p = size;
        return (void *)((char *)p + SIZE_T_SIZE);
    }
#else
    /*int newsize = ALIGN(size + SIZE_T_SIZE + BLOCK_OVERHEAD_SIZE);*/
    int newsize = ALIGN(size) + BLOCK_OVERHEAD_SIZE;

    /*printf("mm_malloc try to seglist_try_malloc for %d:%d bytes\n", BLOCK_PAYLOAD_SIZE(newsize), size);*/
    /*PTRTYPE ret = seglist_try_malloc(seglist_g, newsize);*/
    PTRTYPE ret = seglist_try_malloc(seglist_g, BLOCK_PAYLOAD_SIZE(newsize));

    if(NULL == ret) {
        // request more mem from system
        void *p = mem_sbrk(newsize);
        if (p == (void *)-1)
	        return NULL;

        seglist_add_item(seglist_g, RAW_PTR_TO_SLPTR(p),  BLOCK_PAYLOAD_SIZE(newsize));

        // try second allocation from seglist managed blocks
        // TODO: need to rethink if size is correct
        ret = seglist_try_malloc(seglist_g, BLOCK_PAYLOAD_SIZE(newsize));
        if(NULL == ret) {
            /*printf("seglist_try_malloc failed for %d:%d bytes\n", BLOCK_PAYLOAD_SIZE(newsize), size);*/
            seglist_dump(seglist_g);
        }

        assert(NULL != ret);
    }

    /*printf("mm_malloc end\n");*/
    return (void*)ret;
#endif
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    // TODO:
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}














