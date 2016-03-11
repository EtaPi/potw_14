// c3.c crack single byte XOR

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "util.h"

int main() {
  char* enc = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  size_t size = 68;

  uint8_t* enc_bytes = calloc( size/2, sizeof( uint8_t ) );

  to_byte_array( enc, size, enc_bytes, size/2 );

  uint8_t* out = calloc( size/2, sizeof( uint8_t ) );
  for ( uint8_t i = 0; i < 0xFF; i++ ) {
    xor_single_byte_byte( enc_bytes, size/2, i, out );
    //printf("%s\n", out);
  }

  free( enc_bytes );
  free( out );

  return 0;
}
