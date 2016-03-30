// runner.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "util.h"
#include "stats.h"

void answer( uint8_t result );
void testHexToBase64_NoPadding();
void testHexToBase64_OnePadding();
void testHexToBase64_TwoPadding();
void testXorBuffer();
void testXorSingle();
void testToByteArray();
void testXorSingleByteByte();
void testHisto();
void testScoreHistoSum();
void testCopy();
void testReadline();

int main() {
  testHexToBase64_NoPadding();
  testHexToBase64_OnePadding();
  testHexToBase64_TwoPadding();

  testXorBuffer();

  testXorSingle();

  testToByteArray();

  testXorSingleByteByte();

  testHisto();
  testScoreHistoSum();

  testCopy();

  testReadline();
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
  printf("testXorBuffer... \t\t\t\t");

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


void testToByteArray() {
  printf("testToByteArray... \t\t\t\t");

  char* in = "f00f";
  uint8_t expected[2] = { 0xF0, 0x0F };
  uint8_t* actual = calloc( 2, sizeof( char ) );

  to_byte_array(in, actual, 2);

  uint8_t equal = 1;
  for ( uint8_t i = 0; i < 2; i++ ) {
    if ( *(actual + i) != *(expected + i) ) {
      equal = 0;
    }
  }

  answer( equal );

  free( actual );
}

void testXorSingleByteByte() {
  printf("testXorSingleByteByte... \t\t\t");

  uint8_t in[2] = { 0xF0, 0x0F };
  uint8_t key = 0xFF;
  uint8_t expected[2] = { 0x0F, 0xF0 };
  uint8_t* actual = calloc( 2, sizeof( uint8_t ) );

  xor_single_byte_byte( in, 2, key, actual );

  uint8_t equal = 1;
  for ( size_t i = 0; i < 2; i++ ) {
    if ( *(actual + i) != *(expected + i) ) {
      equal = 0;
    }
  }

  answer( equal );

  free( actual );
}

void testHisto() {
  printf("testHisto... \t\t\t\t\t");

  char* in = "AaabBc";

  float expected[26] = {0};
  expected[0] = 3.0f / 6.0f;
  expected[1] = 2.0f / 6.0f;
  expected[2] = 1.0f / 6.0f;

  float actual[26] = {0};

  histo( in, 6, actual );

  uint8_t equal = 1;
  for ( uint8_t i = 0; i < 26; i++ ) {
    if ( *(actual + i) != *(expected + i) ) {
      printf("index: %d:%f:%f\n", i, actual[i], expected[i] );
      equal = 0;
    }
  }

  answer( equal );
}

void testScoreHistoSum() {
  printf("testScoreHisto... \t\t\t\t");

  float in_a[27] = { 1.0f,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0.5f, 1.0f };
  float in_b[27] = { 0.5f,0.25f,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0.25f, 1.0f };

  float expected = 1.0f;

  float actual = score_histo_sum( in_a, in_b );

  if (actual != expected) answer( 0 );
  else answer( 1 );
}

void testCopy() {
  printf("testCopy... \t\t\t\t\t");

  char in[4] = "ABCD";
  char out[4] = {0};

  copy( in, out, 4 );

  uint8_t result = compare( in, out, 4);
  answer( result );
}

void testReadline() {
  printf("testReadline... \t\t\t\t");

  FILE* f = fopen("4.txt", "r");
  char* expected = "0e3647e8592d35514a081243582536ed3de6734059001e3f535ce6271032";
  char actual[60];

  readline( f, actual );

  uint8_t result = compare( actual, expected, 60 );
  answer( result );
}
