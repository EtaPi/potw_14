// c5.c Repeating key XOR Cipher

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

size_t BLOCK_SIZE = 32;

int main( int argc, char** argv ) {
  if (argc != 4) {
    printf("Usage: c5 <input file> <output file> <key>\n");
  }

  // input file
  char* input_name = argv[1];

  FILE* f_in = fopen( input_name, "rb" );

  if (NULL == f_in) {
    printf("Input file not found.\n");
    return 1;
  }

  // key
  char* key = argv[3];
  uint8_t key_size = strlen( key );

  // output file
  char* output_name = argv[2];

  FILE* f_out = fopen( output_name, "wb" );

  if (NULL == f_out) {
    printf("Error opening output file.");
    return 2;
  }

  // encrypt
  uint8_t* tmp = calloc( BLOCK_SIZE, sizeof( uint8_t ) );
  size_t check = fread( tmp, BLOCK_SIZE, 1, f_in );

  if (check != BLOCK_SIZE) {
    if ( feof(f_in) ) {

    } else {
      // read error?
    }
  }






}
