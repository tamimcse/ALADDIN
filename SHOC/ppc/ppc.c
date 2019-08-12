#include "ppc.h"

#define POPCNT_LFT(X, N) (__builtin_popcount(((X) >> (63 - (N))) >> 1))

void fib_lookup(struct bitmap_pc *B16, uint8_t *N16, struct bitmap_pc *C16, struct bitmap_pc *B32, uint8_t *N32, struct bitmap_pc *C32,
	struct bitmap_pc *B40, uint8_t *N40, struct bitmap_pc *C40, struct bitmap_pc *B48, uint8_t *N48, struct bitmap_pc *C48,
	struct bitmap_pc *B64, uint8_t *N64, uint64_t key, uint8_t *nh){
  /*This variables are made uint64_t to avoid generating trunc opcode*/
  uint32_t n_idx;
  uint32_t off;
  uint32_t idx, idx_sail;
  uint32_t ck_idx;

	idx_sail = key >> 48;
        idx = idx_sail >> 6;
        off = idx_sail & 63;

        if (B16[idx].bitmap & (MSK >> off)) {
            n_idx = B16[idx].popcnt + __builtin_popcount((B16[idx].bitmap >> (63 - off)) >> 1);
            *nh = N16[n_idx];
        }

        if (C16[idx].bitmap & (MSK >> off)) {
                ck_idx = C16[idx].popcnt + __builtin_popcount((C16[idx].bitmap >> (63 - off)) >> 1);
                idx_sail = (ck_idx << 16) + ((key >> 32) & 0XFFFF);
                idx = idx_sail >> 6;
                off = idx_sail & 63;
        } else {
                return;
        }

        if (B32[idx].bitmap & (MSK >> off)) {
            n_idx = B32[idx].popcnt + __builtin_popcount((B32[idx].bitmap >> (63 - off)) >> 1);
            *nh = N32[n_idx];
        }

        if (C32[idx].bitmap & (MSK >> off)) {
                ck_idx = C32[idx].popcnt + __builtin_popcount((C32[idx].bitmap >> (63 - off)) >> 1);
                idx_sail = (ck_idx << 8) + ((key >> 24) & 0XFF);
                idx = idx_sail >> 6;
                off = idx_sail & 63;
        } else {
                return;
        }

        if (B40[idx].bitmap & (MSK >> off)) {
            n_idx = B40[idx].popcnt + __builtin_popcount((B40[idx].bitmap >> (63 - off)) >> 1);
            *nh = N40[n_idx];
        }

        if (C40[idx].bitmap & (MSK >> off)) {
                ck_idx = C40[idx].popcnt + __builtin_popcount((C40[idx].bitmap >> (63 - off)) >> 1);
                idx_sail = (ck_idx << 8) + ((key >> 16) & 0XFF);
                idx = idx_sail >> 6;
                off = idx_sail & 63;
        } else {
                return;
        }

        if (B48[idx].bitmap & (MSK >> off)) {
            n_idx = B48[idx].popcnt + __builtin_popcount((B48[idx].bitmap >> (63 - off)) >> 1);
            *nh = N48[n_idx];
        }

        if (C48[idx].bitmap & (MSK >> off)) {
                ck_idx = C48[idx].popcnt + __builtin_popcount((C48[idx].bitmap >> (63 - off)) >> 1);
                idx_sail = (ck_idx << 16) + (key & 0XFFFF);
                idx = idx_sail >> 6;
                off = idx_sail & 63;
        } else {
                return;
        }

        if (B64[idx].bitmap & (MSK >> off)) {
            n_idx = B64[idx].popcnt + __builtin_popcount((B64[idx].bitmap >> (63 - off)) >> 1);
            *nh = N64[n_idx];
        }
}

void reset_ppc (struct bitmap_pc *ppc) {
	ppc->bitmap = 0XFFFFFFFFFFFFFFFF;
	ppc->popcnt = 5;
}

int main(){
	uint8_t nh;
	uint8_t *N16, *N32, *N40, *N48, *N64;
	struct bitmap_pc *C16, *C32, *C40, *C48, *B16, *B32, *B40, *B48, *B64;
        
    B16 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B16_SIZE);
    N16 = (uint8_t *) malloc (sizeof(uint8_t) * N16_SIZE);
    C16 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B16_SIZE);

    B32 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B32_SIZE);
    N32 = (uint8_t *) malloc (sizeof(uint8_t) * N32_SIZE);
    C32 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B32_SIZE);

    B40 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B40_B48_SIZE);
    N40 = (uint8_t *) malloc (sizeof(uint8_t) * N40_N48_SIZE);
    C40 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B40_B48_SIZE);

    B48 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B40_B48_SIZE);
    N48 = (uint8_t *) malloc (sizeof(uint8_t) * N40_N48_SIZE);
    C48 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B40_B48_SIZE);

    B64 = (struct bitmap_pc *) malloc (sizeof(struct bitmap_pc) * B64_SIZE);
    N64 = (uint8_t *) malloc (sizeof(uint8_t) * N64_SIZE);

	int i;
  srand(time(NULL));
	for(i=0; i<B16_SIZE; i++){
		reset_ppc(&B16[i]);
		reset_ppc(&C16[i]);
	}

	for(i=0; i<N16_SIZE; i++){
		N16[i] = 1;
	}

	for(i=0; i<B32_SIZE; i++){
		reset_ppc(&B32[i]);
		reset_ppc(&C32[i]);	
	}

	for(i=0; i<N32_SIZE; i++){
		N32[i] = 1;
	}

	for(i=0; i<B40_B48_SIZE; i++){
		reset_ppc(&B40[i]);
		reset_ppc(&C40[i]);
		reset_ppc(&B48[i]);
		reset_ppc(&C48[i]);	
	}

	for(i=0; i<N40_N48_SIZE; i++){
		N40[i] = 1;
		N48[i] = 1;	
	}

	for(i=0; i<B64_SIZE; i++){
		reset_ppc(&B64[i]);
	}

	for(i=0; i<N64_SIZE; i++){
		N64[i] = 1;
	}

	fib_lookup(B16, N16, C16, B32, N32, C32, B40, N40, C40, B48, N48, C48, B64, N64, 67, &nh);

  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "next-hop = %d\n", nh);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
