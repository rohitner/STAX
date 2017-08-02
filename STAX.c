#include <stdio.h>
#include <stdlib.h>
#include "stax.h"

void main() {
  char **model=init_stax(model);
  print(model);
  char out[4];
  printf("Enter the required sequence.\n");
  int temp;
  scanf("%d",&temp);
  for(int i=0;i<4;i++)
  {
    scanf("%c",&out[i]);
  }
  for(int i=0;i<4;i++)
  {
    printf("%c ",out[i]);
  }printf("\n");
  move(model,'M','L');
  move(model,'M','L');
  move(model,'M','R');
  move(model,'M','R');
  if(model[0][1]==out[0] || model[2][1]==out[0])
  {
    if(model[0][1]==out[0])
    {
      move(model,'R','M');
    }
    else move(model,'L','M');
  }
  else
  {
    if(model[2][0]==out[0])
    {
      move(model,'L','R');
      move(model,'L','M');
    }
    else if(model[0][0]==out[0])
    {
      move(model,'R','L');
      move(model,'R','M');
    }
  }
  if(model[0][0]!=' ' && model[2][0]!=' ')
  {
    if(model[0][1]==' ')
    {
      if(model[0][0]==out[1])
      {
        move(model,'R','M');
      }
      else if(model[2][1]==out[1])
      {
        move(model,'L','M');
      }
      else
      {
        move(model,'L','R');
        move(model,'L','M');
      }
    }
    if(model[2][1]==' ')
    {
      if(model[2][0]==out[1])
      {
        move(model,'L','M');
      }
      else if(model[0][1]==out[1])
      {
        move(model,'R','M');
      }
      else
      {
        move(model,'R','L');
        move(model,'R','M');
      }
    }
  }
  else if(model[0][0]==' ')
  {
    if(model[2][2]==out[1])
    {
      move(model,'L','M');
    }
    else if(model[2][1]==out[1])
    {
      move(model,'L','R');
      move(model,'L','M');
    }
    else
    {
      move(model,'L','R');
      move(model,'L','R');
      move(model,'L','M');
    }
  }
  else if(model[2][0]==' ')
  {
    if(model[0][2]==out[1])
    {
      move(model,'R','M');
    }
    else if(model[0][1]==out[1])
    {
      move(model,'R','L');
      move(model,'R','M');
    }
    else
    {
      move(model,'R','L');
      move(model,'R','L');
      move(model,'R','M');
    }
  }
  if(model[0][0]==' ' || model[2][0]==' ')
  {
    if(model[0][0]==' ')
    {
      if(model[2][1]==out[2])
      {
        move(model,'L','M');
        move(model,'L','M');
        return;
      }
      else
      {
        move(model,'L','R');
        move(model,'L','M');
        move(model,'R','M');
        return;
      }
    }
    if(model[2][0]==' ')
    {
      if(model[0][1]==out[2])
      {
        move(model,'R','M');
        move(model,'R','M');
        return;
      }
      else
      {
        move(model,'R','L');
        move(model,'R','M');
        move(model,'L','M');
        return;
      }
    }
  }
  else
  {
    if(model[0][0]==out[2])
    {
      move(model,'R','M');
      move(model,'L','M');
      return;
    }
    else
    {
      move(model,'L','M');
      move(model,'R','M');
      return;
    }
  }
}
