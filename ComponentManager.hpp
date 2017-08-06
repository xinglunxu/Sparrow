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

using namespace std;

template <typename ComponentList, typename SystemList>
class World;

template <typename DataType>
class ComponentManager{
private:
    unordered_map<int, unordered_map<int, DataType>*> datas;
    void AddWorld(int worldId);
    ComponentManager();
    
    
    bool Contain(int i);
    void AddComponent(int i);
    
    template <typename ComponentList, typename SystemList>
    friend class World;
public:
    static ComponentManager inst;
};



template <typename T>
bool ComponentManager<T>::Contain(int i){
    return datas.find(i) != datas.end();
}

template <typename T>
void ComponentManager<T>::AddComponent(int i){
    if(!Contain(i)){
        datas[i] = new T();
    }
    else{
        std::cout<<"Added two same components for the same entity"<<std::endl;
    }
}


template <typename T>
ComponentManager<T> ComponentManager<T>::inst = ComponentManager<T>();

template <typename T>
ComponentManager<T>::ComponentManager(){
    datas = unordered_map<int, unordered_map<int, T>*>();
}

template <typename T>
void ComponentManager<T>::AddWorld(int worldId){
    datas[worldId] = new unordered_map<int, T>();
}


#endif /* ComponentManager_hpp */
