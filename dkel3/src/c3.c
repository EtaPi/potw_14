// c3.c crack single byte XOR

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <float.h>

#include "../lib/util.h"
#include "../lib/stats.h"
#include "../lib/freq.h"

uint8_t valid( uint8_t* in, size_t size );

int main() {
  char* enc = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  size_t size = 68;

  uint8_t key = 0;
  float lowest = FLT_MAX;

  for ( uint8_t i = 0; i < 0xFF; i++ ) {
    float score = score_hex( enc, size, i );

    if (score < lowest) {
      lowest = score;
      key = i;
    }
  }

  uint8_t* out = calloc( size/2, sizeof( uint8_t ) );
  xor_single_hex_byte( enc, size, key, out );
  printf("%s   %f\n", out, lowest);

  free( out );

  return 0;
}
