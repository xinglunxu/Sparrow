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

int main(int argc, const char * argv[]) {
    typedef TypeList<PositionComponent, TestComponent> ComponentList;
    typedef TypeList<MovingSystem,TestSystem> SystemList;
    World<ComponentList, SystemList> world = World<ComponentList, SystemList>();
    int e1 =  world.CreateEntity<TypeList<PositionComponent>>();
    int e2 =  world.CreateEntity<TypeList<PositionComponent,TestComponent>>();
    
    BitSetGetter<2> bsg;
    
    bitset<2> bs = bsg.GetBitSet<TypeList<TestComponent>>();
    
    cout<<bs.to_string()<<endl;
    
//    cout<<ComponentCounter::counter<<endl;
    world.Run();
    
    return 0;
}
