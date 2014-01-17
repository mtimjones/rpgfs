#include <stdio.h>
#include <time.h>
#include "rpgtypes.h"

int main()
{

  srand(time(NULL));

  printf("Building the Filesystem...\n");
  rpginit();

  performShell();

  return 0;
}

