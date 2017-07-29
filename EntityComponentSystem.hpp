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
#include "System.hpp"

template<typename ... ComponentTypes>
class EntityComponentSystem :public System{
public:
    virtual void Update()=0;
};

#endif /* EntityComponentSystem_hpp */
