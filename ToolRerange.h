#include "Tool.h"

#ifndef TOOLRE
#define TOOLRE

class Map;

class ToolRerange:public Tool{
    public:
        void use(Map* m); //使用重排小道具
};

#endif