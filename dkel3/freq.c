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
// break_xor_single_hex: find the key yielding the lowest freq score
//  * input: string in hex
// ------------------------------------

float break_xor_single_hex( char* in, size_t size, uint8_t* out_key ) {
  float lowest = FLT_MAX;
  uint8_t key = 0;

  for ( uint8_t i = 0; i < 0xFF; i++ ) {
    float score = score_hex( in, size, i );
    if (score < lowest) {
      lowest = score;
      key = i;
    }
  }

  *out_key = key;
  return lowest;
}

// ------------------------------------
// PRIVATE METHODS
// ------------------------------------

uint8_t valid( uint8_t* in, size_t size ) {
  uint8_t valid = 1;

  for ( size_t i = 0; i < size; i++ ) {
    uint8_t a = *(in + i);

    if ( !(32 <= a && a <= 126) && !(9 <= a && a <= 13) ) {
      valid = 0;
    }
  }

  return valid;
}
