int mid = 0;
int mn = 0;
int mx = 0;

void setup()
{
Serial.begin(9600);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(A4,INPUT);
pinMode(A5,INPUT);
pinMode(A6,INPUT);
pinMode(12,OUTPUT);
}

void loop()
{

int s0 = 0;
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;
int s6 = 

s0 = analogRead(0);//Signal pin 1 on the board
s1 = analogRead(1);//Signal pin 2 on the board
s2 = analogRead(2);//Signal pin 3 on the board
s3 = analogRead(3);//Signal pin 4 on the board
s4 = analogRead(4);//Signal pin 5 on the board
s5 = analogRead(5);//Signal pin 6 on the board
s6 = analogRead(6);//Signal pin 6 on the board


Serial.print("Mid: ");
Serial.print(mid); 
Serial.print(" ");
Serial.print(s0); 
Serial.print(" ");
Serial.print(s1); 
Serial.print(" ");
Serial.print(s2); 
Serial.print(" ");
Serial.print(s3); 
Serial.print(" ");
Serial.print(s4); 
Serial.print(" ");
Serial.print(s5); 
Serial.print(" ");
Serial.print(s6); 
Serial.print(" ");
Serial.print(" ");



if((((s0+s1+s2)/3)>(((s6+s4+s5)/3)+240)))//Move right
{
Serial.print(" RIGHT");
digitalWrite(12,HIGH);
digitalWrite(13,LOW);
}

if((((s0+s1+s2)/3)<(((s6+s4+s5)/3)-240)))//Move left
{

Serial.print(" LEFT");
digitalWrite(12,LOW);
digitalWrite(13,HIGH);
}

if((s0 > mid)&&(s6 > mid))//Stop if all the sensors give low 

Serial.println(" STOP");

digitalWrite(12,LOW);
digitalWrite(13,LOW);

}


