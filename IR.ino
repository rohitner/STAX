#define L3 A0
#define L2 A1
#define L1 A2
#define M A3
#define R1 A4
#define R2 A5
#define R3 A6

int thresh=512; //a value between 0 and 1023 which will differentiate betwen white and black

void setup() {
  // put your setup code here, to run once:
  pinMode(L3,INPUT);
  pinMode(L2,INPUT);
  pinMode(L1,INPUT);
  pinMode(M,INPUT);
  pinMode(R1,INPUT);
  pinMode(R2,INPUT);
  pinMode(R3,INPUT);
}

int* IR(int*a)
{
  a[0]=analogRead(L3);
  a[1]=analogRead(L2);
  a[2]=analogRead(L1);
  a[3]=analogRead(M);
  a[4]=analogRead(R1);
  a[5]=analogRead(R2);
  a[6]=analogRead(R3);
  return a;
}

void loop() {
  // put your main code here, to run repeatedly:
  int *a;
  a=(int*)malloc(8*sizeof(int));
  a=IR(a);
}
