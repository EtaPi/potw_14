// runner_util.c Util methods for runners.

#include <stdint.h>
#include <stdio.h>

void answer( uint8_t result ) {
  if (result) printf("\x1b[39;49mPass\n");
  else        printf("\x1b[31mFail\n");
}
