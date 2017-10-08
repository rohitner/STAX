char curr;

char** init_stax(char** model)
{
  char in[4];
  Serial.print("Enter the initial sequence.\n");
  in[0]='A',in[1]='C',in[2]='C',in[3]='D';
  
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
    model[1][i]=in[i];
  }
  return model;
}

void gofront(){}
void pickblock(){}
void goback(){}
void cl(){}
void cc(){}
void go(){}
void dropblock(){}

char** move(char **a,char s1,char s2)
{
  //-----------------------------
  //convert s1 to 0,1,2 for model and same for s2
  //model[s1]--; if s1>1  
  //model[s2]++
  //-----------------------------
  char c=curr;
  if(c=='S') gofront();         //takes bot until node
  if(c==s1) pickblock();
  goback(); //take bot to node
  if(c!=s1)
  {
    if(c=='M')
    {
      if(s1=='L'){ cc();}        //counterclockwise
      else if(s1=='R'){ cl();}   //clockwise
    }
    if(c=='L')
    {
      if(s1=='M'){ cl();}       
      else if(s1=='R'){ cl();cl();} 
    }
    if(c=='R')
    {
      if(s1=='M'){ cc();}       
      else if(s1=='L'){ cc(); cc();}   
    }
    go();   //gountil stack comes in front
    pickblock();
    goback();
  }

  
  if(s1=='M')
  {
    if(s2=='L'){ cc();}       //counterclockwise
    else if(s2=='R'){ cl();}   //clockwise
  }
  if(s1=='L')
  {
    if(s2=='M'){ cl();}       
    else if(s2=='R'){ cl(); cl();} 
  }
  if(s1=='R')
  {
    if(s2=='M'){ cc();}       
    else if(s2=='L'){ cc(); cc();}   
  }
  go();
  dropblock();
  curr=s2;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  char **model=init_stax(model);
  char out[4];
  Serial.print("Enter the required sequence.\n");
  out[0]='A',out[1]='B',out[2]='C',out[3]='D';
  for(int i=0;i<4;i++)
  {
    Serial.print(model[0][i]);
  }Serial.print("\n");
  curr='S';
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

void loop() {
  // put your main code here, to run repeatedly:
  
}
