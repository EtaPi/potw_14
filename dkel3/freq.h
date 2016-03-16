// freq.h

#pragma once

#include <stdint.h>
#include <stdlib.h>

// ------------------------------------
// score_string: score the output of decrypting the string with the given key
//    regarding english frequency
//  * input: string in hex
//  * input: byte key
// ------------------------------------

float score_hex( char* in, size_t size, uint8_t key );
