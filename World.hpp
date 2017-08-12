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
#include "WorldSetting.hpp"
#include <bitset>

using namespace std;

class System;



///template programming code

template <typename ...SystemTypeList>
struct SystemListToComponentTypeListList{
    
};

template <typename T, typename ...TS>
struct SystemListToComponentTypeListList<T, TS...>{
    typedef typename Union<typename SystemListToComponentTypeListList<T>::valueTypeList, typename SystemListToComponentTypeListList<TS...>::valueTypeList>::valueTypeList valueTypeList;
};

template <typename T>
struct SystemListToComponentTypeListList<T>{
    typedef TypeList<typename T::componentTypeList> valueTypeList;
};






template <typename ...TS>
struct _ComponentListUnion{
    
};

template <typename T, typename U, typename ...TS>
struct _ComponentListUnion<T, U, TS...>{
    typedef typename _ComponentListUnion<typename Union<T, U>::valueTypeList, TS...>::valueTypeList valueTypeList;
};

template <typename T>
struct _ComponentListUnion<T>{
    typedef T valueTypeList;
};

template <typename typeList>
struct ComponentListUnion{
    
};

template <typename ...ComponentLists>
struct ComponentListUnion<TypeList<ComponentLists...>>{
    typedef typename _ComponentListUnion<ComponentLists...>::valueTypeList valueTypeList;
};

template <typename SystemTypeList>
struct GetComponentsFromSystemTypeList{
    
};

template <typename ...SystemTypes>
struct GetComponentsFromSystemTypeList<TypeList<SystemTypes...>>{
    typedef typename ComponentListUnion<typename SystemListToComponentTypeListList<SystemTypes...>::valueTypeList>::valueTypeList valueTypeList;
};

//end template programming code


//declare
template <typename worldSetting>
class World{
public:
    void Run();
    template<typename EntityComponentList>
    int CreateEntity();
    World();
    
private:
    typedef typename worldSetting::systemTypeList SystemTypeList;
    typedef typename worldSetting::entitySystemTypeList EntitySystemTypeList;
    typedef typename GetComponentsFromSystemTypeList<EntitySystemTypeList>::valueTypeList ComponentTypeList;
    typedef bitset<ComponentTypeList::Size()> Bitset;
    void Update();
    list<System*> systems;
    IdAllocator idAllocator;
    unordered_set<int> entityIds;
    
    unordered_map<int, Bitset> entitySignatures;
    
    template <typename T>
    void AddSystem();
    
    static IdAllocator gl_IdAllocator;
    
    //should not be changed after init, try to define with const specifier
    int id;
    
    template <typename _WorldSetting>
    friend class SystemInitVisitor;
};



//-------------------------
// imp
//-------------------------

template <typename SystemList>
IdAllocator World<SystemList>::gl_IdAllocator = IdAllocator();


//add system begin
template <typename WorldSetting>
class SystemInitVisitor{
public:
    static World<WorldSetting>* w;
    template<typename System>
    static int Visit(){
        System* system = new System();
        system->worldId = w->id;
        w->systems.insert(w->systems.end(), system);
        return 0;
    }
    static int Concatenate(int a, int b){
        return 0;
    }
};

template<typename WorldSetting>
World<WorldSetting>* SystemInitVisitor<WorldSetting>::w = NULL;
//add system end

const int interval = 1000000;

class ComponentVisitor2{
public:
    template<typename Component>
    static int Visit(){
        return 1;
    }
    static int Concatenate(int a, int b){
        return a+b;
    }
};

struct ComponentInitiationVisitor{
    static int counter;
    static int worldId;
    template<typename Component>
    static int Visit(){
        ComponentManager<Component>::inst.bitSetIndex[worldId] = counter;
        counter++;
        return 1;
    }
    static int Concatenate(int a, int b){
        return a+b;
    }
};



template < typename WorldSetting>
World<WorldSetting>::World(){
    idAllocator = IdAllocator();
    id = gl_IdAllocator.GetId();
    systems = list<System*>();
    entityIds = unordered_set<int>();
//    entitySignatures = entitySignatures();
    
    SystemInitVisitor<WorldSetting>::w = this;
    SystemTypeList::template CumulateTypes<SystemInitVisitor<WorldSetting>,int>();
    EntitySystemTypeList::template CumulateTypes<SystemInitVisitor<WorldSetting>,int>();
    
    ComponentInitiationVisitor::counter = 0;
    ComponentInitiationVisitor::worldId = id;
    
    ComponentTypeList::template CumulateTypes<ComponentInitiationVisitor, int>();
    

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



//Entity Related functions end

#endif /* World_hpp */
