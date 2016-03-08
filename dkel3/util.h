// util.h

#pragma once

uint8_t compare( char* a, char* b, uint32_t size );
void encode_base64( char* in, uint32_t size, char* out );
uint8_t parse_hex( char in );
uint8_t* to_byte_array( char* hex, uint32_t size );
char to_hex( uint8_t in );
