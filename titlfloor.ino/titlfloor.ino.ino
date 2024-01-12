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

void setup() {
  Serial.begin(9600);
  // ピンの設定

  /*
   リセット動作
  */
  // 全アクチュエータ縮める

  // リセット水平まで伸ばす
  
}

void loop() {
  // シリアル通信で文字列取得

  // 先頭文字リセットならsetup()から再開

  // アクチュエータ動作
}
