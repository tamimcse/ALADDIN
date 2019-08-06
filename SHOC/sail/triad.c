#include "triad.h"

void triad(int *a,int *b, int *c, int s){
  int i;
    c[0] = a[0] + s*b[0];
}

int main(){
	int *a, *b, *c;
    a = (int *) malloc (sizeof(int) * NUM);
    b = (int *) malloc (sizeof(int) * NUM);
    c = (int *) malloc (sizeof(int) * NUM);
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
    fprintf(output, "%d + %d = %d\n", a[0], b[0], c[0]);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
