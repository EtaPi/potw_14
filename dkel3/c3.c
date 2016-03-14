// c3.c crack single byte XOR

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <float.h>

#include "util.h"
#include "stats.h"

uint8_t valid( uint8_t* in, size_t size );

int main() {
  char* enc = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  size_t size = 68;

  uint8_t* enc_bytes = calloc( size/2, sizeof( uint8_t ) );

  to_byte_array( enc, size, enc_bytes, size/2 );

  uint8_t* temp = calloc( size/2 + 1, sizeof( uint8_t ) );

  uint8_t key = 0;
  uint8_t* out = calloc( size/2 + 1, sizeof( uint8_t ) );

  float lowest = FLT_MAX;

  for ( uint8_t i = 0; i < 0xFF; i++ ) {
    xor_single_byte_byte( enc_bytes, size/2, i, temp );

    float h[26];
    histo( (char* )temp, size/2, h );

    float score = score_histo_sum( h, english_freq );

    // Assuming ASCII output
    // So skip if 'decrypted' result is not printable ASCII
    if ( valid( temp, size/2 ) ) {
      if (score < lowest) {
        lowest = score;
        key = i;
      }
    }
  }

  xor_single_byte_byte( enc_bytes, size/2, key, out );
  printf("%s   %f\n", out, lowest);

  free( enc_bytes );
  free( temp );
  free( out );

  return 0;
}

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
