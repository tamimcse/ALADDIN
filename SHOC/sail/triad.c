#include "triad.h"

void triad(uint64_t *a,uint64_t *b, uint64_t *c, int s){
  int i;
    c[0] = a[0] + s*b[0];
}

int main(){
	uint64_t *a, *b, *c;
    a = (uint64_t *) malloc (sizeof(uint64_t) * NUM);
    b = (uint64_t *) malloc (sizeof(uint64_t) * NUM);
    c = (uint64_t *) malloc (sizeof(uint64_t) * NUM);
	int i;
  srand(time(NULL));
	for(i=0; i<NUM; i++){
		c[i] = 0;
		a[i] = rand();
		b[i] = rand();
	}
	triad(&a[0],&b[0],&c[0],3);

  FILE *output;
  output = fopen("output.data", "w");
	for(i=0; i<NUM; i++)
    fprintf(output, "%lu + %lu = %lu\n", a[0], b[0], c[0]);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
