/*
 * gamemanger.h
 *
 *  Created on: 28.05.2019
 *      Author: student
 */

#ifndef GAME_H_
#define GAME_H_

#include "graphic/mapitemmanager.h"
#include "graphicmanager.h"
#include "periphery/edumkbuttons.h"

class Game{

private:
    GraphicManager* _gManager;
    MapItemManager* _itemManager;

    bool _inGame;

public:

    Game()
    : _inGame(true)
    {
        _itemManager = new MapItemManager;
        _gManager = new GraphicManager( *_itemManager );
    }

    void startGame(){
        //init
        _itemManager->reloadMagazine();
        EdumkIIButtons buttons;


        while(_inGame){
            _gManager->updateScreen();
            if( buttons.topButtonPushed() ){
                _itemManager->deleteOneCartridge();
            }
            else if( buttons.lowButtonPushed() ){
                _itemManager->reloadMagazine();
            }
        }
    }



    ~Game(){
        delete _gManager;
        delete _itemManager;
    }


};


#endif /* GAME_H_ */
