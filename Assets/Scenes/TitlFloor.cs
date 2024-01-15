using System.Collections;
using System.Collections.Generic;
using UnityEngine;


// 平面オブジェクトを矢印キー操作によってオイラーで回転させるスクリプト
public class TiltFloor : MonoBehaviour
{
    // SerialHandlerクラス
    public SerialHandler serialHandler;
    // Arduinoに送信するデータ　形式:Xnum,num,num,num,num, (X==T/F num==move_ms num...num==act_UpDown)

    [SerializeField] GameObject gameObject;
    [SerializeField] private char rotate_direction = 'w'; // switch case で回転方向を判定する
    private float change_deg = 0;
    private float target_deg = 0;
    private bool isMoving = false; // true で回転描画

    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("Start() in Titlfloor");
    }

    // Update is called once per frame
    void Update()
    {
        // 回転方向　Inspectorじゃなくてキー操作でも変えれる
        if (Input.GetKeyDown(KeyCode.W))
        {
            rotate_direction = 'w';
            Debug.Log("change w");
        }
        if (Input.GetKeyDown(KeyCode.A))
        {
            rotate_direction = 'a';
            Debug.Log("change a");
        }
        if (Input.GetKeyDown(KeyCode.S))
        {
            rotate_direction = 's';
            Debug.Log("change s");
        }
        if (Input.GetKeyDown(KeyCode.D))
        {
            rotate_direction = 'd';
            Debug.Log("change d");
        }

        // 1: 1deg
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            // 画面内の傾斜描画
            setDeg(3.00f);
            Debug.Log("serial 1deg");
            // シリアル送信
            serialHandler.Write("F100,1,-1,-1,1,");

        }
        // 2deg
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            setDeg(3.00f);
            Debug.Log("serial 2deg");
        }
        // 3deg
        if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            setDeg(3.00f);
            Debug.Log("serial 3deg");
        }
        //4deg
        if (Input.GetKeyDown(KeyCode.Alpha4))
        {
            setDeg(3.00f);
            Debug.Log("serial 4deg");
        }
        //5deg
        if (Input.GetKeyDown(KeyCode.Alpha5))
        {
            setDeg(3.00f);
            Debug.Log("serial 5deg");
        }




        // Tキー　回転リセット
        if (Input.GetKeyDown(KeyCode.T))
        {
            this.transform.rotation = Quaternion.Euler(0, 0, 0);
            Debug.Log("get T key");
            //serialHandler.Write("T");
        }

        
        if (isMoving == true)
        {
            
            switch (rotate_direction)
            {
                case 'w': // ピッチ前
                    gameObject.transform.Rotate( target_deg * Time.deltaTime, 0, 0);
                    break;
                case 's': // ピッチ後
                    gameObject.transform.Rotate( -(target_deg * Time.deltaTime), 0, 0);
                    break;
                case 'a': // ロール左
                    gameObject.transform.Rotate( 0, 0, target_deg * Time.deltaTime);
                    break;
                case 'd': //ロール右
                    gameObject.transform.Rotate( 0, 0, -(target_deg * Time.deltaTime));
                    break;

            }
            change_deg += target_deg * Time.deltaTime; // 角度更新

            // 角度に到達したら回転終了
            if (change_deg >= target_deg)
            {
                isMoving = false;
                change_deg = 0;
                target_deg = 0;
                Debug.Log("end rotate");
            }
        }

    }

    private void setDeg(float deg)
    {
        target_deg = deg;
        isMoving = true;
    }

}
