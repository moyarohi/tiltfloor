// ピンの対応
#define AR_EN 4
#define AL_EN 9
#define ARPWM 2  //Apwm
#define ALPWM 3
#define BR_EN 10
#define BL_EN 11
#define BRPWM 5  //Bpwm
#define BLPWM 6
#define CR_EN 12
#define CL_EN 13
#define CRPWM 7  //Cpwm
#define CLPWM 8
#define DR_EN 42
#define DL_EN 43
#define DRPWM 44  //Dpwm
#define DLPWM 45

// リセットのためのアドレス0　setup()内 resetfunc()で呼び出し
void(*resetFunc)(void) = 0;

/*
 アクチュエータに指定するPWM電圧(0-255)に係数をかけて調節
 最も遅いアクチュエータを基準(1.00)にする
*/
int A = 255 * 1.00 // A以外を遅くして調整(20240109現在)
int B = 255 * 0.95
int C = 255 * 0.95
int D = 255 * 0.95

// 傾斜秒数に掛ける係数(>=1)
float time_coefficient = 1.00

// リセット秒数[ms]
int reset_ms = 2500;


void setup() {
  Serial.begin(9600);

  /*
   リセットの度に初期化する変数
  */
  // リセット確認文字(T/F)
  char reset = 'F';
  // バッファ一時読み取り (String)
  String tmpString;
  // 各アクチュエータ伸ばし秒数 (int)
  int move_ms = 0;
  // 各アクチュエータ上下判定　(1(UP)/-1(DOWN))
  int act_UpDown[4] = {0,0,0,0};

  // ピンの設定
  // A
  pinMode(AR_EN, OUTPUT);
  pinMode(AL_EN, OUTPUT);
  pinMode(ARPWM, OUTPUT);
  pinMode(ALPWM, OUTPUT);
  digitalWrite(AR_EN, HIGH);
  digitalWrite(AL_EN, HIGH);
  // B
  pinMode(BR_EN, OUTPUT);
  pinMode(BL_EN, OUTPUT);
  pinMode(BRPWM, OUTPUT);
  pinMode(BLPWM, OUTPUT);
  digitalWrite(BR_EN, HIGH);
  digitalWrite(BL_EN, HIGH);
  // C
  pinMode(CR_EN, OUTPUT);
  pinMode(CL_EN, OUTPUT);
  pinMode(CRPWM, OUTPUT);
  pinMode(CLPWM, OUTPUT);
  digitalWrite(CR_EN, HIGH);
  digitalWrite(CL_EN, HIGH);
  // D
  pinMode(DR_EN, OUTPUT);
  pinMode(DL_EN, OUTPUT);
  pinMode(DRPWM, OUTPUT);
  pinMode(DLPWM, OUTPUT);
  digitalWrite(DR_EN, HIGH);
  digitalWrite(DL_EN, HIGH);

  /*
   リセット動作
  */
  //アクチュエータをリミットスイッチ位置まで縮める
  analogWrite(ARPWM, 255);  //縮
  analogWrite(ALPWM, 0);
  analogWrite(BRPWM, 255);
  analogWrite(BLPWM, 0);
  analogWrite(CRPWM, 255);
  analogWrite(CLPWM, 0);
  analogWrite(DRPWM, 255);
  analogWrite(DLPWM, 0);
  //4sまって確実に縮める
  delay(4000);

  // リセット水平まで伸ばす
  analogWrite(ARPWM, 0);
  analogWrite(ALPWM, A);
  analogWrite(BRPWM, 0);
  analogWrite(BLPWM, B);
  analogWrite(CRPWM, 0);
  analogWrite(CLPWM, C);
  analogWrite(DRPWM, 0);
  analogWrite(DLPWM, D);
  delay(reset_ms);

}


void loop() {
  /*
   シリアル通信で文字列取得　形式:Xnum,num,num,num,num, (X==T/F num==move_ms num...num==1/-1)
   リセット文字確認して、Fなら','区切りで読みだす
  */
  // データ受信まで待機
  while (Serial.available() = 0) {}

  // 先頭文字リセットならsetup()から再開
  reset = Serial.read();
  if (reset = 'T'){
    Serial.println("reset True");
    // バッファクリア
    while(Serial.available() > 0) {
      Serial.read();
    }
    // setup()から再開
    resetfunc();
  } 
  else if (reset = 'F') {
    Serial.println("reset False");
  } 
  else {
    ("reset code isn't T/F");
  }

  // ','区切りで読みだす
  // 伸ばし秒数[ms]
  tmpString = Serial.readStringUntil(',');
  move_ms = tmpString.toInt();
  for (i = 1; i < 4; i++) {
    tmpString = Serial.readStringUntil(',');
    // int に変換
    act_UpDown[i] = tmpString.toInt();

    Serial.println(act_UpDown[i]); // デバッグ用
  }

  /*
   アクチュエータ動作
  */
  // A
  if (act_UpDown[0] > 0) {  // 伸ばす場合
    analogWrite(ARPWM, 0);
    analogWrite(ALPWM, A);
  }
  else if (act_UpDown[0] < 0) {  // 縮める場合
    analogWrite(ARPWM, A);
    analogWrite(ALPWM, 0);
  }

  // B
  if (act_UpDown[1] > 0) {  // 伸ばす場合
    analogWrite(BRPWM, 0);
    analogWrite(BLPWM, B);
  }
  else if (act_UpDown[1] < 0) {  // 縮める場合
    analogWrite(BRPWM, B);
    analogWrite(BLPWM, 0);
  }
  
  // C
  if (act_UpDown[2] > 0) {  // 伸ばす場合
    analogWrite(CRPWM, 0);
    analogWrite(CLPWM, C);
  }
  else if (act_UpDown[2] < 0) {  // 縮める場合
    analogWrite(CRPWM, C);
    analogWrite(CLPWM, 0);
  }

  // D
  if (act_UpDown[3] > 0) {  // 伸ばす場合
    analogWrite(DRPWM, 0);
    analogWrite(DLPWM, D);
  }
  else if (act_UpDown[3] < 0) {  // 縮める場合
    analogWrite(DRPWM, D);
    analogWrite(DLPWM, 0);
  }

  delay(move_ms);

}
