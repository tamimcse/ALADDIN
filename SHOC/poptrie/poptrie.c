#include "poptrie.h"

#define POPCNT_LFT(X, N) (__builtin_popcount(((X) >> (63 - (N))) >> 1))

/*Currently Aladdin messes things up if there are more than one return statements. So write the function in a way that it return only once.
Currently Aladdin messes things up if return type is void.
*/
uint8_t fib_lookup(uint8_t *N16, uint16_t *C16, struct bitmap_pc *B22, uint8_t *N22, struct bitmap_pc *B28, uint8_t *N28,
		   struct bitmap_pc *B34, uint8_t *N34, struct bitmap_pc *B40, uint8_t *N40, struct bitmap_pc *B46, uint8_t *N46,
		   struct bitmap_pc *B52, uint8_t *N52, struct bitmap_pc *B58, uint8_t *N58, struct bitmap_pc *B64, uint8_t *N64,   
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
	  if (!vector & (1ULL << v)) {
	    n_idx = node->base0 + __builtin_popcount(node->leafvec & ((2ULL << v) - 1));
	    return N22[n_idx];
	  } else {
	    idx = node->base1 + __builtin_popcount(node->vec & ((2ULL << v) - 1));
	    node = &B28[idx];
       	    vector = node->vec;
            v = ((key >> 36) & 63);
	    if (!vector & (1ULL << v)) {
	      n_idx = node->base0 + __builtin_popcount(node->leafvec & ((2ULL << v) - 1));
	      return N28[n_idx];
	    } else {
	      idx = node->base1 + __builtin_popcount(node->vec & ((2ULL << v) - 1));
	      node = &B34[idx];
	    }
	  } 
	}
        

	return nh;
}

void reset_ppc (struct bitmap_pc *ppc) {
	ppc->vec = 0XFFFFFFFFFFFFFFFF;
	ppc->leafvec = 0XFFFFFFFFFFFFFFFF;
	ppc->base0 = 5;
	ppc->base1 = 5;
}

int main(){
	uint8_t nh;
	uint8_t *N16, *N22, *N28, *N34, *N40, *N46, *N52, *N58, *N64;
	uint16_t *C16;
	struct bitmap_pc *B22, *B28, *B34, *B40, *B46, *B52, *B58, *B64;
        

    N16 = (uint8_t *) malloc (sizeof(uint8_t) * N16_SIZE);
    C16 = (uint16_t *) malloc (sizeof(uint16_t) * N16_SIZE);

    B22 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B32_SIZE);
    N22 = (uint8_t *) malloc (sizeof(uint8_t) * N32_SIZE);
    B28 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B32_SIZE);
    N28 = (uint8_t *) malloc (sizeof(uint8_t) * N32_SIZE);
    B34 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B32_SIZE);
    N34 = (uint8_t *) malloc (sizeof(uint8_t) * N32_SIZE);
    B40 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B32_SIZE);
    N40 = (uint8_t *) malloc (sizeof(uint8_t) * N32_SIZE);
    B46 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B32_SIZE);
    N46 = (uint8_t *) malloc (sizeof(uint8_t) * N32_SIZE);
    B52 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B32_SIZE);
    N52 = (uint8_t *) malloc (sizeof(uint8_t) * N32_SIZE);
    B58 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B32_SIZE);
    N58 = (uint8_t *) malloc (sizeof(uint8_t) * N32_SIZE);
    B64 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B32_SIZE);
    N64 = (uint8_t *) malloc (sizeof(uint8_t) * N32_SIZE);



	int i;
  srand(time(NULL));

	for(i=0; i<N16_SIZE; i++){
		N16[i] = 0;
		C16[i] = 1;
	}

	for(i=0; i<B32_SIZE; i++)
		reset_ppc(&B22[i]);

	for(i=0; i<N32_SIZE; i++)
		N22[i] = 1;

	for(i=0; i<B32_SIZE; i++)
		reset_ppc(&B28[i]);

	for(i=0; i<N32_SIZE; i++)
		N28[i] = 1;

	for(i=0; i<B32_SIZE; i++)
		reset_ppc(&B34[i]);

	for(i=0; i<N32_SIZE; i++)
		N34[i] = 1;

	for(i=0; i<B32_SIZE; i++)
		reset_ppc(&B40[i]);

	for(i=0; i<N32_SIZE; i++)
		N40[i] = 1;

	for(i=0; i<B32_SIZE; i++)
		reset_ppc(&B46[i]);

	for(i=0; i<N32_SIZE; i++)
		N46[i] = 1;

	for(i=0; i<B32_SIZE; i++)
		reset_ppc(&B52[i]);

	for(i=0; i<N32_SIZE; i++)
		N52[i] = 1;

	for(i=0; i<B32_SIZE; i++)
		reset_ppc(&B58[i]);

	for(i=0; i<N32_SIZE; i++)
		N58[i] = 1;

	for(i=0; i<B32_SIZE; i++)
		reset_ppc(&B64[i]);

	for(i=0; i<N32_SIZE; i++)
		N64[i] = 1;

	nh = fib_lookup(N16, C16, B22, N22, B28, N28, B34, N34, B40, N40, B46, N46, B52, N52, B58, N58, B64, N64, 67);

  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "next-hop = %d\n", nh);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
