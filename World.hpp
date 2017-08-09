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
#include <unordered_set>
#include "BitSetGetter.hpp"
#include "ComponentCounter.hpp"

using namespace std;

class System;

//declare
template <typename SystemList>
class World{
public:
    void Run();
    template<typename EntityComponentList>
    int CreateEntity();
    
private:
    World();
    void Update();
    list<System*> systems;
    IdAllocator idAllocator;
    unordered_set<int> entityIds;
    
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
        void AddSystem(World &w);
        void ParseEntityComponent(int EntityId,World &w);
    };
    
    static IdAllocator gl_IdAllocator;
    
    //should not be changed after init, try to define with const specifier
    int id;
    
    template<typename ComponentTypeList>
    friend class Universe;
};



//-------------------------
// imp
//-------------------------

template <typename SystemList>
IdAllocator World<SystemList>::gl_IdAllocator = IdAllocator();


//add system begin
template <typename SystemList>
template <typename ... TS>
void World<SystemList>::TypeExpander<TypeList<TS...>>::AddSystem(World &w){
    w._AddSystem<TS...>();
}

template <typename SystemList>
template <typename T, typename ...TS>
void World<SystemList>::_AddSystem(typename enable_if<sizeof...(TS)!=0, int>::type i){
    AddSystem<T>();
    _AddSystem<TS...>();
}

template <typename SystemList>
template <typename T>
void World<SystemList>::_AddSystem(){
    AddSystem<T>();
}


template <typename SystemList>
template <typename T>
void World<SystemList>::AddSystem(){
    T* t = new T();
    t->worldId = id;
    systems.insert(systems.end(), t);
}
//add system end

const int interval = 1000000;

template < typename SystemList>
World<SystemList>::World(){
    idAllocator = IdAllocator();
    id = gl_IdAllocator.GetId();
    systems = list<System*>();
    entityIds = unordered_set<int>();
    
//    struct TypeExpander<ComponentList> ComponentExpander;
//    ComponentExpander.AddComponent(*this);
    
    struct TypeExpander<SystemList> SystemExpander;
    SystemExpander.AddSystem(*this);
    
}

template <typename SystemList>
void World<SystemList>::Run(){
    while(true){
        Update();
        usleep(interval);
    }
}

template <typename SystemList>
void World<SystemList>::Update(){
//    for(auto it = systems.begin(); it!=systems.end();it++){
//        (*it)->Update();
//    }
}


//Entity Related Functions
template <typename SystemList>
template <typename EntityComponentList>
int World<SystemList>::CreateEntity(){
    int newId = idAllocator.GetId();
    TypeExpander<EntityComponentList> EntityComponentExpander;
    EntityComponentExpander.ParseEntityComponent(newId,*this);
    return newId;
}

template <typename SystemList>
template <typename ... TS>
void World<SystemList>::TypeExpander<TypeList<TS...>>::ParseEntityComponent(int EntityId, World &w){
    w._ParseEntityComponent<TS...>(EntityId);
}

template <typename SystemList>
template <typename T, typename ...TS>
void World<SystemList>::_ParseEntityComponent(int EntityId,typename enable_if<sizeof...(TS)!=0, int>::type i){
    __ParseEntityComponent<T>(EntityId);
    _ParseEntityComponent<TS...>(EntityId);
}

template <typename SystemList>
template <typename T>
void World<SystemList>::_ParseEntityComponent(int EntityId){
    __ParseEntityComponent<T>(EntityId);
}

template < typename SystemList>
template <typename T>
void World<SystemList>::__ParseEntityComponent(int EntityId){
    ComponentManager<T>::inst.AddComponent(id, EntityId);
}


#endif /* World_hpp */
