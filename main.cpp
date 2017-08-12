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

using namespace std;

class ComponentVisitor{
public:
    template<typename Component>
    static int Visit(){
        return 1;
    }
    static int Concatenate(int a, int b){
        return a+b;
    }
};



int main(int argc, const char * argv[]) {
    typedef TypeList<PositionComponent, TestComponent> ComponentList;
    typedef TypeList<> SystemList;
    typedef TypeList<TestSystem,MovingSystem> EntityComponentSystemList;
    typedef WorldSetting<SystemList, EntityComponentSystemList> worldSetting;
//    Universe<ComponentList> U = Universe<ComponentList>();
//    auto world = U.CreateWorld<SystemList>();
//    int e1 =  world.CreateEntity<TypeList<PositionComponent>>();
//    int e2 =  world.CreateEntity<TypeList<PositionComponent,TestComponent>>();
    
    World<worldSetting> world;
    
    cout<<"S"<<endl;
    
//    typedef TypeList<int,float,TestComponent> list1;
//    typedef TypeList<double, unsigned int,TestComponent> list2;
//    typedef TypeList<string, long> list3;
//    
////
//    typedef Union<list1, list2>::valueTypeList U_Type;
//    typedef Union<U_Type, list3>::valueTypeList U_Type2;
    typedef typename TestSystem::componentTypeList ctl;
    typedef typename MovingSystem::componentTypeList ctl2;
//    cout<<ctl::template CumulateTypes<ComponentVisitor,int>()<<endl;
//    cout<<ctl2::template CumulateTypes<ComponentVisitor,int>()<<endl;
    world.Run();
    return 0;
}
