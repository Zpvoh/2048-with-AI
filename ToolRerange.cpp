#include <ctime>
#include "ToolRerange.h"
#include "Map.h"

void ToolRerange::use(Map* m){
    Map m2;
    long seed=(unsigned)time(NULL);
    while(!m2.squareList.empty()){
        Square& s=m2.squareList.back();
        m2.deleteSquare(s);
    }

    while(!m->squareList.empty()){
        Square& s=m->squareList.back();
        Position pos=m2.randomSelect(seed);
        s.getPos().x=pos.x;
        s.getPos().y=pos.y;
        m2.addSquare(s); 
        m->deleteSquare(s);
    }

    //bool vacancy[4][4]={{true, true, true, true}, {true, true, true, true}, {true, true, true, true}, {true, true, true, true};
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            m->vacancy[i][j]=true;
        }
    }

    while(!m2.squareList.empty()){
        Square& s=m2.squareList.back();
        m->addSquare(s);
        m2.squareList.pop_back();
    }
}