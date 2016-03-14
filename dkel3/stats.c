// stats.c

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "stats.h"

void histo( char* in, size_t size, float* out ) {
  for ( size_t i = 0; i < size; i++ ) {
    char next = *(in + i);

    if ( ((next & 0x60) == 0x40) || ((next & 0x60) == 0x60 )) {
      uint8_t lower = next & 0x1F;

      if (1 <= lower && lower <= 26) {
        out[ lower - 1 ]++;
      }
    }
  }

  // normalize
  for ( uint8_t i = 0; i < 26; i++ ) {
    *(out + i) /= (float)size;
  }
}

float score_histo_sum( float* a, float* b ) {
  float ret = 0;
  float diff = 0;
  for ( uint8_t i = 0; i < 26; i++ ) {
    diff = fabs( *(b + i) - *(a + i) );
    ret += diff;
  }

  return ret;
}

float english_freq[26] = {  .08167, .01492, .02782, .04253, .12702,
                            .02228, .02015, .06094, .06966, .00153,
                            .00772, .04025, .02406, .06749, .07507,
                            .01929, .00095, .05987, .06327, .09056,
                            .02758, .00978, .02361, .00150, .01974,
                            .00074 };
