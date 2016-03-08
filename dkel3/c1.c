// c1.c

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int main() {
  uint32_t size = 6;
  char* in = "affaaf";

  char* out = calloc( size, sizeof( char ) );
  encode_base64( in, size, out );

  printf("Got: %s\n", out);

  free(out);
}
