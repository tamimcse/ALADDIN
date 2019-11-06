#include "sail.h"

//Number of elements needed in each level (obtrained from data from ppc.sh)
#define CNK24 60
#define CNK32 6000
#define CNK40 7000
#define CNK48 11000
#define CNK56 700
#define CNK64 700
#define CNK72 500
#define CNK80 500
#define CNK88 500
#define CNK96 500
#define CNK104 500
#define CNK112 500
#define CNK120 500
#define CNK128 500

/*chunk size is 2^8*/
#define CNK_8 256

#define SIZE16 65536
#define SIZE24 CNK24 * CNK_8
#define SIZE32 CNK32 * CNK_8
#define SIZE40 CNK40 * CNK_8
#define SIZE48 CNK48 * CNK_8
#define SIZE56 CNK56 * CNK_8
#define SIZE64 CNK64 * CNK_8

#define SIZE72 CNK72 * CNK_8
#define SIZE80 CNK80 * CNK_8
#define SIZE88 CNK88 * CNK_8
#define SIZE96 CNK96 * CNK_8
#define SIZE104 CNK104 * CNK_8
#define SIZE112 CNK112 * CNK_8
#define SIZE120 CNK120 * CNK_8
#define SIZE128 CNK128 * CNK_8


#define MSK 0X8000000000000000ULL

static int sail_init (struct sail *sail) {
  int err = 0;

  sail->def_nh = 1;
  err = sail_level_init (&sail->level16, 16, SIZE16, CNK_8, NULL);
  err = sail_level_init (&sail->level24, 24, SIZE24, CNK_8, &sail->level16);
  err = sail_level_init (&sail->level32, 32, SIZE32, CNK_8, &sail->level24);
  err = sail_level_init (&sail->level40, 40, SIZE40, CNK_8, &sail->level32);
  err = sail_level_init (&sail->level48, 48, SIZE48, CNK_8, &sail->level40);
  err = sail_level_init (&sail->level56, 56, SIZE56, CNK_8, &sail->level48);
  err = sail_level_init (&sail->level64, 64, SIZE64, CNK_8, &sail->level56);
  err = sail_level_init (&sail->level72, 72, SIZE72, CNK_8, &sail->level64);
  err = sail_level_init (&sail->level80, 80, SIZE80, CNK_8, &sail->level72);
  err = sail_level_init (&sail->level88, 88, SIZE88, CNK_8, &sail->level80);
  err = sail_level_init (&sail->level96, 96, SIZE96, CNK_8, &sail->level88);
  err = sail_level_init (&sail->level104, 104, SIZE104, CNK_8, &sail->level96);
  err = sail_level_init (&sail->level112, 112, SIZE112, CNK_8, &sail->level104);
  err = sail_level_init (&sail->level120, 120, SIZE120, CNK_8, &sail->level112);
  err = sail_level_init (&sail->level128, 128, SIZE128, CNK_8, &sail->level120);

  return err;
}

uint8_t fib_lookup(uint8_t *N16, uint32_t *C16, uint8_t *N24, uint32_t *C24, uint8_t *N32, uint32_t *C32, uint8_t *N40, uint32_t *C40,
                    uint8_t *N48, uint32_t *C48, uint8_t *N56, uint32_t *C56, uint8_t *N64, uint32_t *C64, uint8_t *N72, uint32_t *C72,
                    uint8_t *N80, uint32_t *C80, uint8_t *N88, uint32_t *C88, uint8_t *N96, uint32_t *C96, uint8_t *N104, uint32_t *C104,
                    uint8_t *N112, uint32_t *C112, uint8_t *N120, uint32_t *C120, uint8_t *N128, uint8_t def_nh,
                    uint64_t key1, uint64_t key2) {

  uint32_t idx;
  uint8_t nh = def_nh;

  idx = key1 >> 48;

  if (N16[idx] != 0)
    nh = N16[idx];

  if (C16[idx] != 0) {
    idx = (C16[idx] - 1) * CNK_8 + ((key1 >> 40) & 0XFF);
  } else {
    goto finish;
  }

  if (N24[idx] != 0)
    nh = N24[idx];
    
  if (C24[idx] != 0) {
    idx = (C24[idx] - 1) * CNK_8 + ((key1 >> 32) & 0XFF);
  } else {
    goto finish;
  }        

  if (N32[idx] != 0)
    nh = N32[idx];

  if (C32[idx] != 0) {
    idx = (C32[idx] - 1) * CNK_8 + ((key1 >> 24) & 0XFF);
  } else {
    goto finish;
  }

  if (N40[idx] != 0)
    nh = N40[idx];

  if (C40[idx] != 0) {
    idx = (C40[idx] - 1) * CNK_8 + ((key1 >> 16) & 0XFF);
  } else {
    goto finish;
  }

  if (N48[idx] != 0)
    nh = N48[idx];

  if (C48[idx] != 0) {
    idx = (C48[idx] - 1) * CNK_8 + ((key1 >> 8) & 0XFF);
  } else {
    goto finish;
  }

  if (N56[idx] != 0)
    nh = N56[idx];

  if (C56[idx] != 0) {
    idx = (C56[idx] - 1) * CNK_8 + (key1 & 0XFF);
  } else {
    goto finish;
  }

  if (N64[idx] != 0)
    nh = N64[idx];

  if (C64[idx] != 0)
    idx = (C64[idx] - 1) * CNK_8 + ((key2 >> 56) & 0XFF);
  else
    goto finish;

  if (N72[idx] != 0)
    nh = N72[idx];

  if (C72[idx] != 0)
    idx = (C72[idx] - 1) * CNK_8 + ((key2 >> 48) & 0XFF);
  else
    goto finish;

  if (N80[idx] != 0)
    nh = N80[idx];

  if (C80[idx] != 0)
    idx = (C80[idx] - 1) * CNK_8 + ((key2 >> 40) & 0XFF);
  else
    goto finish;

  if (N88[idx] != 0)
    nh = N88[idx];

  if (C88[idx] != 0)
    idx = (C88[idx] - 1) * CNK_8 + ((key2 >> 32) & 0XFF);
  else
    goto finish;

  if (N96[idx] != 0)
    nh = N96[idx];

  if (C96[idx] != 0)
    idx = (C96[idx] - 1) * CNK_8 + ((key2 >> 24) & 0XFF);
  else
    goto finish;

  if (N104[idx] != 0)
    nh = N104[idx];

  if (C104[idx] != 0)
    idx = (C104[idx] - 1) * CNK_8 + ((key2 >> 16) & 0XFF);
  else
    goto finish;

  if (N112[idx] != 0)
    nh = N112[idx];

  if (C112[idx] != 0)
    idx = (C112[idx] - 1) * CNK_8 + ((key2 >> 8) & 0XFF);
  else
    goto finish;

  if (N120[idx] != 0)
    nh = N120[idx];

  if (C120[idx] != 0)
    idx = (C120[idx] - 1) * CNK_8 + (key2 & 0XFF);
  else
    goto finish;

  if (N128[idx] != 0)
    nh = N128[idx];

finish:
  return nh;
}

int main(){
  struct sail sail;
  uint8_t nh;
  
  sail_init(&sail);

  nh = fib_lookup(sail.level16.N, sail.level16.C, sail.level24.N, sail.level24.C, sail.level32.N, sail.level32.C, sail.level40.N, sail.level40.C,
                  sail.level48.N, sail.level48.C, sail.level56.N, sail.level56.C, sail.level64.N, sail.level64.C, sail.level72.N, sail.level72.C,
                  sail.level80.N, sail.level80.C, sail.level88.N, sail.level88.C, sail.level96.N, sail.level96.C, sail.level104.N, sail.level104.C,
                  sail.level112.N, sail.level112.C, sail.level120.N, sail.level120.C, sail.level128.N, sail.def_nh, 67, 65);

  FILE *output;
  output = fopen("output.data", "w");
  fprintf(output, "next-hop = %d\n", nh);
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
