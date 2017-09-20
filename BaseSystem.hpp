//
//  BaseSystem.hpp
//  Sparrow
//
//  Created by 许兴伦 on 8/19/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef BaseSystem_hpp
#define BaseSystem_hpp

#include <stdio.h>
#include "System.hpp"

class BaseSystem : public System{
public:
    void Update() override;
    BaseSystem(int worldId):System(worldId){
        
    }
};

#endif /* BaseSystem_hpp */
