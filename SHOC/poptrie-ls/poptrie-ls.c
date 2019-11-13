#include "poptrie-ls.h"

#define POPCNT_LFT(X, N) (__builtin_popcount(((X) >> (63 - (N))) >> 1))

/*Calculates the number of bits set to 1*/
#define POPCNT(X) (__builtin_popcountll(X))

#define SIZE16 1024
#define N16_CNT 100
#define SIZE24 240
#define N24_CNT 400
#define SIZE32 24000
#define N32_CNT 50000
#define SIZE40 28000
#define N40_CNT 300000
#define SIZE48 44000
#define N48_CNT 300000
#define SIZE56 4000
#define N56_CNT 7000
#define SIZE64 4000
#define SIZE72 100
#define SIZE80 100
#define SIZE88 100
#define SIZE96 100
#define SIZE104 100
#define SIZE112 100
#define SIZE120 100
#define SIZE128 100
#define N64_CNT 7000

#define N_CNT (N16_CNT + N24_CNT + N32_CNT + N40_CNT + N48_CNT + N56_CNT + N64_CNT)

int poptrie_ls_init (struct poptrie_ls *poptrie_ls) {
  int err = 0;

  poptrie_ls->def_nh = 1;
  leaf_init (&poptrie_ls->leafs, N_CNT);
  err = poptrie_ls_level_init (&poptrie_ls->level16, 16, SIZE16/4, NULL);
  err = poptrie_ls_level_init (&poptrie_ls->level24, 24, SIZE24, &poptrie_ls->level16);
  err = poptrie_ls_level_init (&poptrie_ls->level32, 32, SIZE32, &poptrie_ls->level24);
  err = poptrie_ls_level_init (&poptrie_ls->level40, 40, SIZE40, &poptrie_ls->level32);
  err = poptrie_ls_level_init (&poptrie_ls->level48, 48, SIZE48, &poptrie_ls->level40);
  err = poptrie_ls_level_init (&poptrie_ls->level56, 56, SIZE56, &poptrie_ls->level48);
  err = poptrie_ls_level_init (&poptrie_ls->level64, 64, SIZE64, &poptrie_ls->level56);
  err = poptrie_ls_level_init (&poptrie_ls->level72, 72, SIZE72, &poptrie_ls->level64);
  err = poptrie_ls_level_init (&poptrie_ls->level80, 80, SIZE80, &poptrie_ls->level72);
  err = poptrie_ls_level_init (&poptrie_ls->level88, 88, SIZE88, &poptrie_ls->level80);
  err = poptrie_ls_level_init (&poptrie_ls->level96, 96, SIZE96, &poptrie_ls->level88);
  err = poptrie_ls_level_init (&poptrie_ls->level104, 104, SIZE104, &poptrie_ls->level96);
  err = poptrie_ls_level_init (&poptrie_ls->level112, 112, SIZE112, &poptrie_ls->level104);
  err = poptrie_ls_level_init (&poptrie_ls->level120, 120, SIZE120, &poptrie_ls->level112);
  err = poptrie_ls_level_init (&poptrie_ls->level128, 128, SIZE128, &poptrie_ls->level120);
}


/*Currently Aladdin messes things up if there are more than one return statements. So write the function in a way that it return only once.
Currently Aladdin messes things up if return type is void.
*/
uint8_t fib_lookup(struct bitmap_poptrie_ls *C16, struct bitmap_poptrie_ls *B16, struct bitmap_poptrie_ls *C24, struct bitmap_poptrie_ls *B24,
                   struct bitmap_poptrie_ls *C32, struct bitmap_poptrie_ls *B32, struct bitmap_poptrie_ls *C40, struct bitmap_poptrie_ls *B40,
                   struct bitmap_poptrie_ls *C48, struct bitmap_poptrie_ls *B48, struct bitmap_poptrie_ls *C56, struct bitmap_poptrie_ls *B56,
                   struct bitmap_poptrie_ls *C64, struct bitmap_poptrie_ls *B64, struct bitmap_poptrie_ls *C72, struct bitmap_poptrie_ls *B72,
                   struct bitmap_poptrie_ls *C80, struct bitmap_poptrie_ls *B80, struct bitmap_poptrie_ls *C88, struct bitmap_poptrie_ls *B88,
                   struct bitmap_poptrie_ls *C96, struct bitmap_poptrie_ls *B96, struct bitmap_poptrie_ls *C104, struct bitmap_poptrie_ls *B104,
                   struct bitmap_poptrie_ls *C112, struct bitmap_poptrie_ls *B112, struct bitmap_poptrie_ls *C120, struct bitmap_poptrie_ls *B120,
                   struct bitmap_poptrie_ls *B128, uint8_t *leafN, uint8_t def_nh, uint64_t key1, uint64_t key2) {
  return 1;
}

int main(){

struct poptrie_ls poptrie_ls;
  uint8_t nh;

  poptrie_ls_init(&poptrie_ls);
  nh = fib_lookup(poptrie_ls.level16.C, poptrie_ls.level16.B, poptrie_ls.level24.C, poptrie_ls.level24.B, poptrie_ls.level32.C, poptrie_ls.level32.B,
                  poptrie_ls.level40.C, poptrie_ls.level40.B, poptrie_ls.level48.C, poptrie_ls.level48.B, poptrie_ls.level56.C, poptrie_ls.level56.B,
                  poptrie_ls.level64.C, poptrie_ls.level64.B, poptrie_ls.level72.C, poptrie_ls.level72.B, poptrie_ls.level80.C, poptrie_ls.level80.B,
                  poptrie_ls.level88.C, poptrie_ls.level88.B, poptrie_ls.level96.C, poptrie_ls.level96.B, poptrie_ls.level104.C, poptrie_ls.level104.B,
                  poptrie_ls.level112.C, poptrie_ls.level112.B, poptrie_ls.level120.C, poptrie_ls.level120.B, poptrie_ls.level128.B, poptrie_ls.leafs.N, poptrie_ls.def_nh, 67, 65);

  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "next-hop = %d\n", nh);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
