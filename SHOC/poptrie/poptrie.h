#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define B16_SIZE 1024
#define N16_SIZE 100

/*Number of chunks in level 32*/
#define NUM32 64

/*Number of chunks in level 40 and 48*/
#define NUM40 16384

/*Number of chunks in level 64*/
#define NUM64 400

/*As we group each 64 elements, each chunk in level 32 and level 64 
 * contains 1024 (65536/64) elements. On the other hand, chunks in level 40 and 
 * level 48 contain 4 (256/64) chunks */
#define ELEMS_PER_CHUNK 1024
#define ELEMS_PER_CHUNK_40 4

/*The size of B32 and C32. Here each chunk consists of 64 groups*/
#define B32_SIZE NUM32 * ELEMS_PER_CHUNK

/*The size of N32/P32/N64/P64*/
#define N32_SIZE 65536

/*The size of N64/P64*/
#define N64_SIZE 655360

/*The size of C40 and C48. Here each chunk consists of 4 groups*/
#define B40_B48_SIZE NUM40 * ELEMS_PER_CHUNK_40

/*The size of N40/P40/N48/P48. We assume each chunk on average will have 16 elements*/
#define N40_N48_SIZE NUM40 * 16

#define B64_SIZE NUM64 * 64

#define MSK 0X8000000000000000ULL

#define DEF_NH 1

struct bitmap_pc {
    uint64_t vec;
    uint64_t leafvec;
    uint16_t base0;
    uint16_t base1;
};

uint8_t fib_lookup(uint8_t *N16, uint16_t *C16, struct bitmap_pc *B22, uint8_t *N22, struct bitmap_pc *B28, uint8_t *N28,
		   struct bitmap_pc *B34, uint8_t *N34, struct bitmap_pc *B40, uint8_t *N40, struct bitmap_pc *B46, uint8_t *N46,
		   struct bitmap_pc *B52, uint8_t *N52, struct bitmap_pc *B58, uint8_t *N58, struct bitmap_pc *B64, uint8_t *N64,   
		   uint64_t key);
