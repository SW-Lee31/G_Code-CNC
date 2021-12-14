#include <SoftwareSerial.h>
#include <MsTimer2.h>
#define motStepPinX 2    //모터 아두이노 통신
#define motDirPinX 5     //모터 아두이노 통신
#define motStepPinY 3    //모터 아두이노 통신
#define motDirPinY 6     //모터 아두이노 통신
#define enable 8
#define ABORT A0  /* Abort input pin */
#define HOLD A1   /* Hold input pin */
#define RESUME A2 /* Resume input pin */
#define X_ENDSTOP 9   /* X axis endstop input pin */
#define Y_ENDSTOP 10  /* Y axis endstop input pin */
#define Z_ENDSTOP 11  /* Z axis endstop input pin */

SoftwareSerial BTSerial(13, 12);

char recv;
volatile char recv_str[200];
String str;
int Speed = 500;
int str1 = 0;
int str2 = 0;
int x;
int y;
bool x_ = true;
bool y_ = true;
int save1 = 0;
int save2 = 0;
int count = 0;
int timeout = 32000;
int smooth_x = 0;
int smoot_x = 1;

void setup() {
  Serial.begin(115200);
  BTSerial.begin(115200);
  Serial.println("Hello!");

  pinMode(enable, OUTPUT);
  pinMode(motStepPinX,OUTPUT); 
  pinMode(motDirPinX,OUTPUT);
  pinMode(motStepPinY,OUTPUT); 
  pinMode(motDirPinY,OUTPUT);

  pinMode(X_ENDSTOP, INPUT_PULLUP);
  pinMode(Y_ENDSTOP, INPUT_PULLUP);

  pinMode(ABORT, INPUT_PULLUP);
  pinMode(HOLD, INPUT_PULLUP);
  pinMode(RESUME, INPUT_PULLUP);
  digitalWrite(enable, LOW);

   MsTimer2::set(1, xaxis);
   MsTimer2::start();

}

void loop() {
  if(recvMsg(timeout) == 0)
  {
    str = recv_str;
    
    int first = str.indexOf("/");
    int length = str.length();

    save1 = str1;
    save2 = str2;
  
    str1 = (str.substring(0, first)).toInt()*2;
    str2 = (str.substring(first+1, length)).toInt()*2;
//    Serial.print("X좌표: ");
//    Serial.println(str1);
//    Serial.print("Y좌표: ");
//    Serial.println(str2);
//    Serial.print(x);
//    Serial.print(" / ");
//    Serial.println(y);
  }
  //else Serial.println("OK");

  if(count < 50)
  {
    if(abs(save1-str1) > 50) x_ = false;
    else x_ = true;
    
    if(abs(save2-str2) > 50) y_ = false;
    else y_ = true;
    
    count++;
  }
  else{
    x_ = true;
    y_ = true;
  }

//  if(str1 > x && x != str1 && x_ && y_){
//    digitalWrite(motDirPinX, HIGH); // 모터 방향 설정. HIGH = 시계, LOW = 반시계
//    if(smoot_x == 0){
//      for(int i = 1; i < 4; i++) { // x스텝만큼 이동
//        digitalWrite(motStepPinX,HIGH);  //1
//        delayMicroseconds(800-(100*i));        //스텝
//        digitalWrite(motStepPinX,LOW);   //이동
//        delayMicroseconds(800-(100*i));        //딜레이down = 속도 증가
//      }
//      smoot_x = 1;
//    }
//    else if(smoot_x == 1){
//      if(x < str1-6){
//        for(x = x; x<str1-4; x++) { // x스텝만큼 이동
//          digitalWrite(motStepPinX,HIGH);  //1
//          delayMicroseconds(Speed);        //스텝
//          digitalWrite(motStepPinX,LOW);   //이동
//          delayMicroseconds(Speed);        //딜레이down = 속도 증가
//        }
//      }
//      smoot_x = 2;
//    }
//    else if(smoot_x == 2){
//      for(int i = 1; i < 4; i++) { // x스텝만큼 이동
//        digitalWrite(motStepPinX,HIGH);  //1
//        delayMicroseconds(Speed+(100*i));        //스텝
//        digitalWrite(motStepPinX,LOW);   //이동
//        delayMicroseconds(Speed+(100*i));        //딜레이down = 속도 증가
//      }
//      smoot_x = 0;
//      x = str1;
//    }
//
//    count = 0;
//    //Serial.println(x/16);
//  }
//  else if(str1 < x && x != str1 && x_ && y_){
//    digitalWrite(motDirPinX, LOW); // 모터 방향 설정. HIGH = 시계, LOW = 반시계
//    for(x = x; x > str1; x--) {
//      digitalWrite(motStepPinX,HIGH);  //1
//      delayMicroseconds(Speed);        //스텝
//      digitalWrite(motStepPinX,LOW);   //이동
//      delayMicroseconds(Speed);        //딜레이down = 속도 증가
//    }
//    count = 0;
//    //Serial.println(x/16);
//  }
  
//  if(smooth_x == 1){
//    digitalWrite(motDirPinX, HIGH); // 모터 방향 설정. HIGH = 시계, LOW = 반시계
//    for(int i = 1; i < 6; i++) { // x스텝만큼 이동
//      digitalWrite(motStepPinX,HIGH);  //1
//      delayMicroseconds(Speed+(100*i));        //스텝
//      digitalWrite(motStepPinX,LOW);   //이동
//      delayMicroseconds(Speed+(100*i));        //딜레이down = 속도 증가
//    }
//    smooth_x = 0;
//  }
//  else if(smooth_x == -1){
//    digitalWrite(motDirPinX, LOW); // 모터 방향 설정. HIGH = 시계, LOW = 반시계
//    for(int i = 1; i < 6; i++) { // x스텝만큼 이동
//    digitalWrite(motStepPinX,HIGH);  //1
//    delayMicroseconds(Speed+(100*i));        //스텝
//    digitalWrite(motStepPinX,LOW);   //이동
//    delayMicroseconds(Speed+(100*i));        //딜레이down = 속도 증가
//    }
//    smooth_x = 0;
//  }
}


int recvMsg(int timeout)
{
  int time = 0;
  char i;
  
  i = 0;
  while(1)
  {
    if(BTSerial.available())
    {
      recv_str[i] = char(BTSerial.read());
      i++;
      break;
    }
    time++;
    if(time > timeout) return -1;
  }
  delay(10);
  while(BTSerial.available() && (i < 200))
  {                                              
    recv_str[i] = char(BTSerial.read());
    i++;
  }
  #if NLCR    
  recv_str[i-2] = '\0';       //discard two character \n\r
  #else
  recv_str[i] = '\0';
  #endif
  return 0;
}

void xaxis(){
  cli();
  if(str1 > x && x != str1 && x_ && y_){
    digitalWrite(motDirPinX, HIGH); // 모터 방향 설정. HIGH = 시계, LOW = 반시계
    if(smoot_x == 0){
      for(int i = 1; i < 11; i++) { // x스텝만큼 이동
        digitalWrite(motStepPinX,HIGH);  //1
        delayMicroseconds(1500-(100*i));        //스텝
        digitalWrite(motStepPinX,LOW);   //이동
        delayMicroseconds(1500-(100*i));        //딜레이down = 속도 증가
      }
      smoot_x = 1;
    }
    else if(smoot_x == 1){
      if(x < str1-6){
        for(x = x; x<str1-4; x++) { // x스텝만큼 이동
          digitalWrite(motStepPinX,HIGH);  //1
          delayMicroseconds(Speed);        //스텝
          digitalWrite(motStepPinX,LOW);   //이동
          delayMicroseconds(Speed);        //딜레이down = 속도 증가
        }
      }
      smoot_x = 2;
    }
    else if(smoot_x == 2){
      for(int i = 1; i < 11; i++) { // x스텝만큼 이동
        digitalWrite(motStepPinX,HIGH);  //1
        delayMicroseconds(Speed+(100*i));        //스텝
        digitalWrite(motStepPinX,LOW);   //이동
        delayMicroseconds(Speed+(100*i));        //딜레이down = 속도 증가
      }
      smoot_x = 0;
      x = str1;
    }

    count = 0;
    //Serial.println(x/16);
  }
  else if(str1 < x && x != str1 && x_ && y_){
    digitalWrite(motDirPinX, LOW); // 모터 방향 설정. HIGH = 시계, LOW = 반시계
    for(x = x; x > str1; x--) {
      digitalWrite(motStepPinX,HIGH);  //1
      delayMicroseconds(Speed);        //스텝
      digitalWrite(motStepPinX,LOW);   //이동
      delayMicroseconds(Speed);        //딜레이down = 속도 증가
    }
    count = 0;
    //Serial.println(x/16);
  }
  sei();
}

void yaxis(){
  if(str2 > y && y != str2 && x_ && y_){
    digitalWrite(motDirPinY, HIGH); // 모터 방향 설정. HIGH = 시계, LOW = 반시계
    for(y = y; y<str2; y++) { // y스텝만큼 이동
      digitalWrite(motStepPinY,HIGH);  //1
      delayMicroseconds(Speed);        //스텝
      digitalWrite(motStepPinY,LOW);   //이동
      delayMicroseconds(Speed);        //딜레이down = 속도 증가
    }
    //Serial.println(y);
  }
  else if(str2 < y && y != str2 && x_ && y_){
    digitalWrite(motDirPinY, LOW); // 모터 방향 설정. HIGH = 시계, LOW = 반시계
    for(y = y; y > str2; y--) {
      digitalWrite(motStepPinY,HIGH);  //1
      delayMicroseconds(Speed);        //스텝
      digitalWrite(motStepPinY,LOW);   //이동
      delayMicroseconds(Speed);        //딜레이down = 속도 증가
    }
    //Serial.println(y/16);
  }
}
