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

struct bitmap_poptrie_ls {
    uint64_t bitmap;
    uint32_t popcnt;
};

struct poptrie_ls_level {
  struct bitmap_poptrie_ls *B, *C;
  uint8_t level_num;
  uint32_t count;
  uint32_t size;
  struct poptrie_ls_level *parent, *chield;
};

int poptrie_ls_level_init (struct poptrie_ls_level *l, uint8_t level_num, uint32_t size, struct poptrie_ls_level *parent) {
  long long i;

  l->B = (struct bitmap_poptrie_ls *) calloc (size, sizeof (struct bitmap_poptrie_ls));
  l->C = (struct bitmap_poptrie_ls *) calloc (size, sizeof (struct bitmap_poptrie_ls));
  if (!l->B || !l->C)
    return -1;
  l->level_num = level_num;
  l->size = size;
  l->parent = parent;
  if (parent != NULL)
    parent->chield = l;
  for (i = 0; i < size; i++) {
    l->B[i].bitmap = 255;
    l->C[i].bitmap = 255;
  }
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

struct poptrie_ls {
  uint8_t def_nh;
  struct poptrie_ls_level level16, level24, level32, level40, level48, level56, level64, level72, level80, level88, level96, level104, level112, level120, level128;
  struct leaf leafs;
};

uint8_t fib_lookup(struct bitmap_poptrie_ls *C16, struct bitmap_poptrie_ls *B16, struct bitmap_poptrie_ls *C24, struct bitmap_poptrie_ls *B24,
                   struct bitmap_poptrie_ls *C32, struct bitmap_poptrie_ls *B32, struct bitmap_poptrie_ls *C40, struct bitmap_poptrie_ls *B40,
                   struct bitmap_poptrie_ls *C48, struct bitmap_poptrie_ls *B48, struct bitmap_poptrie_ls *C56, struct bitmap_poptrie_ls *B56,
                   struct bitmap_poptrie_ls *C64, struct bitmap_poptrie_ls *B64, struct bitmap_poptrie_ls *C72, struct bitmap_poptrie_ls *B72,
                   struct bitmap_poptrie_ls *C80, struct bitmap_poptrie_ls *B80, struct bitmap_poptrie_ls *C88, struct bitmap_poptrie_ls *B88,
                   struct bitmap_poptrie_ls *C96, struct bitmap_poptrie_ls *B96, struct bitmap_poptrie_ls *C104, struct bitmap_poptrie_ls *B104,
                   struct bitmap_poptrie_ls *C112, struct bitmap_poptrie_ls *B112, struct bitmap_poptrie_ls *C120, struct bitmap_poptrie_ls *B120,
                   struct bitmap_poptrie_ls *B128, uint8_t *leafN, uint8_t def_nh, uint64_t key1, uint64_t key2);
