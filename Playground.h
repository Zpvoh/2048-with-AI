#include <signal.h>
#include <sys/time.h>
#include "Map.h"
#include "AutoAlgorithm.h"
#include "ToolRerange.h"
#include "ToolRandomRemove.h"

#ifndef PLAYGROUND
#define PLAYGROUND

class Playground{
    Map *playMap; //存放游戏局面
    std::vector<int> rankList; //存放排行榜
    time_t playtime; //存放游戏开始时间
    std::vector<ToolRerange> rerangeToolBox; //存放重置方块小道具
    std::vector<ToolRandomRemove> randomRemoveToolBox; //存放删除方块小道具
    AutoAlgorithm* autoAlg; //存放自动算法对象 

    void saveRankList();
    void readRankList();
    public:
        Playground();
        void handle(char); //处理输入的操作
        void restart(); //重新开始游戏
        void exit(); //退出游戏
        void setAutoAlgorithm(AutoAlgorithm* autoAlg){
            this->autoAlg=autoAlg;
        }; //设置自动算法
        void useAutoAlgorithm(); //使用自动算法
        int getState(){
            return playMap->getState();
        } //获取当前游戏胜负状况
        void printRank(); //打印排行榜
        void printPlayground(); //打印游戏操作环境
        friend void timeoutHandle(int); //引入超时函数作为友元
};

#endif