#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>

#include "creator.h"

using namespace std;


int Creator::genData(int dataLength, int * p)
{
    if (! p)
    {
        if (crcLength) len = dataLength + crcLength - 1;
        else if (hammingLength) len = dataLength + hammingLength;
        else
        {
            cout << "setCrcCode First!" << endl;
            return 0;
        }
        delete[] data;
        data = new int[len];
        p = this->data;
        this->dataLength = dataLength;

    }

    int r;  //随机数
    srand((int)time(NULL));
    for(int i=0; i<dataLength; i++)
    {
        r = rand()%2;
        p[i]= r;
    }
    p[0] = 1;
    cout << "随机数据为:";
    show(p, dataLength);
}


int Creator::genCRC()
{
    if (! crcLength || ! dataLength)
    {
        cout << "crc长度为0" << endl;
        return 1;
    }
    
    this->fillZeroAF(data, dataLength, crcLength);

    //计算
    int shift = 0;
    int answer[crcLength]; //计算答案

    // this->machine(data, crcCode, answer, crcLength);

    this->oper_machine(data, crcCode, answer, crcLength);
    for(int i=crcLength; i<len + 1;)
    {      
        this->oper_machine(answer, crcCode, answer, crcLength);
        
        // show(answer, crcLength);
        //跟新结果:将结果往左移并且从数据中补齐尾部
        shift = shift_L(answer, crcLength);
        // show(answer, crcLength);
        for(int j=shift-1, k = 1; j>=0; j--, k ++)
        {
            // cout << i << endl;
            answer[crcLength-1 - j] = data[i];
            i ++;            
            if (i >= len)
            {
                int true_len = crcLength - (shift - k);
                // cout << shift << ":" << k << ":" << j << endl;
                // show(answer, crcLength);
                if (true_len == crcLength)
                {
                    this->oper_machine(answer, crcCode, answer, crcLength);
                    for (int q = 0; q < crcLength - 1; q++)
                    {
                        target[q] = answer[q + 1];
                    }
                    
                }
                else if (true_len == crcLength - 1)
                {
                    for (int k = 0; k < crcLength - 1; k++)
                    {
                        target[k] = answer[k];
                    }
                }
                else
                {
                    for (int k = 0; k < crcLength - 1; k++)
                    {
                        if (k < crcLength - 1 - true_len)
                        {
                            target[k] = 0;
                        }
                        else
                        {
                            target[k] = answer[k - (crcLength - 1 - true_len)];
                        }
                    }
                }
                cout << "冗余码:";
                show(target, crcLength - 1);

                cout << "最终结果:";
                stickData();
                show(data, len);

                // p = new int[len];
                // for (int k = 0; k < len; k++)
                // {
                //     p[k] = data[k];
                // }
                // show(p, len);
                return len;
            }
        }
        // cout << "---" << i - crcLength << "---" << endl;
        // show(answer, crcLength);
    }
}


int Creator::genHamming()
{
    if (! dataLength)
    {
        cout << "没有数据" << endl;
        return 1;        
    }

    //数据补齐海明码位
    int _data[len];
    for (int i = 0; i < hammingLength; i++)
        _data[hammingCode[i]] = -1;
    for (int i = 0, k = 0; i < len; i++)
    {
        if (_data[i] == -1)
        {
            k++;
            continue;
        }
        else
            _data[i] = data[i - k];
    }
    for (int i = 0; i < len; i++)
    {
        data[i] = _data[i];
    }
    cout << "待处理的数据";
    show(data, len);
    
    // 生成检测位
    for (int i = 0; i < hammingLength; i++)
    {
        int dector[len] = {};
        int flag = pow(2, i + 1);
        for (int j = hammingCode[i]; j < len; j += flag)
        {
            for (int k = 0; k < hammingCode[i] + 1; k++)
            {
                if (j + k < len)
                    dector[j + k] = 1;
                else 
                    break;
            }
        }
        dector[hammingCode[i]] = 0;

        int answer = 0;
        for (int j = 0; j < len; j++)
        {
            if (dector[j])
                answer = data[j] ^ answer;
        }
        data[hammingCode[i]] = answer;
    }

    cout << "生成的海明码:";
    show(data, len);
    return len;
}

