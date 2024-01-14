using UnityEngine;
using System.Collections;
using System.IO.Ports;
using System.Threading;

public class SerialHandler : MonoBehaviour
{
    public delegate void SerialDataReceivedEventHandler(string message);
    public event SerialDataReceivedEventHandler OnDataReceived;

    //ポート名
    //例
    //Linuxでは/dev/ttyUSB0
    //windowsではCOM1
    //Macでは/dev/tty.usbmodem1421など
    [SerializeField] string portName = "COM1";
    [SerializeField] int baudRate    = 9600;

    private SerialPort serialPort_;
    private Thread thread_;
    private bool isRunning_ = false;
    // シリアル通信の値格納
    private string message_;
    // シリアル受信フラッグ
    private bool isNewMessageReceived_ = false;

    void Awake()
    {
        Open();
    }

    /*
    read() によって isNewMessageReceived_ == true
    delegate型 OnDataReceived(string message) の定義元メソッドにしたがって
    messageが処理される
    */
    void Update()
    {
        if (isNewMessageReceived_) {
            OnDataReceived(message_);
        }
        isNewMessageReceived_ = false; // falseに戻す
    }

    void OnDestroy()
    {
        Close(); // Close()呼び出し
    }

    private void Open()
    {
        serialPort_ = new SerialPort(portName, baudRate, Parity.None, 8, StopBits.One);
         //または
         //serialPort_ = new SerialPort(portName, baudRate);
        serialPort_.Open();

        isRunning_ = true;

        thread_ = new Thread(Read);
        thread_.Start();
    }

    /*
    OnDestroy() から呼び出される
    */
    private void Close()
    {
        isNewMessageReceived_ = false;
        isRunning_ = false;

        if (thread_ != null && thread_.IsAlive) {
            thread_.Join();
        }

        if (serialPort_ != null && serialPort_.IsOpen) {
            serialPort_.Close();
            serialPort_.Dispose();
        }
    }

    /*
    スレッドで動く中身
    シリアルデータを受信すると message_に値格納する
    isNewMessageReceivedで update()が実行される
    */
    private void Read()
    {
        while (isRunning_ && serialPort_ != null && serialPort_.IsOpen) {
            try {
                message_ = serialPort_.ReadLine();
                isNewMessageReceived_ = true;
            } catch (System.Exception e) {
                Debug.LogWarning(e.Message);
            }
        }
    }

    public void Write(string message)
    {
        try {
            serialPort_.Write(message);
        } catch (System.Exception e) {
            Debug.LogWarning(e.Message);
        }
    }
}
