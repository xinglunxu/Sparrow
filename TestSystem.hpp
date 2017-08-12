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
#include "TestComponent.hpp"
#include "PositionComponent.hpp"

class TestSystem : public EntityComponentSystem<TestComponent, PositionComponent>{
public:
    void Update(int entityId) override;
};

#endif /* TestSystem_hpp */
