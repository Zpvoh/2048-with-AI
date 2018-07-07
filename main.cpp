#include <iostream>
#include "constants.h"
#include "AlphaAlgorithm.h"
#include "Playground.h"

using namespace std;

extern int random(int, int, long&);
extern int timeoutInterval;
extern void setTimer(int);
extern void timeoutHandle(int);
Playground pg;

int main(int argc, char** argv){
    cout<<"Welcome to play 2048"<<endl;
    signal(SIGALRM, timeoutHandle); 

    AlphaAlgorithm* alg=new AlphaAlgorithm();
    pg.setAutoAlgorithm(alg);

    char instruction='r';

    while(instruction=='r' || instruction=='t'){
        pg.handle(instruction);
        while(pg.getState()==state::PROCESSING){
            setTimer(timeoutInterval);
            pg.printPlayground();
            cin>>instruction;
            pg.handle(instruction);
        }
        cout<<"Enter r to restart game. Enter t to see the rank list. Enter any other key to quit"<<endl;
        cin>>instruction;
    }

    delete alg;
    pg.exit();
}