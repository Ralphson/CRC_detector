#include<iostream>
#include<cstdlib>
#include"creator.h"
#include"checker.h"
#include"data.h"

using namespace std;

int main(int, char **)
{
    int data[10] = {
        1,0,0,1,
        1,1,1,0,
        0,0
    };

    /**
     * 
     * 实验一
    */
    cout << "---------项目一---------" << endl;
    Creator mmm;
    int len;
    int p[10];
    mmm.setCrcCode(0);
    mmm.genData(10);
    // mmm.inputData(data, 10);
    len = mmm.genCRC();

    //TODO:如何使随机数不在1s内重复
    // cout << endl;
    // mmm.genData(10, p);
    // mmm.show(p, 10);
    // mmm.show(mmm.data, mmm.dataLength);

    /**
     * 实验二
     * 
    */
   
    cout << endl;
    cout << "---------项目二---------" << endl;
    int data1[len];
    int len1 = len;
    for (int i = 0; i < len1; i++)
    {
        data1[i] = mmm.data[i];
    }
    // mmm.show(data2, len1);
    Checker c;
    c.setCrcCode(0);
    c.inputData(data1, len1);
    c.noise(3);
    c.detectorCRC();

    /**
     * 
     * 实验三
    */
    cout << endl;
    cout << "---------项目三---------" << endl;
    int data2[10] = {
        1,0,0,1,
        1,1,1,0,
        0,0
    };
    int len2 = 10;
    Creator ham;
    ham.setHammingCode(len2);
    ham.genData(7);
    // ham.inputData(data2, len2);
    len = ham.genHamming();


    /**
     * 
     * 实验四
     */
    cout << endl;
    cout << "---------项目四---------" << endl;
    int data3[len];
    int len3 = 0;
    len3 = len;
    for (int i = 0; i < len; i++)
    {
        data3[i] = ham.data[i];
    }
    Checker c_ham;
    c_ham.setHammingCode(len2);
    c_ham.inputData(data3, len3, 1);
    c_ham.noise(1);
    c_ham.detectorHamming();

}
