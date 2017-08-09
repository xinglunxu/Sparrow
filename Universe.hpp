//
//  Universe.hpp
//  Sparrow
//
//  Created by 许兴伦 on 8/9/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef Universe_hpp
#define Universe_hpp

#include <stdio.h>
#include "World.hpp"

class ComponentInitiationVisitor{
public:
    static int curWorldId;
    template<typename Component>
    static int Visit(){
        ComponentManager<Component>::inst.AddWorld(curWorldId);
        return 0;
    }
    static int Concatenate(int a, int b){
        return 0;
    }
};

template <typename ComponentTypeList>
class Universe{
public:
    template<typename SystemTypeList>
    World<SystemTypeList> CreateWorld();
    
    Universe();
};

template<typename ComponentTypeList>
template<typename SystemTypeList>
World< SystemTypeList> Universe<ComponentTypeList>::CreateWorld(){
    World<SystemTypeList> W = World<SystemTypeList>();
    ComponentInitiationVisitor::curWorldId = W.id;
    ComponentTypeList::template CumulateTypes<ComponentInitiationVisitor, int>();
    return W;
}

template<typename ComponentTypeList>
Universe<ComponentTypeList>::Universe(){}

#endif /* Universe_hpp */
