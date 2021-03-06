//
//  ComponentManager.hpp
//  Sparrow
//
//  Created by 许兴伦 on 7/29/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef ComponentManager_hpp
#define ComponentManager_hpp

#include <stdio.h>
#include <unordered_map>
#include "ComponentCounter.hpp"

using namespace std;

template <typename SystemList>
class World;

template <typename DataType>
class ComponentManager{
private:
    unordered_map<int, unordered_map<int, DataType*>*> datas;
    void AddWorld(int worldId);
    ComponentManager();
    unordered_map<int,int> bitSetIndex;
    
    bool Contain(int worldId, int i);
    void AddComponent(int worldId, int i);
    
    DataType* GetComponent(int worldId, int entityId);
    
    template <typename SystemList>
    friend class World;
    
    friend class ComponentInitiationVisitor;
    
    template<typename BitsetType>
    friend struct GetBisetVisitor;
    
    friend struct Debugger;
    friend struct EntityComponentInitiationVisitor;
    
    template<typename ... ComponentTypes>
    friend class EntityComponentSystem;
public:
    static ComponentManager inst;
//    int bitSetIndex;
};

template <typename T>
bool ComponentManager<T>::Contain(int worldId, int i){
    unordered_map<int, T*>* worldDatas = datas[worldId];
    return worldDatas->find(i) != worldDatas->end();
}

template <typename T>
void ComponentManager<T>::AddComponent(int worldId,int i){
    unordered_map<int, T*>* worldDatas = datas[worldId];
    if(!Contain(worldId, i)){
        (*worldDatas)[i] = new T();
    }
    else{
        std::cout<<"Added two same components for the same entity"<<std::endl;
    }
}


template <typename T>
ComponentManager<T> ComponentManager<T>::inst = ComponentManager<T>();

template <typename T>
ComponentManager<T>::ComponentManager(){
//    bitSetIndex = ComponentCounter::counter;
//    cout<<ComponentCounter::counter<<endl;
    ComponentCounter::counter++;
    datas = unordered_map<int, unordered_map<int, T*>*>();
    bitSetIndex = unordered_map<int, int>();
}

template <typename T>
void ComponentManager<T>::AddWorld(int worldId){
    datas[worldId] = new unordered_map<int, T*>();
}

template <typename T>
T* ComponentManager<T>::GetComponent(int worldId, int entityId){
    return (*(datas[worldId]))[entityId];
}


#endif /* ComponentManager_hpp */
