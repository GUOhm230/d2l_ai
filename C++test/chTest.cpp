#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
// paddle——api
using namespace std;
//返回0：无中文，返回1：有中文
int IncludeChinese(char *str)
{
char c;
while(1)
{
        c=*str++;
        if (c==0) break;  //如果到字符串尾则说明该字符串没有中文字符
        if (c&0x80)        //如果字符高位为1且下一字符高位也是1则有中文字符
                if (*str & 0x80) return 1;
    }
    return 0;
}

int main(){
    string str = "keine berstunden machen";
    string str2 = "lnйnnla";
    // char a = '我'; 
    cout<<"汉字占用长度："<<strlen("㸃")<<endl;
    cout<<"汉字占用长度："<<strlen("\"")<<endl;
    vector<vector<int>> list{{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    vector<vector<int>> aaa;
    aaa.insert(aaa.begin(), list.begin(), list.end());
    vector<vector<int>> bbb(list);
    // aaa=list;
    cout<<list.size()<<endl;
    for(vector<int> elms : aaa){
        for(int elm: elms){
            cout<<elm<<endl;
        }
        
    }

    // cout<<count(list.begin(), list.end(), 3)<<endl;
    // vector <int>().swap(list);  //清除容器并最小化它的容量，
    // cout<<list.size()<<endl;
    // list.push_back(3);
    // cout<<list[0]<<endl;
    // str.append(str2);
    // char arr[100];
    // // string s("ABCDEFG");
    // int len = str.copy(arr, 99);
    // arr[len] = '\0';
    // cout<<"arr数组\t"<<arr<<endl;
    // // // for(char e: arr){
    // // // cout<<e<<endl;
    // // // }
    // // // cout<<str<<endl;
    // cout<<IncludeChinese(arr)<<endl;
    return 0;
}