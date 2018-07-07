#include <iostream>
#include "constants.h"
#include "Playground.h"

using namespace std;

int timeoutInterval=60;
extern Playground pg;

void setTimer(int interval){
    struct itimerval new_value, old_value;
    new_value.it_value.tv_sec=interval;
    new_value.it_value.tv_usec=0;
    new_value.it_interval.tv_sec=0;
    new_value.it_interval.tv_usec=0;
    setitimer(ITIMER_REAL, &new_value, &old_value);
}

void timeoutHandle(int sig){
    if(pg.playMap->squareList.size()!=16 && pg.getState()==state::PROCESSING){
        cout<<"Time out! One more square"<<endl;

        long seed=(unsigned)time(NULL);
        pg.playMap->randomAdd(seed);
        setTimer(timeoutInterval);
        pg.printPlayground();
    }
}