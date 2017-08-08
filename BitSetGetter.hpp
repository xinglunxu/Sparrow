//
//  BitSetGetter.hpp
//  Sparrow
//
//  Created by 许兴伦 on 8/8/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef BitSetGetter_hpp
#define BitSetGetter_hpp

#include <stdio.h>
#include <bitset>
#include "ComponentManager.hpp"

using namespace std;

template<int ComponentNum>
class BitSetGetter{
public:
    template <typename ComponentTypeList>
    bitset<ComponentNum> GetBitSet();
private:
    template <typename T>
    struct TypeExpander{
        
    };
    
    template <typename ... TS>
    struct TypeExpander<TypeList<TS...>>{
    public:
        void SetBitSet(bitset<ComponentNum>& bitSet);
        
        template<typename Component ,typename ... Components>
        void _SetBitSet(bitset<ComponentNum>& bitSet, typename enable_if<sizeof...(Components)!=0, int>::type i=0);
        
        template<typename Component>
        void _SetBitSet(bitset<ComponentNum>& bitSet);
    };
};

template <int ComponentNum>
template <typename ComponentTypeList>
bitset<ComponentNum> BitSetGetter<ComponentNum>::GetBitSet(){
    bitset<ComponentNum> bitSet;
    TypeExpander<ComponentTypeList> expander;
    expander.SetBitSet(bitSet);
    
    return bitSet;
}


template <int ComponentNum>
template <typename ... TS>
void BitSetGetter<ComponentNum>::TypeExpander<TypeList<TS...>>::SetBitSet(bitset<ComponentNum> &bitSet){
    _SetBitSet<TS...>(bitSet);
}

template <int ComponentNum>
template <typename ... TS>
template <typename Component>
void BitSetGetter<ComponentNum>::TypeExpander<TypeList<TS...>>::_SetBitSet(bitset<ComponentNum> &bitSet){
//    cout<<ComponentManager<Component>::inst.bitSetIndex+1<<endl;
    bitSet.set(ComponentManager<Component>::inst.bitSetIndex);
//    bitSet.set(Component::bitIndex+1);
}

template <int ComponentNum>
template <typename ... TS>
template <typename Component, typename ... Components>
void BitSetGetter<ComponentNum>::TypeExpander<TypeList<TS...>>::_SetBitSet(bitset<ComponentNum> &bitSet, typename enable_if<sizeof...(Components)!=0, int>::type i){
//    cout<<ComponentManager<Component>::inst.bitSetIndex+1<<endl;
    bitSet.set(ComponentManager<Component>::inst.bitSetIndex);
//    bitSet.set(Component::bitIndex+1);
    _SetBitSet<Components...>(bitSet);
}


#endif /* BitSetGetter_hpp */
