//
//  World.hpp
//  Sparrow
//
//  Created by 许兴伦 on 7/20/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include "System.hpp"
#include <unistd.h>
#include "TypeList.hpp"
#include <typeinfo>
#include "ComponentManager.hpp"
#include "IdAllocator.hpp"

using namespace std;

class System;

//declare
template <typename ComponentList, typename SystemList>
class World{
public:
    void Run();
    World();
    template<typename EntityComponentList>
    int CreateEntity();
    
private:
    void Update();
    list<System*> systems;
    IdAllocator idAllocator;
    
    template <typename T>
    void AddComponent();
    template <typename T, typename ...TS>
    void _AddComponent(typename enable_if<sizeof...(TS)!=0, int>::type i=0);
    template <typename T>
    void _AddComponent();
    
    template <typename T>
    void AddSystem();
    template <typename T, typename ...TS>
    void _AddSystem(typename enable_if<sizeof...(TS)!=0, int>::type i=0);
    template <typename T>
    void _AddSystem();
    
    
    template <typename T, typename ... TSS>
    void _ParseEntityComponent(int EntityId,typename enable_if<sizeof...(TSS)!=0, int>::type i=0);
    template <typename T>
    void _ParseEntityComponent(int EntityId);
    template <typename T>
    void __ParseEntityComponent(int EntityId);
    
    
    template <typename T>
    struct TypeExpander{
        
    };
    
    template <typename ... TS>
    struct TypeExpander<TypeList<TS...>>{
    public:
        void AddComponent(World &w);
        void AddSystem(World &w);
        
        void ParseEntityComponent(int EntityId,World &w);
        };
    
    static IdAllocator gl_IdAllocator;
    
    //should not be changed after init, try to define with const specifier
    int id;
};



//-------------------------
// imp
//-------------------------

template <typename ComponentList, typename SystemList>
IdAllocator World<ComponentList,SystemList>::gl_IdAllocator = IdAllocator();


// add components begin
template <typename ComponentList, typename SystemList>
template <typename T, typename ...TS>
void World<ComponentList,SystemList>::_AddComponent(typename enable_if<sizeof...(TS)!=0, int>::type i){
    AddComponent<T>();
    _AddComponent<TS...>();
}

template <typename ComponentList, typename SystemList>
template <typename T>
void World<ComponentList,SystemList>::_AddComponent(){
    AddComponent<T>();
}


template <typename ComponentList, typename SystemList>
template <typename ... TS>
void World<ComponentList,SystemList>::TypeExpander<TypeList<TS...>>::AddComponent(World &w){
    w._AddComponent<TS...>();
}

template <typename ComponentList, typename SystemList>
template <typename T>
void World<ComponentList,SystemList>::AddComponent(){
    ComponentManager<T>::inst.AddWorld(id);
}
//add component end


//add system begin
template <typename ComponentList, typename SystemList>
template <typename ... TS>
void World<ComponentList,SystemList>::TypeExpander<TypeList<TS...>>::AddSystem(World &w){
    w._AddSystem<TS...>();
}

template <typename ComponentList, typename SystemList>
template <typename T, typename ...TS>
void World<ComponentList,SystemList>::_AddSystem(typename enable_if<sizeof...(TS)!=0, int>::type i){
    AddSystem<T>();
    _AddSystem<TS...>();
}

template <typename ComponentList, typename SystemList>
template <typename T>
void World<ComponentList,SystemList>::_AddSystem(){
    AddSystem<T>();
}


template <typename ComponentList, typename SystemList>
template <typename T>
void World<ComponentList,SystemList>::AddSystem(){
    T* t = new T();
    t->worldId = id;
    systems.insert(systems.end(), t);
}
//add system end

const int interval = 1000000;

template <typename ComponentList, typename SystemList>
World<ComponentList, SystemList>::World(){
    idAllocator = IdAllocator();
    id = gl_IdAllocator.GetId();
    systems = list<System*>();
    
    struct TypeExpander<ComponentList> ComponentExpander;
    ComponentExpander.AddComponent(*this);
    
    struct TypeExpander<SystemList> SystemExpander;
    SystemExpander.AddSystem(*this);
    
}

template <typename ComponentList, typename SystemList>
void World<ComponentList, SystemList>::Run(){
    while(true){
        Update();
        usleep(interval);
    }
}

template <typename ComponentList, typename SystemList>
void World<ComponentList, SystemList>::Update(){
    for(auto it = systems.begin(); it!=systems.end();it++){
        (*it)->Update();
    }
}


//Entity Related Functions
template <typename ComponentList, typename SystemList>
template <typename EntityComponentList>
int World<ComponentList,SystemList>::CreateEntity(){
    int newId = idAllocator.GetId();
    TypeExpander<EntityComponentList> EntityComponentExpander;
    EntityComponentExpander.ParseEntityComponent(newId,*this);
}

template <typename ComponentList, typename SystemList>
template <typename ... TS>
void World<ComponentList,SystemList>::TypeExpander<TypeList<TS...>>::ParseEntityComponent(int EntityId, World &w){
    w._ParseEntityComponent<TS...>(EntityId);
}

template <typename ComponentList, typename SystemList>
template <typename T, typename ...TS>
void World<ComponentList,SystemList>::_ParseEntityComponent(int EntityId,typename enable_if<sizeof...(TS)!=0, int>::type i){
    __ParseEntityComponent(EntityId);
    _ParseEntityComponent<TS...>(EntityId);
}

template <typename ComponentList, typename SystemList>
template <typename T>
void World<ComponentList,SystemList>::_ParseEntityComponent(int EntityId){
    __ParseEntityComponent(EntityId);
}

template <typename ComponentList, typename SystemList>
template <typename T>
void World<ComponentList,SystemList>::__ParseEntityComponent(int EntityId){
    ComponentManager<T>::inst.AddComponent(EntityId);
}


#endif /* World_hpp */
