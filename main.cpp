//
//  main.cpp
//  Sparrow
//
//  Created by 许兴伦 on 7/20/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "World.hpp"
#include "MovingSystem.hpp"
#include "TypeList.hpp"
#include "PositionComponent.hpp"

int main(int argc, const char * argv[]) {
    typedef TypeList<PositionComponent> ComponentList;
    typedef TypeList<int, float> SystemList;
    World<ComponentList, SystemList> world = World<ComponentList, SystemList>();
    world.AddSystem<MovingSystem>();
    world.Run();
    
    
    return 0;
}
