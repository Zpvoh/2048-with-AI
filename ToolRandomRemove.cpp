#include <ctime>
#include "Map.h"

using namespace std;
extern int random(int a, int b, long& seed);

void ToolRandomRemove::use(Map* m){
    if(!m->squareList.empty()){
        bool isMin=false;
        vector<Square>::iterator it;
        int b=m->squareList.size()-1;
        long seed=(unsigned)time(NULL);
        while(!isMin){
            isMin=true;
            int index=random(0, b, seed);
            Square& s=m->squareList[index];
            
            for(it=m->squareList.begin(); it!=m->squareList.end(); it++){
                if(it->getValue()<s.getValue()){
                    isMin=false;
                    break;
                }
            }

            if(isMin)
                m->deleteSquare(s);
        }
    }
}