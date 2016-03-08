// util.h

#pragma once

// ------------------------------------
// compare
//  * compare two equal length string buffers
//  * return 1 on equality, 0 otherwise
// ------------------------------------

uint8_t compare( char* a, char* b, uint32_t size );

// ------------------------------------
// encode_base64
//  * in: hex string
//  * size: length of input string
//  * out: base64 output
// ------------------------------------

void encode_base64( char* in, uint32_t size, char* out );

// ------------------------------------
// parse_hex
//  * convert hex character into byte
// ------------------------------------

uint8_t parse_hex( char in );

// ------------------------------------
// to_byte_array
//  * convert hex string into its byte array
// ------------------------------------

uint8_t* to_byte_array( char* hex, uint32_t size );

// ------------------------------------
// to_hex
//  * turn byte into hex character
// ------------------------------------

char to_hex( uint8_t in );

// ------------------------------------
// to_hex
//  * turn byte into hex character
// ------------------------------------

char xor_char( char a, char b );
