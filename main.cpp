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
//#include "Universe.hpp"
#include <unordered_set>
#include <typeinfo>
#include <typeindex>
#include "WorldSetting.hpp"
#include "BaseSystem.hpp"

using namespace std;

class _ComponentVisitor{
public:
    template<typename Component>
    static int Visit(){
        return 1;
    }
    static int Concatenate(int a, int b){
        return a+b;
    }
};

struct ComponentVisitor{
public:
    template<typename Component>
    int Visit(){
        return 1;
    }
    int Concatenate(int a, int b){
        return a+b;
    }
};

struct Debugger{
    template<typename worldSetting>
    static void DebugWorld(World<worldSetting> &w){
        int entity = w.template CreateEntity<TestComponent,PositionComponent>();
        auto bs = w.entitySignatures[entity];
        PositionComponent* p = (*(ComponentManager<PositionComponent>::inst.datas[w.id]))[entity];
        p->x=10;
        
    };
};


int main(int argc, const char * argv[]) {
    typedef TypeList<PositionComponent, TestComponent> ComponentList;
    typedef TypeList<BaseSystem> SystemList;
    typedef TypeList<TestSystem,MovingSystem> EntityComponentSystemList;
    typedef WorldSetting<SystemList, EntityComponentSystemList> worldSetting;

    World<worldSetting> world;
    
    ComponentVisitor cv;
    Debugger::DebugWorld<worldSetting>(world);
    world.Run();
    return 0;
}
