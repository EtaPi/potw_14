// runner.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "util.h"

void answer( uint8_t result );
void testHexToBase64_NoPadding();
void testHexToBase64_OnePadding();
void testHexToBase64_TwoPadding();

int main() {
  testHexToBase64_NoPadding();
  testHexToBase64_OnePadding();
  testHexToBase64_TwoPadding();
}

void answer( uint8_t result ) {
  if (result) printf("Pass\n");
  else        printf("Fail\n");
}

void testHexToBase64_NoPadding() {
  printf("testHexToBase64_NoPadding... \t\t\t");

  char* in = "affaaf";
  char* expected = "r/qv";
  char* actual = calloc( 6, sizeof( char ) );

  encode_base64( in, 6, actual );

  uint8_t result = compare( actual, expected, 4 );
  answer( result );

  free( actual );
}

void testHexToBase64_OnePadding() {
  printf("testHexToBase64_OnePadding... \t\t\t");

  char* in = "affa";
  char* expected = "r/o=";
  char* actual = calloc( 4, sizeof( char ) );

  encode_base64( in, 4, actual );

  uint8_t result = compare( actual, expected, 4 );
  answer( result );

  free( actual );
}

void testHexToBase64_TwoPadding() {
  printf("testHexToBase64_TwoPadding... \t\t\t");

  char* in = "af";
  char* expected = "rw==";
  char* actual = calloc( 4, sizeof( char ) );

  encode_base64( in, 2, actual );

  uint8_t result = compare( actual, expected, 4 );
  answer( result );

  free( actual );
}
