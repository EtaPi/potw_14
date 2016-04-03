// util.h

#pragma once

#include <stdio.h>

// ------------------------------------
// compare
//  * compare two equal length string buffers
//  * return 1 on equality, 0 otherwise
// ------------------------------------

uint8_t compare( char* a, char* b, uint32_t size );

// ------------------------------------
// copy from on buffer to another in bytes
// ------------------------------------

void copy( void* a, void* b, uint32_t bytes );

// ------------------------------------
// encode_base64
//  * in: hex string
//  * size: length of input string
//  * out: base64 output
// ------------------------------------

void encode_base64( char* in, uint32_t size, char* out );

// ------------------------------------
// nibble_to_byte
// ------------------------------------

uint8_t nibbles_to_byte( uint8_t a, uint8_t b );

// ------------------------------------
// parse_hex
//  * convert hex character into byte
// ------------------------------------

uint8_t parse_hex( char in );

// ------------------------------------
// readline
//  * input: FILE pointer
//  * returns number of chars readline
// ------------------------------------

size_t readline( FILE* in, char* out );

// ------------------------------------
// to_nibble_array
//  * convert hex string into its byte array
// ------------------------------------

uint8_t* to_nibble_array( char* hex, uint32_t size );

// ------------------------------------
// to_byte_array
//  * convert hex string into byte array
//  * size: num of chars in input hex string
// ------------------------------------

void to_byte_array( char* hex, uint8_t* out, size_t out_size );

// ------------------------------------
// to_hex
//  * turn byte into hex character
// ------------------------------------

char to_hex( uint8_t in );

// ------------------------------------
// xor two equal length hex strings
// ------------------------------------

void xor_buffer( char* a, char* b, uint32_t size, char* out );

// ------------------------------------
// xors two hex characters
//  * return: hex character
// ------------------------------------

char xor_char( char a, char b );

// ------------------------------------
// xors a hex input string with a single byte
//  * takes input string two characters at a time
// ------------------------------------

void xor_single( char* in, uint32_t size, uint8_t key, char* out );

// ------------------------------------
// xor_single_hex_byte
//  * input: hex string
//  * output: byte_array
//  * xors input string with a single byte key
// ------------------------------------

void xor_single_hex_byte(  char* in, size_t size, uint8_t key, uint8_t* out );

// ------------------------------------
// xor_single_byte_byte
//  * input: byte array
//  * output: byte_array
//  * xors input array with a single byte key
// ------------------------------------

void xor_single_byte_byte(  uint8_t* in, size_t size, uint8_t key, uint8_t* out );
