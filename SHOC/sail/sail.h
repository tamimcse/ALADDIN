#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#define LEVEL16_SIZE 65536
#define NUM_CHUNKS 16384
#define ARR_SIZE NUM_CHUNKS * 256

struct sail_level {
  uint8_t *N, *P;
  uint32_t *C;
  uint8_t level_num;
  uint32_t count;
  uint32_t size;
  uint32_t cnk_size;
  struct sail_level *parent, *chield;
};

int sail_level_init (struct sail_level *c, uint8_t level_num, uint32_t size, uint32_t cnk_size, struct sail_level *parent) {
  long long i;
 
  c->N = (uint8_t *) calloc (size, sizeof (uint8_t));
  c->P = (uint8_t *) calloc (size, sizeof (uint8_t));
  c->C = (uint32_t *) calloc (size, sizeof (uint32_t));
  if (!c->N || !c->P || !c->C)
    return -1;
  c->level_num = level_num;
  c->size = size;
  c->cnk_size = cnk_size;
  c->parent = parent;
  if (parent != NULL)
    parent->chield = c;

  for(i=0; i < size; i++){
    c->N[i] = level_num;
    c->C[i] = 1;
  }
  return 0;
}


struct sail {
  uint8_t def_nh;
  struct sail_level level16, level24, level32, level40, level48, level56, level64, level72, level80, level88, level96, level104, level112, level120, level128; 
};

/*
uint8_t sail_lookup(uint8_t *N16, uint32_t *C16, uint8_t *N24, uint32_t *C24, uint8_t *N32, uint32_t *C32, uint8_t *N40, uint32_t *C40,
                    uint8_t *N48, uint32_t *C48, uint8_t *N56, uint32_t *C56, uint8_t *N64, uint32_t *C64, uint8_t *N72, uint32_t *C72,
                    uint8_t *N80, uint32_t *C80, uint8_t *N88, uint32_t *C88, uint8_t *N96, uint32_t *C96, uint8_t *N104, uint32_t *C104,
                    uint8_t *N112, uint32_t *C112, uint8_t *N120, uint32_t *C120, uint8_t *N128, uint8_t def_nh,
                    __uint128_t key);*/


uint8_t fib_lookup(uint8_t *N16, uint32_t *C16, uint8_t *N24, uint32_t *C24, uint8_t *N32, uint32_t *C32, uint8_t *N40, uint32_t *C40, uint8_t *N48, uint32_t *C48,
		uint8_t *N56, uint32_t *C56, uint8_t *N64, uint64_t ip);
