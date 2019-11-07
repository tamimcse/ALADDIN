#include "poptrie-ls.h"

#define POPCNT_LFT(X, N) (__builtin_popcount(((X) >> (63 - (N))) >> 1))

/*Calculates the number of bits set to 1*/
#define POPCNT(X) (__builtin_popcountll(X))


int poptrie_init (struct poptrie *pt) {
  int err = 0;

  pt->def_nh = 10;
  err = leaf_init (&pt->leafs16, SIZE16);
  err = dir_init (&pt->dir16, SIZE16);
  err = leaf_init (&pt->leafs, N_SIZE);
  err = poptrie_level_init (&pt->L16, 16, SIZE16/64, NULL);
  err = poptrie_level_init (&pt->L22, 22, SIZE22, &pt->L16);
  err = poptrie_level_init (&pt->L28, 28, SIZE28, &pt->L22);
  err = poptrie_level_init (&pt->L34, 34, SIZE34, &pt->L28);
  err = poptrie_level_init (&pt->L40, 40, SIZE40, &pt->L34);
  err = poptrie_level_init (&pt->L46, 46, SIZE46, &pt->L40);
  err = poptrie_level_init (&pt->L52, 52, SIZE52, &pt->L46);
  err = poptrie_level_init (&pt->L58, 58, SIZE58, &pt->L52);
  err = poptrie_level_init (&pt->L64, 64, SIZE64, &pt->L58);
  err = poptrie_level_init (&pt->L70, 70, SIZE70, &pt->L64);
  err = poptrie_level_init (&pt->L76, 76, SIZE76, &pt->L70);
  err = poptrie_level_init (&pt->L82, 82, SIZE82, &pt->L76);
  err = poptrie_level_init (&pt->L88, 88, SIZE88, &pt->L82);
  err = poptrie_level_init (&pt->L94, 94, SIZE94, &pt->L88);
  err = poptrie_level_init (&pt->L100, 100, SIZE100, &pt->L94);
  err = poptrie_level_init (&pt->L106, 106, SIZE106, &pt->L100);
  err = poptrie_level_init (&pt->L112, 112, SIZE112, &pt->L106);
  err = poptrie_level_init (&pt->L118, 118, SIZE118, &pt->L112);
  err = poptrie_level_init (&pt->L124, 124, SIZE124, &pt->L118);

  if (err)
    return -1;   
  else
    return 1;
}

/*Currently Aladdin messes things up if there are more than one return statements. So write the function in a way that it return only once.
Currently Aladdin messes things up if return type is void.
*/
uint8_t fib_lookup(struct poptrie_node *B16, struct poptrie_node *B22, struct poptrie_node *B28, struct poptrie_node *B34, struct poptrie_node *B40,
                       struct poptrie_node *B46, struct poptrie_node *B52, struct poptrie_node *B58, struct poptrie_node *B64, struct poptrie_node *B70,
                       struct poptrie_node *B76, struct poptrie_node *B82, struct poptrie_node *B88, struct poptrie_node *B94, struct poptrie_node *B100,
                       struct poptrie_node *B106, struct poptrie_node *B112, struct poptrie_node *B118, struct poptrie_node *B124, uint8_t *N16,
                       uint8_t *leafN, uint16_t *dirC, uint8_t def_nh, uint64_t key1, uint64_t key2) {
  uint32_t n_idx;
  uint32_t off;
  uint32_t idx, idx_sail;
  uint32_t ck_idx;
  struct poptrie_node *node;
  uint8_t nh = def_nh;

  idx = key1 >> 48;
  if (N16[idx]) {
    return N16[idx];
  }

  idx = dirC[idx];
  if (!idx)
    return nh;
  node = &B16[idx - 1];
  off = (key1 >> 42) & 63;
  if (node->vec & (1ULL << off)) {
    idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
    node = &B22[idx];
    off = (key1 >> 36) & 63;
    if (node->vec & (1ULL << off)) {
      idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
      node = &B28[idx];
      off = ((key1 >> 30) & 63);
      if (node->vec & (1ULL << off)) {
        idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
        node = &B34[idx];
        off = ((key1 >> 24) & 63);
        if (node->vec & (1ULL << off)) {
          idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
          node = &B40[idx];
          off = ((key1 >> 18) & 63);
          if (node->vec & (1ULL << off)) {
            idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
            node = &B46[idx];
            off = ((key1 >> 12) & 63);
            if (node->vec & (1ULL << off)) {
              idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
              node = &B52[idx];
              off = ((key1 >> 6) & 63);
              if (node->vec & (1ULL << off)) {
                idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                node = &B58[idx];
                off = (key1 & 63);
                if (node->vec & (1ULL << off)) {
                  idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                  node = &B64[idx];
                  off = ((key2 >> 58) & 63);
                  if (node->vec & (1ULL << off)) {
                    idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                    node = &B70[idx];
                    off = ((key2 >> 52) & 63);
                    if (node->vec & (1ULL << off)) {
                      idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                      node = &B76[idx];
                      off = ((key2 >> 46) & 63);
                      if (node->vec & (1ULL << off)) {
                        idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                        node = &B82[idx];
                        off = ((key2 >> 40) & 63);
                        if (node->vec & (1ULL << off)) {
                          idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                          node = &B88[idx];
                          off = ((key2 >> 34) & 63);
                          if (node->vec & (1ULL << off)) {
                            idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                            node = &B94[idx];
                            off = ((key2 >> 28) & 63);
                            if (node->vec & (1ULL << off)) {
                              idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                              node = &B100[idx];
                              off = ((key2 >> 22) & 63);
                              if (node->vec & (1ULL << off)) {
                                idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                                node = &B106[idx];
                                off = ((key2 >> 16) & 63);
                                if (node->vec & (1ULL << off)) {
                                  idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                                  node = &B112[idx];
                                  off = ((key2 >> 10) & 63);
                                  if (node->vec & (1ULL << off)) {
                                    idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                                    node = &B118[idx];
                                    off = ((key2 >> 4) & 63);
                                    if (node->vec & (1ULL << off)) {
                                      idx = node->base0 + POPCNT(node->vec & ((2ULL << off) - 1)) - 1;
                                      node = &B124[idx];
                                      off = (key2 & 15) << 2;
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
        }
      }
    }
  }
  if (node->leafvec & (1ULL << off)) {
    n_idx = node->base1 + POPCNT(node->leafvec & ((2ULL << off) - 1)) - 1;
    nh = leafN[n_idx];
  }

  return nh;
}

int main(){

  struct poptrie poptrie;
  uint8_t nh;

  poptrie_init(&poptrie);
  nh = fib_lookup(poptrie.L16.B, poptrie.L22.B, poptrie.L28.B, poptrie.L34.B, poptrie.L40.B, poptrie.L46.B, poptrie.L52.B,
                       poptrie.L58.B, poptrie.L64.B, poptrie.L70.B, poptrie.L76.B, poptrie.L82.B, poptrie.L88.B, poptrie.L94.B,
                       poptrie.L100.B, poptrie.L106.B, poptrie.L112.B, poptrie.L118.B, poptrie.L124.B, poptrie.leafs16.N,
                       poptrie.leafs.N, poptrie.dir16.c, poptrie.def_nh, 67, 65);

  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "next-hop = %d\n", nh);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
