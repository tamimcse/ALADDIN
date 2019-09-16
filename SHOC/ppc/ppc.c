#include "ppc.h"

#define POPCNT_LFT(X, N) (__builtin_popcount(((X) >> (63 - (N))) >> 1))

/* Although multiple returns in a function are allowed by both Aladdin and HLS, they are in general a bad idea (blue book). Rewrite the logic
 * such that there is one return statement
 */
uint8_t fib_lookup(struct bitmap_pc *B16, uint8_t *N16, struct bitmap_pc *C16, struct bitmap_pc *B24, uint8_t *N24, struct bitmap_pc *C24,
		   struct bitmap_pc *B32, uint8_t *N32, struct bitmap_pc *C32, struct bitmap_pc *B40, uint8_t *N40, struct bitmap_pc *C40,
		   struct bitmap_pc *B48, uint8_t *N48, struct bitmap_pc *C48, struct bitmap_pc *B56, uint8_t *N56, struct bitmap_pc *C56,
		   struct bitmap_pc *B64, uint8_t *N64, uint64_t key){

	uint32_t n_idx;
	uint32_t off;
	uint32_t idx, idx_sail;
	uint32_t ck_idx;
	uint8_t nh = DEF_NH;

	idx_sail = key >> 48;
        idx = idx_sail >> 6;
        off = idx_sail & 63;

        if (B16[idx].bitmap & (MSK >> off)) {
            n_idx = B16[idx].popcnt + __builtin_popcount((B16[idx].bitmap >> (63 - off)) >> 1);
            nh = N16[n_idx];
        }

        if (C16[idx].bitmap & (MSK >> off)) {
                ck_idx = C16[idx].popcnt + __builtin_popcount((C16[idx].bitmap >> (63 - off)) >> 1);
                idx_sail = (ck_idx << 8) + ((key >> 40) & 0XFF);
                idx = idx_sail >> 6;
                off = idx_sail & 63;

		if (B24[idx].bitmap & (MSK >> off)) {
		    n_idx = B24[idx].popcnt + __builtin_popcount((B24[idx].bitmap >> (63 - off)) >> 1);
		    nh = N24[n_idx];
		}

		if (C24[idx].bitmap & (MSK >> off)) {
		        ck_idx = C24[idx].popcnt + __builtin_popcount((C24[idx].bitmap >> (63 - off)) >> 1);
		        idx_sail = (ck_idx << 8) + ((key >> 32) & 0XFF);
		        idx = idx_sail >> 6;
		        off = idx_sail & 63;

			if (B32[idx].bitmap & (MSK >> off)) {
			    n_idx = B32[idx].popcnt + __builtin_popcount((B32[idx].bitmap >> (63 - off)) >> 1);
			    nh = N32[n_idx];
			}

			if (C32[idx].bitmap & (MSK >> off)) {
				ck_idx = C32[idx].popcnt + __builtin_popcount((C32[idx].bitmap >> (63 - off)) >> 1);
				idx_sail = (ck_idx << 8) + ((key >> 24) & 0XFF);
				idx = idx_sail >> 6;
				off = idx_sail & 63;

				if (B40[idx].bitmap & (MSK >> off)) {
				    n_idx = B40[idx].popcnt + __builtin_popcount((B40[idx].bitmap >> (63 - off)) >> 1);
				    nh = N40[n_idx];
				}

				if (C40[idx].bitmap & (MSK >> off)) {
					ck_idx = C40[idx].popcnt + __builtin_popcount((C40[idx].bitmap >> (63 - off)) >> 1);
					idx_sail = (ck_idx << 8) + ((key >> 16) & 0XFF);
					idx = idx_sail >> 6;
					off = idx_sail & 63;

					if (B48[idx].bitmap & (MSK >> off)) {
					    n_idx = B48[idx].popcnt + __builtin_popcount((B48[idx].bitmap >> (63 - off)) >> 1);
					    nh = N48[n_idx];
					}

					if (C48[idx].bitmap & (MSK >> off)) {
						ck_idx = C48[idx].popcnt + __builtin_popcount((C48[idx].bitmap >> (63 - off)) >> 1);
						idx_sail = (ck_idx << 8) + ((key >> 8) & 0XFF);
						idx = idx_sail >> 6;
						off = idx_sail & 63;

						if (B56[idx].bitmap & (MSK >> off)) {
						    n_idx = B56[idx].popcnt + __builtin_popcount((B56[idx].bitmap >> (63 - off)) >> 1);
						    nh = N56[n_idx];
						}

						if (C56[idx].bitmap & (MSK >> off)) {
							ck_idx = C56[idx].popcnt + __builtin_popcount((C56[idx].bitmap >> (63 - off)) >> 1);
							idx_sail = (ck_idx << 8) + (key & 0XFF);
							idx = idx_sail >> 6;
							off = idx_sail & 63;

							if (B64[idx].bitmap & (MSK >> off)) {
							    n_idx = B64[idx].popcnt + __builtin_popcount((B64[idx].bitmap >> (63 - off)) >> 1);
							    nh = N64[n_idx];
							}
						}
					}
				} 
			}
		}
        }
	return nh;
}

void reset_ppc (struct bitmap_pc *ppc) {
    ppc->bitmap = 0XFFFFFFFFFFFFFFFF;
    ppc->popcnt = 5;
}

int main(){
	uint8_t nh;
	uint8_t *N16, *N24, *N32, *N40, *N48, *N56, *N64;
	struct bitmap_pc *C16, *C24, *C32, *C40, *C48, *C56, *B16, *B24, *B32, *B40, *B48, *B56, *B64;
        
    B16 = (struct bitmap_pc *) malloc (B16S);
    N16 = (uint8_t *) malloc (N16S);
    C16 = (struct bitmap_pc *) malloc (C16S);

    B24 = (struct bitmap_pc *) malloc (B24S);
    N24 = (uint8_t *) malloc (N24S);
    C24 = (struct bitmap_pc *) malloc (C24S);

    B32 = (struct bitmap_pc *) malloc (B32S);
    N32 = (uint8_t *) malloc (N32S);
    C32 = (struct bitmap_pc *) malloc (C32S);

    B40 = (struct bitmap_pc *) malloc (B40S);
    N40 = (uint8_t *) malloc (N40S);
    C40 = (struct bitmap_pc *) malloc (C40S);

    B48 = (struct bitmap_pc *) malloc (B48S);
    N48 = (uint8_t *) malloc (N48S);
    C48 = (struct bitmap_pc *) malloc (C48S);

    B56 = (struct bitmap_pc *) malloc (B56S);
    N56 = (uint8_t *) malloc (N56S);
    C56 = (struct bitmap_pc *) malloc (C56S);

    B64 = (struct bitmap_pc *) malloc (B64S);
    N64 = (uint8_t *) malloc (N64S);

  srand(time(NULL));

	for(int i = 0; i< (B16S/10); i++) reset_ppc(B16);
	for(int i = 0; i< (C16S/10); i++) reset_ppc(C16);
	for(int i = 0; i< (B24S/10); i++) reset_ppc(B24);
	for(int i = 0; i< (C24S/10); i++) reset_ppc(C24);
	for(int i = 0; i< (B32S/10); i++) reset_ppc(B32);
	for(int i = 0; i< (C32S/10); i++) reset_ppc(C32);
	for(int i = 0; i< (B40S/10); i++) reset_ppc(B40);
	for(int i = 0; i< (C40S/10); i++) reset_ppc(C40);
	for(int i = 0; i< (B48S/10); i++) reset_ppc(B48);
	for(int i = 0; i< (C48S/10); i++) reset_ppc(C48);
	for(int i = 0; i< (B56S/10); i++) reset_ppc(B56);
	for(int i = 0; i< (C56S/10); i++) reset_ppc(C56);
	for(int i = 0; i< (B64S/10); i++) reset_ppc(B64);


	for(int i = 0; i<N16S; i++) N16[i] = 1;
	for(int i = 0; i<N24S; i++) N24[i] = 1;
	for(int i = 0; i<N32S; i++) N32[i] = 1;
	for(int i = 0; i<N40S; i++) N40[i] = 1;
	for(int i = 0; i<N48S; i++) N48[i] = 1;
	for(int i = 0; i<N56S; i++) N56[i] = 1;
	for(int i = 0; i<N64S; i++) N64[i] = 1;


	nh = fib_lookup(B16, N16, C16, B24, N24, C24, B32, N32, C32, B40, N40, C40, B48, N48, C48, B56, N56, C56, B64, N64, 67);

  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "next-hop = %d\n", nh);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
