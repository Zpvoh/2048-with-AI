#include "Map.h"
#include "AlphaAlgorithm.h"

using namespace std;

char AlphaAlgorithm::use(Map& m){
    //if(!m.getMoveState()
    int depth=5;
    int alpha=-10000000;
    int beta=10000000;
    return alphaBeta(depth, alpha, m).move;
}

int AlphaAlgorithm::evaluate(Map& m){
    return m.getLargestValue()*m.getMark()*(16-m.squareNum()+1); 
}

AlphaAlgorithm::moveValuePeer AlphaAlgorithm::alphaBeta(int depth, int alpha, Map& m){
    moveValuePeer result;
    static int count=0;
    int val, pVal=0;
    bool allEqual=true;

    if(depth==0){
        result.move='w';
        result.value=evaluate(m);
        return result;
    }


    vector<char> directions=m.getMoveableDirection();
    if(!m.getMoveState()){
        result.move=directions.back();
        result.value=0;
        return result;
    }

    while(!directions.empty()){
        char move=directions.back();

        Map mcopy=m;
        mcopy.move(move);
        val=alphaBeta(depth-1, alpha, mcopy).value;
        /*if(pVal=0 || pVal==val){
            allEqual=allEqual && true;
        }else{
            allEqual=false;
        }
        pVal=val;*/

        /*if(val>=beta){
            result.move=move;
            result.value=beta;
            return result;
        }*/

        if(val>alpha){
            result.move=move;
            alpha=val;
        }

        directions.pop_back();
    }

    /*if(allEqual){
        switch(count){
            case 0:
                result.move='w';
                break;
            case 1:
                result.move='s';
                break;
            case 2:
                result.move='a';
                break;
            case 3:
                result.move='d';
                count=0;
                break;
        }
        count++;
    }*/

    result.value=alpha;
    return result;

}