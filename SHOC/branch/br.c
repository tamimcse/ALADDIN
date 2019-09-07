#include "br.h"

uint8_t br(uint8_t *N16, uint16_t *C16, uint8_t *N24, uint64_t ip){
    uint16_t nix;
    uint32_t cix;
    uint8_t nh;

    nix = ip >> 48;

    if (N16[nix])
	nh = N16[nix];

    if (C16[nix]) {
	nix = (C16[nix] - 1) * 256 + ((ip >> 40) & 0XFF);
        if (N24[nix])
	    nh = N24[nix];
    }

    return nh;
}

int main(){
	uint8_t nh;
	uint8_t *N16, *N24;
	uint16_t *C16;

    N16 = (uint8_t *) malloc (sizeof(uint8_t) * LEVEL16_SIZE);
    C16 = (uint16_t *) malloc (sizeof(uint16_t) * LEVEL16_SIZE);
    N24 = (uint8_t *) malloc (sizeof(uint8_t) * ARR_SIZE);

	int i;
  srand(time(NULL));
	for(i=0; i<LEVEL16_SIZE; i++){
		N16[i] = 1;
		C16[i] = 1;
		N24[i] = rand();
	}
	nh = br(&N16[0], &C16[0], &N24[0], 67);

  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "next-hop = %d\n", nh);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
