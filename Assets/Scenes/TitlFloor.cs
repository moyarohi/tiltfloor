using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// 平面オブジェクトを矢印キー操作によってオイラーで回転させるスクリプト
public class TiltFloor : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        // SerialHandlerクラス
        //public SerialHandler serialHandler;       
        // Arduinoに送信するデータ　形式:Xnum,num,num,num,num, (X==T/F num==move_ms num...num==act_UpDown)
        //private string cmds_ = "F500,1,-1,-1,1,";
    }

    // Update is called once per frame
    void Update()
    {
        // 左矢印キー ロール回転
        // 滑らかに回転させたい
        if (Input.GetKeyDown(KeyCode.LeftArrow)) {
            // 画面内の傾斜描画
            this.transform.rotation = Quaternion.Euler(0,0,10);
            // シリアル送信
            //serialHandler.Write(cmds_);
        }

        // 右矢印キー ロール回転
        if (Input.GetKey (KeyCode.RightArrow)) {
            this.transform.rotation = Quaternion.Euler(0,0,-10);
        }
        // 上矢印キー　ピッチ回転
        if (Input.GetKey (KeyCode.UpArrow)) {
            this.transform.rotation = Quaternion.Euler(10,0,0);
        }
        // 下矢印キー　ピッチ回転
        if (Input.GetKey (KeyCode.DownArrow)) {
            this.transform.rotation = Quaternion.Euler(-10,0,0);
        }
        // Enterキー　回転リセット
        if (Input.GetKey (KeyCode.R)) {
            this.transform.rotation = Quaternion.Euler(0,0,0);
        }
    }
}
