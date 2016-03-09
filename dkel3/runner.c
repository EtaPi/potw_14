// runner.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "util.h"

void answer( uint8_t result );
void testHexToBase64_NoPadding();
void testHexToBase64_OnePadding();
void testHexToBase64_TwoPadding();
void testXorBuffer();
void testXorSingle();

int main() {
  testHexToBase64_NoPadding();
  testHexToBase64_OnePadding();
  testHexToBase64_TwoPadding();

  testXorBuffer();

  testXorSingle();
}

void answer( uint8_t result ) {
  if (result) printf("\x1b[39;49mPass\n");
  else        printf("\x1b[31mFail\n");
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

void testXorBuffer() {
  printf("testXor... \t\t\t\t\t");

  char* in1 = "1c0111001f010100061a024b53535009181c";
  char* in2 = "686974207468652062756c6c277320657965";
  char* expected = "746865206b696420646f6e277420706c6179";
  char* actual = calloc( 36, sizeof( char ) );

  xor_buffer( in1, in2, 36, actual );

  uint8_t result = compare( actual, expected, 36 );
  answer( result );

  free( actual );
}

void testXorSingle() {
  printf("textXorSingle... \t\t\t\t");

  char* in = "f00f";
  uint8_t key = 0xFF;
  char* expected = "0ff0";
  char* actual = calloc( 4, sizeof( char ) );

  xor_single( in, 4, key, actual );

  uint8_t result = compare( actual, expected, 4 );
  answer( result );

  free( actual );
}
