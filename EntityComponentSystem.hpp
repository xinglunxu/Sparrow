//
//  EntityComponentSystem.hpp
//  Sparrow
//
//  Created by 许兴伦 on 7/20/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef EntityComponentSystem_hpp
#define EntityComponentSystem_hpp

#include <stdio.h>
#include <unordered_set>
#include "TypeList.hpp"
#include "System.hpp"
#include "ComponentManager.hpp"

using namespace std;

template<typename ... ComponentTypes>
class EntityComponentSystem :public System{
private:
    EntityComponentSystem();
public:
    typedef TypeList<ComponentTypes...> componentTypeList;
    virtual void Update()=0;
    EntityComponentSystem(int worldId, unordered_set<int>* entities): System(worldId){
        this->entities = entities;
    }
private:
    unordered_set<int>* entities;
protected:
    typedef unordered_set<int>::iterator EntityIterator;
    EntityIterator GetIterator(){
        return entities->begin();
    }
    EntityIterator EndOfIterator(){
        return entities->end();
    }
    
    template<typename ToGetComponent>
    ToGetComponent* GetComponent(int entity){
        return ComponentManager<ToGetComponent>::inst.GetComponent(worldId,entity);
    }
};

#endif /* EntityComponentSystem_hpp */
