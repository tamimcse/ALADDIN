#include "if-else.h"

int br(int a, int b, int c, int d){
    int out;

    if (a > c) {
	out = a & c;
        if (out > d) {
	  out = c & d;
          if (a > out)
	    out = a & d;
        }
    }

    return out;
}

int main(){
  srand(time(NULL));
  int a, b, c, d, out;
  a = 5;
  b = 2;
  c = 1;
  d = 0;
  out = br(a, b, c, d);
  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "a = %d b = %d c = %d d = %d out = %d \n", a, b, c, d, out);
  fprintf(output, "\n");
  fclose(output);
  return 0;
}
