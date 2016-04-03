// xor.c

#include "xor.h"

void cipher_xor_repeating(  uint8_t* in,
                            uint8_t* key,
                            size_t key_size,
                            size_t block_size,
                            uint8_t* out)
{
  for ( size_t i = 0; i < block_size; i++ ) {
    uint8_t key_index = i % key_size;

    *(out + i) = *(in + i) ^ *(key + key_index);
  }
}
