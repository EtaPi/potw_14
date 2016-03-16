// c4.c Detect single-byte XOR

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "stats.h"

typedef struct {
  char raw[61];
  uint8_t key;
  float freq_score;
} CHUNK;

int main() {
  uint32_t LINE_SIZE = 60;
  uint32_t NUM_LINES = 327;

  FILE* f = fopen("4.txt", "r");

  CHUNK in[327] = {{ {0}, 0, 0 }};

  for ( uint32_t i = 0; i < NUM_LINES; i++ ) {
    CHUNK next = in[i];
    size_t count = readline( f, next.raw );
    //printf( "Chars: %zu: %s\n", count, next.raw );


  }




}
