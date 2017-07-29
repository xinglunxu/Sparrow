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

using namespace std;


//declare
template <typename ComponentList, typename SystemList>
class World{
public:
    void Run();
    World();
    template <typename T>
    void AddSystem();
    
private:
    void Update();
    list<System*> systems;
    
    template <typename T>
    void AddComponent();
    
    template <typename T, typename ...TS>
    void _AddComponent(typename enable_if<sizeof...(TS)!=0, int>::type i=0);
    
    template <typename T>
    void _AddComponent();
    
    void AddSystem();
    
    template <typename T>
    struct TypeExpander{
        
    };
    
    template <typename ... TS>
    struct TypeExpander<TypeList<TS...>>{
    public:
        void AddComponent(World w);
        void AddSystem(World w);
    };
    
    struct IdAllocator{
    public:
        static int GetNewId(){
            nextId++;
            return nextId;
        }
    private:
        static int nextId;
    };
    
    //should not be changed after init, try to define with const specifier
    int id;
};



//-------------------------
// imp
//-------------------------

template <typename ComponentList, typename SystemList>
int World<ComponentList,SystemList>::IdAllocator::nextId = 0;

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
void World<ComponentList,SystemList>::TypeExpander<TypeList<TS...>>::AddComponent(World w){
    w._AddComponent<TS...>();
}

template <typename ComponentList, typename SystemList>
template <typename ... TS>
void World<ComponentList,SystemList>::TypeExpander<TypeList<TS...>>::AddSystem(World w){
    
}


template <typename ComponentList, typename SystemList>
template <typename T>
void World<ComponentList,SystemList>::AddSystem(){
    systems.insert(systems.end(), new T());
}

const int interval = 1000000;

template <typename ComponentList, typename SystemList>
World<ComponentList, SystemList>::World(){
    id = IdAllocator::GetNewId();
    systems = list<System*>();
    
    struct TypeExpander<ComponentList> ComponentExpander;
    ComponentExpander.AddComponent(*this);
    
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

template <typename ComponentList, typename SystemList>
template <typename T>
void World<ComponentList,SystemList>::AddComponent(){
    ComponentManager<T>::inst.AddWorld(id);
}

#endif /* World_hpp */
