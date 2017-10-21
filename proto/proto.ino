//__________________________________________color sensor variables
#define S0 44
#define S1 42
#define S2 6
#define S3 7
#define sensorOut 8
#define OE 40
int frequency = 0;
int rgb[3]={1000,1000,1000};
int pick=0;
//__________________________________________traversal variables
#define rf 14
#define rb 15
#define lf 10
#define lb 11
#define en1 4
#define en2 5
#define gpf 30
#define gpl 31 
char curr;
//__________________________________________line follower variables
int s0 = 0;
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;
int s6 = 0;
void detect(int* rgb);
void pickblock(){
  pick=1;
  Serial.print("pickblock");
  digitalWrite(rf,LOW);
  digitalWrite(rb,LOW);
  digitalWrite(lf,LOW); 
  digitalWrite(lb,LOW);
  digitalWrite(gpf,HIGH);
  digitalWrite(gpl,LOW);
  delay(2000);
}
void dropblock(){
  pick=0;
  digitalWrite(gpf,LOW);
  digitalWrite(gpl,HIGH);
  delay(100);
  digitalWrite(gpl,LOW);
}
void cl(){
  Serial.print("clockwise");
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
  Serial.println("gogogogogogogo");
  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH); 
  digitalWrite(rf,HIGH);
  digitalWrite(lf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
   delay(900);
  align();
}
void align(){
  s1 = analogRead(0);//Signal pin 2 on the board
  Serial.print(" ");
  Serial.print(s1);
  s5 = analogRead(6);//Signal pin 6 on the board
  Serial.print(" ");
  Serial.println(s5);
  detect(rgb);
  if((rgb[0]>400 && rgb[1]>400 && rgb[2]>400) || pick==1){
  if(s1>400 && s5<400)//Move right
  {
    Serial.print(" RIGHT");
    digitalWrite(rf,HIGH);
    digitalWrite(rb,LOW);
    digitalWrite(lf,LOW);
    digitalWrite(lb,HIGH);
  }

  else if(s5>400 && s1<400)//Move left
  {

    Serial.print(" LEFT");
    digitalWrite(rf,LOW);
    digitalWrite(rb,HIGH);
    digitalWrite(lf,HIGH);
    digitalWrite(lb,LOW);
  }
  else if((s1>400 && s5>400))//Stop if all the sensors give low or block detected
  {
    Serial.println(" STOP");
    digitalWrite(rf,LOW);
    digitalWrite(lf,LOW);
    digitalWrite(lb,LOW);
    digitalWrite(rb,LOW);
    return;
  }
  else
  {
    Serial.println(" FORWARD");
    digitalWrite(rf,HIGH);
    digitalWrite(lf,HIGH);
    digitalWrite(lb,LOW);
    digitalWrite(rb,LOW);
  }
  align();}
  else{
    rgb[0]=1000;rgb[1]=1000;rgb[2]=1000;
  }
}
void alignback(){
  Serial.println("alignback");
  digitalWrite(rf,LOW);
  digitalWrite(lf,LOW);
  digitalWrite(lb,HIGH);
  digitalWrite(rb,HIGH);
  s1 = analogRead(0);//Signal pin 2 on the board
  Serial.print(" ");
  Serial.print(s1);
  s5 = analogRead(6);//Signal pin 6 on the board
  Serial.print(" ");
  Serial.print(s5);
  if(s5>400 && s1<400)//Move left
  {
    Serial.println(" LEFT");
    digitalWrite(rf,HIGH);
    digitalWrite(rb,LOW);
    digitalWrite(lf,LOW);
    digitalWrite(lb,HIGH);
  }

  else if(s1>400 && s5<400)//Move right
  {
    Serial.println(" RIGHT");
    digitalWrite(rf,LOW);
    digitalWrite(rb,HIGH);
    digitalWrite(lf,HIGH);
    digitalWrite(lb,LOW);
  }
  else if(s1>400 && s5>400)//Stop if all the sensors give low
  {
    Serial.println(" STOP");
    digitalWrite(rf,LOW);
    digitalWrite(lf,LOW);
    digitalWrite(lb,LOW);
    digitalWrite(rb,LOW);
    Serial.println("beforereturn");
    return;
  }
  else
  {
    Serial.println(" BACKWARD");
    digitalWrite(rf,LOW);
    digitalWrite(lf,LOW);
    digitalWrite(lb,HIGH);
    digitalWrite(rb,HIGH);
  }
  delay(50);
  alignback();
  
}
void detect(int* rgb){
  Serial.println("detectdetect");
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
  rgb[1]=frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing GREEN color frequency
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
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  //__________________________________________TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(OE, OUTPUT);
  pinMode(gpf, OUTPUT);
  pinMode(gpl, OUTPUT);
  //__________________________________________Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(OE,LOW);
  //__________________________________________bot detects final sequence
  char out[4];
  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH);
  digitalWrite(rf,HIGH);
  digitalWrite(lf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  align();
  Serial.println("CHECKPOINT1");
  go();
  Serial.println("CHECKPOINT2");
  pickblock();
  Serial.println("CHECKPOINT3");
  alignback();
  Serial.println("CHECKPOINT4");
  cl();
  Serial.println("CHECKPOINT5");
  go();
  Serial.println("CHECKPOINT6");
  dropblock();
  Serial.println("end");
  
}
void loop(){
  
 }

