#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#define LEVEL16_SIZE 65536
#define NUM_CHUNKS 16384
#define ARR_SIZE NUM_CHUNKS * 256

void triad(uint8_t *N16, uint16_t *C16, uint8_t *N24, uint16_t *C24, uint8_t *N32, uint16_t *C32, uint8_t *N40, uint16_t *C40, uint8_t *N48, uint16_t *C48,
		uint8_t *N56, uint16_t *C56, uint8_t *N64, uint64_t ip, uint8_t *nh);
