#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <algorithm>
#include "constants.h"
#include "Playground.h"

const int rerangeNum=3;
const int removeNum=3;
extern int timeoutInterval;
extern void setTimer(int);

Playground::Playground():playtime(time(NULL)), playMap(new Map()){
    readRankList();

    playtime=time(NULL);
    for(int i=0; i<rerangeNum; i++){
        rerangeToolBox.push_back(ToolRerange());
    }

    for(int i=0; i<removeNum; i++){
        randomRemoveToolBox.push_back(ToolRandomRemove());
    }
}

void Playground::handle(char instruction){
    switch(instruction){
        case 'w':
        case 'a':
        case 's':
        case 'd':
            playMap->move(instruction); 
            break;
        case 'q':
            exit();
            break;
        case 'c':
            while(playMap->getState()==state::PROCESSING){
                setTimer(timeoutInterval);
                useAutoAlgorithm();
            }
            break;
        case 'z':
            if(!rerangeToolBox.empty()){
                rerangeToolBox.back().use(playMap);
                rerangeToolBox.pop_back();
            }else{
                std::cout<<"Your rerange tool has been used up"<<std::endl;
            }
            break;
        case 'x':
            if(!randomRemoveToolBox.empty() && playMap->squareNum()>1){
                randomRemoveToolBox.back().use(playMap);
                randomRemoveToolBox.pop_back();
            }else if(playMap->squareNum()<=1){
                std::cout<<"You cannot delete all of squares"<<std::endl;
            }else{
                std::cout<<"Your random remove tool has been used up"<<std::endl;
            }
            break;
        case 'r':
            restart();
            break;
        case 't':
            if(playMap->getState()==state::PROCESSING)
                playMap->pauseGame();
            printRank();
            if(playMap->getState()==state::PAUSE)
                playMap->startGame();
            return;
        case 'i':
            std::cin>>timeoutInterval;
            break;
        default:
            std::cout<<"Please input something meaningful"<<std::endl;
            char newIns;
            std::cin>>newIns;
            handle(newIns);
            break;
    }

    if(playMap->getState()==state::LOSE){
        std::cout<<"What a pity! You can do better next time."<<std::endl;
    }else if(playMap->getState()==state::WIN){
        std::cout<<"Congratulations! You get 2048!"<<std::endl;
        rankList.push_back(time(NULL)-playtime);
        std::sort(rankList.begin(), rankList.end());
        //restart();
    }
}

void Playground::saveRankList(){
    std::ofstream of;
    of.open("rank.txt");
    std::vector<int>::iterator it;
    for(it=rankList.begin(); it!=rankList.end(); it++){
        of<<" "<<*it;
    }
    of.close();
}

void Playground::readRankList(){
    std::ifstream ifile;
    ifile.open("rank.txt");
    rankList.clear();
    int i;
    while(!ifile.eof()){
        int i;
        ifile>>i;
        rankList.push_back(i);
    }
    ifile.close();
}

void Playground::exit(){
    saveRankList();
    delete playMap;
    std::cout<<"Thanks for playing my 2048! Have a good day!"<<std::endl;
    std::exit(0);
}

void Playground::restart(){
    delete playMap;
    playMap=new Map();
    playtime=time(NULL);
    rerangeToolBox.clear();
    randomRemoveToolBox.clear();

    for(int i=0; i<rerangeNum; i++){
        rerangeToolBox.push_back(ToolRerange());
    }

    for(int i=0; i<removeNum; i++){
        randomRemoveToolBox.push_back(ToolRandomRemove());
    }
}

void Playground::useAutoAlgorithm(){
    char direction=autoAlg->use(*playMap);
    playMap->move(direction);
    printPlayground();
}

void Playground::printRank(){
    std::cout<<"************RANKING LIST**************"<<std::endl;

    std::vector<int>::iterator it;
    int count=1;
    for(it=rankList.begin(); it!=rankList.end(); it++){
        std::cout<<"The "<<count<<"th is "<<*it<<" secs"<<std::endl;
        count++;
    }

    if(rankList.size()==0){
        std::cout<<"I am sorry. There is no winning record."<<std::endl;
    }

    std::cout<<"***************************************"<<std::endl;
    std::cout<<"Enter something to continue the game"<<std::endl;

    std::string s;
    std::cin>>s;
}

void Playground::printPlayground(){
    std::cout<<std::endl;
    playMap->printMap();
    std::cout<<"Has used "<<time(NULL)-playtime<<" secs"<<std::endl;
    std::cout<<"You have "<<rerangeToolBox.size()<<" rerange tools"<<std::endl;
    std::cout<<"You have "<<randomRemoveToolBox.size()<<" random remove tools"<<std::endl;
}