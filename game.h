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
    Highscore* _high;
public:

    Game(){
        _itemManager = new MapItemManager;
        _gManager = new GraphicManager( *_itemManager );
        _settings = new Settings;
        _high = new Highscore;
    }

    ~Game(){
        delete _gManager;
        delete _itemManager;
        delete _settings;
        delete _high;
    }

    void loadMenu(){
        _itemManager->buildStartScreen(_high->hasStatistic());
        //_itemManager->buildStartScreen(false);
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
                else if( i == TypeIdMenuEntryHighscore ){
                    loadHighscore();
                    runHighscore();
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

        loadStatistic();
        runStatatistic(stat);
    }

    void loadStatistic(){
        _itemManager->buildStatHighScreen();
    }

    void runStatatistic( Statistic& stat, bool add = true){
        EdumkIIButtons buttons;
        while(true){
            _gManager->printStatistic(stat);
            if(buttons.topButtonPushed() && _itemManager->processHit() == TypeIdMenuEntryOk){
                if(add){
                    _high->add(stat);
                }
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

    void loadHighscore(){
        _itemManager->buildStatHighScreen();
        uint8_t highAmount = 0;
        if( _high->stat_third != nullptr ){
            highAmount = 3;
        }
        else if( _high->stat_second != nullptr ){
            highAmount = 2;
        }
        else if( _high->stat_first != nullptr ){
            highAmount = 1;
        }
        _itemManager->buildHighscoreHitboxes(highAmount);
    }

    void runHighscore(){
        EdumkIIButtons buttons;
        while(true){
            _gManager->printHighscore(*_high);
            if(buttons.topButtonPushed() ){
                uint8_t type = _itemManager->processHit();
                if( type == TypeIdHitboxOne ){
                    loadStatistic();
                    runStatatistic(*(_high->stat_first), false);
                    loadHighscore();
                }
                if( type == TypeIdHitboxTwo ){
                    loadStatistic();
                    runStatatistic(*(_high->stat_second), false);
                    loadHighscore();
                }
                if( type == TypeIdHitboxThree ){
                    loadStatistic();
                    runStatatistic(*(_high->stat_third), false);
                    loadHighscore();
                }
                if( type == TypeIdMenuEntryOk ){
                    return;
                }
            }
        }
    }


};


#endif /* GAME_H_ */
