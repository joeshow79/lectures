#include "cachelab.h"

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

unsigned get_timestamp() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec * 1000  + tv.tv_usec;
}

typedef struct cache_line {
    int valid;  // 1: valid , 0 otherwize
    unsigned tag;
    // no need to store the data since it's just a simulator to count miss or hit
    unsigned timestamp;
} cache_line_t;

typedef struct cache_set {
    cache_line_t* lines;
} cache_set_t;

typedef struct cache {
    int set_bits;
    int set_len;
    int offset_bits;
    cache_set_t* sets;
} cache_t;

cache_t*  construct_cache(int s, int E, int b) {
    cache_t* cache = malloc(sizeof(cache_t));

    if (NULL != cache) {
        cache->set_bits = s;
        int number_of_sets = (1<<s);
        cache->set_len = E;
        cache->offset_bits = b;

        cache_set_t* cache_sets = malloc(sizeof(cache_set_t) * number_of_sets);
        if (NULL == cache_sets) {
            free(cache);
            cache = NULL;
            return NULL;
       }

        cache->sets = cache_sets;

        cache_set_t* iterator = cache_sets;
        for(int i = 0; i < number_of_sets; ++i, ++iterator) {
            cache_line_t* lines = malloc(sizeof(cache_line_t) * E);

            if(NULL != lines) {

                iterator->lines = lines;

                cache_line_t* line = lines;
                for(int entity = 0; entity < E; ++entity, ++line) {
                    line->valid = 1;
                    line->tag = 0;
                    line->timestamp = 0;
                }
            } else {
                // free all allocated mem
                cache_set_t* set_head = cache_sets;
                for(int j = 0; j <= i; ++j) {
                    free(set_head->lines);
                    set_head->lines = NULL;
                }

                free(cache_sets);
                cache->sets = NULL;

                free(cache);
                cache = NULL;
                break;
            }
        }
    }

    return cache;
}

void deconstruct_cache(cache_t * cache) {
    if(NULL != cache) {
        cache_set_t* set_iterator = cache->sets;
        int number_of_sets = (1<<cache->set_bits);

        for(int i = 0; i < number_of_sets; ++i) {
            if (NULL != set_iterator) {
                free(set_iterator->lines);
                set_iterator->lines = NULL;
            }

            set_iterator += 1;
        }

        free(cache->sets);
        free(cache);
    }
}

/*
 * Return value:
 * 0: hit
 * 1: miss
 * 2: eviction
 * -1: error
 * */
int search_cache(cache_t* cache, unsigned addr, unsigned size) {
    if (NULL == cache) {
        return -1;
    }

    unsigned bits_of_pointer = sizeof(char*) * 8;
    unsigned tag = (addr >> (cache->set_bits + cache->offset_bits));
    unsigned tag_bits_n = bits_of_pointer - cache->set_bits - cache->offset_bits;
    unsigned set_index = (addr << tag_bits_n) >> (tag_bits_n + cache->offset_bits);
    /*unsigned tag_and_index_bits_n = bits_of_pointer - cache->offset_bits;*/
    /*unsigned offset = ((addr << tag_and_index_bits_n) >> tag_and_index_bits_n);*/

/*printf("search_queue addr:%x size:%d tag:%u set_index:%u offset:%u \n", addr, size, tag, set_index, offset);*/
    cache_set_t* set = (cache->sets + set_index);
    if (NULL == set) {
        return -1;
    }

    int hit = 0;
    for (int i = 0; i < cache->set_len; ++i) {
        // traverse try to match tag
        cache_line_t* line = set->lines + i;
        if(NULL == line) {
            return -1;
        }

        if ((0 == line->valid) && (tag == line->tag)) {
            hit = 1;
            line->timestamp = get_timestamp();

            // FIXME: what if the size exceed the block/line length
            // for the cases tested, no such issue happend
            /*if ((offset + size) < (1<<(cache->offset_bits + 1))) {*/
                /*return 0;  // hit*/
            /*}*/
            return 0;  // hit
        }
    }

    if (0 == hit) {  // miss
        int placed = 0;
        for (int i = 0; i < cache->set_len; ++i) {
            cache_line_t* line = set->lines + i;

            // actually no need to check line is NULL again
            if(NULL == line) {
                return -1;
            }

            if (1 == line->valid) {
                line->valid = 0;
                line->tag = tag;
                line->timestamp = get_timestamp();

                placed = 1;

                return 1;  // miss but fill the cache
            }
        }

        if (0 == placed) {
            cache_line_t* line = set->lines;  // first line

            // actually no need to check line is NULL again
            if(NULL == line) {
                return -1;
            }

            unsigned ts = line->timestamp;
            unsigned pos = 0;
            for (int i = 1; i < cache->set_len; ++i) {
                line = line + 1;
                if(ts > line->timestamp) {
                    ts = line->timestamp;
                    pos = i;
                }
            }

            // evict and replace
            cache_line_t* evict_line = set->lines + pos;
            evict_line->valid = 0;
            evict_line->tag = tag;
            evict_line->timestamp = get_timestamp();
            return 2;   // evict
        }
    }

    return -1;
}

void dump_cache(cache_t* cache) {
    printf("cache line set:line v\ttag\tts\n");

    for (int set_index = 0; set_index < (1<<cache->set_bits); ++set_index) {
        cache_set_t* set = (cache->sets + set_index);

        for (int i = 0; i < cache->set_len; ++i) {
            cache_line_t* line = set->lines + i;

            printf("cache line %d:%d %d\t%u\t%u\n", set_index, i, line->valid, line->tag, line->timestamp);
        }
    }

    printf("-------------------------------------------------------------------\n");
}

void usage() {
	printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
	printf("Options:\n");
	printf("  -h         Print this help message. \n");
	printf("  -v         Optional verbose flag. \n");
	printf("  -s <num>   Number of set index bits. \n");
	printf("  -E <num>   Number of lines per set. \n");
	printf("  -b <num>   Number of block offset bits. \n");
	printf("  -t <file>  Trace file. \n");
	printf("\n");
	printf("Examples: \n");
	printf("linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace \n");
	printf("linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace \n");
}

int main(int argc, char** argv)
{
	int opt;
    int set_bits = 0;
    int lines_per_set = 0;
    int block_size = 0;
    int verbose;

    char* trace_file_path = NULL;
    size_t len;

	while(-1 != (opt = getopt(argc, argv, "hvs:E:b:t:"))) {
		switch(opt) {
            case 'h':
                usage();
                break;
            case 'v':
                verbose = 1;
                break;
            case 's':
                set_bits = atoi(optarg);
                break;
            case 'E':
                lines_per_set = atoi(optarg);
                break;
            case 'b':
                block_size = atoi(optarg);
                break;
            case 't':
                len = strlen(optarg);
                trace_file_path = malloc(len + 1);
                memset(trace_file_path, 0, len + 1);
                strncpy(trace_file_path, optarg, len);
                trace_file_path[len] = '\0';
                break;
            default:
                usage();
                break;
		}
	}

    if (argc <= 1) {
        usage();
    }

    if ((set_bits > 0) && (lines_per_set > 0) && (block_size > 0) && (trace_file_path != NULL))  {
        // TODO: input arg validateion

        // TODO: check the file existence

        // construct cache
        cache_t* cache =  construct_cache(set_bits, lines_per_set, block_size);
        if (NULL == cache) {
            fprintf(stderr, "Construct cache simulator failed.\n");
        }

        // iterate the trace file
        FILE* file = NULL;
        file = fopen(trace_file_path, "r");
        char identifier;
        unsigned address;
        int size;

        // Readinglineslike " M 20,1" or " L 19,3"

        int hit_n = 0;
        int miss_n = 0;
        int evict_n = 0;

        while (fscanf(file, " %c %x,%d", &identifier, &address, &size) > 0) {

            if ('I' == identifier) continue;

            int ret = search_cache(cache, address, size);
            switch(ret) {
                case 0:
                    hit_n += 1;

                    if (1 == verbose) {
                        printf("%c %x,%d hit", identifier, address, size);
                    }

                    if('M' == identifier) {
                        hit_n += 1;

                        if (1 == verbose) {
                            printf(" hit");
                        }
                    }

                    printf("\n");
                    break;
                case 1:
                    miss_n += 1;

                    if (1 == verbose) {
                        printf("%c %x,%d miss", identifier, address, size);
                    }

                    if('M' == identifier) {
                        hit_n += 1;

                        if (1 == verbose) {
                            printf(" hit");
                        }
                    }
                    printf("\n");
                    break;
                case 2:
                    miss_n += 1;
                    evict_n += 1;

                    if (1 == verbose) {
                        printf("%c %x,%d miss evition", identifier, address, size);
                    }

                    if('M' == identifier) {
                        hit_n += 1;

                        if (1 == verbose) {
                            printf(" hit");
                        }
                    }

                    printf("\n");
                    break;
                default:
                    fprintf(stderr, "Search cache failed.\n");
                    break;

            }

            // dump_cache(cache);
        }

        fclose(file);

        //
        deconstruct_cache(cache);

        printf("summary: %d %d %d\n", hit_n, miss_n, evict_n);

        printSummary(hit_n, miss_n, evict_n);
    }

    // clean up
    if (trace_file_path != NULL) {
        free(trace_file_path);
        trace_file_path = NULL;
    }

    return 0;
}
