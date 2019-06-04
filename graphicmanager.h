/*
 * graphicmanager.h
 *
 *  Created on: 04.06.2019
 *      Author: student
 */

#ifndef GRAPHICMANAGER_H_
#define GRAPHICMANAGER_H_

#include "graphic/map.h"

//#include "periphery/display.h"

class GraphicManager{

private:

    static GraphicManager* instance;

public:

    static GraphicManager& getInstance(){
        if( GraphicManager::instance == nullptr ){
            GraphicManager::instance = new GraphicManager();
        }
        return *instance;
    }


    Map* map;
//    Display* display;


    GraphicManager(){

    }

public:



    ~GraphicManager(){

    }
};




#endif /* GRAPHICMANAGER_H_ */
