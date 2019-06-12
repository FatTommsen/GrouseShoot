/*****************************************************************************
*
* MSP432 empty main.c template
*
******************************************************************************/

#include "settings.h"
#include "msp.h"
#include "game.h"

#include "util/timer.h"
#include "util/uartlogger.h"

int main(void)
{
    Game game;
    game.loadMenu();
    game.runMenu();


    return 0;

}


/*
#include "graphic/mapitemmanager.h"
#include "graphicmanager.h"
#include "periphery/edumkbuttons.h"
#include "util/timer.h"


MapItemManager itemManager;
GraphicManager gManager( itemManager );
Settings settings;


void loadGame();
void runGame();
void loadSettings();
void runSettings();


    int main(){
        itemManager.buildStartScreen(true);
        EdumkIIButtons buttons;
        while(true){
            gManager.updateMenuScreen();
            if( buttons.topButtonPushed() ){
                int i = itemManager.processHit();
                if(i == TypeIdMenuEntryStart){
                    loadGame();
                    runGame();
                    itemManager.buildStartScreen(true);
                }
                else if( i == TypeIdMenuEntrySettings ){
                    loadSettings();
                    runSettings();
                    itemManager.buildStartScreen(true);
                }
            }

        }
        return 0;
    }

    void loadGame(){
        gManager.resetMap();
        itemManager.buildGameScreen();
        itemManager.reloadMagazine();
    }

    void runGame(){
        bool inGame = true;
        EdumkIIButtons buttons;
        Timer timer;
        timer.startGame(GAME_DURATION_S, &inGame );

        while(inGame){
            gManager.updateScreen();
            if( buttons.topButtonPushed() ){
                itemManager.deleteOneCartridge();
                if(itemManager.getCartridgeCount() > 0){
                    itemManager.processHit();
                }
            }
            else if( buttons.lowButtonPushed() ){
                itemManager.reloadMagazine();
            }
        }
    }

    void loadSettings(){
        itemManager.buildSettingsScreen( settings );
    }

    void runSettings(){
        EdumkIIButtons buttons;
        while(true){
            gManager.updateMenuScreen();
            if( buttons.topButtonPushed() ){
                int i = itemManager.processHit();
                if( i == TypeIdMenuEntryOk ){
                    return;
                }
                else if( i == TypeIdMenuEntryCheckbox ){
                    itemManager.toggleAllCheckboxes();
                    settings.reload = !settings.reload;
                }
                else if( i == TypeIdSymbolSwitch ){
                    settings.mapViaGSensor = !settings.mapViaGSensor;
                    itemManager.toggleSettingSymbols();
                    gManager.toggleMapNavigation();
                    itemManager.toggleTopLevelNavigation();
                }
            }
        }
    }
*/
