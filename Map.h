#include <vector>
#include "constants.h"
#include "ToolRerange.h"
#include "ToolRandomRemove.h"
#include "Square.h"

#ifndef MAP
#define MAP

class Map{
    //空闲状况表
    bool vacancy[4][4]={{true, true, true, true}, {true, true, true, true}, {true, true, true, true}, {true, true, true, true}};
    std::vector<Square> squareList; //局面中的方块集合
    int state; //局面状况
    bool lastMove; //上一次是否成功移动
    bool isMove; //本次是否成功移动
    int mark; //游戏得分

    /*以下是有关移动的辅助函数*/
    void rawMove(char);
    bool merge(Square&, Square&);
    void mergeSingleDirection(char);
    public:
        Map();
        bool addSquare(Square&); //添加方块
        Position randomSelect(long&); //随机在空闲位置中挑选一个
        void randomAdd(long&); //随机添加2或4
        bool move(char); //处理移动指令
        void pauseGame(){
            state=state::PAUSE;
        }; //暂停游戏
        void startGame(){
            state=state::PROCESSING;
        } //从暂停中开始游戏
        bool hasMoveable(); //判断是否还有可以移动的方块
        void printMap(); //打印游戏局面
        int getState(); //获取游戏状态
        int getMark(){
            return mark;
        }; //获取游戏分数
        bool getMoveState(){
            return lastMove;
        } //获取上一局是否移动
        Square* findSquare(Position); //通过位置来寻找方块
        bool deleteSquare(Square&); //删除方块
        
        int squareNum(){
            return squareList.size();
        } //返回方块总数
        int getLargestValue(); //获取局面中最大方块值
        std::vector<char> getMoveableDirection(); //获取可移动的方向集合
        bool hasVacancy(); //判断是否还有空闲位置

        friend void ToolRerange::use(Map* m);
        friend void ToolRandomRemove::use(Map* m);
        friend void timeoutHandle(int);
};

#endif