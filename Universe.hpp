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

template <typename ComponentTypeList>
class Universe{
public:
    template<typename SystemTypeList>
    World<ComponentTypeList, SystemTypeList> CreateWorld();
};

template<typename ComponentTypeList>
template<typename SystemTypeList>
World<ComponentTypeList, SystemTypeList> Universe<ComponentTypeList>::CreateWorld(){
    return World<ComponentTypeList, SystemTypeList>();
}

#endif /* Universe_hpp */
