#define RUN 1
#define STOP 0

enum {
       ST_Init = 0,
       ST_On,
       ST_OnKeep,
       ST_Off,
       ST_OffKeep,
       ST_Stop,
};

char gRunStop = STOP;

void setup() {
  pinMode(3, OUTPUT);   // PWM
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);   // PWM
  pinMode(6, OUTPUT);   // PWM
  pinMode(9, OUTPUT);   // PWM
  pinMode(10, OUTPUT);  // PWM
  pinMode(11, OUTPUT);  // PWM
  pinMode(A0, INPUT);

  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);

}
void loop() {
  if(analogRead(A0) <= 600){
    gRunStop = RUN;
  } else {
    gRunStop = STOP;
  }  
  LowLightRedAviationObstacleLight1(4);
  MediumLightRedAviationObstacleLightA(3);
  MediumLightRedAviationObstacleLightB(5);
  HighLightAviationObstacleLight(6);
}

// 低光度赤色航空障害灯1
void LowLightRedAviationObstacleLight1(char LedPort){
    if(gRunStop == RUN )
      digitalWrite(LedPort, HIGH); 
    else
      digitalWrite(LedPort, LOW);    
}

// 低光度赤色航空障害灯2
void LowLightRedAviationObstacleLight2(){
  if(gRunStop == RUN)
    analogWrite(9, 200);
  else
    analogWrite(9,0); 
}


// 中光度赤色航空障害灯1
void MediumLightRedAviationObstacleLightA(char LedPort){
  static uint32_t LastInputTimerTick;
  static int state = ST_Init;
  static int LightIntensity = 0;

  if(gRunStop == STOP)
    state = ST_Stop;
 
  switch(state){
    case ST_Init:
            LastInputTimerTick = millis();
            LightIntensity = 0;
            state = ST_On;
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
                LastInputTimerTick = millis();
                state = ST_Off;
            }
            break;
    case ST_Off:  
            if(millis()-LastInputTimerTick >= 10 ){
              LightIntensity = LightIntensity - 3;
              if(LightIntensity <= 2 ) {
                LightIntensity = 2;
                analogWrite(LedPort, LightIntensity);
                LastInputTimerTick = millis();
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
    case ST_Stop:
            analogWrite(LedPort, 0);
            if(gRunStop == RUN){
              state = ST_Init;
            }
            break;
    default:
            break;
  }
}

// 中光度赤色航空障害灯2
void MediumLightRedAviationObstacleLightB(char LedPort){
  static uint32_t LastInputTimerTick;
  static int state =  ST_Init;

  if(gRunStop == STOP)
    state = ST_Stop;

  switch(state){
    case ST_Init:
            digitalWrite(LedPort, HIGH);
            LastInputTimerTick = millis();
            state = ST_On;
            break;
    case ST_On:
            if(millis()-LastInputTimerTick >= 1000 ){
              digitalWrite(LedPort, LOW);
              LastInputTimerTick = millis();
              state = ST_Off;
            }
            break;

    case ST_Off:  
            if(millis()-LastInputTimerTick >= 650 ){
              digitalWrite(LedPort, HIGH);
              LastInputTimerTick = millis();
              state = ST_On;
              }
            break;
    case ST_Stop:
            digitalWrite(LedPort, LOW);
            if(gRunStop == RUN)
              state = ST_Init;
            break;

     default:
            break;
  }
}


// 高光度航空障害灯
void HighLightAviationObstacleLight(char LedPort){
  static uint32_t LastInputTimerTick;
  static int state =  ST_Init;

  if(gRunStop == STOP)
    state = ST_Stop;

  switch(state){
    case ST_Init:
            digitalWrite(LedPort, HIGH);
            LastInputTimerTick = millis();
            state = ST_On;
            break;
    case ST_On:
            if(millis()-LastInputTimerTick >= 100 ){
              digitalWrite(LedPort, LOW);
              LastInputTimerTick = millis();
              state = ST_Off;
            }
            break;

    case ST_Off:  
            if(millis()-LastInputTimerTick >= 1200 ){
              digitalWrite(LedPort, HIGH);
              LastInputTimerTick = millis();
              state = ST_On;
              }
            break;
    case ST_Stop:
            digitalWrite(LedPort, LOW);
            if(gRunStop == RUN)
              state = ST_Init;
            break;
    default:
            break;
  }
}
