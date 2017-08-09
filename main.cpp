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
#include "TestSystem.hpp"
#include "TestComponent.hpp"
//#include "BitSetGetter.hpp"
#include "Universe.hpp"

int main(int argc, const char * argv[]) {
    typedef TypeList<PositionComponent, TestComponent> ComponentList;
    typedef TypeList<MovingSystem,TestSystem> SystemList;
    Universe<ComponentList> U = Universe<ComponentList>();
    World<SystemList> world = U.CreateWorld<SystemList>();
    int e1 =  world.CreateEntity<TypeList<PositionComponent>>();
    int e2 =  world.CreateEntity<TypeList<PositionComponent,TestComponent>>();
    
    cout<<"S"<<endl;
    
    world.Run();
    
    
    return 0;
}
