#ifndef TOOL
#define TOOL

class map;

class Tool{
    public:
        //void (*toolHandle)();
        virtual void use(map* m){}; //使用该小道具
};

#endif