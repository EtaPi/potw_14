// runner_util.c Util methods for runners.

#include <stdint.h>
#include <stdio.h>

#include "runner_util.h"

void answer( uint8_t result ) {
  if (result) printf("Pass\n");
  else        printf("\x1b[31mFail\x1b[39;49m\n");
}
