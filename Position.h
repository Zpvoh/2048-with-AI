#ifndef POS
#define POS

class Position{
    public:
        int x, y; //位置坐标的x，y值
        Position(int x=-1, int y=-1):x(x), y(y){};
        bool operator==(const Position& pos){
            return pos.x==x && pos.y==y;
        }
        void move(char direction){
            switch(direction){
                case 'w':
                    x--;
                    break;
                case 's':
                    x++;
                    break;
                case 'a':
                    y--;
                    break;
                case 'd':
                    y++;
                    break;
            }
        }; //移动这个位置

        void moveback(char direction, int step){
            switch(direction){
                case 'w':
                    x+=step;
                    break;
                case 's':
                    x-=step;
                    break;
                case 'a':
                    y+=step;
                    break;
                case 'd':
                    y-=step;
                    break;
            }
        }; //往反方向移动这个位置
};

#endif