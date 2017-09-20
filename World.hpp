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

template<typename BitsetType>
struct GetBisetVisitor{
    int worldId;
    template<typename Component>
    BitsetType Visit(){
        BitsetType bs;
        bs.set(ComponentManager<Component>::inst.bitSetIndex[worldId]);
        return bs;
    }
    BitsetType Concatenate(BitsetType a, BitsetType b){
        return a | b;
    }
    GetBisetVisitor(int worldId){
        this->worldId = worldId;
    }
private:
    GetBisetVisitor();
};

//end template programming code


//declare
template <typename worldSetting>
class World{
private:
    typedef typename worldSetting::systemTypeList SystemTypeList;
    typedef typename worldSetting::entitySystemTypeList EntitySystemTypeList;
    typedef typename GetComponentsFromSystemTypeList<EntitySystemTypeList>::valueTypeList ComponentTypeList;
    typedef bitset<ComponentTypeList::Size()> Bitset;
    void Update();
    list<System*> systems;
    IdAllocator idAllocator;
    unordered_set<int> entityIds;
    
    unordered_map<Bitset, unordered_set<int>*> entitiesForSystems;
    
    static IdAllocator gl_IdAllocator;
    
    //should not be changed after init, try to define with const specifier
    int id;
    
    template <typename _WorldSetting>
    friend class SystemInitVisitor;
    friend struct Debugger;
    
    template <typename _worldSetting, typename _Bitset>
    friend class EntityComponentSystemInitVisitor;
public:
    void Run();
    template<typename ...Components>
    int CreateEntity(typename std::enable_if<TypeContainType<ComponentTypeList, TypeList<Components...>>::value, int>::type i=0);
    
    template <typename T>
    T* GetComponentFromEntity(int i);
    
    World();
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
    World<WorldSetting>* w;
    template<typename System>
    int Visit(){
        System* system = new System(w->id);
        system->worldId = w->id;
        w->systems.insert(w->systems.end(), system);
        return 0;
    }
    int Concatenate(int a, int b){
        return 0;
    }
    SystemInitVisitor(World<WorldSetting>* w){
        this->w = w;
    }
private:
    SystemInitVisitor();
};

template <typename WorldSetting, typename Bitset>
class EntityComponentSystemInitVisitor{
public:
    World<WorldSetting>* w;
    template<typename SystemType>
    int Visit(){
        GetBisetVisitor<Bitset> visitor(w->id);
        Bitset bs = SystemType::componentTypeList::template Visit<GetBisetVisitor<Bitset>, Bitset>(visitor);
        if(w->entitiesForSystems.find(bs) == w->entitiesForSystems.end()){
            w->entitiesForSystems[bs] = new unordered_set<int>();
        }
        SystemType* system = new SystemType(w->id, w->entitiesForSystems[bs]);
//        list<System*>* ecSystems =w->entityComponentSystems[bs];
//        if(ecSystems==NULL){
//            w->entityComponentSystems[bs] = new list<System*>();
//            ecSystems =w->entityComponentSystems[bs];
//        }
//        ecSystems->push_front(system);
        w->systems.push_front(system);
        return 0;
    }
    int Concatenate(int a, int b){
        return 0;
    }
    EntityComponentSystemInitVisitor(World<WorldSetting>* w){
        this->w = w;
    }
private:
    EntityComponentSystemInitVisitor();
};

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
    int counter;
    int worldId;
    template<typename Component>
    int Visit(){
        ComponentManager<Component>::inst.bitSetIndex[worldId] = counter;
        ComponentManager<Component>::inst.AddWorld(worldId);
        counter++;
        return 1;
    }
    static int Concatenate(int a, int b){
        return a+b;
    }
    ComponentInitiationVisitor(int worldId){
        counter = 0;
        this->worldId = worldId;
    }
private:
    ComponentInitiationVisitor();
};



template < typename WorldSetting>
World<WorldSetting>::World(){
    idAllocator = IdAllocator();
    id = gl_IdAllocator.GetId();
    systems = list<System*>();
    entityIds = unordered_set<int>();
    
    SystemInitVisitor<WorldSetting> siv(this);
    SystemTypeList::template Visit<SystemInitVisitor<WorldSetting>,int>(siv);
    
    EntityComponentSystemInitVisitor<WorldSetting, Bitset> ecsiv(this);
    EntitySystemTypeList::template Visit<EntityComponentSystemInitVisitor<WorldSetting, Bitset>,int>(ecsiv);
    
    ComponentInitiationVisitor civ(id);
    
    ComponentTypeList::template Visit<ComponentInitiationVisitor, int>(civ);
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
    for(auto it = systems.begin(); it!=systems.end(); it++){
        (*it)->Update();
    }
    
//    for(auto it = entityComponentSystems.begin(); it!=entityComponentSystems.end(); it++){
//        list<System*>* _list = it->second;
//        
//        for(auto _it = _list->begin(); _it!=_list->end(); _it++){
//            System* s = *_it;
//            s->Update();
//        }
//    }
}


//Entity Related Functions

struct EntityComponentInitiationVisitor{
    int worldId;
    int entityId;
    template<typename Component>
    int Visit(){
        ComponentManager<Component>::inst.AddComponent(worldId, entityId);
        return 0;
    }
    int Concatenate(int a, int b){
        return 0;
    }
    EntityComponentInitiationVisitor(int worldId, int entityId){
        this->worldId = worldId;
        this->entityId = entityId;
    }
private:
    EntityComponentInitiationVisitor();
};


template <typename worldSetting>
template<typename ...Components>
int World<worldSetting>::CreateEntity(typename std::enable_if<TypeContainType<ComponentTypeList, TypeList<Components...>>::value, int>::type i){
    int entityId = idAllocator.GetId();
    GetBisetVisitor<Bitset> ei(id);

    Bitset bs = TypeList<Components...>::template Visit<GetBisetVisitor<Bitset>, Bitset>(ei);
    entityIds.insert(entityId);
    
    EntityComponentInitiationVisitor eciv(id, entityId);
    
    TypeList<Components...>::template Visit<EntityComponentInitiationVisitor, int>(eciv);
    
//    for(auto it = entityComponentSystems.begin(); it!=entityComponentSystems.end(); it++){
//        Bitset systemBs = it->first;
//        if(systemBs || bs == bs){
//            list<System*>* systemList = it->second;
//            
//            for(auto it2 = systemList->begin(); it2!=systemList->end(); it2++){
//                
//            }
//        }
//    }
    
    for(auto it = entitiesForSystems.begin(); it!=entitiesForSystems.end(); it++){
        Bitset systemBs = it->first;
        if((systemBs | bs) == bs){
            unordered_set<int>* entitySet = it->second;
            entitySet->insert(entityId);
        }
    }
    
    return entityId;
}

template <typename worldSetting>
template <typename T>
T* World<worldSetting>::GetComponentFromEntity(int i){
    return ComponentManager<T>::inst.GetComponent(id,i);
}

//Entity Related functions end

#endif /* World_hpp */
