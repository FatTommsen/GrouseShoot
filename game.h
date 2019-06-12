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
#include "util/random.h"

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
        Random& rand = Random::getInstance();
        Statistic stat;
        Timer timer;
        timer.startGame(GAME_DURATION_S, &inGame );

        while(inGame){
            //spawning
            if( rand.next() * 100 < SPAWN_PERCENTAGE){
                double d = rand.next();
                if( d * 100 < 45 ){
                    _itemManager->spawnGrouseFly();
                }
                else if( d * 100 < 90 ){
                    _itemManager->spawnGrouseRun();
                }
                else if( !_itemManager->hasActiveGrouseFishing() ){
                    _itemManager->spawnGrouseFishing();
                }
            }

            _gManager->updateScreen();
            if( buttons.topButtonPushed() ){
                _itemManager->deleteOneCartridge();
                stat.shotCount += 1;
                if(_itemManager->getCartridgeCount() > 0){
                    int type = _itemManager->processHit();
                    if( type == TypeIdGrouseFly ){
                        stat.flyCount += 1;
                    }
                    else if( type == TypeIdGrouseRun ){
                        stat.runCount += 1;
                    }
                    else if( type == TypeIdGrouseFishing ){
                        stat.fishCount += 1;
                    }
                }
            }

            if( _settings->reload ){
                if( _itemManager->getCartridgeCount() == 0 ){
                    _itemManager->reloadMagazine();
                }
            }
            else if( buttons.lowButtonPushed() ){
                _itemManager->reloadMagazine();
            }
        }

        _gManager->printStatistic(stat);

        timer.delay(30000);
        while(true){
            if(buttons.topButtonPushed()){
                return;
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
                    _settings->mapViaGSensor = !_settings->mapViaGSensor;
                    _itemManager->toggleSettingSymbols();
                    _gManager->toggleMapNavigation();
                    _itemManager->toggleTopLevelNavigation();
                }
            }
        }
    }


};


#endif /* GAME_H_ */
