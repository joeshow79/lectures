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

#define SEGLIST_MIN_LEVEL 3
// maximum capacity is 16M since maximum heap is MAX_HEAP(20M)
#define SEGLIST_MAX_LEVEL 24
#define SEGLIST_START_LEVEL 3

#define SEGLIST_CLASSES (SEGLIST_MAX_LEVEL - SEGLIST_MIN_LEVEL + 1)

//  get the class level of the seglist from which try to allocate mem
#define GET_ALLOCATION_FROM_CLASS(size) (log2n_of_power2(roundup_to_power2(size)) - SEGLIST_START_LEVEL)

// get the class level of the seglist to which try to put the free mem record
// NOTE: the largest class host all the blocks above the limit size
#define GET_ALLOCATION_CLASS(size) ((GET_ALLOCATION_FROM_CLASS(size + 1) - 1) >= SEGLIST_CLASSES ? \
                                        SEGLIST_CLASSES: (GET_ALLOCATION_FROM_CLASS(size + 1) - 1))

#define ASSERT_CLASS(cls) { \
    assert(cls >= (SEGLIST_MIN_LEVEL - SEGLIST_START_LEVEL)); \
    assert(cls <= (SEGLIST_MAX_LEVEL - SEGLIST_START_LEVEL)); \
    }

typedef unsigned int BASETYPE ;
typedef BASETYPE *  PTRTYPE;

#define HEADER_SIZE (sizeof(void*))
#define FOOTER_SIZE (sizeof(void*))
#define MIN_PAYLOAD_SIZE (2 * sizeof(void*))

#define VALUE_OF_PTR(ptr) (*((PTRTYPE)ptr))
#define RAW_PTR_TO_SLPTR(ptr) ((PTRTYPE)ptr + 1)

#define BLOCK_PTR(ptr) ptr
#define HEADER_PTR(ptr) ((PTRTYPE)ptr - 1)
#define FOOTER_PTR(ptr, size) (PTRTYPE)((char*)ptr + size)
#define BLOCK_NEXT_PTR(ptr) ptr
#define BLOCK_PREV_PTR(ptr) ((PTRTYPE)ptr + 1)

#define NEXT(ptr) ((PTRTYPE)VALUE_OF_PTR(BLOCK_NEXT_PTR(ptr)))
#define PREV(ptr) ((PTRTYPE)VALUE_OF_PTR(BLOCK_PREV_PTR(ptr)))

#define SET_BLOCK_NEXT_PTR(ptr, p) (VALUE_OF_PTR(BLOCK_NEXT_PTR(ptr)) = (BASETYPE)p)
#define SET_BLOCK_PREV_PTR(ptr, p) (VALUE_OF_PTR(BLOCK_PREV_PTR(ptr)) = (BASETYPE)p)

#define BLOCK_SIZE_HEADER(ptr) ((VALUE_OF_PTR(HEADER_PTR(ptr))) & (-2))

#define SET_HEADER_ALLOC(ptr, size)  VALUE_OF_PTR(HEADER_PTR(ptr)) = size; \
    VALUE_OF_PTR(HEADER_PTR(ptr)) |= 0x1;    // Allocated flag
#define SET_FOOTER_ALLOC(ptr, size)  VALUE_OF_PTR(FOOTER_PTR(ptr, size)) = size; \
    VALUE_OF_PTR(FOOTER_PTR(ptr, size)) |= 0x1;    // Allocated flag

#define SET_HEADER_VALID(ptr, size)  VALUE_OF_PTR(HEADER_PTR(ptr)) = size
#define SET_FOOTER_VALID(ptr, size)  VALUE_OF_PTR(FOOTER_PTR(ptr, size)) = size

// 0 for valid for allocation
// 1 for already allocated
#define RESET_HEADER_VALID(ptr, size) VALUE_OF_PTR(HEADER_PTR(ptr)) &= (-2)    // clear allocated flag
#define RESET_FOOTER_VALID(ptr, size) VALUE_OF_PTR(FOOTER_PTR(ptr, size)) &= (-2)

#define IS_BLOCK_VALID(ptr) ((VALUE_OF_PTR(HEADER_PTR(ptr)) & (0x1)) == 0)

#define SPLIT_BLOCK_PTR(ptr, size) ((PTRTYPE)((char*)((PTRTYPE)ptr + 2) + size))
#define SPLIT_BLOCK_PAYLOAD_SIZE(orig, alloc) (orig - alloc - HEADER_SIZE - FOOTER_SIZE)

#define BLOCK_OVERHEAD_SIZE (HEADER_SIZE + FOOTER_SIZE)
#define BLOCK_PAYLOAD_SIZE(size) (size - HEADER_SIZE - FOOTER_SIZE)
#define BLOCK_TOTAL_SIZE(size) (size + BLOCK_OVERHEAD_SIZE)
#define BLOCK_MINIMUM_SIZE (MIN_PAYLOAD_SIZE + BLOCK_OVERHEAD_SIZE)

#define ENABLE_COALESCE 1
#define ENABLE_LOG 0

#if ENABLE_LOG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

#define ERR(...) printf(__VA_ARGS__)

int roundup_to_power2(size_t n) {
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    // needed for 64bit data, not for 32bit
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
 * seglist -- segregated free lists
 */
typedef struct seglist_t {
    /*roots[0]  free block with size range: [2^SEGLIST_MIN_LEVEL ~ 2^(SEGLIST_MIN_LEVEL+1)-1]*/
    /*roots[1]  [2^(SEGLIST_MIN_LEVEL+1) ~ 2^(SEGLIST_MIN_LEVEL+2)-1]*/
    /*...*/
    /*roots[-1]  [2^(SEGLIST_MAX_LEVEL), infi/upper]*/

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

void seglist_dump(char* msg, struct seglist_t* sl) {
    LOG("\n=================SEGLIST DUMP: [%s]=================\n", msg);

    for(int i = 0; i < SEGLIST_CLASSES; ++i) {

        PTRTYPE p = sl->roots[i];
        if(NULL != p)
            LOG("\nSEGLIST[%d]:\t", i);

        while (NULL != p) {
            LOG("[(addr) 0x%x][(sz) %d]\t((next) 0x%x : (prev) 0x%x) -> \n", (BASETYPE)(p),
                    BLOCK_SIZE_HEADER(p), (BASETYPE)NEXT(p), (BASETYPE)PREV(p));

            p = NEXT(p);
        }
    }
}

/**
 * Record free memory ptr into appropirate seglist items
 *
 * fptr: ptr to free block
 * size: size of free block, must be the size of ALIGNMENT bytes aligned memory block
 */
void seglist_add_item(struct seglist_t* seglist, PTRTYPE new_block_ptr, size_t size) {
    assert(size <= (1 << SEGLIST_MAX_LEVEL));
    assert(size >= ALIGNMENT);

    // NOTE: Another policy that not used
    // the idea is split the block to multi classes
    // Reallocate the free memory into seperate classes list
    // Example;
    //   Remainder  |  Half=(Remainder+8)/2  |  Residual=Remainder-Half
    //   120        |             64         |          56
    //    56        |             32         |          24
    //    24        |             16         |          8
    //    8         |             8          |          0

    SET_HEADER_VALID(new_block_ptr, size);
    SET_FOOTER_VALID(new_block_ptr, size);

    // clear the block next&prev pointers first
    SET_BLOCK_NEXT_PTR(new_block_ptr, 0);
    SET_BLOCK_PREV_PTR(new_block_ptr, 0);

    int to_cls = GET_ALLOCATION_CLASS(size);
    assert(to_cls >= 0);

    PTRTYPE tptr = seglist->roots[to_cls];
    if(NULL != tptr) {
        LOG("seglist not empty, try to relink\n");

        // new_block->next = old_block
        SET_BLOCK_NEXT_PTR(new_block_ptr, tptr);
        // old_block->prev = new_block
        SET_BLOCK_PREV_PTR(tptr, new_block_ptr);
    } else {
        SET_BLOCK_NEXT_PTR(new_block_ptr, NULL);
    }

    seglist->roots[to_cls] = BLOCK_PTR(new_block_ptr);
}

void* seglist_try_malloc(struct seglist_t* seglist, size_t size){
    // step1: search from the free list, if found then return
    size_t asize = ALIGN(size);
    /*int cls = GET_ALLOCATION_FROM_CLASS(asize);*/
    int cls = GET_ALLOCATION_CLASS(asize);

    LOG("seglist_try_malloc from class %d for %d->%d bytes mem\n", cls, size, asize);

    ASSERT_CLASS(cls);

    for(int i = cls; i < SEGLIST_CLASSES; ++i) {
        PTRTYPE ptr = seglist->roots[i];

        while(NULL != ptr) {
            size_t block_size = BLOCK_SIZE_HEADER(ptr);

            if(block_size < asize) {
                // ptr = ptr->next
                ptr = NEXT(ptr);
                continue;
            }

            PTRTYPE pnext =  NEXT(ptr);

            // remove the block from the list since will allocate the mem from the head
            // TODO: verify pnext is valid pointer
            seglist->roots[i] = pnext;

            // if the margin bytes can not reside one minimum block
            // then assign the margin bytes into the block for the request
            if ((block_size >=asize) &&
                    (block_size < (asize + BLOCK_MINIMUM_SIZE))) {
                        SET_HEADER_ALLOC(ptr, block_size);
                        SET_FOOTER_ALLOC(ptr, block_size);
                       return ptr;
            }

            if (block_size >= (asize + BLOCK_MINIMUM_SIZE))  {
               // split and return the memory
               size_t new_block_sz = SPLIT_BLOCK_PAYLOAD_SIZE(block_size, asize);
               PTRTYPE new_block_ptr = SPLIT_BLOCK_PTR(ptr, asize);

               LOG("split %d bytes block to %d bytes allocated block and %d bytes free block\n",
                       block_size, asize, new_block_sz);

               // set header&footer for allocated block
               SET_HEADER_ALLOC(ptr, asize);
               SET_FOOTER_ALLOC(ptr, asize);

               // Add split block back to seglist
               seglist_add_item(seglist, new_block_ptr, new_block_sz);
               seglist_dump("after split", seglist);

               return ptr;
            }
        }
    }

    // failed to allocate
    return NULL;
}

/**
 * Return:
 * 0: Blocks not adjecent
 * 1: blocks pointted by ptr_a and ptr_b are adjecent and block A preceed block B
 * -1: blocks pointted by ptr_a and ptr_b are adjecent and block B preceed block A
 */
int is_block_adjecent(PTRTYPE ptr_a, PTRTYPE ptr_b) {
    assert(NULL != ptr_a);
    assert(NULL != ptr_b);

    PTRTYPE header_ptr_a = HEADER_PTR(ptr_a);
    PTRTYPE header_ptr_b = HEADER_PTR(ptr_b);
    size_t sz_a = BLOCK_SIZE_HEADER(ptr_a);
    PTRTYPE footer_ptr_a = FOOTER_PTR(ptr_a, sz_a);
    size_t sz_b = BLOCK_SIZE_HEADER(ptr_b);
    PTRTYPE footer_ptr_b = FOOTER_PTR(ptr_b, sz_b);

    BASETYPE header_a = (BASETYPE) header_ptr_a;
    BASETYPE header_b = (BASETYPE) header_ptr_b;
    BASETYPE footer_a = (BASETYPE) footer_ptr_a;
    BASETYPE footer_b = (BASETYPE) footer_ptr_b;

#define IS_ADJECENT(a, b) ((a-4) == b)
    /*LOG("check is_adjecent 0x%x:%d and 0x%x:%d\n", (BASETYPE)ptr_a, sz_a, (BASETYPE)ptr_b, sz_b);*/
    /*LOG("a header: 0x%x, b header: 0x%x\n", (BASETYPE)header_a, (BASETYPE)header_b);*/
    /*LOG("a footer: 0x%x, b footer: 0x%x\n", (BASETYPE)footer_a, (BASETYPE)footer_b);*/
    if (IS_ADJECENT(header_a, footer_b)) {
        return -1;
    }

    if (IS_ADJECENT(header_b, footer_a)) {
        return 1;
    }
#undef IS_ADJECENT

    return 0;
}

/**
 * merge the 2 blocks
 * Note: front is preceed read
 * Before merge
     *Block front
     *  [  size_f   ]
     *  [   next    ]
     *  [   prev    ]
     *  [           ]
     *  [ blk front ]
     *  [           ]
     *  [  size_f   ]
     *
     *Block rear
     *  [  size_r   ]
     *  [   next    ]
     *  [   prev    ]
     *  [           ]
     *  [ blk front ]
     *  [           ]
     *  [  size_r   ]
     *
 * After merge
     *Block
     *  [ size_f+r  ]
     *  [   next    ]
     *  [   prev    ]
     *  [           ]
     *  [ blk front ]
     *  [           ]
     *  [ size_f+r  ]
 */
PTRTYPE merge_block(PTRTYPE front, PTRTYPE rear) {
    assert(1 == is_block_adjecent(front, rear));

    size_t sz_f = BLOCK_SIZE_HEADER(front);
    size_t sz_r = BLOCK_SIZE_HEADER(rear);
    size_t sz_n = sz_f + sz_r + BLOCK_OVERHEAD_SIZE;   // 1 header and 1 footer eliminated

    LOG("merge_block 0x%x:%d and 0x%x:%d to 0x%x:%d\n",
            (BASETYPE)front, sz_f, (BASETYPE)rear, sz_r, (BASETYPE)front, sz_n);

    SET_HEADER_VALID(front, sz_n);
    SET_FOOTER_VALID(front, sz_n);

    return front;
}


/*
 * Reclaim the block into seglist, and do coalescing before that
 */
void seglist_reclaim(struct seglist_t* seglist, PTRTYPE ptr) {
    for(int i = 0; i < SEGLIST_CLASSES; ++i) {
        PTRTYPE iter = seglist->roots[i];

        while(NULL != iter) {
            int ret = is_block_adjecent(iter, ptr);

            PTRTYPE inext = NEXT(iter);

            // iter precede ptr
            if (0 != ret) {
                PTRTYPE iprev = PREV(iter);

                // iter is head
                if (seglist->roots[i] == iter) {
                    seglist->roots[i] = inext;

                } else {
                    if (NULL != iprev) {
                        // iter->prev->next = iter->next
                        SET_BLOCK_NEXT_PTR(iprev, inext);
                    }
                }

                if (NULL != inext) {
                    // iter->next->prev = iter->prev
                    SET_BLOCK_PREV_PTR(inext, iprev);
                }

                PTRTYPE new_block;

                if (1 == ret) {
                    new_block = merge_block(iter, ptr);
                }

                if (-1 == ret) {
                    new_block = merge_block(ptr, iter);
                }

                // recursive(at most 2 passes) to make sure all adjecent blocks been coalesced
                // this could solve the case that the reclaimed block adjecent
                // to one preceding block and one posterior block
                //
                // Before reclaim blockR (which adjecent blockA and blockB both)
                // [blockA] ... [blockBsymotion-prefix)] (blockA and blockB are not adjecent)
                //
                // Pass 1:
                // [blockA+R][blockB]
                //
                // Pass 2:
                // [blockA+R+B]
                return seglist_reclaim(seglist, new_block);
            }

            // iter = iter->next
            iter = inext;
        }
    }

    size_t sz = BLOCK_SIZE_HEADER(ptr);
    seglist_add_item(seglist, ptr, sz);
}

seglist_t* seglist_g;

/*
 *
 * mm_check - seglist sanity checking
 */
int mm_check(struct seglist_t* seglist) {
    for(int i = 0; i < SEGLIST_CLASSES; ++i) {
        PTRTYPE iter = seglist->roots[i];

        while(NULL != iter) {
            // 1:  block marked as empty?
            if (! IS_BLOCK_VALID(iter)) {
                ERR("block sanity checking failed addr:0x%x sz:%d valid:%d\n",
                        (BASETYPE)iter, BLOCK_SIZE_HEADER(iter), IS_BLOCK_VALID(iter));

                assert(0);
            }

            // 2: any continous free blocks escaped coalescing?

            // 3: pointer in the free list point to valid free blocks?

            // 4: any overlapping block

            iter = NEXT(iter);
        }
    }

    return 0;
}

/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    int sl_size = ALIGN(sizeof(struct seglist_t));
    seglist_g= (seglist_t*)mem_sbrk(sl_size);

    seglist_init(seglist_g);

    // NOTE: shift  4 byte for 8 byte alignment requirement
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
    seglist_dump("before mm_malloc", seglist_g);
    int newsize = ALIGN(size) + BLOCK_OVERHEAD_SIZE;

    PTRTYPE ret = seglist_try_malloc(seglist_g, BLOCK_PAYLOAD_SIZE(newsize));

    if(NULL == ret) {
        // request more mem from system
        void *p = mem_sbrk(newsize);
        if (p == (void *)-1)
	        return NULL;

        seglist_add_item(seglist_g, RAW_PTR_TO_SLPTR(p),  BLOCK_PAYLOAD_SIZE(newsize));

        seglist_dump("after mem_sbrk", seglist_g);

        // try second allocation from seglist managed blocks
        ret = seglist_try_malloc(seglist_g, BLOCK_PAYLOAD_SIZE(newsize));

        assert(NULL != ret);
    }
    seglist_dump("after mm_malloc", seglist_g);

    LOG("mm_malloc addr: 0x%x sz: %d\n", (BASETYPE)ret, BLOCK_PAYLOAD_SIZE(newsize));

    return (void*)ret;
#endif
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    size_t sz = BLOCK_SIZE_HEADER(ptr);
    RESET_HEADER_VALID(ptr, sz);
    RESET_FOOTER_VALID(ptr, sz);
    SET_BLOCK_NEXT_PTR(ptr, 0);
    SET_BLOCK_PREV_PTR(ptr, 0);

#ifdef ENABLE_COALESCE
    seglist_reclaim(seglist_g, ptr);
#else
    seglist_add_item(seglist_g, ptr, sz);
#endif

    seglist_dump("after mm_free", seglist_g);

    mm_check(seglist_g);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
#ifdef DEBUG
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
#else
    size_t sz = BLOCK_SIZE_HEADER(ptr);

    void* oldptr = ptr;
    void* newptr;

    newptr = mm_malloc(size);

    if (newptr == NULL)
      return NULL;

    if (size < sz)
      sz = size;

    memcpy(newptr, oldptr, sz);
    mm_free(oldptr);

    return newptr;
#endif
}
