// c2.c XOR

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "util.h"

int main() {
  uint32_t size = 36;
  char* a = "1c0111001f010100061a024b53535009181c";
  char* b = "686974207468652062756c6c277320657965";
  char* test = "746865206b696420646f6e277420706c6179";

  char* out = calloc( size, sizeof( char ) );
  xor_buffer(a, b, size, out);

  if (compare( test, out, size )) {
    printf("Got: %s\n", out);
  }

  free( out );

  return 0;
}
