#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

vector<string> split(string str) {
  int size = str.size();
  cout<<size<<endl;
  vector<string> ans;
  int j = 0;
  for (int i = 0; i < size; i++) {
    if (str[i] == ' '||str[i] == ','||str[i] == '.') {
      ans.push_back(str.substr(j, i - j));
      j = i+1;
    }
  }
  ans.push_back(str.substr(j, size - j));
  return ans;
}

bool digitDet(string str){
    for(char elm: str){
        if(!(isdigit(elm)||elm=='.'||elm==' '))    return false;
    }
    return true;
}

//字符串分割（中英法德等均可）,分割再判定
vector<string> split_isContainsBF_2(string str, int &isContains_BeatFlag, int &isAll_BeatFlag2) {
    //包含以下,要用空格，逗号，句号分隔，并检测:音乐节拍速度标记，力度标记术语
    vector<string> beatFlag = {"largo", "larghetto", "adagio", "andante", "moderato", "allegro", "presto", "prestissimo",
                "poco", "più", "lentissimo", "tempo", "vivace", "grave", "lento", "andante", "andantino",
                "allegretto", "tempodimarcia", "tempodiballo", "rit", "riten", "ritenuto", "rall", "rallentando",
                "allarg", "allargando", "smorzando", "accel.","accelerando", "smorzando", "string", "stringendo", "listessotempo",
                "atempo", "molto", "assai", "meno", "possibile", "piu", "nontroppo", "sempre", "mosso", "rubato", "stretto",
                "lento", "cresc", "crescendo", "dim", "diminuendo", "comeprima", "precipitato", "vivo", "[", "]","(", ")", "（", "）", "{", "}"};

    // //不用空格分割，包含即否认
    // vector<string> parentheses = {};

    //边框内字符串仅由以下字符组成，则不为标题：阿拉伯数字，强度标记，乐器
    vector<string> beatFlag2 = {"Ⅰ", "Ⅱ", "Ⅲ", "Ⅳ", "Ⅴ", "Ⅵ", "Ⅶ", "Ⅷ", "Ⅸ", "Ⅹ", "Ⅺ", "Ⅻ",
                    "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII",
                    "piano", "violin", "cello", "viola", "pp", "ppp", "pppp" , "mf", "ff", "fff", "sf", "fp"};
    int size = str.size();
    cout<<size<<endl;
    vector<string> ans;
    int j = 0;
    isContains_BeatFlag = 0;
    isAll_BeatFlag2=1;
    for (int i = 0; i < size; i++) {
        if (str[i] == ' '||str[i] == ','||str[i] == '.') {
            string strElm= str.substr(j, i - j);
            ans.push_back(strElm);
            if(!isContains_BeatFlag && count(beatFlag.begin(), beatFlag.end(), strElm))     isContains_BeatFlag = 1;
            if(isAll_BeatFlag2 && !count(beatFlag2.begin(), beatFlag2.end(), strElm))      isAll_BeatFlag2=0;
        j = i+1;
        }
    }
    ans.push_back(str.substr(j, size - j));
    if(!isContains_BeatFlag && count(beatFlag.begin(), beatFlag.end(), str.substr(j, size - j)))     isContains_BeatFlag = 1;
    if(isAll_BeatFlag2 && !count(beatFlag2.begin(), beatFlag2.end(), str.substr(j, size - j)))      isAll_BeatFlag2=0;
    return ans;
}

int add(int &a, int &b){
    int c = a + b;
    a = 8989;
    return c;
}

int main(){
    
    // vector<int> v = {1,2,3,4,5};
    // // vector<int> v1 = {9, 8, 7};
    // // vector<int> v3;
    // // cout<<v.back()<<endl;
    // string str="hka 中国 人k hk aj，k,hah";
    // // char c = stint isContains_BeatFlag; 
    // vector<string> a = split(str);
    // // if
    // // for(string elm: a){
    // //     cout<<elm<<"\t"<<endl;
    // // }
    // string line = "0.1 ,12";
    
    // // auto c = isdigit(atoi(line.c_str()));
    //  if (digitDet(line))
    //     cout<<"当前字符串为数字"<<endl;
    //  else
    //     cout<<"不为数字"<<endl;
    
    // int a = 3;
    // int b = 4;
    // int d = add(a, b);
    // cout<<d<<"\n"<<a<<endl;
    // v.insert(v.begin()-1, v1.begin(), v1.end());
    // vector<int> v2(v);
    // v = vector<int>(v.rbegin(), v.rend());

    // v.insert(v.begin(), 0);
    // for(int elm: v){
    //     cout<<elm<<endl;
    // }
    //--------------------------------分割字符串，包含在内测试-----------------------------//
    int isContains_BeatFlag; 
    int isAll_BeatFlag2;
    string str = "IV 12 violin";
    vector<string> ans = split_isContainsBF_2(str, isContains_BeatFlag, isAll_BeatFlag2);
    cout<<"isContains_BeatFlag="<<isContains_BeatFlag<<"\t"<<"isAll_BeatFlag2="<<isAll_BeatFlag2<<endl;
    cout<<"\n";
    for(string elm: ans){
        cout<<elm<<"\t";
    }
    cout<<endl;
    return 0;
}