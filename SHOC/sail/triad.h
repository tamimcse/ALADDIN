#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#define LEVEL16_SIZE 65536
#define NUM_CHUNKS 16384
#define ARR_SIZE NUM_CHUNKS * 256

void triad(uint8_t *N16,uint8_t *N24, uint8_t *N32, uint64_t ip);
