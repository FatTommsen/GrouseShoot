/*
 * gamemanger.h
 *
 *  Created on: 28.05.2019
 *      Author: student
 */

#ifndef GAME_H_
#define GAME_H_

#include "graphic/mapitemmanager.h"

class Game{

private:

    static Game* instance;


    Game() {

    }
public:

    static Game& getInstance(){
        if( Game::instance == nullptr ){
            Game::instance = new Game();
        }
        return *Game::instance;
    }


    ~Game(){

    }

    void run(){
        //MapItemManager::getInstance().deleteItemsOutOfMap();
    }

};


#endif /* GAME_H_ */
