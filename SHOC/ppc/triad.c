#include "triad.h"

void triad(struct bitmap_pc *B16, uint8_t *N16, struct bitmap_pc *C16, struct bitmap_pc *B32, uint8_t *N32, struct bitmap_pc *C32,
	struct bitmap_pc *B40, uint8_t *N40, struct bitmap_pc *C40, struct bitmap_pc *B48, uint8_t *N48, struct bitmap_pc *C48,
	struct bitmap_pc *B64, uint8_t *N64, uint64_t ip, uint8_t *nh){
  uint16_t nix;
  uint32_t cix;

    nix = ip >> 48;
/*
    if (N16[nix])
	*nh = N16[nix];

    if (C16[nix]) {
	nix = (C16[nix] - 1) * 256 + ((ip >> 40) & 0XFF);
    }

    if (N24[nix])
	*nh = N24[nix];

    if (C24[nix]) {
	nix = (C24[nix] - 1) * 256 + ((ip >> 32) & 0XFF);
    }

    if (N32[nix])
	*nh = N32[nix];

    if (C32[nix]) {
	nix = (C32[nix] - 1) * 256 + ((ip >> 24) & 0XFF);
    }

    if (N40[nix])
	*nh = N40[nix];

    if (C40[nix]) {
	nix = (C40[nix] - 1) * 256 + ((ip >> 16) & 0XFF);
    }

    if (N48[nix])
	*nh = N48[nix];

    if (C48[nix]) {
	nix = (C48[nix] - 1) * 256 + ((ip >> 8) & 0XFF);
    }

    if (N56[nix])
	*nh = N56[nix];

    if (C56[nix]) {
	nix = (C56[nix] - 1) * 256 + (ip & 0XFF);
    }

    if (N64[nix])
	*nh = N64[nix];
*/
}

void reset_ppc (struct bitmap_pc *ppc) {
	ppc->bitmap = 0;
	ppc->popcnt = 0;
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
	for(i=0; i<10; i++){
		reset_ppc(&B16[i]);
		N16[i] = 1;
		reset_ppc(&C16[i]);

		reset_ppc(&B32[i]);
		N32[i] = 1;
		reset_ppc(&C32[i]);

		reset_ppc(&B40[i]);
		N40[i] = 1;
		reset_ppc(&C40[i]);

		reset_ppc(&B48[i]);
		N48[i] = 1;
		reset_ppc(&C48[i]);

		reset_ppc(&B64[i]);
		N64[i] = 1;
	}
	triad(B16, N16, C16, B32, N32, C32, B40, N40, C40, B48, N48, C48, B64, N64, 67, &nh);

  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "next-hop = %d\n", nh);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
