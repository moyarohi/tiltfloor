using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// キューブオブジェクトを矢印キーで操作するスクリプト
public class MoveCube : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // 左矢印キー
        // 押すまたは離す入力のみ動作
        if (Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetKeyUp(KeyCode.LeftArrow)) {
            this.transform.Translate (-0.1f,0.0f,0.0f);
        }
        // 右矢印キー
        if (Input.GetKey (KeyCode.RightArrow)) {
            this.transform.Translate (0.1f,0.0f,0.0f);
        }
        // 上矢印キー
        if (Input.GetKey (KeyCode.UpArrow)) {
            this.transform.Translate (0.0f,0.0f,0.1f);
        }
        // 下矢印キー
        if (Input.GetKey (KeyCode.DownArrow)) {
            this.transform.Translate (0.0f,0.0f,-0.1f);
        }
    }
}
