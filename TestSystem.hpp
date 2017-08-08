//
//  TestSystem.hpp
//  Sparrow
//
//  Created by 许兴伦 on 8/2/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef TestSystem_hpp
#define TestSystem_hpp

#include <stdio.h>
#include "EntityComponentSystem.hpp"

class TestSystem : public EntityComponentSystem<TestSystem>{
public:
    void Update(int entityId) override;
};

#endif /* TestSystem_hpp */
