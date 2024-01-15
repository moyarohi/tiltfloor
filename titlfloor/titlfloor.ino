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

// 最終的な各電圧に掛ける調整係数
float Avol_coefficient = 1; // A以外を遅くして調整(20240109現在)
float Bvol_coefficient = 1;
float Cvol_coefficient = 1;
float Dvol_coefficient = 0.98;
// 各アクチュエータ電圧
int Avol;
int Bvol;
int Cvol;
int Dvol;

// リセット秒数[ms]
int reset_ms = 2800;

// バッファ一時読み取り (String)
String tmpString;
// リセット確認文字_シリアル受信 (T/F)
char reset;
// 各アクチュエータ電圧_シリアル受信 (int)
int vol;
// 各アクチュエータ上下判定_シリアル受信　(1(UP)/-1(DOWN))
int act_UpDown[4];

// ループカウンタ
int i;

void setup() {
  Serial.begin(9600);
  Serial.println("setup()");
  /*
   リセットの度に初期化する変数
  */
  // リセット確認文字(T/F)
  reset = 'F';
  // バッファ一時読み取り (String)
  tmpString;
  // 各アクチュエータ伸ばし秒数 (int)
  //move_ms = 0;
  // 各アクチュエータ電圧 (int)
  vol = 0;
  // 各アクチュエータ上下判定　(1(UP)/-1(DOWN))
  for (i = 0; i < 4; i++) {
    act_UpDown[i] = 0;
  }
  // 各アクチュエータ電圧
  Avol = 255 * Avol_coefficient;
  Bvol = 255 * Bvol_coefficient;
  Cvol = 255 * Cvol_coefficient;
  Dvol = 255 * Dvol_coefficient;


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
  analogWrite(ALPWM, Avol);
  analogWrite(BRPWM, 0);
  analogWrite(BLPWM, Bvol);
  analogWrite(CRPWM, 0);
  analogWrite(CLPWM, Cvol);
  analogWrite(DRPWM, 0);
  analogWrite(DLPWM, Dvol);
  delay(reset_ms);

  analogWrite(ARPWM, 0);
  analogWrite(ALPWM, 0);
  analogWrite(BRPWM, 0);
  analogWrite(BLPWM, 0);
  analogWrite(CRPWM, 0);
  analogWrite(CLPWM, 0);
  analogWrite(DRPWM, 0);
  analogWrite(DLPWM, 0);

  Serial.println("end of setup()");

}


void loop() {
  /*
   シリアル通信で文字列取得　形式:Xnum,num,num,num,num, (X==T/F num==vol num...num==act_UpDown)
   リセット文字確認して、Tでないなら','区切りで読みだす
  */
  // データ受信まで待機
  while (Serial.available() <= 0) {}

  // 先頭文字リセットならsetup()から再開
  reset = Serial.read();
  if (reset == 'T'){
    Serial.println("reset True");
    // バッファクリア
    while(Serial.available() > 0) {
      Serial.read();
    }
    // setup()から再開
    resetFunc();
  } 
  else if (reset == 'F') {
    Serial.println("reset False");
  } 
  else {
    Serial.println("reset code isn't T/F");
  }

  // ','区切りで読みだす
  // 伸ばし秒数[ms]
  tmpString = Serial.readStringUntil(',');
  vol = tmpString.toInt();
  //Serial.println(vol);  // for debug
  for (i = 0; i < 4; i++) {
    tmpString = Serial.readStringUntil(',');
    // int に変換
    act_UpDown[i] = tmpString.toInt();

    //Serial.println(act_UpDown[i]); // デバッグ用
  }

  // 各電圧の決定
  Avol = vol * Avol_coefficient;
  Bvol = vol * Bvol_coefficient;
  Cvol = vol * Cvol_coefficient;
  Dvol = vol * Dvol_coefficient;


  /*
   アクチュエータ動作
  */
  // A
  if (act_UpDown[0] > 0) {  // 伸ばす場合
    analogWrite(ARPWM, 0);
    analogWrite(ALPWM, Avol);
  }
  else if (act_UpDown[0] < 0) {  // 縮める場合
    analogWrite(ARPWM, Avol);
    analogWrite(ALPWM, 0);
  }

  // B
  if (act_UpDown[1] > 0) {  // 伸ばす場合
    analogWrite(BRPWM, 0);
    analogWrite(BLPWM, Bvol);
  }
  else if (act_UpDown[1] < 0) {  // 縮める場合
    analogWrite(BRPWM, Bvol);
    analogWrite(BLPWM, 0);
  }
  
  // C
  if (act_UpDown[2] > 0) {  // 伸ばす場合
    analogWrite(CRPWM, 0);
    analogWrite(CLPWM, Cvol);
  }
  else if (act_UpDown[2] < 0) {  // 縮める場合
    analogWrite(CRPWM, Cvol);
    analogWrite(CLPWM, 0);
  }

  // D
  if (act_UpDown[3] > 0) {  // 伸ばす場合
    analogWrite(DRPWM, 0);
    analogWrite(DLPWM, Dvol);
  }
  else if (act_UpDown[3] < 0) {  // 縮める場合
    analogWrite(DRPWM, Dvol);
    analogWrite(DLPWM, 0);
  }
  // 1000msで目標位置に到達
  delay(1000);
  // 停止
  analogWrite(ARPWM, 0);
  analogWrite(ALPWM, 0);
  analogWrite(BRPWM, 0);
  analogWrite(BLPWM, 0);
  analogWrite(CRPWM, 0);
  analogWrite(CLPWM, 0);
  analogWrite(DRPWM, 0);
  analogWrite(DLPWM, 0);

  // バッファクリア
  while(Serial.available() > 0) {
    Serial.read();
  }

  Serial.println("end of loop()");

}
