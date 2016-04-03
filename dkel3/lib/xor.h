// xor.h XOR cipher utilities

#include <stdlib.h>
#include <stdint.h>

#pragma once

// ------------------------------------
// apply repeating key XOR cipher
// ------------------------------------

void cipher_xor_repeating(  uint8_t* in,
                            uint8_t* key,
                            size_t key_size,
                            size_t block_size,
                            uint8_t* out);
