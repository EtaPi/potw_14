// freq.c

#include <stdint.h>
#include <stdlib.h>
#include <float.h>

#include "stats.h"
#include "util.h"

uint8_t valid( uint8_t* in, size_t size );

// ------------------------------------
// score_string: score the output of decrypting the string with the given key
//    regarding english frequency
//  * input: string in hex
//  * input: byte key
// ------------------------------------

float score_hex( char* in, size_t size, uint8_t key ) {
  // xor byte array
  uint8_t* out = calloc( size/2, sizeof( uint8_t ) );
  xor_single_hex_byte( in, size, key, out );

  // score resulting string if printable ASCII
  float score = FLT_MAX;
  if ( valid( out, size/2 ) ) {
    float h[26] = {0};
    histo( (char* )out, size/2, h );

    score = score_histo_sum( h, english_freq );
  }

  free( out );

  return score;
}

// ------------------------------------
// PRIVATE METHODS
// ------------------------------------

uint8_t valid( uint8_t* in, size_t size ) {
  uint8_t valid = 1;

  for ( size_t i = 0; i < size; i++ ) {
    uint8_t a = *(in + i);

    if (a < 32 || 126 < a) {
      valid = 0;
    }
  }

  return valid;
}
