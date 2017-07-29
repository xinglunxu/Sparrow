//
//  main.cpp
//  Sparrow
//
//  Created by 许兴伦 on 7/20/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#include <iostream>
#include "World.hpp"
#include "MovingSystem.hpp"

int main(int argc, const char * argv[]) {
    World world = World();
    world.AddSystem<MovingSystem>();
    world.Run();
    
    
    return 0;
}
