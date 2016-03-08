// c2.c XOR

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "util.h"

void xor( uint32_t size, char* a, char* b, char* out );

char* lookup = "0123456789abcdef";

int main() {
  uint32_t size = 36;
  char* a = "1c0111001f010100061a024b53535009181c";
  char* b = "686974207468652062756c6c277320657965";
  char* test = "746865206b696420646f6e277420706c6179";

  char* out = calloc( size, sizeof( char ) );
  xor(size, a, b, out);

  if (compare( test, out, size )) {
    printf("Got: %s\n", out);
  }

  free( out );

  return 0;
}

void xor( uint32_t size, char* a, char* b, char* out ) {
  uint8_t* a_bytes = to_byte_array( a, size );
  uint8_t* b_bytes = to_byte_array( b, size );

  for ( uint32_t i = 0; i < size; i++ ) {
    uint8_t x = *(a_bytes + i) ^ *(b_bytes + i);
    *(out + i) = to_hex( x );
  }

  free( a_bytes );
  free( b_bytes );
}
