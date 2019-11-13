#include "poptrie-ls.h"

#define POPCNT_LFT(X, N) (__builtin_popcount(((X) >> (63 - (N))) >> 1))

/*Calculates the number of bits set to 1*/
#define POPCNT(X) (__builtin_popcountll(X))

//Size of each level
#define SIZE16 1024
#define SIZE24 240
#define SIZE32 24000
#define SIZE40 28000
#define SIZE48 44000
#define SIZE56 4000
#define SIZE64 4000
#define SIZE72 100
#define SIZE80 100
#define SIZE88 100
#define SIZE96 100
#define SIZE104 100
#define SIZE112 100
#define SIZE120 100
#define SIZE128 100

#define N_CNT 664500


int poptrie_ls_init (struct poptrie_ls *poptrie_ls) {
  int err = 0;

  poptrie_ls->def_nh = 2;
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
  uint32_t n_idx;
  uint32_t off;
  uint32_t idx, idx_sail;
  uint32_t ck_idx;
  uint8_t nh = def_nh;
  int level;

  idx_sail = key1 >> 48;
  idx = idx_sail >> 6;
  off = idx_sail & 63;
  level = 16;
  if (C16[idx].bitmap & (MSK >> off)) {    
    ck_idx = C16[idx].popcnt + POPCNT((C16[idx].bitmap >> (63 - off)) >> 1);
    idx_sail = (ck_idx << 8) + ((key1 >> 40) & 0XFF);
    idx = idx_sail >> 6;
    off = idx_sail & 63;
    level = 24;
    if (C24[idx].bitmap & (MSK >> off)) {
      ck_idx = C24[idx].popcnt + POPCNT((C24[idx].bitmap >> (63 - off)) >> 1);
      idx_sail = (ck_idx << 8) + ((key1 >> 32) & 0XFF);
      idx = idx_sail >> 6;
      off = idx_sail & 63;
      level = 32;
      if (C32[idx].bitmap & (MSK >> off)) {
        ck_idx = C32[idx].popcnt + POPCNT((C32[idx].bitmap >> (63 - off)) >> 1);
        idx_sail = (ck_idx << 8) + ((key1 >> 24) & 0XFF);
        idx = idx_sail >> 6;
        off = idx_sail & 63;
        level = 40;
        if (C40[idx].bitmap & (MSK >> off)) {          
          ck_idx = C40[idx].popcnt + POPCNT((C40[idx].bitmap >> (63 - off)) >> 1);
          idx_sail = (ck_idx << 8) + ((key1 >> 16) & 0XFF);
          idx = idx_sail >> 6;
          off = idx_sail & 63;
          level = 48;
          if (C48[idx].bitmap & (MSK >> off)) {
            ck_idx = C48[idx].popcnt + POPCNT((C48[idx].bitmap >> (63 - off)) >> 1);
            idx_sail = (ck_idx << 8) + ((key1 >> 8) & 0XFF);
            idx = idx_sail >> 6;
            off = idx_sail & 63;
            level = 56;
            if (C56[idx].bitmap & (MSK >> off)) {
              ck_idx = C56[idx].popcnt + POPCNT((C56[idx].bitmap >> (63 - off)) >> 1);
              idx_sail = (ck_idx << 8) + (key1 & 0XFF);
              idx = idx_sail >> 6;
              off = idx_sail & 63;
              level = 64;
              if (C64[idx].bitmap & (MSK >> off)) {
                ck_idx = C64[idx].popcnt + POPCNT((C64[idx].bitmap >> (63 - off)) >> 1);
                idx_sail = (ck_idx << 8) + ((key2 >> 56) & 0XFF);
                idx = idx_sail >> 6;
                off = idx_sail & 63;
                level = 72;
                if (C72[idx].bitmap & (MSK >> off)) {
                  ck_idx = C72[idx].popcnt + POPCNT((C72[idx].bitmap >> (63 - off)) >> 1);
                  idx_sail = (ck_idx << 8) + ((key2 >> 48) & 0XFF);
                  idx = idx_sail >> 6;
                  off = idx_sail & 63;
                  level = 80;
                  if (C80[idx].bitmap & (MSK >> off)) {
                    ck_idx = C80[idx].popcnt + POPCNT((C80[idx].bitmap >> (63 - off)) >> 1);
                    idx_sail = (ck_idx << 8) + ((key2 >> 40) & 0XFF);
                    idx = idx_sail >> 6;
                    off = idx_sail & 63;
                    level = 88;
                    if (C88[idx].bitmap & (MSK >> off)) {
                      ck_idx = C88[idx].popcnt + POPCNT((C88[idx].bitmap >> (63 - off)) >> 1);
                      idx_sail = (ck_idx << 8) + ((key2 >> 32) & 0XFF);
                      idx = idx_sail >> 6;
                      off = idx_sail & 63;
                      level = 96;
                      if (C96[idx].bitmap & (MSK >> off)) {
                        ck_idx = C96[idx].popcnt + POPCNT((C96[idx].bitmap >> (63 - off)) >> 1);
                        idx_sail = (ck_idx << 8) + ((key2 >> 24) & 0XFF);
                        idx = idx_sail >> 6;
                        off = idx_sail & 63;
                        level = 104;
                        if (C104[idx].bitmap & (MSK >> off)) {
                          ck_idx = C104[idx].popcnt + POPCNT((C104[idx].bitmap >> (63 - off)) >> 1);
                          idx_sail = (ck_idx << 8) + ((key2 >> 16) & 0XFF);
                          idx = idx_sail >> 6;
                          off = idx_sail & 63;
                          level = 112;
                          if (C112[idx].bitmap & (MSK >> off)) {
                            ck_idx = C112[idx].popcnt + POPCNT((C112[idx].bitmap >> (63 - off)) >> 1);
                            idx_sail = (ck_idx << 8) + ((key2 >> 8) & 0XFF);
                            idx = idx_sail >> 6;
                            off = idx_sail & 63;
                            level = 120;
                            if (C120[idx].bitmap & (MSK >> off)) {
                              ck_idx = C120[idx].popcnt + POPCNT((C120[idx].bitmap >> (63 - off)) >> 1);
                              idx_sail = (ck_idx << 8) + (key2 & 0XFF);
                              idx = idx_sail >> 6;
                              off = idx_sail & 63;
                              level = 128;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        } 
      }
    }
  }

  if (level == 16 && B16[idx].bitmap & (MSK >> off)) {
    n_idx = B16[idx].popcnt + POPCNT((B16[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 24 && B24[idx].bitmap & (MSK >> off)) {
    n_idx = B24[idx].popcnt + POPCNT((B24[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 32 && B32[idx].bitmap & (MSK >> off)) {
    n_idx = B32[idx].popcnt + POPCNT((B32[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 40 && B40[idx].bitmap & (MSK >> off)) {
    n_idx = B40[idx].popcnt + POPCNT((B40[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 48 && B48[idx].bitmap & (MSK >> off)) {
    n_idx = B48[idx].popcnt + POPCNT((B48[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 56 && B56[idx].bitmap & (MSK >> off)) {
    n_idx = B56[idx].popcnt + POPCNT((B56[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 64 && B64[idx].bitmap & (MSK >> off)) {
    n_idx = B64[idx].popcnt + POPCNT((B64[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 72 && B72[idx].bitmap & (MSK >> off)) {
    n_idx = B72[idx].popcnt + POPCNT((B72[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 80 && B80[idx].bitmap & (MSK >> off)) {
    n_idx = B80[idx].popcnt + POPCNT((B80[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 88 && B88[idx].bitmap & (MSK >> off)) {
    n_idx = B88[idx].popcnt + POPCNT((B88[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 96 && B96[idx].bitmap & (MSK >> off)) {
    n_idx = B96[idx].popcnt + POPCNT((B96[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 104 && B104[idx].bitmap & (MSK >> off)) {
    n_idx = B104[idx].popcnt + POPCNT((B104[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 112 && B112[idx].bitmap & (MSK >> off)) {
    n_idx = B112[idx].popcnt + POPCNT((B112[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 120 && B120[idx].bitmap & (MSK >> off)) {
    n_idx = B120[idx].popcnt + POPCNT((B120[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  } else if (level == 128 && B128[idx].bitmap & (MSK >> off)) {
    n_idx = B128[idx].popcnt + POPCNT((B128[idx].bitmap >> (63 - off)) >> 1);
    nh = leafN[n_idx];
  }

  return nh;
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
