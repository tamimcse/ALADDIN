#include "sail.h"

void fib_lookup(uint8_t *N16, uint16_t *C16, uint8_t *N24, uint16_t *C24, uint8_t *N32, uint16_t *C32, uint8_t *N40, uint16_t *C40, uint8_t *N48, uint16_t *C48,
		uint8_t *N56, uint16_t *C56, uint8_t *N64, uint64_t ip, uint8_t *nh){
  uint16_t nix;
  uint32_t cix;

    nix = ip >> 48;

    if (N16[nix])
	*nh = N16[nix];

    if (C16[nix]) {
	nix = (C16[nix] - 1) * 256 + ((ip >> 40) & 0XFF);
    }

    if (N24[nix])
	*nh = N24[nix];

    if (C24[nix]) {
	nix = (C24[nix] - 1) * 256 + ((ip >> 32) & 0XFF);
    } else {
	return;
    }

    if (N32[nix])
	*nh = N32[nix];

    if (C32[nix]) {
	nix = (C32[nix] - 1) * 256 + ((ip >> 24) & 0XFF);
    } else {
	return;
    }

    if (N40[nix])
	*nh = N40[nix];

    if (C40[nix]) {
	nix = (C40[nix] - 1) * 256 + ((ip >> 16) & 0XFF);
    } else {
	return;
    }

    if (N48[nix])
	*nh = N48[nix];

    if (C48[nix]) {
	nix = (C48[nix] - 1) * 256 + ((ip >> 8) & 0XFF);
    } else {
	return;
    }

    if (N56[nix])
	*nh = N56[nix];

    if (C56[nix]) {
	nix = (C56[nix] - 1) * 256 + (ip & 0XFF);
    } else {
	return;
    }

    if (N64[nix])
	*nh = N64[nix];

}

int main(){
	uint8_t nh;
	uint8_t *N16, *N24, *N32, *N40, *N48, *N56, *N64;
	uint16_t *C16, *C24, *C32, *C40, *C48, *C56;

    N16 = (uint8_t *) malloc (sizeof(uint8_t) * LEVEL16_SIZE);
    C16 = (uint16_t *) malloc (sizeof(uint16_t) * LEVEL16_SIZE);
    N24 = (uint8_t *) malloc (sizeof(uint8_t) * ARR_SIZE);
    C24 = (uint16_t *) malloc (sizeof(uint16_t) * ARR_SIZE);
    N32 = (uint8_t *) malloc (sizeof(uint8_t) * ARR_SIZE);
    C32 = (uint16_t *) malloc (sizeof(uint16_t) * ARR_SIZE);
    N40 = (uint8_t *) malloc (sizeof(uint8_t) * ARR_SIZE);
    C40 = (uint16_t *) malloc (sizeof(uint16_t) * ARR_SIZE);
    N48 = (uint8_t *) malloc (sizeof(uint8_t) * ARR_SIZE);
    C48 = (uint16_t *) malloc (sizeof(uint16_t) * ARR_SIZE);
    N56 = (uint8_t *) malloc (sizeof(uint8_t) * ARR_SIZE);
    C56 = (uint16_t *) malloc (sizeof(uint16_t) * ARR_SIZE);
    N64 = (uint8_t *) malloc (sizeof(uint8_t) * ARR_SIZE);


	int i;
  srand(time(NULL));
	for(i=0; i<LEVEL16_SIZE; i++){
		N16[i] = 1;
		C16[i] = 1;
		N24[i] = rand();
		C24[i] = rand();
		N32[i] = rand();
		C32[i] = rand();
		N40[i] = rand();
		C40[i] = 1;
		N48[i] = 1;
		C48[i] = 1;
		N56[i] = 1;
		C56[i] = 1;
		N64[i] = 1;
	}
	fib_lookup(&N16[0], &C16[0], &N24[0], &C24[0], &N32[0], &C32[0], &N40[0], &C40[0], &N48[0], &C48[0], &N56[0], &C56[0], &N64[0], 67, &nh);

  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "next-hop = %d\n", nh);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
