using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// 平面オブジェクトを矢印キー操作によってオイラーで回転させるスクリプト
public class TiltFloor : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // 左矢印キー ロール回転
        // 滑らかに回転させたい
        if (Input.GetKeyDown(KeyCode.LeftArrow)) {
            this.transform.rotation = Quaternion.Euler(0,0,10);
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
