/*
实现黑马课程中的通讯录管理系统
系统需求：
    实现一个记录亲人，好友信息的工具
    包含以下功能：
    1.添加联系人：向通讯录中添加新人，包括（姓名，性别，年龄，联系电话，家庭住址）最多记录1000人
    2.显示联系人：显示通讯录中所有联系人信息
    3.查找联系人：按照姓名查看指定联系人
    4.删除联系人：按照指定姓名删除联系人
    5.修改联系人：按照姓名重新修改联系人的信息
    6.清空联系人：清空通讯录中所有信息
    7.退出通讯录：退出当前使用的通讯录
*/
#define MAX_SIZE 1000
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

//问题：数组问题，传参没错，但是不能在函数里面执行sizeof(arr)操作，因为此时arr代表的是一个指针,而非整个数组
int find_arr(int arr[], int elm, int arr_len){
    int flag = 0;
    for(int i=0; i<arr_len; i++){
        if(arr[i]==elm){
            flag = 1;
            return i;
        }
    }
    if (!flag){
        return -1;
    }
}


void showMenu(){
    cout<<"**************************************"<<endl;
    cout<<"*********    1.添加联系人    *********"<<endl;
    cout<<"*********    2.显示联系人    *********"<<endl;
    cout<<"*********    3.查找联系人    *********"<<endl;
    cout<<"*********    4.删除联系人    *********"<<endl;
    cout<<"*********    5.修改联系人    *********"<<endl;
    cout<<"*********    6.添加联系人    *********"<<endl;
    cout<<"*********    0.退出通讯录    *********"<<endl;
    cout<<"**************************************"<<endl;
}


// 设置添加联系人：1.创建储存联系人信息的结构体；2.创建通讯录结构体
struct contact{
    std::string m_Name;
    int m_Sex;
    int m_Age;
    std::string m_Tel;
    std::string address;
};

struct adressBooks{
    struct contact personArray[MAX_SIZE]; //结构体中创建结构体数组
    int m_size;
};


void add_contact(struct adressBooks* abs){
    // 设定之后，需要把数据添加到contact的目录中，这个应该怎么添加呢？
    if(abs->m_size == MAX_SIZE){
        cout<<"通讯录已满，无法添加"<<endl;
        return;
    }
    else{
        cout<<"请添加联系人姓名"<<endl;
        std::string name;
        cin>>name;
        abs->personArray[abs->m_size].m_Name = name;
        cout<<"请添加联系人性别"<<endl;
        int sex;
        while(true){
            cin>>sex;
            if(sex!=0 && sex!=1){
                cout<<"请重新输入性别"<<endl;
            }
            else{
                break;
            }
        }
        abs->personArray[abs->m_size].m_Sex = sex;

        cout<<"请添加联系人年龄"<<endl;
        int age;
         while(true){
            cin>>age;
            if(age>120 || age<0){
                cout<<"年龄重新输入："<<endl;
            }
            else{
                break;
            }
        }
        abs->personArray[abs->m_size].m_Age = age;
        cout<<"请添加联系人联系方式"<<endl;
        std::string tel;
        cin>>tel;
        abs->personArray[abs->m_size].m_Tel = tel;
        cout<<"请添加联系人住址"<<endl;
        std::string address;
        cin>>address;
        abs->personArray[abs->m_size].address = address;
    }
    abs->m_size++; // 怎么表示num+1
    // cout<<abs->m_size<<endl; //此处数字也有误
}

void showContact(struct adressBooks* abs){
    for(int i=0; i<abs->m_size;i++){
        std::string sex2Str = abs->personArray[i].m_Sex==0 ? "男":"女";
        cout<<i<<"\t"<<abs->personArray[i].m_Name<<"\t"<<sex2Str<<"\t"<<abs->personArray[i].m_Age<<"\t"
        <<abs->personArray[i].m_Tel<<"\t"<<abs->personArray[i].address<<endl;
    }
    return;
}

int find(struct adressBooks* abs, string name){
    int flag=0;
    for(int i=0; i<abs->m_size;i++){
        if(abs->personArray[i].m_Name==name) {
            flag = 1;
            return i;
            }
    }
    if (!flag){
        return -1;
    }  
}

void find_contact(struct adressBooks* abs, string name){
    int index = find(abs, name);
    if(index == -1){
        cout<<"查无此人"<<endl;
    }
    else{
        std::string sex2Str = abs->personArray[index].m_Sex==0 ? "男":"女";
        cout<<"联系人序号：" + to_string(index)<<"\t"<<abs->personArray[index].m_Name<<"\t"<<sex2Str<<"\t"<<abs->personArray[index].m_Age<<"\t"
        <<abs->personArray[index].m_Tel<<"\t"<<abs->personArray[index].address<<endl;
    }
  
}

void del_contact(struct adressBooks* abs, string name){
    int index = find(abs, name);
        if(index == -1){
            cout<<"查无此人"<<endl;
        }
        else{
            for(int i=index; i<abs->m_size-1; i++){
                abs->personArray[i] = abs->personArray[i+1];
            }
            abs->m_size--;
        }
}

void revise_contact(struct adressBooks* abs, string name){
    int index = find(abs, name);
        if(index == -1){
            cout<<"查无此人"<<endl;
        }
        else{
            cout<<"请修改联系人姓名"<<endl;
            std::string name;
            cin>>name;
            abs->personArray[index].m_Name = name;
            cout<<"请添加联系人性别"<<endl;
            int sex;
            while(true){
                cin>>sex;
                if(sex!=0 && sex!=1){
                    cout<<"请重新输入性别"<<endl;
                }
                else{
                    break;
                }
            }
            abs->personArray[index].m_Sex = sex;

            cout<<"请修改联系人年龄"<<endl;
            int age;
            while(true){
                cin>>age;
                if(age>120 || age<0){
                    cout<<"年龄重新输入："<<endl;
                }
                else{
                    break;
                }
            }
            abs->personArray[index].m_Age = age;
            cout<<"请修改联系人联系方式"<<endl;
            std::string tel;
            cin>>tel;
            abs->personArray[index].m_Tel = tel;
            cout<<"请修改联系人住址"<<endl;
            std::string address;
            cin>>address;
            abs->personArray[index].address = address;
        }
    return;
}

int frame(){
    struct adressBooks abs; // 为什么会出现这样的问题
    abs.m_size = 0;
    // abs->num = 0; // 指针只定义，而未初始化，因此不能直接用。必须先p = &a;
    while(true){
        int select;
        int arr[7] = {1,2,3,4,5,6,0};
        int len_arr = sizeof(arr)/sizeof(arr[0]);
        cout<<"请在下方输入你想进行的操作："<<endl;
        while(true){
            cin>>select;// 控制台输入字符串或者整型
            cin.clear();
            cin.ignore(); //防止非法输入字符串等错误信息
            if(find_arr(arr, select, len_arr)==-1 or cin.fail())
            {cout<<"抱歉，您刚才为非法输入！请继续输入"<<endl;}    
            else
            {break;}  
          
        }
        switch (select)
        {
            case 0:{ 
                cout<<"你确定退出吗 ? yes/no"<<endl;
                std::string exit;
                cin>>exit;
                if (exit=="yes"){
                    // cout << "\033[2J\033[1;1H";//ubuntu中清空终端的语句,但是在函数体内不执行
                    return 0;//跳出当前函数。但是如果whie放在函数外，则会执行下一个frame。相当于不跳出   
                }
                else            
                    // system("cls");//是visual studio中清除控制台内容的工具
                    // system("pause");
                    break;
            }
            case 1:{
                cout<<"添加联系人"<<endl;
                add_contact(&abs);
                break;
            }
            case 2:{
                cout<<"显示联系人"<<endl;
                showContact(&abs);
                break;
            }
            case 3:{
                cout<<"查找联系人"<<endl;
                cout<<"输入需要查找的用户名"<<endl;
                std::string find_Name;
                cin>>find_Name;
                find_contact(&abs, find_Name);
                // 按编号或者姓名查找。先要检测是否存在
                break;
            }
            case 4:{
                cout<<"删除联系人"<<endl;
                cout<<"输入待删除的用户名"<<endl;
                std::string del_Name;
                cin>>del_Name;
                del_contact(&abs, del_Name);
                // 按姓名删除：查找，再删除:逐渐平移，并总数减1
                break;
            }
            case 5:{
                cout<<"修改联系人"<<endl;
                cout<<"输入待修改的用户名"<<endl;
                std::string revise_Name;
                cin>>revise_Name;
                revise_contact(&abs, revise_Name);
                break;
            }
            case 6:{
                cout<<"清空联系人"<<endl;
                abs.m_size=0;
                break;
            }
        }
    }

    }

//1.实现菜单功能,退出功能，以及框架
int main(){
    showMenu();
    frame();
    cout << "\033[2J\033[1;1H";
    return 0;
}
//实现退出功能：
//功能描述