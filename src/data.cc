#include<iostream>
#include<map>
#include<cmath>

#include"CRC_CODE.h"
#include"data.h"

using namespace std;


//crc码长度记录表
map<int, int> lengthMap = {
    {0, 17},
    {1, 5}
};


//crc码转换表
map<int,int *> switchMap = {
    {0, CRC_16_IBM},
    {1, CRC_5}
};


/**
 * 设置crc多项式
*/
int Data::setCrcCode(int code)
{
    this->crcLength = lengthMap.find(code)->second;
    if (! crcLength)
    {
        return 1;
    }
    target = new int[crcLength - 1];

    this->crcCode = switchMap.find(code)->second;
    cout << "设置crc码:";
    for (int i = 0; i < crcLength; i++)
    {
        cout << crcCode[i] << " ";
    }
    cout << endl;
}


/**
 * 接收数据
*/
int Data::inputData(int * yourData, int dataLength, int sp)
{ 
    if (crcLength)
    len = dataLength + crcLength - 1;
    else if (hammingLength)
    len = dataLength + hammingLength;
    else
    {   
        len = dataLength;
        //TODO为避让checker.cc的bug,应该重写inputData函数
        // cout << "setCrcCode First!" << endl;
        // return 0;
    }

    if (sp) len = dataLength;
    
    delete[] data;
    data = new int[len];
    for (int i = 0; i < dataLength; i++)
    {
        *(data + i) = yourData[i];
    }
    this->dataLength = dataLength;
    cout << "原始数据为:";
    show(data, dataLength);
}


/**
 * 数据尾部补0
*/
//TODO:待处理
int Data::fillZeroAF(int * yourData, int dataLength, int crcLength)
{
    //将数据后面补0
    cout << "待处理数据:";
    for(int i=0; i < len; i++)
    {
        if (i <= dataLength)
        {
            yourData[i] = yourData[i];
            cout << yourData[i] << " ";

        }
        else
        {
            yourData[i] = 0;
            cout << yourData[i] << " ";
        }
    }
    cout << endl;
}


/**
 * 打印数据
*/
void Data::show(int *yourData, int dataLength)
{
    for(int i=0; i<dataLength; i++)
    {
        cout << *(yourData + i) << " ";
    }
    cout << endl;
}


/**
 * 数据左移补零
*/
int Data::shift_L(int * yourData, int length)
{
    int shift = 0;
    bool flag = true;
    for (int i=0; i<length; i++)
    {
        if (flag && !*(yourData + i))
        {
            shift++;
            continue;
        }
        else
        {
            flag = false;
        }
        *(yourData + i - shift) = *(yourData + i);
    }
    for (int i=0; i<shift; i++)
    {
        *(yourData + length-1 - i) = 0;
    }
    return shift;
}


//将结果与crc码相异或
void Data::oper_machine(int * yourData1, int * yourData2, int * target, int length)
{
    for (int i = 0; i < length; i++)
    {
        target[i] = yourData1[i] ^ yourData2[i];
    }
}


void Data::stickData(int * yourData, int * crcCode, int dataLength, int crcLength)
{
    if (! yourData)
    {
        for (int i = 0; i < this->crcLength - 1; i++)
        {
            data[i + this->dataLength] = target[i];
        }
    }
}


int Data::setHammingCode(unsigned int yourDataLen)
{
    if (! yourDataLen)
    {
        return 0;
    }
    
    int _2r = 0;

    for (int i = 2; ; i++)
    {
        _2r = pow(2,i);

        if (_2r - i - 1 >= yourDataLen)
        {
            hammingLength = i;
            delete[] hammingCode;
            // cout << hammingCode << " " << hammingLength << endl;
            this->hammingCode = new int[this->hammingLength];
            for (int j = 0; j < hammingLength; j++)
            {
                hammingCode[j] = pow(2,j) - 1;
            }
            cout << "设置海明码:";
            show(hammingCode, hammingLength);
            
            return 0;
        }
    }
}
