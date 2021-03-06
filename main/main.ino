//__________________________________________color sensor variables
#define S0 44
#define S1 42
#define S2 6
#define S3 7
#define sensorOut 8
#define OE 40
int frequency = 0;
int rgb[3];
//__________________________________________traversal variables
#define rf 12
#define rb 13
#define lf 10
#define lb 11
#define gp 3
char curr;
//__________________________________________line follower variables
int s0 = 0;
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;
int s6 = 0;
//__________________________________________definitions
char** init_stax(char** model){
  char in[4];
  Serial.print("Enter the initial sequence.\n");
  in[0]='A',in[1]='C',in[2]='C',in[3]='D';
  //__________________________________________this will be given

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

void goback(){
  while(1){
    alignback();
  }
}
void pickblock(){
  digitalWrite(gp,HIGH);
}
void dropblock(){
  digitalWrite(gp,LOW);
}
void cl(){
  digitalWrite(rf,LOW);
  digitalWrite(rb,HIGH);
  digitalWrite(lf,HIGH);
  digitalWrite(lb,LOW);
  delay(2000);     //calibrate we can't use line follower for this
  digitalWrite(rb,LOW);
  digitalWrite(lf,LOW);
}
void cc(){
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lf,LOW);
  digitalWrite(lb,HIGH);
  delay(2000);      //calibrate we can't use line follower for this
  digitalWrite(rf,LOW);
  digitalWrite(lb,LOW);
}
void go(){
  while(rgb[0]>1000 && rgb[1]>1000 && rgb[2]>1000)
  {
    align();
  }
  digitalWrite(rf,LOW);
  digitalWrite(lf,LOW);
}
void align(){
  s1 = analogRead(1);//Signal pin 2 on the board
  Serial.print(" "+s1);
  s5 = analogRead(5);//Signal pin 6 on the board
  Serial.print(" "+s5);
  if(s1>800)//Move right
  {
    Serial.print(" RIGHT");
    digitalWrite(rf,HIGH);
    digitalWrite(rb,LOW);
    digitalWrite(lf,LOW);
    digitalWrite(lb,HIGH);
  }

  if(s5>800)//Move left
  {

    Serial.print(" LEFT");
    digitalWrite(rf,LOW);
    digitalWrite(rb,HIGH);
    digitalWrite(lf,HIGH);
    digitalWrite(lb,LOW);
  }
  if(s1>800 && s5>800)//Stop if all the sensors give low
  {
    Serial.println(" STOP");
    digitalWrite(rf,LOW);
    digitalWrite(lf,LOW);
    digitalWrite(lb,LOW);
    digitalWrite(rb,LOW);
  }
}
void alignback(){
  s1 = analogRead(1);//Signal pin 2 on the board
  Serial.print(" "+s1);
  s5 = analogRead(5);//Signal pin 6 on the board
  Serial.print(" "+s5);
  if(s1>800)//Move right
  {
    Serial.print(" LEFT");
    digitalWrite(rf,LOW);
    digitalWrite(rb,HIGH);
    digitalWrite(lf,HIGH);
    digitalWrite(lb,LOW);
  }

  if(s5>800)//Move left
  {
    Serial.print(" RIGHT");
    digitalWrite(rf,HIGH);
    digitalWrite(rb,LOW);
    digitalWrite(lf,LOW);
    digitalWrite(lb,HIGH);
  }
  if(s1>800 && s5>800)//Stop if all the sensors give low
  {
    Serial.println(" STOP");
    digitalWrite(rf,LOW);
    digitalWrite(lf,LOW);
    digitalWrite(lb,LOW);
    digitalWrite(rb,LOW);
  }
}
void detect(){
  
}
char** move(char **model,char s1,char s2){
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
  int i=0;
  while(model[i1][i]!=" ")
  {
    i++;
  }
  int j=0;
  while(model[i2][j]!=" ")
  {
    j++;
  }
  model[i2][++j]=model[i1][i];
  model[i1][i]=" ";
  //-----------------------------
  //convert s1 to 0,1,2 for model and same for s2
  //model[s1]--;
  //model[s2]++
  //-----------------------------
  char c=curr;
  if(c=='S') go();          //takes bot until node
  curr='M';
  c=curr;
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
void setup(){
  //__________________________________________line follower
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);
  //__________________________________________traversal
  pinMode(rf, OUTPUT);
  pinMode(rb, OUTPUT);
  pinMode(lf, OUTPUT);
  pinMode(lb, OUTPUT);
  //__________________________________________TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(OE, OUTPUT);
  //__________________________________________Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(OE,LOW);
  //__________________________________________bot detects final sequence
  char out[4];
  digitalWrite(rf,HIGH);
  digitalWrite(lf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  align();
//  detect(out);         //_____________________4 times
  char **model=init_stax(model);
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
void loop(){
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
  s0 = analogRead(0);//Signal pin 1 on the board
  Serial.print(" "+s0);
  s1 = analogRead(1);//Signal pin 2 on the board
  Serial.print(" "+s1);
  s2 = analogRead(2);//Signal pin 3 on the board
  Serial.print(" "+s2);
  s3 = analogRead(3);//Signal pin 4 on the board
  Serial.print(" "+s3);
  s4 = analogRead(4);//Signal pin 5 on the board
  Serial.print(" "+s4);
  s5 = analogRead(5);//Signal pin 6 on the board
  Serial.print(" "+s5);
  s6 = analogRead(6);//Signal pin 6 on the board
  Serial.println(" "+s6);
 }
