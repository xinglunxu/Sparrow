//
//  MovingSystem.hpp
//  Sparrow
//
//  Created by 许兴伦 on 7/20/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef MovingSystem_hpp
#define MovingSystem_hpp

#include <stdio.h>
#include "EntityComponentSystem.hpp"
#include <iostream>
#include "PositionComponent.hpp"

class MovingSystem: public EntityComponentSystem<PositionComponent>{
public:
    void Update() override;
    MovingSystem(int worldId, unordered_set<int>* entities):EntityComponentSystem<PositionComponent>(worldId, entities){
        
    }
};

#endif /* MovingSystem_hpp */
