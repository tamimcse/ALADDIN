#include "triad.h"

void triad(uint8_t *N16,uint8_t *N24, uint8_t *N32, uint64_t ip){
  int i;
    N16[0] = N24[0] + ip*N32[0];
}

int main(){
	uint8_t *N16, *N24, *N32;

    N16 = (uint8_t *) malloc (sizeof(uint8_t) * LEVEL16_SIZE);
    N24 = (uint8_t *) malloc (sizeof(uint8_t) * LEVEL16_SIZE);
    N32 = (uint8_t *) malloc (sizeof(uint8_t) * LEVEL16_SIZE);

	int i;
  srand(time(NULL));
	for(i=0; i<LEVEL16_SIZE; i++){
		N16[i] = 1;
		N24[i] = rand();
		N32[i] = rand();
	}
	triad(&N16[0],&N24[0],&N32[0],67);

  FILE *output;
  output = fopen("output.data", "w");
	for(i=0; i<LEVEL16_SIZE; i++)
    fprintf(output, "%d + %d = %d\n", N16[0], N24[0], N32[0]);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
