/*
 * gamemanger.h
 *
 *  Created on: 28.05.2019
 *      Author: student
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "graphic/mapitemmanager.h"

class GameManager{

private:

    static GameManager* instance;


    GameManager() {

    }
public:

    static GameManager& getInstance(){
        if( GameManager::instance == nullptr ){
            GameManager::instance = new GameManager();
        }
        return *GameManager::instance;
    }


    ~GameManager(){

    }

    void run(){
        MapItemManager::getInstance().deleteItemsOutOfMap();
    }

};


#endif /* GAMEMANAGER_H_ */
