//
//  World.cpp
//  Sparrow
//
//  Created by 许兴伦 on 7/20/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#include "World.hpp"
#include <unistd.h>

const int interval = 1000000;

World::World(){
    systems = list<System*>();
}

void World::Run(){
    while(true){
        Update();
        usleep(interval);
    }
}

void World::Update(){
    for(auto it = systems.begin(); it!=systems.end();it++){
        (*it)->Update();
    }
}
