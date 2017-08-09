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
    World<ComponentTypeList, SystemTypeList> CreateWorld();
    
    Universe();
};

template<typename ComponentTypeList>
template<typename SystemTypeList>
World<ComponentTypeList, SystemTypeList> Universe<ComponentTypeList>::CreateWorld(){
    World<ComponentTypeList, SystemTypeList> W = World<ComponentTypeList, SystemTypeList>();
    ComponentInitiationVisitor::curWorldId = W.id;
    ComponentTypeList::template CumulateTypes<ComponentInitiationVisitor, int>();
    return W;
}

template<typename ComponentTypeList>
Universe<ComponentTypeList>::Universe(){}

#endif /* Universe_hpp */
