#include "constants.h"
#include "Map.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;
void printSameLength(int num);

int random(int a, int b, long& seed){
    srand(seed);
    int result = rand()%(b-a+1)+a;
    seed=rand()%(10000000+1);
    return result;
}

Map::Map():state(state::PROCESSING),mark(0),isMove(false){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            vacancy[i][j]=true;
        }
    }

    long seed=(unsigned)time(NULL);
    randomAdd(seed);
    randomAdd(seed);
}

Position Map::randomSelect(long& seed){
    int x, y, count;
    x=random(0, 3, seed);
    y=random(0, 3, seed);
    while(hasVacancy() && !vacancy[x][y]){
        x=random(0, 3, seed);
        y=random(0, 3, seed);
        //count++;
    }

    return Position(x, y);
}

void Map::randomAdd(long& seed){
    int rand=random(1, 10, seed);
    int value=rand==1?4:2;
    Position pos=randomSelect(seed);
    Square s1(value, pos.x, pos.y);
    this->addSquare(s1);
}

bool Map::addSquare(Square& s){
    if(vacancy[s.getPos().x][s.getPos().y]){
        squareList.push_back(s);
        vacancy[s.getPos().x][s.getPos().y]=false;
        return true;
    }else{
        return false;
    }
}

void Map::rawMove(char direction){
    for(vector<Square>::iterator it=squareList.begin(); it!=squareList.end(); it++){
            Position pos(it->getPos().x, it->getPos().y);
            pos.move(direction);

            while(findSquare(pos)==nullptr){
                vacancy[it->getPos().x][it->getPos().y]=true;
                vacancy[pos.x][pos.y]=false;
                it->getPos().move(direction);
                isMove=true;
                pos.move(direction);
            }
        }
}

bool Map::merge(Square& s1, Square& s2){
    if(s1.getValue()==s2.getValue()){
        //vacancy[s2.getPos().x][s2.getPos().y]=true;
        s1+s2;
        mark+=s1.getValue();
        deleteSquare(s2);
        isMove=true;
        if(s1.getValue()==2048){
            state=state::WIN;
            //cout<<"Get 2048!"<<endl;
        }
        return true;
    }

    return false;
}

void Map::mergeSingleDirection(char direction){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            Position pos;
            switch(direction){
                case 'w':
                    pos.x=i;
                    pos.y=j;
                    break;
                case 's':
                    pos.x=3-i;
                    pos.y=j;
                    break;
                case 'a':
                    pos.x=j;
                    pos.y=i;
                    break;
                case 'd':
                    pos.x=j;
                    pos.y=3-i;
                    break;
            }

            Square *current=findSquare(pos);
            pos.move(direction);
            Square *pre=findSquare(pos);

            if(current!=nullptr && pre!=nullptr
                && current->getValue()!=squareType::WALL && pre->getValue()!=squareType::WALL){
                    merge(*pre, *current);
                    rawMove(direction);
            }

        }
    }
    
}

bool Map::move(char direction){
    rawMove(direction);
    rawMove(direction);
    rawMove(direction);
    mergeSingleDirection(direction);
    //mergeSingleDirection(direction);

    lastMove=isMove;
    if(isMove){
        long seed=(unsigned)time(NULL);
        randomAdd(seed);
        isMove=false;
    }
}

Square* Map::findSquare(Position pos){
    static Square s(squareType::WALL);

    if(pos.x<0 || pos.y<0 || pos.x>3 || pos.y>3)
        return &s;

    if(vacancy[pos.x][pos.y])
        return nullptr;
    
    for(vector<Square>::iterator it=squareList.begin(); it!=squareList.end(); it++){
        if(it->getPos()==pos)
            return &(*it);
    }
}

bool Map::deleteSquare(Square& s){
    for(vector<Square>::iterator it=squareList.begin(); it!=squareList.end(); it++){
        if((&s)==(&(*it))){
            vacancy[s.getPos().x][s.getPos().y]=true;
            squareList.erase(it);
            return true;
        }
    }

    return false;
}

bool Map::hasMoveable(){
    if(squareList.size()!=16)
        return true;

    for(vector<Square>::iterator it=squareList.begin(); it!=squareList.end(); it++){
        Position pos(it->getPos().x, it->getPos().y);
        pos.move('w');
        bool canW=findSquare(pos)==nullptr || findSquare(pos)->getValue()==it->getValue();
        pos.moveback('w', 1);

        pos.move('s');
        bool canS=findSquare(pos)==nullptr || findSquare(pos)->getValue()==it->getValue();
        pos.moveback('s', 1);

        pos.move('a');
        bool canA=findSquare(pos)==nullptr || findSquare(pos)->getValue()==it->getValue();
        pos.moveback('a', 1);

        pos.move('d');
        bool canD=findSquare(pos)==nullptr || findSquare(pos)->getValue()==it->getValue();
        pos.moveback('d', 1);

        if(canW || canS || canA || canD)
            return true;
    }

    state=state==state::WIN?state::WIN:state::LOSE;
    return false;
}

int Map::getLargestValue(){
    int max=0;
    for(vector<Square>::iterator it=squareList.begin(); it!=squareList.end(); it++){
        max=(it->getValue()>max)?it->getValue():max;
    }

    return max;
}

bool Map::hasVacancy(){
    bool result=false;

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            result=result||vacancy[i][j];
        }
    }

    return result;
}

int Map::getState(){
    if(getLargestValue()>=2048)
        return state::WIN;
    hasMoveable();
    return state;
}

vector<char> Map::getMoveableDirection(){
    vector<char> result;

    Map mcopy=*this;
    mcopy.move('w');
    if(mcopy.getMoveState()){
        result.push_back('w');
    }

    mcopy=Map(*this);
    mcopy.move('s');
    if(mcopy.getMoveState()){
        result.push_back('s');
    }

    mcopy=Map(*this);
    mcopy.move('a');
    if(mcopy.getMoveState()){
        result.push_back('a');
    }

    mcopy=Map(*this);
    mcopy.move('d');
    if(mcopy.getMoveState()){
        result.push_back('d');
    }

    return result;

}

void Map::printMap(){
    int mapArray[4][4]={{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    for(vector<Square>::iterator it=squareList.begin(); it!=squareList.end(); it++){
        mapArray[it->getPos().x][it->getPos().y]=it->getValue();
    }

    cout<<"Your mark:"<<mark<<endl;

    cout<<"---------------------"<<endl;
    for(int i=0; i<4; i++){
        cout<<"|";
        for(int j=0; j<4; j++){
            printSameLength(mapArray[i][j]);
        }
        cout<<endl;
        cout<<"---------------------"<<endl;
    }
}

void printSameLength(int num){
    int d=num?(log10(num)+1):1;
    int spaceNum=4-d;
    if(num!=0){
        cout<<num;
    }else{
        cout<<" ";
    }

    for(int i=0; i<spaceNum; i++){
        cout<<" ";
    }
    cout<<"|";
}