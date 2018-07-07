#include "Position.h"
#ifndef SQUARE
#define SQUARE

class Square{
    int value; //该方块的值
    Position pos; //该方块的位置
    public:
        Square(int v=0, int x=0, int y=0):pos(x, y), value(v){};
        int getValue(){
            return value;
        }; //获取值
        Position& getPos(){
            return pos;
        }; //获取位置
        //bool moveable(square*);
        //void move(char);
        const Square& operator+(Square&); //两个方块的合并
};

#endif