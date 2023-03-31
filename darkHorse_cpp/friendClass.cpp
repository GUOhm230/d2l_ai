/*
*目的：实现友元
*1.全局函数做友元
*2.友元类
*3.成员函数做友元
*4.类外实现成员函数实现类分离


假如不采用类分离，只在当前类定义成员函数，并调用其他类
会不会报错：incomplete type

不使用类分离效果：
    1.如果需要声明类。则在当前类中使用声明类应当创建指针对象，而不是直接创建对象。
    2.不使用声明类的话，类的先后顺序没有问题，则可以使用对象，也能直接使用友元类。
    3.但是无法直接创建友元类成员函数，会显示当前Father类并没定义:
classSplitTest.cpp:18:34: error: invalid use of incomplete type ‘class Father’
     friend void Father::visitSon();
                                  ^
    4.因为友元成员函数所在的类（Father）必须在当前类(Son)的上方，因此，必须使用类声明，所以对象的创建必须要用到指针和new.
    但是不做类分离呢？能否定义友元成员函数：答案：不行。报错如下：
    classSplitTest.cpp:29:18: error: invalid use of incomplete type ‘class Son’
         cout<<son->m_age<<endl;
                  ^~
                                
因此：
    1.使用类分离的书写方式，从此改变C++的书写规范
    2.当使用声明类时，需要调用声明的类对象，需要用指针对象，只用对象会报错如上(3.）
    3.当在Son中创建友元类函数时，被创建的友元类函数的类必须在当前类上方，但是该类中又要先调用Son类，因此Son类只能声明
*/
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class Son;
class Father{
public:
    class Son* son;
    Father();  
    void visitSon();
};

class Son{
    friend void Father::visitSon();
    // friend class Father;
public:
    int m_age;
private:
    std::string m_name;
public:
    Son();
};


Father::Father(){
    son = new Son;
}

void Father::visitSon(){
    cout<<son->m_age<<endl;
    cout<<son->m_name<<endl;
}

Son::Son(){
    m_age = 18;
    m_name = "郭辉铭";
}

void test(){
    class Father f;
    f.visitSon();
}


int main(){
    test();
    return 0;
}