# OOP Project: 2048游戏
**16302010023 邱轶扬**
-----

## <center>类结构设计</center>
整个2048游戏是在一个Playground对象中进行的。Playground是一个游戏操作环境类，封装了游戏局面，排行榜，小道具和自动算法。Playground可以处理输入的各种指令，如打印排行榜，使用小道具以及使用自动算法等。<br>
游戏局面由Map类封装，小道具由Tool类封装，继承为ToolRerange和ToolRandomRemove两种小道具。自动算法由抽象类AutoAlgorithm封装，拥有子类AlphaAlgorithm,为现在使用的自动算法。<br>
同时游戏局面类Map中包含了整个2048游戏的运行逻辑。里面封装了方块Square类的对象容器，同时维护了一个表征空闲位置的二维数组。游戏中的move动作由Map来处理。
另外Square类中封装了这一方块的位置对象Position，以灵活运动。<br>

- ### Playground类：游戏操作环境
    ``` c++
    class Playground{
        Map *playMap; //存放游戏局面
        std::vector<int> rankList; //存放排行榜
        time_t playtime; //存放游戏开始时间
        std::vector<ToolRerange> rerangeToolBox; //存放重置方块小道具
        std::vector<ToolRandomRemove> randomRemoveToolBox; //存放删除方块小道具
        AutoAlgorithm* autoAlg; //存放自动算法对象 
        public:
            void handle(char); //处理输入的操作
            void restart(); //重新开始游戏
            void exit(); //退出游戏
            void setAutoAlgorithm(AutoAlgorithm* autoAlg); //设置自动算法
            void useAutoAlgorithm(); //使用自动算法
            int getState(); //获取当前游戏的胜负状况
            void printRank(); //打印排行榜
            void printPlayground(); //打印整个游戏操作环境
    };
    ```
- ### Map类：游戏局面
    ``` c++
    class Map{
        //空闲状况表
        bool vacancy[4][4];
        std::vector<Square> squareList; //局面中的方块集合
        int state; //局面状况
        bool lastMove; //上一次是否成功移动
        bool isMove; //本次是否成功移动
        int mark; //游戏得分
        public:
            bool addSquare(Square&); //添加方块
            Position randomSelect(long&); //随机在空闲位置中挑选一个
            void randomAdd(long&); //随机添加2或4
            bool move(char); //处理移动指令
            void pauseGame(); //暂停游戏
            void startGame(); //从暂停中开始游戏
            bool hasMoveable(); //判断是否还有可以移动的方块
            void printMap(); //打印游戏局面
            int getState(); //获取游戏状态
            int getMark(); //获取游戏分数
            bool getMoveState(); //获取上一局是否移动
            Square* findSquare(Position); //通过位置来寻找方块
            bool deleteSquare(Square&); //删除方块
            int squareNum(); //返回方块总数
            int getLargestValue(); //获取局面中最大方块值
            std::vector<char> getMoveableDirection(); //获取可移动的方向集合
            bool hasVacancy(); //判断是否还有空闲位置
    };
    ```
- ### Square类：局面中的方块
    ``` c++
    class Square{
        int value; //该方块的值
        Position pos; //该方块的位置
        public:
            int getValue(); //获取值
            Position& getPos(); //获取位置
            const Square& operator+(Square&); //两个方块的合并
    };
    ```
- ### Position类：局面中的位置
    ``` c++
    class Position{
        public:
            int x, y; //位置坐标的x，y值
            void move(char direction); //移动这个位置
            void moveback(char direction, int step); //往反方向移动这个位置
    };
    ```

- ### Tool类：小道具的基类
    ``` c++
    class Tool{
        public:
            virtual void use(map* m); //使用该小道具
    };
    ```
- ### AutoAlgorithm类：自动算法的基类
    ``` c++
    class AutoAlgorithm{
        public:
            virtual char use(Map&); //使用自动算法
    };
    ```
## <center>游戏使用说明</center>
游戏界面如下图所示<br>

有如下两种编译方式：
1. 在终端中输入 `g++ AlphaAlgorithm.cpp Square.cpp Map.cpp ToolRerange.cpp ToolRandomRemove.cpp Playground.cpp Timer.cpp Main.cpp -o game -std=c++11 -g` 即可手动编译
2. 在终端中直接输入 `make` 即可使用makefile编译

然后输入 `./game` 即可运行本游戏

每次显示都会显示已用时间与获得的分数值。
初始状态下你有三个重排道具与三个随机消除道具。<br>
输入 **z** 可使用重排道具，输入 **x** 可使用随机消除道具。<br>
输入 **w** **a** **s** **d** 即可上下左右移动<br>
输入 **r** 即可重新开始<br>
输入 **t** 即可打印排行榜（注意查看完排行榜需输入一个字符以继续游戏）<br>
输入 **c** 即可使用自动算法<br>

## <center>自动算法策略：迭代最大评估</center>
本2048的自动完成算法基于对每一步所生成的新局面进行评估，迭代求取最优操作。<br>
我使用了考虑之后5步的算法迭代，评估函数为
> **局面价值 = 局面上最大方块值 * 本局游戏总分 * （16 - 局面剩余空闲位置数 + 1）**



