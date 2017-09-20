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

using namespace std;

class TestSystem : public EntityComponentSystem<TestComponent, PositionComponent>{
public:
    void Update() override;
    TestSystem(int worldId, unordered_set<int>* es):EntityComponentSystem<TestComponent, PositionComponent>(worldId,es){
        
    }
};

#endif /* TestSystem_hpp */
