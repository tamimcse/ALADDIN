#include "triad.h"

void triad(uint8_t *N16, uint16_t *C16, uint8_t *N24, uint16_t *C24, uint8_t *N32, uint16_t *C32, uint8_t *N40, uint16_t *C40, uint8_t *N48, uint16_t *C48,
		uint8_t *N56, uint16_t *C56, uint8_t *N64, uint64_t ip){
  int i;
    N16[0] = N24[0] + ip*C24[0];
}

int main(){
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
	triad(&N16[0], &C16[0], &N24[0], &C24[0], &N32[0], &C32[0], &N40[0], &C40[0], &N48[0], &C48[0], &N56[0], &C56[0], &N64[0], 67);

  FILE *output;
  output = fopen("output.data", "w");
	for(i=0; i<LEVEL16_SIZE; i++)
    fprintf(output, "%d + %d = %d\n", N16[0], N24[0], C24[0]);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
