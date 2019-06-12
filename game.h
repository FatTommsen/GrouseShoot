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
#include "util/timer.h"
#include "util/uartlogger.h"

class Game{

private:
    GraphicManager* _gManager;
    MapItemManager* _itemManager;
    Settings* _settings;
public:

    Game(){
        _itemManager = new MapItemManager;
        _gManager = new GraphicManager( *_itemManager );
        _settings = new Settings;
    }

    ~Game(){
        delete _gManager;
        delete _itemManager;
        delete _settings;
    }

    void loadMenu(){
        _itemManager->buildStartScreen(true);
    }

    void runMenu(){
        EdumkIIButtons buttons;
        while(true){
            _gManager->updateMenuScreen();
            if( buttons.topButtonPushed() ){
                int i = _itemManager->processHit();
                if(i == TypeIdMenuEntryStart){
                    loadGame();
                    runGame();
                    loadMenu();
                }
                else if( i == TypeIdMenuEntrySettings ){
                    loadSettings();
                    runSettings();
                    loadMenu();
                }
            }

        }
    }

    void loadGame(){
        _gManager->resetMap();
        _itemManager->buildGameScreen();
        _itemManager->reloadMagazine();
    }

    void runGame(){
        bool inGame = true;
        EdumkIIButtons buttons;
        //Timer timer;
        //timer.startGame(2, &inGame );

        while(inGame){
            _gManager->updateScreen();
            if( buttons.topButtonPushed() ){
                _itemManager->deleteOneCartridge();
                if(_itemManager->getCartridgeCount() > 0){
                    _itemManager->processHit();
                }
            }
            else if( buttons.lowButtonPushed() ){
                _itemManager->reloadMagazine();
            }
        }
    }

    void loadSettings(){
        _itemManager->buildSettingsScreen( *_settings );
    }

    void runSettings(){
        EdumkIIButtons buttons;
        while(true){
            _gManager->updateMenuScreen();
            if( buttons.topButtonPushed() ){
                int i = _itemManager->processHit();
                if( i == TypeIdMenuEntryOk ){
                    return;
                }
                else if( i == TypeIdMenuEntryCheckbox ){
                    _itemManager->toggleAllCheckboxes();
                    _settings->reload = !_settings->reload;
                }
                else if( i == TypeIdSymbolSwitch ){
                    _itemManager->toggleSettingSymbols();
                    _settings->mapViaGSensor = !_settings->mapViaGSensor;
                }
            }
        }
    }




};


#endif /* GAME_H_ */
