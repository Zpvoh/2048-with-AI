#include "AutoAlgorithm.h"
#ifndef ABAUTO
#define ABAUTO

class AlphaAlgorithm:public AutoAlgorithm{
    struct moveValuePeer{
        char move;
        int value;
    }; //移动-评估值对结构
    public:
        char use(Map&);
        int evaluate(Map&); //评估函数
        moveValuePeer alphaBeta(int depth, int alpha, Map& m); //最大估值预测函数
};

#endif