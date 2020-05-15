#include<iostream>
#include<cstdlib>
#include<vector>
#include<cmath>

#include"checker.h"

using namespace std;


bool Checker::detectorCRC()
{
    this->len = dataLength;
    cout << "待处理数据:";
    show(data, len);

    //计算
    int shift = 0;
    int answer[crcLength]; //计算答案

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

                // cout << "计算结果:";
                // stickData();
                // show(data, len);

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


void Checker::noise(int n, int * yourData, int dataLength)
{
    if (! yourData)
    {
        dataLength = this->dataLength;
        yourData = this->data;
    }

    srand(time(NULL));
    //产生n个随机位置
    //TODO:数据首位不处理
    int pos[dataLength - 1] = {};
    for (int i = 0; i < dataLength - 1; i++) pos[i] = i + 1;    //第0位不参与
    for (int i = 0; i < n; i++) swap(pos[i], pos[rand()%(dataLength-1)]);

    //按位取反
    cout << n << "个修改位:";
    for (int i = 0; i < n; i++)
    {
        cout << pos[i] + 1 << " ";
        yourData[pos[i]] = yourData[pos[i]] ^ 1;
    }
    cout << endl;
    // cout << "叠加噪声后:";
    // show(data, dataLength);
}


//TODO包含此重写后data.cc-160出现莫名bug
// int Checker::inputData(int * yourData, int dataLength)
// {
//     if (! hammingLength)
//         len = dataLength;
//     else
//         len = dataLength + hammingLength;
    

//     data = new int[len];
//     for (int i = 0; i < dataLength; i++)
//     {
//         data[i] = yourData[i];
//     }
//     this->dataLength = dataLength;
//     cout << "原始数据为:";
//     show(data, dataLength);
// }


bool Checker::detectorHamming()
{
    cout << "待处理的数据:";
    show(data, len);

    int _data[len];
    int target[hammingLength];
    for (int i = 0; i < len; i++)
    {
        _data[i] = data[i];
    }
    
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
        // show(dector, len);

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

    for (int i = 0, k = hammingLength - 1; i < hammingLength; i++, k--)
    {
        target[k] = data[hammingCode[i]] ^ _data[hammingCode[i]];
    }
    cout << "对应的错误位:";
    show(target, hammingLength);
    
    return len;

}
