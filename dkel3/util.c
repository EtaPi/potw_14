// util.c

#include <stdint.h>
#include <stdlib.h>
#include "util.h"

// ------------------------------------
// compare
//  * compare two equal length string buffers
//  * return 1 on equality, 0 otherwise
// ------------------------------------

uint8_t compare( char* a, char* b, uint32_t size ) {
  uint8_t ret = 1;
  for ( uint32_t i = 0; i < size; i++ ) {
    if ( *(a + i) != *(b + i) ) {
      ret = 0;
    }
  }

  return ret;
}

// ------------------------------------
// copy from on buffer to another in bytes
// ------------------------------------

void copy( void* a, void* b, uint32_t bytes ) {
  uint8_t* src = a;
  uint8_t* dst = b;

  for ( uint32_t i = 0; i < bytes; i++ ) {
    *(src++) = *(dst++);
  }
}

// ------------------------------------
// encode_base64
//  * in: hex string
//  * size: length of input string
//  * out: base64 output
// ------------------------------------

char* _base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encode_base64( char* in, uint32_t size, char* out ) {
  char* p_in = in;
  char* p_out = out;
  uint8_t step = 0;
  uint8_t extra = 0;
  uint32_t count = 0;


  while (count < size) {
    char a = parse_hex( *(p_in++) );
    char b = parse_hex( *(p_in++) );

    uint8_t next = (a << 4) | b;

    if (step == 0) {
      uint8_t mask = 0xFC;
      *(p_out++) = _base64_table[ (mask & next) >> 2 ];

      extra = (next & 0x3) << 4;

      step = 1;
    } else if (step == 1) {
      uint8_t mask = 0xF0;
      *(p_out++) = _base64_table[ ((mask & next) >> 4) | extra ];

      extra = (next & 0xF) << 2;

      step = 2;
    } else {
      uint8_t mask = 0xC0;
      *(p_out++) = _base64_table[ ((mask & next) >> 6) | extra ];

      *(p_out++) = _base64_table[ next & 0x3F ];

      step = 0;
    }

    count += 2;
  }

  if (step == 1) {
    *(p_out++) = _base64_table[ extra ];
    *(p_out++) = '=';
    *(p_out++) = '=';
  } else if (step == 2) {
    *(p_out++) = _base64_table[ extra ];
    *(p_out++) = '=';
  }
}

// ------------------------------------
// nibble_to_byte
// ------------------------------------

uint8_t nibbles_to_byte( uint8_t a, uint8_t b ) {
  return ((a & 0xF) << 4) | (b & 0xF);
}

// ------------------------------------
// parse_hex
//  * convert hex character into byte
// ------------------------------------

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

// ------------------------------------
// hex_to_ascii
//  * convert hex string to ascii
// ------------------------------------

//void hex_to_ascii( char* in,

// ------------------------------------
// to_nibble_array
//  * convert hex string into its nibble array
// ------------------------------------

uint8_t* to_nibble_array( char* hex, uint32_t size ) {
  uint8_t* ret = calloc( size, sizeof( uint8_t ) );
  uint8_t* out = ret;

  for ( uint32_t i = 0; i < size; i++ ) {
    *(out++) = parse_hex( *(hex++) );
  }

  return ret;
}

// ------------------------------------
// to_byte_array
//  * convert hex string into byte array
//  * size: num of chars in input hex string
// ------------------------------------

void to_byte_array( char* hex,
                        size_t in_size,
                        uint8_t* out,
                        size_t out_size )
{
  // TODO: check out size?

  char* p_in = hex;
  uint8_t* p_out = out;

  for ( size_t i = 0; i < out_size; i++ ) {
    char a = parse_hex( *(p_in++) );
    char b = parse_hex( *(p_in++) );

    uint8_t next = nibbles_to_byte( a, b );

    *(p_out++) = next;
  }
}

// ------------------------------------
// to_hex
//  * turn byte into hex character
// ------------------------------------

char to_hex( uint8_t in ) {
  char* lookup = "0123456789abcdef";

  return lookup[ in & 0xF ];
}

// ------------------------------------
// xor two equal length hex strings
// ------------------------------------

void xor_buffer( char* a, char* b, uint32_t size, char* out ) {
  uint8_t* a_bytes = to_nibble_array( a, size );
  uint8_t* b_bytes = to_nibble_array( b, size );

  for ( uint32_t i = 0; i < size; i++ ) {
    uint8_t x = *(a_bytes + i) ^ *(b_bytes + i);
    *(out + i) = to_hex( x );
  }

  free( a_bytes );
  free( b_bytes );
}

// ------------------------------------
// to_hex
//  * turn byte into hex character
// ------------------------------------

char xor_char( char a, char b ) {
  uint8_t ret = parse_hex( a ) ^ parse_hex( b );

  return to_hex( ret );
}

// ------------------------------------
// xors a hex input string with a single byte
//  * takes input string two characters at a time
// ------------------------------------

void xor_single( char* in, uint32_t size, uint8_t key, char* out ) {
  uint8_t upper_key = (key & 0xF0) >> 4;
  uint8_t lower_key = key & 0x0F;

  for ( uint32_t i = 0; i < size; i += 2 ) {
    uint8_t upper = parse_hex( *(in + i) );
    uint8_t lower = parse_hex( *(in + i + 1) );

    *(out + i) = to_hex( upper ^ upper_key );
    *(out + i + 1) = to_hex( lower ^ lower_key );
  }
}

// ------------------------------------
// xor_single_byte_byte
//  * input: byte array
//  * output: byte_array
//  * xors input array with a single byte key
// ------------------------------------

void xor_single_byte_byte(  uint8_t* in,
                            size_t size,
                            uint8_t key,
                            uint8_t* out )
{
  for ( size_t i = 0; i < size; i++ ) {
    *(out + i) = *(in + i) ^ key;
  }
}
