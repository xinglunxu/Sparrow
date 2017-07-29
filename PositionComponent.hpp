//
//  PositionComponent.hpp
//  Sparrow
//
//  Created by 许兴伦 on 7/29/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef PositionComponent_hpp
#define PositionComponent_hpp

#include <stdio.h>
#include "Component.hpp"

struct PositionComponent:public Component{
    int x;
    int y;
    int z;
};

#endif /* PositionComponent_hpp */
