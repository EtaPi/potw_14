// c4.c Detect single-byte XOR

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "util.h"
#include "stats.h"
#include "freq.h"

typedef struct {
  char raw[61];
  uint8_t key;
  float freq_score;
} CHUNK;

int main() {
  uint32_t LINE_SIZE = 60;
  uint32_t NUM_LINES = 327;

  FILE* f = fopen("4.txt", "r");

  CHUNK in[327] = {{ {0}, 0xFF, FLT_MAX }};

  for ( size_t i = 0; i < NUM_LINES; i++ ) {
    CHUNK* next = &in[i];
    readline( f, next->raw );

    next->freq_score = break_xor_single_hex( next->raw, LINE_SIZE, &next->key );
  }

  // find min
  size_t min_index = 0;
  float min_score = FLT_MAX;

  for ( size_t i = 0; i < NUM_LINES; i++ ) {
    CHUNK next = in[i];

    if ( next.freq_score < min_score ) {
      min_index = i;
      min_score = next.freq_score;
    }
  }

  CHUNK solution = in[ min_index ];

  char dec[31] = {0};
  xor_single_hex_byte( solution.raw, LINE_SIZE, solution.key, (uint8_t* )dec );

  printf("Dec: %s, %f, %x\n", dec, solution.freq_score, solution.key );
}
