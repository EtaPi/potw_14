// freq.h

#pragma once

#include <stdint.h>
#include <stdlib.h>

// ------------------------------------
// score_hex: score the output of decrypting the string with the given key
//    regarding english frequency
//  * input: string in hex
//  * input: byte key
// ------------------------------------

float score_hex( char* in, size_t size, uint8_t key );

// ------------------------------------
// break_xor_single_hex: find the key yielding the lowest freq score
//  * input: string in hex
// ------------------------------------

float break_xor_single_hex( char* in, size_t size, uint8_t* out_key );
