#include "Tool.h"

#ifndef TOOLRAN
#define TOOLRAN

class map;

class ToolRandomRemove:public Tool{
    public:
        void use(Map* m); //使用随机消除小道具
};

#endif

