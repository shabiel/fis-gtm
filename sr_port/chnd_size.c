#include "mdef.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "error.h"

void main(int argc, char *argv[])
{
  condition_handler ch;

  printf("sizeof chnd = %d, jmp_buf offset = %d\n",
                sizeof(ch), offsetof(condition_handler, jmp));
  exit(0);
}
