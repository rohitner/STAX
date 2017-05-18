#include <stdio.h>
#include <stdlib.h>
#include "stax.h"

void main() {
  char **model=init_stax(model);
  print(model);
  while(1)
  {
    char s1,s2,temp;
    scanf("%c%c%c",&temp,&s1,&s2);
    move(model,s1,s2);
  }
}
