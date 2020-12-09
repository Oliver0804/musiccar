#define L_Do  262
#define L_Re  294
#define L_Mi  330
#define L_Fa  349
#define L_So  392
#define L_La  440
#define L_Si  494

#define M_Do  523
#define M_Re  587
#define M_Mi  659
#define M_Fa  698
#define M_So  784
#define M_La  880
#define M_Si  988

#define H_Do  1046
#define H_Re  1175
#define H_Mi  1318
#define H_Fa  1397
#define H_So  1568
#define H_La  1760
#define H_Si  1976

//展示模式 0=關閉,1=開啟
int demoMode = 0;

//除錯模式
int debugMode = 1;

//單聲響持續時間 預設500ms=>0.5秒
int delayTime = 500;
//設定偵測距離
int distance = 790;

//以上為可自行修改


//展示歌曲 小蜜蜂
int LittleBeeSong[53] = {
  5, 3, 3, 4, 2, 2,
  1, 2, 3, 4, 5, 5, 5,
  5, 3, 3, 4, 2, 2,
  1, 3, 5, 5, 3, 3, 3,
  2, 2, 2, 2, 2, 3, 4,
  3, 3, 3, 3, 3, 4, 5,
  5, 3, 3, 4, 2, 2,
  1, 3, 5, 5, 1, 1, 1,
};

//7個音符*三階＝21
//加上0 共22
int melody[22] = {0,
                  L_Do, L_Re, L_Mi, L_Fa, L_So, L_La, L_Si,
                  M_Do, M_Re, M_Mi, M_Fa, M_So, M_La, M_Si,
                  H_Do, H_Re, H_Mi, H_Fa, H_So, H_La, H_Si,
                 };
/*
 * 4321
 * 0001(1)  M_DO
 * 0010(2)  M_RE
 * 0100(4)  M_MI
 * 1000(8)  M_FA
 * 0011(3)  M_SO
 * 0101(5)  M_LA
 * 1001(9)  M_SI
 * 1100(12) H_DO
 * 1010(10) H_RE
 * 下列為參考位置
 * int userDefine[22]= {0,
                  1, 2, 3, 4, 5, 6, 7,
                  8, 9, 10, 11, 12, 13, 14,
                  15, 16, 17, 18, 19, 20, 21,
                 };

 */
 //實際引用
int userDefine[22]= {0,
                  M_Do, M_Re, M_So, M_Mi, M_La, 0, 0,
                  M_Fa, M_Si, H_Re, 0, H_Do, 0, 0,
                  0, 0, 0, 0, 0, 0, 0,
                 };

//宣告腳位定義
int tonePin = 9;
int channelA = A3;
int channelB = A2;
int channelC = A1;
int channelD = A0;

int LED1 = 5;
int LED2 = 6;
int LED3 = 7;
int LED4 = 8;


int toneValue = 0;

int playTone(int toneVal, int pitch) {
  if (toneVal == 0) {
    return 1;
  }
  //客製化版本
  tone(tonePin, userDefine[toneVal + pitch], delayTime);

  //表準版本
  //tone(tonePin, melody[toneVal + pitch], delayTime);
  delay(delayTime);
  return 0;

}


void setup() {

  //設定輸出位置
  pinMode(tonePin, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  delay(100);

  //展示模式
  if (demoMode == 1) {
    for (int x = 0 ; x < 53; x++) {
      playTone(LittleBeeSong[x], 0);
    }
    for (int x = 0 ; x < 53; x++) {
      playTone(LittleBeeSong[x], 7);
    }
    for (int x = 0 ; x < 53; x++) {
      playTone(LittleBeeSong[x], 14);
    }
  }
  Serial.println("Goodnight moon!");
}



void loop() {

  //讀取四路Sensor距離
  int sensorValue1 = analogRead(channelA);
  int sensorValue2 = analogRead(channelB);
  int sensorValue3 = analogRead(channelC);
  int sensorValue4 = analogRead(channelD);

  //偵測四路是否有接近的狀況，使用二進制進行統計
  if (sensorValue1 < distance){
    toneValue = toneValue + 1;
    digitalWrite(LED1, HIGH);
  }
  if (sensorValue2 < distance){
    toneValue = toneValue + 2;
    digitalWrite(LED2, HIGH);
  }
  if (sensorValue3 < distance){
    toneValue = toneValue + 4;
    digitalWrite(LED3, HIGH);
  }
  if (sensorValue4 < distance){
    toneValue = toneValue + 8;
    digitalWrite(LED4, HIGH);
  }

  //使用中間音域(7)進行展示
  //如需使用其他音域則子用0或是14
  playTone(toneValue, 0);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  //清除本次讀取數值
  toneValue = 0;
  if(debugMode==1){
    Serial.println(sensorValue1);
    Serial.println(sensorValue2);
    Serial.println(sensorValue3);
    Serial.println(sensorValue4);
    Serial.println("=========");
    delay(250);
  }
  

}
