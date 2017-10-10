#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define OE 9
int frequency = 0;
int rgb[3];
#define rf 12
#define rb 13
#define lf 10
#define lb 11
#define gp 3
char curr;

char** init_stax(char** model)
{
  char in[4];
  Serial.print("Enter the initial sequence.\n");
  in[0]='A',in[1]='C',in[2]='C',in[3]='D';                  //this will be given
  
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

void gofront(){
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lf,HIGH);
  digitalWrite(lb,LOW);
  if(rgb[0]<300 && rgb[1]<300 && rgb[2]<300)
  {
    digitalWrite(rf,LOW);
    digitalWrite(lf,LOW);
  }
  goback();  
}
void pickblock(){
  digitalWrite(gp,HIGH);  
}
void goback(){
  digitalWrite(rf,LOW);
  digitalWrite(rb,HIGH);
  digitalWrite(lf,LOW);
  digitalWrite(lb,HIGH);
  if(rgb[0]<300 && rgb[1]<300 && rgb[2]<300)
  {
    digitalWrite(rb,LOW);
    digitalWrite(lb,LOW);
  }
  goback();
}
void cl(){
  digitalWrite(rf,LOW);
  digitalWrite(rb,HIGH);
  digitalWrite(lf,HIGH);
  digitalWrite(lb,LOW);
  delay(2000);
  digitalWrite(rb,LOW);
  digitalWrite(lf,LOW);  
}
void cc(){
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lf,LOW);
  digitalWrite(lb,HIGH);
  delay(2000);
  digitalWrite(rf,LOW);
  digitalWrite(lb,LOW);
}
void go(){
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lf,HIGH);
  digitalWrite(lb,LOW);
  while(rgb[0]<300 && rgb[1]<300 && rgb[2]<300)
  {
    digitalWrite(rf,LOW);
    digitalWrite(lf,LOW);
  }
  go();
}
void dropblock(){
  digitalWrite(gp,LOW);
}
void detect(char* out){
  int n=4;
  while(n)
  {
    if(rgb[0]<300 && rgb[1]<300 && rgb[2]<300)
    {
      if(rgb[0]<rgb[1] && rgb[0]<rgb[2])
      {
        out[0]='R';
      }
      else if(rgb[1]<rgb[2] && rgb[1]<rgb[0])
      {
        out[0]='G';
      }
      else if(rgb[2]<rgb[1] && rgb[2]<rgb[0])
      {
        out[0]='B';
      }
    }
  }
}

char** move(char **a,char s1,char s2)
{
  int i1,i2;
  switch(s1)
  {
    case 'R':i1=0;
      break;
    case 'M':i1=1;
      break;
    case 'L':i1=2;
      break;
  }
  switch(s2)
  {
    case 'R':i2=0;
      break;
    case 'M':i2=1;
      break;
    case 'L':i2=2;
      break;
  }
  
  //-----------------------------
  //convert s1 to 0,1,2 for model and same for s2
  //model[s1]--;  
  //model[s2]++
  //-----------------------------
  char c=curr;
  if(c=='S') gofront();          //takes bot until node
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
  pinMode(rf, OUTPUT);
  pinMode(rb, OUTPUT);
  pinMode(lf, OUTPUT);
  pinMode(lb, OUTPUT);
  //_______________________________________________________
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(OE, OUTPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(OE,LOW);
  //_______________________________________________________
  //bot detects final sequence
  char out[4];
  detect(out);         //4 times
  char **model=init_stax(model);
  Serial.print("Enter the required sequence.\n");
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
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  rgb[0]=frequency;
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing GREEN color frequency
  rgb[1]=frequency;
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing BLUE color frequency
  rgb[2]=frequency;
  Serial.println("  ");
  delay(100);  
}
