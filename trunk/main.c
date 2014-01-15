#include <stdio.h>
#include <time.h>
#include "rpgtypes.h"

int main()
{

  srand(time(NULL));

  printf("Building the Filesystem...\n");
  rpginit();

  printf("Populating the tree...\n");

  printf("Starting the shell...\n");

  performShell();

  return 0;
}

