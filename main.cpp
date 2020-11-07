#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

//テキストまとめ
const string startTMessage = "開始時刻を入力してください：";
const string endTMessage = "終了時刻を入力してください：";
const string judgeTMessage = "判定する時刻を入力してください:";
const string errStrMessage = "時刻は半角数字(0～23)で入力してください\n";
const string errNumMessage = "時刻は半角数字(0～23)で入力してください\n";
const string warningMessage = "終了時刻＜開始時刻となっています、日付を跨いで判定します\n";
const string inMessage = "指定した時刻の範囲内に入っています\n";
const string outMessage = "指定した時刻の範囲内には入っていません\n";

//入力三つ、mapで使う(ここで宣言すべき？)
const string str[] = {"start", "end", "judge"};

//質問文と回答を入れるクラス
class T
{
public:
    //質問文
    vector<string> message;
    //入力された値の挿入
    map<string, int> time{
        {str[0], -1},
        {str[1], -1},
        {str[2], -1}};
    //コンストラクタ、質問文の入力
    T()
    {
        message.push_back(startTMessage);
        message.push_back(endTMessage);
        message.push_back(judgeTMessage);
    }
};

//stringの変換、定義外な値の場合は-1を返す
int numCheck(string s)
{
    int num;
    try
    {
        num = stoi(s);
    }
    catch (invalid_argument e)
    { //入力が数字でない
        cout << errStrMessage;
        return -1;
    }
    catch (out_of_range e)
    { //入力がintの範囲外
        cout << errNumMessage;
        return -1;
    }
    if (num < 0 || 24 <= num)
    { //入力が0〜23の範囲に無い
        cout << errNumMessage;
        return -1;
    }
    return num;
}
//入力ガイド文の提示とinput
int userInput(string message)
{
    string inputNum;
    cout << message;
    cin >> inputNum;
    return numCheck(inputNum);
}

int main(void)
{
    //クラスの宣言
    T cla;
    //質問文とinputの表示
    for (int i = 0; i < cla.message.size(); i++)
    {
        cla.time[str[i]] = userInput(cla.message[i]);
        if (cla.time[str[i]] == -1)
        {
            i = -1;
            continue;
        }
    }
    //"start"とかはstr[0]で書くべきででょうか？可読性とは...
    //「終了時刻＜開始時刻」の場合、日付を跨いで判定する(終了時刻+24hすることで解決)
    if (cla.time["end"] < cla.time["start"])
    {
        cla.time["end"] += 24;
        //判定時刻もずらすかどうか考慮
        if (cla.time["judge"] < cla.time["start"])
        {
            cla.time["judge"] += 24;
        }
        //日付をまたぐ場合、警告を出す
        cout << warningMessage;
    }
    //判定と出力
    if (cla.time["start"] <= cla.time["judge"] && cla.time["judge"] < cla.time["end"])
    {
        //時刻内に判定が存在する場合
        cout << inMessage;
    }
    else
    {
        if (cla.time["start"] == cla.time["judge"] && cla.time["judge"] == cla.time["end"])
        {
            //開始時刻＝終了時刻の場合
            cout << inMessage;
        }
        else
        {
            //判定外の場合
            cout << outMessage;
        }
    }
    return 0;
}
