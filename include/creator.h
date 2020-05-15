#ifndef __CREATOR_H
#define __CREATOR_H

#include"data.h"


class Creator: public Data
{
private:


public:

    //生成crc码
    int genCRC();
    //生成随机数
    int genData(int dataLength, int * p = NULL);

    //生成海明码
    int genHamming();

};

#endif // __CREATOR_H
