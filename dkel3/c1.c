// c1.c

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void encode( char* in, uint32_t size, char* out );
uint8_t get_byte( uint8_t a, uint8_t b );
uint8_t parse_hex( char a );

char* lookup = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main( int argc, char** argv ) {
  uint32_t size = 6;
  char* in = "affaaf";

  char* out = calloc( size, sizeof( char ) );
  encode( in, size, out );

  printf("Got: %s\n", out);
}

void encode( char* in, uint32_t size, char* out ) {
  char* p_in = in;
  char* p_out = out;
  uint8_t step = 0;
  uint8_t extra = 0;
  uint32_t count = 0;


  while (count < size) {
    char a = parse_hex( *(p_in++) );
    char b = parse_hex( *(p_in++) );

    uint8_t next = get_byte( a, b );

    if (step == 0) {
      uint8_t mask = 0xFC;
      *(p_out++) = lookup[ (mask & next) >> 2 ];

      extra = (next & 0x3) << 4;

      step = 1;
    } else if (step == 1) {
      uint8_t mask = 0xF0;
      *(p_out++) = lookup[ ((mask & next) >> 4) | extra ];

      extra = (next & 0xF) << 2;

      step = 2;
    } else {
      uint8_t mask = 0xC0;
      *(p_out++) = lookup[ ((mask & next) >> 6) | extra ];

      *(p_out++) = lookup[ next & 0x3F ];

      step = 0;
    }

    count += 2;
  }

  if (step == 1) {
    *(p_out++) = lookup[ extra ];
    *(p_out++) = '=';
    *(p_out++) = '=';
  } else if (step == 2) {
    *(p_out++) = lookup[ extra ];
    *(p_out++) = '=';
  }
}

uint8_t get_byte( uint8_t a, uint8_t b ) {
  return (a << 4) | b;
}

uint8_t parse_hex( char in ) {
  if (48 <= in  && in <= 57) {
    return in & 0xF;
  } else if (65 <= in && in <= 70) {
    return (in & 0xF) + 9;
  } else if (97 <= in && in <= 102) {
    return (in & 0xF) + 9;
  }

  return 0;
}
