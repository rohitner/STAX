char** init_stax(char** model)
{
  char in[4];
  printf("Enter the initial sequence.\n");
  for(int i=0;i<4;i++)
  {
    scanf("%c",&in[i]);
  }
  char temp;
  scanf("%c",&temp);
  char out[4];
  printf("Enter the actual sequence.\n");
  for(int i=0;i<4;i++)
  {
    scanf("%c",&out[i]);
  }
  model=(char**)malloc(3*sizeof(char*));
  for(int i=0;i<3;i++)
  {
    model[i]=(char*)malloc(4*sizeof(char));
  }
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<4;j++)
    {
      model[i][j]=' ';
    }
  }
  for(int i=0;i<4;i++)
  {
    model[1][i]=out[i];
  }
  return model;
}

void print(char **a)
{
  printf("--------\n");
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<4;j++)
    {
      printf("%c ",a[i][j]);
    }
    printf("\n");
  }
  printf("--------\n");
}

int detect(char **a,int index)
{
  for(int i=0;i<4;i++)
  {
    if(a[index][i]==' ')
    {
      return i;
    }
  }
}

int detectf(char **a,int index)
{
  for(int i=3;i>=0;i--)
  {
    if(a[index][i]!=' ')
    {
      return i;
    }
  }
}

char** move(char **a,char s1,char s2)
{
  if(s1==s2)
  {
    printf("invalid.\n");
  }
  else if(s1=='L')
  {
    if(s2=='M')
    {
      a[1][detect(a,1)]=a[2][detectf(a,2)];
      a[2][detectf(a,2)]=' ';
    }
    else if(s2=='R')
    {
      a[0][detect(a,0)]=a[2][detectf(a,2)];
      a[2][detectf(a,2)]=' ';
    }
  }
  else if(s1=='M')
  {
    if(s2=='L')
    {
      a[2][detect(a,2)]=a[1][detectf(a,1)];
      a[1][detectf(a,1)]=' ';
    }
    else if(s2=='R')
    {
      a[0][detect(a,0)]=a[1][detectf(a,1)];
      a[1][detectf(a,1)]=' ';
    }
  }
  else if(s1=='R')
  {
    if(s2=='M')
    {
      a[1][detect(a,1)]=a[0][detectf(a,0)];
      a[0][detectf(a,0)]=' ';
    }
    else if(s2=='L')
    {
      a[2][detect(a,2)]=a[0][detectf(a,0)];
      a[0][detectf(a,0)]=' ';
    }
  }
  print(a);
}
