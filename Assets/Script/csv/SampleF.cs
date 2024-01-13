using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

// Fキーを検出するコード
// Fへアタッチする
public class SampleF : MonoBehaviour
{
    private float time;

    GameObject saveCsv;
    SampleSaveCsv sampleSaveCsv;

    // Start is called before the first frame update
    void Start()
    {
        /**
         * SaveCsvのスクリプトを参照する
         * @see https://docs.unity3d.com/ja/current/ScriptReference/GameObject.Find.html
         */ 
        saveCsv = GameObject.Find("SaveCsv");

        /**
         * コンポーネントを返す
         * @see https://docs.unity3d.com/ja/current/ScriptReference/GameObject.GetComponent.html
         */
        sampleSaveCsv = saveCsv.GetComponent<SampleSaveCsv>();
    }

    // Update is called once per frame
    void Update()
    {
        // Fキーの入力時間をCSVに記入する
        time += Time.deltaTime;

        if (Input.GetKeyDown(KeyCode.F))
        {
            sampleSaveCsv.SaveData("F", " ", time.ToString());
        }
    }
}
