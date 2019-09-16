#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define N16_CNT 65536
#define C16_CNT 65536
#define B22_CNT 60
#define N22_CNT 18750
#define B28_CNT 1900
#define N28_CNT 18750
#define B34_CNT 14000
#define N34_CNT 18750
#define B40_CNT 8000
#define N40_CNT 18750
#define B46_CNT 11000
#define N46_CNT 18750
#define B52_CNT 20000
#define N52_CNT 18750
#define B58_CNT 1000
#define N58_CNT 18750
#define B64_CNT 1000
#define N64_CNT 18750

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
