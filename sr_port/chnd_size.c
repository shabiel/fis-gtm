#include "mdef.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "error.h"

int main(int argc, char *argv[])
{
  condition_handler ch;

  printf("sizeof chnd = %ld, jmp_buf offset = %ld\n",
                sizeof(ch), offsetof(condition_handler, jmp));
  exit(0);
}
