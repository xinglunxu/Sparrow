//
//  Component.hpp
//  Sparrow
//
//  Created by 许兴伦 on 7/22/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>

struct ComponentCounter{
    static int counter;
};

int ComponentCounter::counter = 0;

struct Component{
private:
    static int bitIndex;
};

int Component::bitIndex = ComponentCounter::counter++;

#endif /* Component_hpp */
