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

class MovingSystem: public EntityComponentSystem<int>{
public:
    void Update(int entityId) override;
};

#endif /* MovingSystem_hpp */
