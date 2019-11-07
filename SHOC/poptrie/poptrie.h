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
#define N_CNT 150000

/////////////////////////
#define SIZE16 65536
#define SIZE22 3000
#define SIZE28 15000
#define SIZE34 14000
#define SIZE40 15000
#define SIZE46 20000
#define SIZE52 20000
#define SIZE58 1000
#define SIZE64 1000
#define SIZE70 1000
#define SIZE76 1000
#define SIZE82 1000
#define SIZE88 1000
#define SIZE94 1000
#define SIZE100 1000
#define SIZE106 1000
#define SIZE112 1000
#define SIZE118 1000
#define SIZE124 1000
#define N_SIZE 1500000

/////////////////////////

#define MSK 0X8000000000000000ULL

#define DEF_NH 1

struct poptrie_node {
    uint64_t vec;
    uint64_t leafvec;
    uint32_t base0;
    uint32_t base1;
};

struct poptrie_level {
  struct poptrie_node *B;
  uint8_t level_num;
  uint32_t count;
  uint32_t size;
  struct poptrie_level *parent, *chield;
};

int poptrie_level_init (struct poptrie_level *l, uint8_t level_num, uint32_t size, struct poptrie_level *parent) {
  long long i;

  l->B = (struct poptrie_node *) calloc (size, sizeof (struct poptrie_node));
  if (!l->B)
    return -1;
  l->level_num = level_num;
  l->size = size;
  l->parent = parent;
  if (parent != NULL)
    parent->chield = l;
  for (i = 0; i < size; i++) {
    l->B[i].vec = 255;
    l->B[i].vec = 255;
  }
  return 0;
}

struct dir {
  uint16_t *c;
  uint64_t size;
  uint64_t count;
};

int dir_init (struct dir *d, uint32_t size) {
  long long i;

  d->c = (uint16_t *) calloc (size, sizeof(uint16_t));
  d->size = size;
  d->count = 0;

  if (!d->c)
    return -1;
  else
    return 0;
}


struct leaf {
  uint8_t *N;
  uint8_t *P;
  uint64_t size;
  uint64_t count;
};

int leaf_init (struct leaf *l, uint32_t size) {
  long long i;

  l->N = (uint8_t *) calloc (size, sizeof(uint8_t));
  l->P = (uint8_t *) calloc (size, sizeof(uint8_t));
  l->size = size;
  l->count = 0;

  for (i = 0; i < size; i++) {
    l->N[i] = 128;
  }

  if (!l->N || !l->P)
    return -1;
  else
    return 0;
}

struct poptrie {
  uint8_t def_nh;
  struct leaf leafs16;
  //direct pointer
  struct dir dir16;
  //Rest of the leafs
  struct leaf leafs;
  //Non-leaf nodes
  struct poptrie_level L16, L22, L28, L34, L40, L46, L52, L58, L64, L70, L76, L82, L88, L94, L100, L106, L112, L118, L124;
};

struct bitmap_pc {
    uint64_t vec;
    uint64_t leafvec;
    uint16_t base0;
    uint16_t base1;
};



uint8_t fib_lookup(uint8_t *N16, uint16_t *C16, struct bitmap_pc *B22, struct bitmap_pc *B28,
		   struct bitmap_pc *B34, struct bitmap_pc *B40, struct bitmap_pc *B46,
		   struct bitmap_pc *B52, struct bitmap_pc *B58, struct bitmap_pc *B64, uint8_t *N,   
		   uint64_t key);
