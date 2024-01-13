using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Text;

// scvに保存するためのコード
// SaveCsvにアタッチする
public class SampleSaveCsv : MonoBehaviour
{
    // System.IO
    private StreamWriter sw;

    // Start is called before the first frame update
    void Start()
    {
        // 新しくcsvファイルを作成して{}の中の要素分csvに追記する
        sw = new StreamWriter(@"SaveData.csv", true, Encoding.GetEncoding("Shift_JIS"));

        // CSV1行目のカラムで StreamWriter オブジェクトに書き込む
        string[] s1 = { "F", "J", "time" };

        /**
         * s1の文字列配列のすべての要素を「,」で連結する
         * @see https://docs.microsoft.com/ja-jp/dotnet/api/system.string.join?view=net-6.0#System_String_Join_System_String_System_String___
         */
        string s2 = string.Join(",", s1);

        /**
         * s2文字列をcsvファイルへ書き込む
         * @see https://docs.microsoft.com/ja-jp/dotnet/api/system.io.streamwriter.writeline?view=net-6.0#System_IO_StreamWriter_WriteLine_System_String_
         */
        sw.WriteLine(s2);
    }

    // Update is called once per frame
    void Update()
    {
        // Enterキーが押されたらcsvへの書き込みを終了する
        if (Input.GetKeyDown(KeyCode.Return))
        {
            /**
             * @see https://docs.microsoft.com/ja-jp/dotnet/api/system.io.streamwriter.close?view=net-6.0#System_IO_StreamWriter_Close
             */
            sw.Close();
        }
    }

    public void SaveData(string txt1, string txt2, string txt3)
    {
        string[] s1 = { txt1, txt2, txt3 };
        string s2 = string.Join(",", s1);
        sw.WriteLine(s2);
    }
}
