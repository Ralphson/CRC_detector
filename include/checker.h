#ifndef ___CHECKER_H
#define ___CHECKER_H

#include"data.h"

class Checker: public Data
{
private:
    /* data */
public:

    // int inputData(int * yourData, int dataLength);

    //检测crc数据
    bool detectorCRC();
    //添加噪声
    void noise(int n, int * yourData = NULL, int dataLength = 0);

    //检测海明码
    bool detectorHamming();

};

#endif