#include "poptrie.h"

#define POPCNT_LFT(X, N) (__builtin_popcount(((X) >> (63 - (N))) >> 1))

/*Currently Aladdin messes things up if there are more than one return statements. So write the function in a way that it return only once.
Currently Aladdin messes things up if return type is void.
*/
uint8_t fib_lookup(uint8_t *N16, uint16_t *C16, struct bitmap_pc *B22, struct bitmap_pc *B28,
		   struct bitmap_pc *B34, struct bitmap_pc *B40, struct bitmap_pc *B46,
		   struct bitmap_pc *B52, struct bitmap_pc *B58, struct bitmap_pc *B64, uint8_t *N,   
		   uint64_t key) {
	uint32_t n_idx;
	uint32_t v;
	uint32_t idx;
	uint32_t ck_idx;
	uint8_t nh = DEF_NH;
	uint64_t vector;
	struct bitmap_pc *node;

	idx = key >> 48;

	if (N16[idx])
	  return N16[idx];

	if (C16[idx]) {
	  node = &B22[C16[idx]];
	  vector = node->vec;
          v = ((key >> 42) & 63);
	  if (vector & (1ULL << v)) {
	    idx = node->base1 + __builtin_popcount(node->vec & ((2ULL << v) - 1));
	    node = &B28[idx];
       	    vector = node->vec;
            v = ((key >> 36) & 63);
	    if (vector & (1ULL << v)) {
	      idx = node->base1 + __builtin_popcount(node->vec & ((2ULL << v) - 1));
	      node = &B34[idx];
	    }
	  } 
	}
	if (!vector & (1ULL << v)) {
    	  n_idx = node->base0 + __builtin_popcount(node->leafvec & ((2ULL << v) - 1));
          return N[n_idx];
        }
	return nh;
}

void reset_node (struct bitmap_pc *ppc) {
	ppc->vec = 0XFFFFFFFFFFFFFFFF;
	ppc->leafvec = 0XFFFFFFFFFFFFFFFF;
	ppc->base0 = 5;
	ppc->base1 = 5;
}

int main(){
	uint8_t nh;
	uint8_t *N16, *N;
	uint16_t *C16;
	struct bitmap_pc *B22, *B28, *B34, *B40, *B46, *B52, *B58, *B64;
        

    N16 = (uint8_t *) malloc (sizeof(uint8_t) * N16_CNT);
    C16 = (uint16_t *) malloc (sizeof(uint16_t) * C16_CNT);

    B22 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B22_CNT);
    B28 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B28_CNT);
    B34 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B34_CNT);
    B40 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B40_CNT);
    B46 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B46_CNT);
    B52 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B52_CNT);
    B58 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B58_CNT);
    B64 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B64_CNT);
    N = (uint8_t *) malloc (sizeof(uint8_t) * N_CNT);

	int i;
  srand(time(NULL));

	for(i=0; i<N16_CNT; i++) N16[i] = 0;
	for(i=0; i<C16_CNT; i++) C16[i] = 1;


	for(i=0; i<B22_CNT; i++) reset_node(&B22[i]);
	for(i=0; i<B28_CNT; i++) reset_node(&B28[i]);
	for(i=0; i<B34_CNT; i++) reset_node(&B34[i]);
	for(i=0; i<B40_CNT; i++) reset_node(&B40[i]);
	for(i=0; i<B46_CNT; i++) reset_node(&B46[i]);
	for(i=0; i<B52_CNT; i++) reset_node(&B52[i]);
	for(i=0; i<B58_CNT; i++) reset_node(&B58[i]);
	for(i=0; i<B64_CNT; i++) reset_node(&B64[i]);

	for(i=0; i<N_CNT; i++) N[i] = 1;

	nh = fib_lookup(N16, C16, B22, B28, B34, B40, B46, B52, B58, B64, N, 67);

  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "next-hop = %d\n", nh);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
