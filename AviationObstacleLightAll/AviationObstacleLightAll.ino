#define RUN 1
#define STOP 0

char gOnOff = STOP;

void setup() {
  pinMode(3, OUTPUT); // PWM
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); // PWM
  pinMode(6, OUTPUT); // PWM
  pinMode(9, OUTPUT); // PWM
  pinMode(10, OUTPUT); // PWM
  pinMode(11, OUTPUT); // PWM
  pinMode(A0, INPUT);
  Serial.begin(115200);
}
void loop() {
  if(analogRead(A0) <= 600){
    gOnOff = RUN;
  } else {
    gOnOff = STOP;
  }
//LowLightRedAviationObstacleLight();
  MediumLightRedAviationObstacleLightA();
  MediumLightRedAviationObstacleLightB();
  HighLightAviationObstacleLight();    

  MediumLightRedAviationObstacleLightA2();
  MediumLightRedAviationObstacleLightA3();
  MediumLightRedAviationObstacleLightA4();

}

// 低光度赤色航空障害灯1
void LowLightRedAviationObstacleLight1(){
  if(gOnOff == STOP)
    digitalWrite(4,LOW);
  else
    digitalWrite(4,HIGH); 
}

// 低光度赤色航空障害灯2
void LowLightRedAviationObstacleLight2(){
  if(gOnOff == STOP)
    analogWrite(9, 0);
  else
    analogWrite(9,200); 
}


// 中光度赤色航空障害灯1
void MediumLightRedAviationObstacleLightA(){
  enum {
        ST_Init = 0,
        ST_On,
        ST_OnKeep,
        ST_Off,
        ST_OffKeep,
        ST_Stop,
  };
  const char LedPort = 3; 
  static uint32_t LastInputTimerTick;
  static int state = ST_Init;
  static int LightIntensity = 0;

  switch(state){
    case ST_Init:
            LastInputTimerTick = millis();
            state = 1;
            break;
    case ST_On:
            if(millis()-LastInputTimerTick >= 10 ){
              LightIntensity = LightIntensity + 4;
              if(LightIntensity >=255 ) {
                LightIntensity = 255;
                LastInputTimerTick = millis();
                state = 2;
                break;
              }
              LastInputTimerTick = millis();
              analogWrite(3, LightIntensity);
            }
            break;
      case ST_OnKeep:  
            if(millis()-LastInputTimerTick >= 50 ){
                state = 3;
            }
            break;
      case ST_Off:  
            if(millis()-LastInputTimerTick >= 10 ){
              LightIntensity = LightIntensity - 3;
              if(LightIntensity <= 2 ) {
                LightIntensity = 2;
                analogWrite(3, LightIntensity);
                state = 4;
                break;
              }
              LastInputTimerTick = millis();
              analogWrite(3, LightIntensity);
            }
            break;
      case ST_OffKeep:  
            if(millis()-LastInputTimerTick >= 200 ){
                state = 0;
            }
            break;
     default:
            break;
  }
}

// 中光度赤色航空障害灯2
void MediumLightRedAviationObstacleLightB(){
  enum {
        ST_Init = 0,
        ST_On,
        ST_OnKeep,
        ST_Off,
        ST_OffKeep,
        ST_Stop,
  };
  static uint32_t LastInputTimerTick;
  static int state =  ST_Init;

  switch(state){
    case ST_Init:
            digitalWrite(5, HIGH);
            LastInputTimerTick = millis();
            state = ST_On;
            break;
    case ST_On:
            if(millis()-LastInputTimerTick >= 1000 ){
              digitalWrite(5, LOW);
              LastInputTimerTick = millis();
              state = ST_Off;
            }
            break;

    case ST_Off:  
            if(millis()-LastInputTimerTick >= 650 ){
              digitalWrite(5, HIGH);
              LastInputTimerTick = millis();
              state = ST_On;
              }

            break;

     default:
            break;
  }
}


// 高光度航空障害灯
void HighLightAviationObstacleLight(){
  enum {
        ST_Init = 0,
        ST_On,
        ST_OnKeep,
        ST_Off,
        ST_OffKeep,
        ST_Stop,
  };
  static uint32_t LastInputTimerTick;
  static int state =  ST_Init;

  switch(state){
    case ST_Init:
            digitalWrite(6, HIGH);
            LastInputTimerTick = millis();
            state = ST_On;
            break;
    case ST_On:
            if(millis()-LastInputTimerTick >= 100 ){
              digitalWrite(6, LOW);
              LastInputTimerTick = millis();
              state = ST_Off;
            }
            break;

    case ST_Off:  
            if(millis()-LastInputTimerTick >= 1200 ){
              digitalWrite(6, HIGH);
              LastInputTimerTick = millis();
              state = ST_On;
              }

            break;

     default:
            break;
  }
}


// 中光度赤色航空障害灯1
void MediumLightRedAviationObstacleLightA2(){
  enum {
        ST_Init = 0,
        ST_Wait,
        ST_On,
        ST_OnKeep,
        ST_Off,
        ST_OffKeep,
        ST_Stop,
  };
  const char LedPort = 9; 
  static uint32_t LastInputTimerTick;
  static int state = ST_Init;
  static int LightIntensity = 0;
   static int RandomWait = 0;
   
  switch(state){
    case ST_Init:
            LastInputTimerTick = millis();
            RandomWait = random(1,10); 
Serial.println(RandomWait);
            state = ST_Wait;
            break;
    case ST_Wait:
            if(millis()-LastInputTimerTick >= RandomWait*100 ){
              state = ST_On;
Serial.println("ST_On");
            }
            break;
    case ST_On:
            if(millis()-LastInputTimerTick >= 10 ){
              LightIntensity = LightIntensity + 4;
              if(LightIntensity >=255 ) {
                LightIntensity = 255;
                LastInputTimerTick = millis();
                state = ST_OnKeep;
                break;
              }
              LastInputTimerTick = millis();
              analogWrite(LedPort, LightIntensity);
            }
            break;
      case ST_OnKeep:  
            if(millis()-LastInputTimerTick >= 50 ){
                state = ST_Off;
            }
            break;
      case ST_Off:  
            if(millis()-LastInputTimerTick >= 10 ){
              LightIntensity = LightIntensity - 3;
              if(LightIntensity <= 2 ) {
                LightIntensity = 2;
                analogWrite(LedPort, LightIntensity);
                state = ST_OffKeep;
                break;
              }
              LastInputTimerTick = millis();
              analogWrite(LedPort, LightIntensity);
            }
            break;
      case ST_OffKeep:  
            if(millis()-LastInputTimerTick >= 200 ){
              LastInputTimerTick = millis();
              state = ST_On;
            }
            break;
     default:
            break;
  }
}




// 中光度赤色航空障害灯1
void MediumLightRedAviationObstacleLightA3(){
  enum {
        ST_Init = 0,
        ST_Wait,
        ST_On,
        ST_OnKeep,
        ST_Off,
        ST_OffKeep,
        ST_Stop,
  };
  const char LedPort = 10; 
  static uint32_t LastInputTimerTick;
  static int state = ST_Init;
  static int LightIntensity = 0;
  static int RandomWait = 0;
 
  switch(state){
    case ST_Init:
            LastInputTimerTick = millis();
            RandomWait = random(1,10); 
            state = ST_Wait;
            break;
    case ST_Wait:
            if(millis()-LastInputTimerTick >= RandomWait*100 ){
              state = ST_On;
            }
            break;
    case ST_On:
            if(millis()-LastInputTimerTick >= 10 ){
              LightIntensity = LightIntensity + 4;
              if(LightIntensity >=255 ) {
                LightIntensity = 255;
                LastInputTimerTick = millis();
                state = ST_OnKeep;
                break;
              }
              LastInputTimerTick = millis();
              analogWrite(LedPort, LightIntensity);
            }
            break;
      case ST_OnKeep:  
            if(millis()-LastInputTimerTick >= 50 ){
                state = ST_Off;
            }
            break;
      case ST_Off:  
            if(millis()-LastInputTimerTick >= 10 ){
              LightIntensity = LightIntensity - 3;
              if(LightIntensity <= 2 ) {
                LightIntensity = 2;
                analogWrite(LedPort, LightIntensity);
                state = ST_OffKeep;
                break;
              }
              LastInputTimerTick = millis();
              analogWrite(LedPort, LightIntensity);
            }
            break;
      case ST_OffKeep:  
            if(millis()-LastInputTimerTick >= 200 ){
              LastInputTimerTick = millis();
                state = ST_On;
            }
            break;
     default:
            break;
  }
}


// 中光度赤色航空障害灯1
void MediumLightRedAviationObstacleLightA4(){
  enum {
        ST_Init = 0,
        ST_Wait,
        ST_On,
        ST_OnKeep,
        ST_Off,
        ST_OffKeep,
        ST_Stop,
  };
  const char LedPort = 11; 
  static uint32_t LastInputTimerTick;
  static int state = ST_Init;
  static int LightIntensity = 0;
  static int RandomWait = 0;
 
  switch(state){
    case ST_Init:
            LastInputTimerTick = millis();
            RandomWait = random(1,10); 
            state = ST_Wait;
            break;
    case ST_Wait:
            if(millis()-LastInputTimerTick >= RandomWait*100 ){
              state = ST_On;
            }
            break;
    case ST_On:
            if(millis()-LastInputTimerTick >= 10 ){
              LightIntensity = LightIntensity + 4;
              if(LightIntensity >=255 ) {
                LightIntensity = 255;
                LastInputTimerTick = millis();
                state = ST_OnKeep;
                break;
              }
              LastInputTimerTick = millis();
              analogWrite(LedPort, LightIntensity);
            }
            break;
      case ST_OnKeep:  
            if(millis()-LastInputTimerTick >= 50 ){
                state = ST_Off;
            }
            break;
      case ST_Off:  
            if(millis()-LastInputTimerTick >= 10 ){
              LightIntensity = LightIntensity - 3;
              if(LightIntensity <= 2 ) {
                LightIntensity = 2;
                analogWrite(LedPort, LightIntensity);
                state = ST_OffKeep;
                break;
              }
              LastInputTimerTick = millis();
              analogWrite(LedPort, LightIntensity);
            }
            break;
      case ST_OffKeep:  
            if(millis()-LastInputTimerTick >= 200 ){
                            LastInputTimerTick = millis();
                state = ST_On;
            }
            break;
     default:
            break;
  }
}
