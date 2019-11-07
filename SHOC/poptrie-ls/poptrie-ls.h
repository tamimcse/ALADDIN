#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

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


#define MSK 0X8000000000000000ULL

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
    l->B[i].leafvec = 255;
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

  for (i = 0; i < size; i++) {
    d->c[i] = 1;
  }

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

  if (size != SIZE16) {
    for (i = 0; i < size; i++) {
      l->N[i] = 128;
    }
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

uint8_t fib_lookup(struct poptrie_node *B16, struct poptrie_node *B22, struct poptrie_node *B28, struct poptrie_node *B34, struct poptrie_node *B40,
                       struct poptrie_node *B46, struct poptrie_node *B52, struct poptrie_node *B58, struct poptrie_node *B64, struct poptrie_node *B70,
                       struct poptrie_node *B76, struct poptrie_node *B82, struct poptrie_node *B88, struct poptrie_node *B94, struct poptrie_node *B100,
                       struct poptrie_node *B106, struct poptrie_node *B112, struct poptrie_node *B118, struct poptrie_node *B124, uint8_t *N16,
                       uint8_t *leafN, uint16_t *dirC, uint8_t def_nh, uint64_t key1, uint64_t key2);
