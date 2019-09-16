#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define B16S 10240
#define N16S 100
#define C16S 10240

#define B24S 600
#define N24S 400
#define C24S 600

#define B32S 60000
#define N32S 50000
#define C32S 60000


#define B40S 70000
#define N40S 300000
#define C40S 70000

#define B48S 110000
#define N48S 300000
#define C48S 110000

#define B56S 10000
#define N56S 7000
#define C56S 10000

#define B56S 10000
#define N56S 7000

#define B64S 10000
#define N64S 7000

#define MSK 0X8000000000000000ULL

#define DEF_NH 1

struct bitmap_pc {
    uint64_t bitmap;
    uint16_t popcnt;
};

uint8_t fib_lookup(struct bitmap_pc *B16, uint8_t *N16, struct bitmap_pc *C16, struct bitmap_pc *B24, uint8_t *N24, struct bitmap_pc *C24,
		   struct bitmap_pc *B32, uint8_t *N32, struct bitmap_pc *C32, struct bitmap_pc *B40, uint8_t *N40, struct bitmap_pc *C40,
		   struct bitmap_pc *B48, uint8_t *N48, struct bitmap_pc *C48, struct bitmap_pc *B56, uint8_t *N56, struct bitmap_pc *C56,
		   struct bitmap_pc *B64, uint8_t *N64, uint64_t key);
