#include "poptrie-iu.h"

#define POPCNT_LFT(X, N) (__builtin_popcount(((X) >> (63 - (N))) >> 1))

/*Currently Aladdin messes things up if there are more than one return statements. So write the function in a way that it return only once.
Currently Aladdin messes things up if return type is void.
*/
uint8_t fib_lookup(uint8_t *N16, uint16_t *C16, struct bitmap_pc *B22, uint8_t *N22, struct bitmap_pc *B28,
		   uint8_t *N28, struct bitmap_pc *B34, uint8_t *N34, struct bitmap_pc *B40, uint8_t *N40,
		   struct bitmap_pc *B46, uint8_t *N46, struct bitmap_pc *B52, uint8_t *N52,
		   struct bitmap_pc *B58, uint8_t *N58, struct bitmap_pc *B64, uint8_t *N64,   
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
	  vector = node->leafvec;
          v = ((key >> 42) & 63);
  	  if (vector & (1ULL << v)) {
    	    n_idx = node->base0 + __builtin_popcount(vector & ((2ULL << v) - 1));
            nh = N22[n_idx];
          }
	  vector = node->vec;
	  if (vector & (1ULL << v)) {
	    idx = node->base1 + __builtin_popcount(node->vec & ((2ULL << v) - 1));
	    node = &B28[idx];
       	    vector = node->leafvec;
            v = ((key >> 36) & 63);

  	    if (vector & (1ULL << v)) {
    	      n_idx = node->base0 + __builtin_popcount(vector & ((2ULL << v) - 1));
              nh = N28[n_idx];
            }
	    vector = node->vec;
	    if (vector & (1ULL << v)) {
	      idx = node->base1 + __builtin_popcount(node->vec & ((2ULL << v) - 1));
	      node = &B34[idx];
	      vector = node->leafvec;
              v = ((key >> 30) & 63);
  	      if (vector & (1ULL << v)) {
    	        n_idx = node->base0 + __builtin_popcount(vector & ((2ULL << v) - 1));
                nh = N34[n_idx];
              }
       	      vector = node->vec;
	      if (vector & (1ULL << v)) {
	        idx = node->base1 + __builtin_popcount(node->vec & ((2ULL << v) - 1));
	        node = &B40[idx];
       	        vector = node->leafvec;
                v = ((key >> 24) & 63);
  	        if (vector & (1ULL << v)) {
    	          n_idx = node->base0 + __builtin_popcount(vector & ((2ULL << v) - 1));
                  nh = N40[n_idx];
                }
                vector = node->vec;
	        if (vector & (1ULL << v)) {
	          idx = node->base1 + __builtin_popcount(node->vec & ((2ULL << v) - 1));
	          node = &B46[idx];
       	          vector = node->leafvec;
                  v = ((key >> 18) & 63);
  	          if (vector & (1ULL << v)) {
    	            n_idx = node->base0 + __builtin_popcount(vector & ((2ULL << v) - 1));
                    nh = N46[n_idx];
                  }
       	          vector = node->vec;
	          if (vector & (1ULL << v)) {
	            idx = node->base1 + __builtin_popcount(node->vec & ((2ULL << v) - 1));
	            node = &B52[idx];
      	 	    vector = node->leafvec;
        	    v = ((key >> 12) & 63);
  	            if (vector & (1ULL << v)) {
    	              n_idx = node->base0 + __builtin_popcount(vector & ((2ULL << v) - 1));
                      nh = N52[n_idx];
                    }
       	            vector = node->vec;
		    if (vector & (1ULL << v)) {
		      idx = node->base1 + __builtin_popcount(node->vec & ((2ULL << v) - 1));
		      node = &B58[idx];
       	    	      vector = node->leafvec;
            	      v = ((key >> 6) & 63);
  	              if (vector & (1ULL << v)) {
    	                n_idx = node->base0 + __builtin_popcount(vector & ((2ULL << v) - 1));
                        nh = N58[n_idx];
                      }
       	              vector = node->vec;
		      if (vector & (1ULL << v)) {
		        idx = node->base1 + __builtin_popcount(node->vec & ((2ULL << v) - 1));
	      		node = &B64[idx];
       	    	        vector = node->leafvec;
            	        v = (key & 63);
  	                if (vector & (1ULL << v)) {
    	                  n_idx = node->base0 + __builtin_popcount(vector & ((2ULL << v) - 1));
                          nh = N64[n_idx];
                        }
	    	      }
		    }
	          }
	        }
	      }
	    }
	  } 
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
	uint8_t *N16, *N22, *N28, *N34, *N40, *N46, *N52, *N58, *N64;
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

    N22 = (uint8_t *) malloc (sizeof(uint8_t) * N22_CNT);
    N28 = (uint8_t *) malloc (sizeof(uint8_t) * N28_CNT);
    N34 = (uint8_t *) malloc (sizeof(uint8_t) * N34_CNT);
    N40 = (uint8_t *) malloc (sizeof(uint8_t) * N40_CNT);
    N46 = (uint8_t *) malloc (sizeof(uint8_t) * N46_CNT);
    N52 = (uint8_t *) malloc (sizeof(uint8_t) * N52_CNT);
    N58 = (uint8_t *) malloc (sizeof(uint8_t) * N58_CNT);
    N64 = (uint8_t *) malloc (sizeof(uint8_t) * N64_CNT);

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

	for(i=0; i<N22_CNT; i++) N22[i] = 1;
	for(i=0; i<N28_CNT; i++) N28[i] = 2;
	for(i=0; i<N34_CNT; i++) N34[i] = 3;
	for(i=0; i<N40_CNT; i++) N40[i] = 4;
	for(i=0; i<N46_CNT; i++) N46[i] = 5;
	for(i=0; i<N52_CNT; i++) N52[i] = 6;
	for(i=0; i<N58_CNT; i++) N58[i] = 7;
	for(i=0; i<N64_CNT; i++) N64[i] = 8;

	nh = fib_lookup(N16, C16, B22, N22, B28, N28, B34, N34, B40, N40, B46, N46, B52, N52, B58, N58, B64, N64, 67);

  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "next-hop = %d\n", nh);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
