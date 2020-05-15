#ifndef __DATA_H
#define __DATA_H


class Data
{
private:



public:

    int * crcCode = NULL;
    int crcLength = 0;
    int * hammingCode = NULL;
    int hammingLength = 0;
    int * data = NULL;
    int dataLength = 0;
    int len = 0;    //数据总长

    int * target = NULL;    //计算结果

    //设置crc多项式
    int setCrcCode(int code = 1); 
    //设置海明码长度
    int setHammingCode(unsigned int yourDataLen);   
    //输入数据
    int inputData(int * yourData, int length, int sp = 0);

    //打印数据
    void show(int * yourData, int dataLength);
    //数据异或操作
    void oper_machine(int * yourData1, int * yourData2, int * target, int length);
    //数据尾部补0
    //TODO:讲此函数与最后一个函数整合
    int fillZeroAF(int * yourData, int dataLength, int crcLength);
    //数据左移
    int shift_L(int * yourData, int dataLength);
    //粘上数据与结果
    void stickData(int * yourData = NULL, int * crcCode = NULL, int dataLength = 0, int crcLength = 0);

};

#endif